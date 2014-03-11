#include "PDAnalysis/Ntu/interface/PDGenHandler.h"

#include <iostream>
#include <sstream>
#include <stdio.h>


const std::vector<int>* PDGenHandler::ids = 0;
const std::vector<int>* PDGenHandler::mothers = 0;
std::map< int,std::vector<int> > PDGenHandler::daughters;

std::vector<int>* PDGenHandler::TypeSelect::genId;

/*
const PDGenHandler::TypeSelect& PDGenHandler::isLepton        =
                                       *( new IsLepton );
const PDGenHandler::TypeSelect& PDGenHandler::isMuon          =
                                       *( new IsMuon );
const PDGenHandler::TypeSelect& PDGenHandler::isElectron      =
                                       *( new IsElectron );
const PDGenHandler::TypeSelect& PDGenHandler::isW             =
                                       *( new IsW );
const PDGenHandler::TypeSelect& PDGenHandler::isDirectW       =
                                       *( new IsDirectW );
const PDGenHandler::TypeSelect& PDGenHandler::isTau           =
                                       *( new IsTau );
const PDGenHandler::TypeSelect& PDGenHandler::isDirectTau     =
                                       *( new IsDirectTau );
const PDGenHandler::TypeSelect& PDGenHandler::isBHadron       =
                                       *( new IsBHadron );
const PDGenHandler::TypeSelect& PDGenHandler::isDirectBHadron =
                                       *( new IsDirectBHadron );
const PDGenHandler::TypeSelect& PDGenHandler::isBQuark        =
                                       *( new IsBQuark );
const PDGenHandler::TypeSelect& PDGenHandler::isCHadron       =
                                       *( new IsCHadron );
const PDGenHandler::TypeSelect& PDGenHandler::isDirectCHadron =
                                       *( new IsDirectCHadron );
const PDGenHandler::TypeSelect& PDGenHandler::isCQuark        =
                                       *( new IsCQuark );
const PDGenHandler::TypeSelect& PDGenHandler::isLHadron       =
                                       *( new IsLHadron );
const PDGenHandler::TypeSelect& PDGenHandler::isDirectLHadron =
                                       *( new IsDirectLHadron );
const PDGenHandler::TypeSelect& PDGenHandler::isLQuark        =
                                       *( new IsLQuark );
const PDGenHandler::TypeSelect& PDGenHandler::isQuarkNoBeauty =
                                       *( new IsQuarkNoBeauty );
const PDGenHandler::TypeSelect& PDGenHandler::isQuarkNoTop    =
                                       *( new IsQuarkNoTop );
const PDGenHandler::TypeSelect& PDGenHandler::isQuark         =
                                       *( new IsQuark );
const PDGenHandler::TypeSelect& PDGenHandler::isTQuark        =
                                       *( new IsTQuark );
const PDGenHandler::TypeSelect& PDGenHandler::isDirectTQuark  =
                                       *( new IsDirectTQuark );
const PDGenHandler::TypeSelect& PDGenHandler::isNotTop        =
                                       *( new IsNotTop );
const PDGenHandler::TypeSelect& PDGenHandler::isGluon         =
                                       *( new IsGluon );
*/

PDGenHandler::PDGenHandler():
 lastRun  ( 0 ),
 lastLumi ( 0 ),
 lastEvent( 0 ) {
  TypeSelect::genId = genId;
}


PDGenHandler::~PDGenHandler() {
}


int PDGenHandler::chkId( int id ) {
  if ( id < 0     ) return 0;
  if ( id > nGenP ) return 0;
  return genId->at( id );
}


const std::vector<PDUtil::ObjectAssociation>& PDGenHandler::genAssociation(
      ObjectDistance& dist, PDEnumString::recoObject obj, bool cache ) {

  newEvent();

  std::map< PDEnumString::recoObject,
            std::vector<ObjectAssociation> >& associationMap =
            associationCache[&dist];
  std::map< PDEnumString::recoObject,
            std::vector<ObjectAssociation> >::const_iterator iter =
            associationMap.find( obj );
  std::map< PDEnumString::recoObject,
            std::vector<ObjectAssociation> >::const_iterator iend =
            associationMap.end();
  if ( cache && ( iter != iend ) ) return iter->second;

  switch ( obj ) {
  case PDEnumString::recMuon:
    associateMuon(     dist );
    break;
  case PDEnumString::recElectron:
    associateElectron( dist );
    break;
  case PDEnumString::recTau:
    associateTau(      dist );
    break;
  case PDEnumString::recJet:
    associateJet(      dist );
    break;
  }

  return associationMap[obj];

}


