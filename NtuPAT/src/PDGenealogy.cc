#include "PDAnalysis/NtuPAT/interface/PDGenealogy.h"

#include <iostream>
#include <sstream>
#include <stdio.h>

using namespace std;

const vector<int>* PDGenealogy::ids = 0;
const vector<int>* PDGenealogy::mothers = 0;
map< int,vector<int> > PDGenealogy::daughters;

vector<int>* PDGenealogy::TypeSelect::genId;

PDGenealogy::PDGenealogy():
 lastRun  ( 0 ),
 lastLumi ( 0 ),
 lastEvent( 0 ) {
  TypeSelect::genId = genId;
}


PDGenealogy::~PDGenealogy() {
}


void PDGenealogy::print( const vector<int>* genId,
                         const vector<int>* genMother ) {

  ids = genId;
  mothers = genMother;

  daughters.clear();
  int nPart = genId->size();
  int iPart;
  for ( iPart = 0; iPart < nPart; ++iPart ) {
    int iMoth = genMother->at( iPart );
    daughters[iMoth].push_back( iPart );
  }

/*
  map< int,vector<int> >::const_iterator iter = daughters.begin();
  map< int,vector<int> >::const_iterator iend = daughters.end();
  while ( iter != iend ) {
    const pair< int,vector<int> >& entry = *iter++;
    iPart = entry.first;
    int id = ( iPart < 0 ? 0 : ids->at( iPart ) );
    cout << "m: " << iPart <<"(" << id << ") d: ";
    const vector<int>& ds = entry.second;
    nPart = ds.size();
    for ( iPart = 0; iPart < nPart; ++iPart ) cout << " " << ds[iPart] << "(" << ids->at( ds[iPart] ) << ")";
    cout << endl;
  }
*/

//  print( "", -1 );
  const vector<int>& ds = daughters[-1];
  nPart = ds.size();
  for ( iPart = 0; iPart < nPart; ++iPart ) print( "", ds[iPart] );

  return;

}