void PDGenHandler::print( const std::vector<int>* genId,
                          const std::vector<int>* genMother ) {

  ids = genId;
  mothers = genMother;

  daughters.clear();
  int nPart = genId->size();
  int iPart;
  for ( iPart = 0; iPart < nPart; ++iPart ) {
    int iMoth = genMother->at( iPart );
    daughters[iMoth].push_back( iPart );
  }

  const std::vector<int>& ds = daughters[-1];
  nPart = ds.size();
  for ( iPart = 0; iPart < nPart; ++iPart ) print( "", ds[iPart] );

  return;

}


void PDGenHandler::reshuffleFw( std::vector<int>* newMother,
                                std::vector<int>* newPartner ) {
  *newMother  = *genMother;
  *newPartner = *genPartner;
  int iGen;
  int nGen = genMother->size();
  int moth;
  int iold;
  int inew;
  std::vector<int> link( nGen, -1 );
  for ( iGen = 0; iGen < nGen; ++iGen ) { 
    moth = genMother->at( iGen );
    if ( moth < 0 ) continue;
    if ( ( inew = link[moth] ) >= 0 ) {
      newMother->at( iGen ) = inew;
      continue;
    }
    std::multimap<int,int> mothMap;
    while ( moth >= 0 ) {
      mothMap.insert( std::make_pair( -ancestors( moth ), moth ) );
      moth = genPartner->at( moth );
    }
    std::multimap<int,int>::const_iterator iter = mothMap.begin();
    std::multimap<int,int>::const_iterator iend = mothMap.end();
    iold = moth = newMother->at( iGen ) = iter++->second;
    while ( iter != iend ) {
      inew = iter++->second;
      newPartner->at( iold ) = inew;
      link[inew] = moth;
      iold = inew;
    }
    newPartner->at( iold ) = -1;
  }
  return;
}


void PDGenHandler::reshuffleBw( std::vector<int>* newMother,
                                std::vector<int>* newPartner ) {
  *newMother  = *genMother;
  *newPartner = *genPartner;
  int iGen;
  int nGen = genMother->size();
  int moth;
  int iold;
  int inew;
  std::vector<bool> shuffled( nGen, false );
  std::vector<int> backPartner( nGen, -1 );
  for ( iGen = 0; iGen < nGen; ++iGen ) { 
    moth = genMother->at( iGen );
    if ( moth < 0       ) continue;
    if ( shuffled[moth] ) {
      inew = moth;
      do {
        iold = inew;
        inew = backPartner[iold];
      } while ( inew >= 0 );
      newMother->at( iGen ) = iold;
      continue;
    }
    std::multimap<int,int> mothMap;
    while ( moth >= 0 ) {
      mothMap.insert( std::make_pair( ancestors( moth ), moth ) );
      moth = genPartner->at( moth );
    }
    std::multimap<int,int>::const_iterator iter = mothMap.begin();
    std::multimap<int,int>::const_iterator iend = mothMap.end();
    iold = -1;
    while ( iter != iend ) {
      inew = iter++->second;
      newPartner->at( inew ) = iold;
      shuffled[inew] = true;
      if ( iold >= 0 ) backPartner[iold] = inew;
      iold = inew;
    }
    newMother->at( iGen ) = iold;
  }
  return;
}


const std::vector<int>& PDGenHandler::allMothers( int iGen ) {
  newEvent();
  std::map< int, std::vector<int> >::const_iterator iter =
                                     mothersCache.find( iGen );
  std::map< int, std::vector<int> >::const_iterator iend =
                                     mothersCache.end();
  if ( iter != iend ) return iter->second;
  if ( iGen < 0 ) return mothersCache[-1];
  std::vector<int>& ml = mothersCache[iGen];
  int moth = genMother->at( iGen );
  while ( moth >= 0 ) {
    ml.push_back( moth );
    moth = genPartner->at( moth );
  }
  return ml;
}


const std::vector<int>& PDGenHandler::allDaughters( int iGen ) {
  newEvent();
  std::map< int, std::vector<int> >::const_iterator iter =
                                     daughtersCache.find( iGen );
  std::map< int, std::vector<int> >::const_iterator iend =
                                     daughtersCache.end();
  if ( iter != iend ) return iter->second;
  if ( iGen < -1 ) return daughtersCache[-2];
  std::vector<int>& dl = daughtersCache[iGen];
  int jGen;
  for( jGen = 0; jGen < nGenP; ++jGen ) {
    daughtersCache[jGen].reserve( 2 );
    int moth = genMother->at( jGen );
    if ( moth < 0 ) daughtersCache[moth].push_back( jGen );
    while ( moth >= 0 ) {
      daughtersCache[moth].push_back( jGen );
      moth = genPartner->at( moth );
    }
  }
  return dl;
}


const std::vector<int>& PDGenHandler::finalDescendants( int iGen ) {
  newEvent();
  std::map< int, std::vector<int> >::const_iterator iter =
                                     finalCache.find( iGen );
  std::map< int, std::vector<int> >::const_iterator iend =
                                     finalCache.end();
  if ( iter != iend ) return iter->second;
  std::vector<int>& fl = finalCache[iGen];
  std::set<int> dSet;
  std::set<int>::const_iterator d_iter;
  std::set<int>::const_iterator d_iend;
  const std::vector<int>& dl = allDaughters( iGen );
  int id;
  int nd = dl.size();
  for ( id = 0; id < nd; ++id ) addDaughters( dl[id], dSet );
  d_iter = dSet.begin();
  d_iend = dSet.end();
  while ( d_iter != d_iend ) fl.push_back( *d_iter++ );
  return fl;
}


int PDGenHandler::ancestors( int iGen ) {
  int dmax = 0;
  int dcur;
  int moth = genMother->at( iGen );
  while ( moth >= 0 ) {
    dcur = 1 + ancestors( moth );
    if ( dcur > dmax ) dmax = dcur;
    moth = genPartner->at( moth );
  }
  return dmax;
}


std::multimap<int,int>& PDGenHandler::findAncestor( int iGen,
                                      const PDGenHandler::TypeSelect& sel ) {
  newEvent();
  std::map< int, std::multimap<int,int> >& selMap = ancestorsCache[&sel];
  std::map< int, std::multimap<int,int> >::iterator s_iter =
                                                    selMap.find( iGen );
  std::map< int, std::multimap<int,int> >::iterator s_iend =
                                                    selMap.end();
  if ( s_iter != s_iend ) return s_iter->second;
  if ( iGen < 0 ) return selMap[-1];
  std::multimap<int,int>& dmap = selMap[iGen];
  iGen = firstMother( iGen );
  int moth = ( iGen >= 0 ? genMother->at( iGen ) : -1 );
  while ( moth >= 0 ) {
    if ( sel( moth ) ) dmap.insert( std::make_pair( 1, moth ) );
    std::multimap<int,int>& tmap = findAncestor( moth, sel );
    std::multimap<int,int>::const_iterator iter = tmap.begin();
    std::multimap<int,int>::const_iterator iend = tmap.end();
    while ( iter != iend ) {
      const std::pair<int,int>& entry = *iter++;
      int step = ( genId->at( moth ) == genId->at( iGen ) ? 0 : 1 );
      dmap.insert( std::make_pair( step + entry.first, entry.second ) );
//      dmap.insert( std::make_pair( 1 + entry.first, entry.second ) );
    }
    moth = genPartner->at( moth );
  }
  return dmap;
}


bool PDGenHandler::hasAncestors( int iGen, int ns,
                                 const PDGenHandler::TypeSelect** sel ) {
//  iGen = firstMother( iGen );
  const PDGenHandler::TypeSelect& ts = **sel;
  int dmax = ts.dmax();
  std::multimap<int,int>& tmap = findAncestor( iGen, ts );
  if ( !tmap.size() ) return false;
  if ( ( dmax > 0 ) && ( tmap.begin()->first > dmax ) ) return false;
  if ( --ns ) {
    ++sel;
    std::multimap<int,int>::const_iterator iter = tmap.begin();
    std::multimap<int,int>::const_iterator iend = tmap.end();
    while ( iter != iend ) {
      const std::pair<int,int>& entry = *iter++;
      if ( ( dmax > 0 ) && ( entry.first > dmax ) ) break;
      if ( hasAncestors( entry.second, ns, sel ) ) {
        return true;
      }
    }
    return false;
  }
  return true;
}