void PDGenealogy::reshuffleFw( std::vector<int>* newMother,
                               std::vector<int>* newPartner ) {
  *newMother  = *genMother;
  *newPartner = *genPartner;
  int iGen;
  int nGen = genMother->size();
  int moth;
  int iold;
  int inew;
  vector<int> link( nGen, -1 );
  for ( iGen = 0; iGen < nGen; ++iGen ) { 
    moth = genMother->at( iGen );
    if ( moth < 0 ) continue;
    if ( ( inew = link[moth] ) >= 0 ) {
      newMother->at( iGen ) = inew;
      continue;
    }
    multimap<int,int> mothMap;
    while ( moth >= 0 ) {
      mothMap.insert( make_pair( -ancestors( moth ), moth ) );
      moth = genPartner->at( moth );
    }
    multimap<int,int>::const_iterator iter = mothMap.begin();
    multimap<int,int>::const_iterator iend = mothMap.end();
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


void PDGenealogy::reshuffleBw( std::vector<int>* newMother,
                               std::vector<int>* newPartner ) {
  *newMother  = *genMother;
  *newPartner = *genPartner;
  int iGen;
  int nGen = genMother->size();
  int moth;
  int iold;
  int inew;
  vector<bool> shuffled( nGen, false );
  vector<int> backPartner( nGen, -1 );
  for ( iGen = 0; iGen < nGen; ++iGen ) { 
    moth = genMother->at( iGen );
    if ( moth < 0       ) continue;
    if ( shuffled[moth] ) {
      inew = moth;
      do {
        iold = inew;
        inew = backPartner[iold]; } while ( inew >= 0 );
      newMother->at( iGen ) = iold;
      continue;
    }
    multimap<int,int> mothMap;
    while ( moth >= 0 ) {
      mothMap.insert( make_pair( ancestors( moth ), moth ) );
      moth = genPartner->at( moth );
    }
    multimap<int,int>::const_iterator iter = mothMap.begin();
    multimap<int,int>::const_iterator iend = mothMap.end();
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


const std::map< int, std::vector<int> >& PDGenealogy::allMothers() {
  newEvent();
  if ( mothersFound ) return mothersCache;
  int iGen;
  for( iGen = 0; iGen < nGenP; ++iGen ) {
    int moth = genMother->at( iGen );
    while ( moth >= 0 ) {
      mothersCache[iGen].push_back( moth );
      moth = genPartner->at( moth );
    }
  }
  mothersFound = true;
  return mothersCache;
}


const std::map< int, std::vector<int> >& PDGenealogy::allDaughters() {
  newEvent();
  if ( daughtersFound ) return daughtersCache;
  int iGen;
  for( iGen = 0; iGen < nGenP; ++iGen ) {
    int moth = genMother->at( iGen );
    if ( moth < 0 ) daughtersCache[moth].push_back( iGen );
    while ( moth >= 0 ) {
      daughtersCache[moth].push_back( iGen );
      moth = genPartner->at( moth );
    }
  }
  daughtersFound = true;
  return daughtersCache;
}


const std::map< int, std::vector<int> >& PDGenealogy::finalDescendants() {
  newEvent();
  if ( finalFound ) return finalCache;
  allDaughters();
  std::set<int> dSet;
  std::set<int>::const_iterator iter;
  std::set<int>::const_iterator iend;
  int iGen;
  int nd;
  int id;
  for( iGen = 0; iGen < nGenP; ++iGen ) {
    dSet.clear();
    std::vector<int>& dl = daughtersCache[iGen];
    nd = dl.size();
    for ( id = 0; id < nd; ++id ) addDaughters( dl[id], dSet );
    iter = dSet.begin();
    iend = dSet.end();
    while ( iter != iend ) finalCache[iGen].push_back( *iter++ );
  }
  finalFound = true;
  return finalCache;
}


int PDGenealogy::ancestors( int iGen ) {
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


multimap<int,int>& PDGenealogy::findAncestor( int iGen,
                                const PDGenealogy::TypeSelect& sel ) {
  newEvent();
//  cout << "cache size at " << runNumber << " " << eventNumber << " : " << cacheMap.size() << endl;
  map< const TypeSelect*, multimap<int,int> >& selMap = cacheMap[iGen];
  map< const TypeSelect*, multimap<int,int> >::iterator iter =
                                                        selMap.find( &sel );
  map< const TypeSelect*, multimap<int,int> >::iterator iend =
                                                        selMap.end();
  if ( iter != iend ) return iter->second;
  multimap<int,int>& dmap = selMap[&sel];
/*
  multimap<int,int> dmap;
*/
  int moth = genMother->at( iGen );
  while ( moth >= 0 ) {
    if ( sel( moth ) ) dmap.insert( make_pair( 1, moth ) );
    multimap<int,int>& tmap = findAncestor( moth, sel );
    multimap<int,int>::const_iterator iter = tmap.begin();
    multimap<int,int>::const_iterator iend = tmap.end();
    while ( iter != iend ) {
      const pair<int,int>& entry = *iter++;
      dmap.insert( make_pair( 1 + entry.first, entry.second ) );
    }
    moth = genPartner->at( moth );
  }
//  selMap[&sel] = dmap;
  return dmap;
}


bool PDGenealogy::hasAncestors( int iGen, int ns,
                                const PDGenealogy::TypeSelect** sel ) {
  int moth = genMother->at( iGen );
  while ( moth >= 0 ) {
    if ( genId->at( moth ) ==
         genId->at( iGen ) ) {
//      cout << "replica found " << iGen << " " << moth << " " << genId->at( iGen ) << endl;
      iGen = moth;
      moth = genMother->at( iGen );
      continue;
    }
    moth = genPartner->at( moth );
  }
//  cout << "go on from " << iGen << " " << genId->at( iGen ) << endl;
  const PDGenealogy::TypeSelect& ts = **sel;
  int dmax = ts.dmax();
  multimap<int,int>& tmap = findAncestor( iGen, ts );
//  cout << ns << "," << iGen << " - branches: " << tmap.size() << endl;
  if ( !tmap.size() ) return false;
//  if ( ( dmax > 0 ) && ( tmap.begin()->first > dmax ) ) cout << "left" << endl;
  if ( ( dmax > 0 ) && ( tmap.begin()->first > dmax ) ) return false;
  if ( --ns ) {
    ++sel;
    multimap<int,int>::const_iterator iter = tmap.begin();
    multimap<int,int>::const_iterator iend = tmap.end();
    while ( iter != iend ) {
      const pair<int,int>& entry = *iter++;
//      cout << "test " << iGen << " " << dmax << " " << entry.first << endl;
      if ( ( dmax > 0 ) && ( entry.first > dmax ) ) break;
//      cout << "go on through " << entry.second << endl;
      if ( hasAncestors( entry.second, ns, sel ) ) {
//        cout << "got." << ns << endl;
        return true;
      }
    }
//    cout << "left " << ns << endl;
    return false;
  }
//  cout << "got!" << ns << endl;
  return true;
}


void PDGenealogy::print( const string& head, int iPart, int level ) {
  int id = ( iPart < 0 ? 0 : ids->at( iPart ) );
  char is[10];
  sprintf( is, "%6d", id );
  stringstream sstr;
  sstr << head << is;
  const vector<int>& ds = daughters[iPart];
  int nPart = ds.size();
  if ( nPart ) {
    print( sstr.str() + " | ", ds[0], ++level );
  }
  else {
    cout << sstr.str() << endl;
  }
  string repeat = "";
  int nblank = level;
  while ( nblank-- ) repeat += "       | ";
  for ( iPart = 1; iPart < nPart; ++iPart ) {
    print( repeat, ds[iPart], level );
  }
  return;
}


void PDGenealogy::newEvent() {
  if ( ( lastRun   != runNumber   ) || 
       ( lastLumi  != lumiSection ) || 
       ( lastEvent != eventNumber ) ) {
    cacheMap.clear();
      mothersCache.clear();
    daughtersCache.clear();
        finalCache.clear();
    lastRun   = runNumber;
    lastLumi  = lumiSection;
    lastEvent = eventNumber;
      mothersFound =
    daughtersFound =
        finalFound = false;
  }
  return;
}


void PDGenealogy::addDaughters( int iGen, std::set<int>& dSet ) {
  std::vector<int>& dl = daughtersCache[iGen];
  int nd = dl.size();
  if ( !nd ) {
    dSet.insert( iGen );
    return;
  }
  int id;
  for ( id = 0; id < nd; ++id ) addDaughters( dl[id], dSet );
  return;
}