std::multimap<int,int>& PDGenHandler::findDescendant( int iGen,
                                      const PDGenHandler::TypeSelect& sel ) {
  newEvent();
  std::map< int, std::multimap<int,int> >& selMap = descendantsCache[&sel];
  std::map< int, std::multimap<int,int> >::iterator s_iter =
                                                    selMap.find( iGen );
  std::map< int, std::multimap<int,int> >::iterator s_iend =
                                                    selMap.end();
  if ( s_iter != s_iend ) return s_iter->second;
  if ( iGen < 0 ) return selMap[-1];
  std::multimap<int,int>& dmap = selMap[iGen];
//  iGen = lastDaughter( iGen );
  const std::vector<int>& ds = allDaughters( iGen );
  int iD;
  int nD = ds.size();
  int daug;
  for ( iD = 0; iD < nD; ++iD ) {
    daug = ds[iD];
    if ( sel( daug ) ) dmap.insert( std::make_pair( 1, daug ) );
    std::multimap<int,int>& tmap = findDescendant( daug, sel );
    std::multimap<int,int>::const_iterator t_iter = tmap.begin();
    std::multimap<int,int>::const_iterator t_iend = tmap.end();
    while ( t_iter != t_iend ) {
      const std::pair<int,int>& entry = *t_iter++;
      int step = ( genId->at( daug ) == genId->at( iGen ) ? 0 : 1 );
      dmap.insert( std::make_pair( step + entry.first, entry.second ) );
//      dmap.insert( std::make_pair( 1 + entry.first, entry.second ) );
    }
  }
  return dmap;
}


bool PDGenHandler::hasDescendant( int iGen, int ns,
                                  const PDGenHandler::TypeSelect** sel ) {
  const PDGenHandler::TypeSelect& ts = **sel;
  int dmax = ts.dmax();
  std::multimap<int,int>& tmap = findDescendant( iGen, ts );
  if ( !tmap.size() ) return false;
  if ( ( dmax > 0 ) && ( tmap.begin()->first > dmax ) ) return false;
  if ( --ns ) {
    ++sel;
    std::multimap<int,int>::const_iterator iter = tmap.begin();
    std::multimap<int,int>::const_iterator iend = tmap.end();
    while ( iter != iend ) {
      const std::pair<int,int>& entry = *iter++;
      if ( ( dmax > 0 ) && ( entry.first > dmax ) ) break;
      if ( hasDescendant( entry.second, ns, sel ) ) {
        return true;
      }
    }
    return false;
  }
  return true;
}


int PDGenHandler::sameMother( int iGen ) {
  if ( iGen < 0 ) return iGen;
  int moth = genMother->at( iGen );
  int type = genId->at( iGen );
  while ( moth >= 0 ) {
    if ( genId->at( moth ) == type ) return moth;
    moth = genPartner->at( moth );
  }
  return -1;
}


int PDGenHandler::sameDaughter( int iGen ) {
  if ( iGen < 0 ) return iGen;
  const std::vector<int>& dl = allDaughters( iGen );
  int type = genId->at( iGen );
  int nd = dl.size();
  int id;
  int dp;
  for ( id = 0; id < nd; ++id ) {
    if ( genId->at( dp = dl[id] ) == type ) return dp;
  }
  return -1;
}


int PDGenHandler::firstMother( int iGen ) {
  int moth = iGen;
  while ( moth >= 0 ) {
    iGen = moth;
    moth = sameMother( iGen );
  }
  return iGen;
}


int  PDGenHandler::lastDaughter( int iGen ) {
  int daug = iGen;
  while ( daug >= 0 ) {
    iGen = daug;
    daug = sameDaughter( iGen );
  }
  return iGen;
}


void PDGenHandler::associateMuon( ObjectDistance& dist ) {
  std::vector<ObjectAssociation>& muoGen =
              associationCache[&dist][PDEnumString::recMuon];
  class SelectMuon: public ObjectSelection {
   public:
    virtual bool operator()( int obj ) {
      return ( isMuon( obj ) && p->sameDaughter( obj ) < 0 );
    }
    PDGenHandler* p;
  } msel;
  msel.p = this;
  associateObjects( *muoPt, *muoEta, *muoPhi, *muoPx, *muoPy, *muoPz,
                    *genPt, *genEta, *genPhi, *genPx, *genPy, *genPz,
                    dist, dummySel, msel, true, muoGen );
  return;
}


void PDGenHandler::associateElectron( ObjectDistance& dist ) {
  std::vector<ObjectAssociation>& eleGen =
              associationCache[&dist][PDEnumString::recElectron];
  class SelectElectron: public ObjectSelection {
   public:
    virtual bool operator()( int obj ) {
      return isElectron( obj );
    }
  } esel;
  associateObjects( *elePt, *eleEta, *elePhi, *elePx, *elePy, *elePz,
                    *genPt, *genEta, *genPhi, *genPx, *genPy, *genPz,
                    dist, dummySel, esel, true, eleGen );
  return;
}


void PDGenHandler::associateTau( ObjectDistance& dist ) {
  std::vector<ObjectAssociation>& tauGen =
              associationCache[&dist][PDEnumString::recTau];
  class SelectTau: public ObjectSelection {
   public:
    virtual bool operator()( int obj ) {
      return isTau( obj );
    }
  } tsel;
  associateObjects( *tauPt, *tauEta, *tauPhi, *tauPx, *tauPy, *tauPz,
                    *genPt, *genEta, *genPhi, *genPx, *genPy, *genPz,
                    dist, dummySel, tsel, true, tauGen );
  return;
}


void PDGenHandler::associateJet( ObjectDistance& dist ) {
  std::vector<ObjectAssociation>& jetGen =
              associationCache[&dist][PDEnumString::recJet];
  class SelectQuark: public ObjectSelection {
   public:
    virtual bool operator()( int obj ) {
/*
      if ( isQuark( obj ) ) return true;
//      if ( isGluon( obj ) ) {
//        if ( genE->at( obj ) > 10.0 ) return true;
//      }
      return false;
*/
      if ( !isQuark( obj ) ) return false;
      const std::vector<int>& daug = gh->allDaughters( obj );
      int iDaug;
      int nDaug = daug.size();
      for ( iDaug = 0; iDaug < nDaug; ++iDaug ) {
        if ( isQuark( daug[iDaug] ) ) return false;
      }
      return true;
    }
    PDGenHandler* gh;
    const std::vector<number>* genE;
  } qsel;
  qsel.gh = this;
  qsel.genE = genE;
  associateObjects( *jetPt, *jetEta, *jetPhi, *jetPx, *jetPy, *jetPz,
                    *genPt, *genEta, *genPhi, *genPx, *genPy, *genPz,
                    dist, dummySel, qsel, true, jetGen );
/*
  class DistByPDiffSquare: public ObjectDistance {
    virtual number operator()(
                   number lObjPt , number lObjEta, number lObjPhi,
                   number lObjPx , number lObjPy , number lObjPz ,
                   number rObjPt , number rObjEta, number rObjPhi,
                   number rObjPx , number rObjPy , number rObjPz ) {
      float xDiff = lObjPx - rObjPx;
      float yDiff = lObjPy - rObjPy;
      float zDiff = lObjPz - rObjPz;
      return ( xDiff * xDiff ) + ( yDiff * yDiff ) + ( zDiff * zDiff );
    }
    virtual number dMax() { return 1000000.0; }
  } pds;
  class SelectFinal: public ObjectSelection {
   public:
    virtual bool operator()( int obj ) {
      const std::vector<int>& aD = gh->allDaughters( obj );
      return !aD.size();
    }
    PDGenHandler* gh;
  } fsel;
  fsel.gh = this;
  std::vector<ObjectAssociation> pfcGen;
  associateObjects( *pfcPt, *pfcEta, *pfcPhi, *pfcPx, *pfcPy, *pfcPz,
                    *genPt, *genEta, *genPhi, *genPx, *genPy, *genPz,
                    pds, dummySel, fsel, true, pfcGen );
  int iPF;
  int nPF = pfcGen.size();
  int iGen;
  int iJet;
  std::vector< std::vector<int> > jgCount( nJets );
  for ( iJet = 0; iJet < nJets; ++iJet ) jgCount[iJet].resize( nGenP, 0 );
//  int qGen;
  for ( iPF = 0; iPF < nPF; ++iPF ) {
    iGen = pfcGen[iPF].iObj;
//    qGen = -1;
    if ( iGen >= 0 ) {
      std::multimap<int,int>& pqm = findAncestor( iGen, isQuark );
//      qGen = ( pqm.size() ? pqm.begin()->second : -1 );
      if ( ( pfcGen[iPF].dist < ( modSqua( pfcPx->at( iPF ),
                                           pfcPy->at( iPF ),
                                           pfcPz->at( iPF ) ) / 100.0 ) ) &&
           ( ( iJet = pfcJet->at( iPF ) ) >= 0 ) &&
           pqm.size() ) ++jgCount[iJet][pqm.begin()->second];
    }
//    std::cout << "PFC-GEN: " << iPF << " "
//              << pfcPt->at( iPF ) << " "
//              << pfcJet->at( iPF ) << " "
//              << iGen << " "
//              << pfcGen[iPF].dist << " "
//              << qGen << std::endl;
  }
  int nqFound;
  for ( iJet = 0; iJet < nJets; ++iJet ) {
    std::map<int,int> jgMap;
    for ( iGen = 0; iGen < nGenP; ++iGen ) {
      nqFound = jgCount[iJet][iGen];
      if ( !nqFound ) continue;
      jgMap[nGenP - nqFound] = iGen;
    }
    if ( jgMap.size() ) iGen = jgMap.begin()->second;
    else                iGen = -1;
    int jGen = jetGen[iJet].iObj;
    std::cout << "JET-GEN: " << iJet << " "
              << jGen << " , "
              << ( jGen < 0 ? -99.0 :
                 deltaR( jetEta->at( iJet ), jetPhi->at( iJet ),
                         genEta->at( jGen ), genPhi->at( jGen ) ) )
              << " (" << ( jGen < 0 ? 0 : genId->at( jGen ) ) << ") "
              << iGen << " , "
              << ( iGen < 0 ? -99.0 :
                 deltaR( jetEta->at( iJet ), jetPhi->at( iJet ),
                         genEta->at( iGen ), genPhi->at( iGen ) ) )
              << " (" << ( iGen < 0 ? 0 : genId->at( iGen ) ) << ") "
              << std::endl;
  }
*/
  return;
}




void PDGenHandler::print( const std::string& head, int iPart, int level ) {
  int id = ( iPart < 0 ? 0 : ids->at( iPart ) );
  char is[10];
  sprintf( is, "%6d", id );
  std::stringstream sstr;
  sstr << head << is;
  const std::vector<int>& ds = daughters[iPart];
  int nPart = ds.size();
  if ( nPart ) {
    print( sstr.str() + " | ", ds[0], ++level );
  }
  else {
    std::cout << sstr.str() << std::endl;
  }
  std::string repeat = "";
  int nblank = level;
  while ( nblank-- ) repeat += "       | ";
  for ( iPart = 1; iPart < nPart; ++iPart ) {
    print( repeat, ds[iPart], level );
  }
  return;
}


void PDGenHandler::newEvent() {
  if ( ( lastRun   != runNumber   ) || 
       ( lastLumi  != lumiSection ) || 
       ( lastEvent != eventNumber ) ) {
    associationCache.clear();
      ancestorsCache.clear();
    descendantsCache.clear();
        mothersCache.clear();
      daughtersCache.clear();
          finalCache.clear();
    lastRun   = runNumber;
    lastLumi  = lumiSection;
    lastEvent = eventNumber;
  }
  return;
}


void PDGenHandler::addDaughters( int iGen, std::set<int>& dSet ) {
  const std::vector<int>& dl = allDaughters( iGen );
  int nd = dl.size();
  if ( !nd ) {
    dSet.insert( iGen );
    return;
  }
  int id;
  for ( id = 0; id < nd; ++id ) addDaughters( dl[id], dSet );
  return;
}


const IsLepton        isLepton       ;
const IsMuon          isMuon         ;
const IsElectron      isElectron     ;
const IsW             isW            ;
const IsDirectW       isDirectW      ;
const IsTau           isTau          ;
const IsDirectTau     isDirectTau    ;
const IsHadron        isHadron       ;
const IsBHadron       isBHadron      ;
const IsDirectBHadron isDirectBHadron;
const IsBQuark        isBQuark       ;
const IsCHadron       isCHadron      ;
const IsDirectCHadron isDirectCHadron;
const IsCQuark        isCQuark       ;
const IsLHadron       isLHadron      ;
const IsDirectLHadron isDirectLHadron;
const IsLQuark        isLQuark       ;
const IsQuarkNoBeauty isQuarkNoBeauty;
const IsQuarkNoTop    isQuarkNoTop   ;
const IsQuark         isQuark        ;
const IsTQuark        isTQuark       ;
const IsDirectTQuark  isDirectTQuark ;
const IsNotTop        isNotTop       ;
const IsGluon         isGluon        ;
const IsString        isString       ;
const IsCluster       isCluster      ;

