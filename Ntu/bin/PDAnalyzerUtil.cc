#include <iostream>
#include <sstream>
#include <string>
#include <math.h>

#include "PDAnalyzerUtil.h"
#include "PDAnalysis/Ntu/interface/PDEnumString.h"

#include "TDirectory.h"
#include "TBranch.h"
#include "TTree.h"
#include "TCanvas.h"
#include "Math/LorentzVector.h"

PDAnalyzerUtil::PDAnalyzerUtil() {

  parameterSet = 0;
  currentRun     = 0;
  currentEvent   = 0;
  currentEvBase  = 0;
  currentEvSetup = 0;

  // user parameters are set as names associated to a string, 
  // default values can be set in the analyzer class contructor

  setUserParameter( "use_hltlist"  , "false" );
  setUserParameter( "use_hlts"     , "true"  );
  setUserParameter( "use_hlto"     , "true"  );
  setUserParameter( "use_bspot"    , "true"  );
  setUserParameter( "use_met"      , "true"  );
  setUserParameter( "use_muons"    , "true"  );
  setUserParameter( "use_electrons", "false" );
  setUserParameter( "use_taus"     , "false" );
  setUserParameter( "use_jets"     , "true"  );
  setUserParameter( "use_info"     , "true"  );
  setUserParameter( "use_pflow"    , "true"  );
  setUserParameter( "use_tracks"   , "true"  );
  setUserParameter( "use_pvts"     , "true"  );
  setUserParameter( "use_svts"     , "true"  );
  setUserParameter( "use_tkips"    , "true"  );
  setUserParameter( "use_vtxps"    , "true"  );
  setUserParameter( "use_puwgt"    , "false" );
  setUserParameter( "use_gen"      , "false" );
  setUserParameter( "use_gpj"      , "false" );

  setUserParameter( "use_hlto_sphe"     , "true"  );
  setUserParameter( "use_hlto_cart"     , "false" );
  setUserParameter( "use_muons_sphe"    , "true"  );
  setUserParameter( "use_muons_cart"    , "false" );
  setUserParameter( "use_electrons_sphe", "true"  );
  setUserParameter( "use_electrons_cart", "false" );
  setUserParameter( "use_taus_sphe"     , "true"  );
  setUserParameter( "use_taus_cart"     , "false" );
  setUserParameter( "use_jets_sphe"     , "true"  );
  setUserParameter( "use_jets_cart"     , "false" );
  setUserParameter( "use_pflow_sphe"    , "true"  );
  setUserParameter( "use_pflow_cart"    , "false" );
  setUserParameter( "use_tracks_sphe"   , "true"  );
  setUserParameter( "use_tracks_cart"   , "false" );
  setUserParameter( "use_vtxps_sphe"    , "true"  );
  setUserParameter( "use_vtxps_cart"    , "false" );
  setUserParameter( "use_gen_sphe"      , "true"  );
  setUserParameter( "use_gen_cart"      , "false" );
  setUserParameter( "use_gpj_sphe"      , "true"  );
  setUserParameter( "use_gpj_cart"      , "false" );

  setUserParameter( "jetNDaumin",  "1" );
  setUserParameter( "jetNDaumax",  "999999999" );
  setUserParameter( "jetNHFmin" , "-999999999.999" );
  setUserParameter( "jetNHFmax" ,  "0.99" );
  setUserParameter( "jetNEFmin" , "-999999999.999" );
  setUserParameter( "jetNEFmax" ,  "0.99" );
  setUserParameter( "jetCHFmin" ,  "0.0" );
  setUserParameter( "jetCHFmax" ,  "999999999.999" );
  setUserParameter( "jetCEFmin" , "-999999999.999" );
  setUserParameter( "jetCEFmax" ,  "0.99" );
  setUserParameter( "jetNCHmin" ,  "0" );
  setUserParameter( "jetNCHmax" ,  "999999999" );
  setUserParameter( "jetEtaCut" , "2.4" );

}


PDAnalyzerUtil::~PDAnalyzerUtil() {
}


void PDAnalyzerUtil::beginJob() {

  // user parameters are retrieved as strings by using their names;
  // numeric parameters ( int, float or whatever ) can be directly set
  // by passing the corresponding variable,
  // e.g. getUserParameter( "name", x )

  getUserParameter( "use_hltlist"  , use_hltlist   );
  getUserParameter( "use_hlts"     , use_hlts      );
  getUserParameter( "use_hlto"     , use_hlto      );
  getUserParameter( "use_bspot"    , use_bspot     );
  getUserParameter( "use_met"      , use_met       );
  getUserParameter( "use_muons"    , use_muons     );
  getUserParameter( "use_electrons", use_electrons );
  getUserParameter( "use_taus"     , use_taus      );
  getUserParameter( "use_jets"     , use_jets      );
  getUserParameter( "use_info"     , use_info      );
  getUserParameter( "use_pflow"    , use_pflow     );
  getUserParameter( "use_tracks"   , use_tracks    );
  getUserParameter( "use_pvts"     , use_pvts      );
  getUserParameter( "use_svts"     , use_svts      );
  getUserParameter( "use_tkips"    , use_tkips     );
  getUserParameter( "use_vtxps"    , use_vtxps     );
  getUserParameter( "use_puwgt"    , use_puwgt     );
  getUserParameter( "use_gen"      , use_gen       );
  getUserParameter( "use_gpj"      , use_gpj       );
  if ( !use_jets ) use_svts = false;
  if ( !use_svts ) { use_tkips = false;
                     use_tkips = false; }
  getUserParameter( "use_hlto_sphe"     , use_hlto_sphe      );
  getUserParameter( "use_hlto_cart"     , use_hlto_cart      );
  getUserParameter( "use_muons_sphe"    , use_muons_sphe     );
  getUserParameter( "use_muons_cart"    , use_muons_cart     );
  getUserParameter( "use_electrons_sphe", use_electrons_sphe );
  getUserParameter( "use_electrons_cart", use_electrons_cart );
  getUserParameter( "use_taus_sphe"     , use_taus_sphe      );
  getUserParameter( "use_taus_cart"     , use_taus_cart      );
  getUserParameter( "use_jets_sphe"     , use_jets_sphe      );
  getUserParameter( "use_jets_cart"     , use_jets_cart      );
  getUserParameter( "use_pflow_sphe"    , use_pflow_sphe     );
  getUserParameter( "use_pflow_cart"    , use_pflow_cart     );
  getUserParameter( "use_tracks_sphe"   , use_tracks_sphe    );
  getUserParameter( "use_tracks_cart"   , use_tracks_cart    );
  getUserParameter( "use_vtxps_sphe"    , use_vtxps_sphe     );
  getUserParameter( "use_vtxps_cart"    , use_vtxps_cart     );
  getUserParameter( "use_gen_sphe"      , use_gen_sphe       );
  getUserParameter( "use_gen_cart"      , use_gen_cart       );
  getUserParameter( "use_gpj_sphe"      , use_gpj_sphe       );
  getUserParameter( "use_gpj_cart"      , use_gpj_cart       );

  initTree();
//  read( getUserParameter( "eventList" ) );
//  skipList = ( getUserParameter( "listType" ) == "skip" );
  std::string evl = getUserParameter( "eventList" );
  bool flag = read( evl );
  skipList = ( flag && ( getUserParameter( "listType" ) == "skip" ) );

  getUserParameter( "jetNDaumin", jetNDaumin );
  getUserParameter( "jetNDaumax", jetNDaumax );
  getUserParameter( "jetNHFmin" , jetNHFmin );
  getUserParameter( "jetNHFmax" , jetNHFmax );
  getUserParameter( "jetNEFmin" , jetNEFmin );
  getUserParameter( "jetNEFmax" , jetNEFmax );
  getUserParameter( "jetCHFmin" , jetCHFmin );
  getUserParameter( "jetCHFmax" , jetCHFmax );
  getUserParameter( "jetCEFmin" , jetCEFmin );
  getUserParameter( "jetCEFmax" , jetCEFmax );
  getUserParameter( "jetNCHmin" , jetNCHmin );
  getUserParameter( "jetNCHmax" , jetNCHmax );
  getUserParameter( "jetEtaCut" , jetEtaCut );

  return;

}


bool PDAnalyzerUtil::getEntry( int ientry ) {
//  cout << "PDAnalyzer::getEntry" << endl;
  b_runNumber  ->GetEntry( ientry );
  b_lumiSection->GetEntry( ientry );
  b_eventNumber->GetEntry( ientry );
  if ( use_hltlist ) {
    b_nHLTPaths->GetEntry( ientry );
    if ( nHLTPaths ) {
      b_hltCode  ->GetEntry( ientry );
      b_hltName  ->GetEntry( ientry );
      PDEnumString::resetTrigMap();
      int iHLT;
      for ( iHLT = 0; iHLT < nHLTPaths; ++iHLT )
            PDEnumString::findTrigPath( hltName->at( iHLT ), false,
                                        hltCode->at( iHLT ) );
      PDEnumString::revertTrigMap();
    }
  }
//  if ( !find( runNumber, eventNumber ) ) return false;
//  getEvPre( ientry );
  if ( skipList != find( runNumber, eventNumber ) ) getEvPre( ientry );
  else return false;
  return true;
}


void PDAnalyzerUtil::getEvPre( int ientry ) {
  currentTree->GetEntry( ientry );
  return;
}


void PDAnalyzerUtil::getEntry( TBranch* branch, int ientry ) {
  if ( currentEvBase != 0 ) return;
  if ( currentEvent  != 0 ) return;
  branch->GetEntry( ientry );
  return;
}


void PDAnalyzerUtil::getHeader( int ientry ) {
  if ( currentEvBase != 0 ) return;
  if ( currentEvent  != 0 ) return;
  b_runNumber  ->GetEntry( ientry );
  b_lumiSection->GetEntry( ientry );
  b_eventNumber->GetEntry( ientry );
  return;
}


bool PDAnalyzerUtil::goodJet( unsigned int iJet ) {
  if ( iJet >= jetPF->size() ) return false;
  if ( jetPF->at( iJet ) ) {
    if ( jetNDau->at( iJet ) <= jetNDaumin ) return false;
    if ( jetNEF ->at( iJet ) >  jetNEFmax  ) return false;
    if ( jetNHF ->at( iJet ) >  jetNHFmax  ) return false;
    if ( fabs( jetEta->at( iJet ) ) <= jetEtaCut ) {
      if ( jetNCH->at( iJet ) <= jetNCHmin ) return false;
      if ( jetCEF->at( iJet ) >  jetCEFmax ) return false;
      if ( jetCHF->at( iJet ) <= jetCHFmin ) return false;
    }
  }
  return true;
}


bool PDAnalyzerUtil::hlt( PDEnumString::trigPath path ) {
  if ( ( runNumber != lastHLT.run ) || ( eventNumber != lastHLT.event ) ) {
    hFlags.clear();
    lastHLT.  run =   runNumber;
    lastHLT.event = eventNumber;
    int iHLT;
    for ( iHLT = 0; iHLT < nHLTStatus; ++iHLT )
          hFlags[hltPath->at( iHLT )] = hltAccept->at( iHLT );
  }
  return hFlags[path];
}


std::vector<PDNtupleData::number>* PDAnalyzerUtil::userInfo(
                                   PDEnumString::recoObject r,
                                   PDEnumString::infoType   t ) {
  if ( ( runNumber != lastInfo.run ) || ( eventNumber != lastInfo.event ) ) {
    uInfos.clear();
    lastInfo.  run =   runNumber;
    lastInfo.event = eventNumber;
  }
  int iUI;
  for ( iUI = 0; iUI < nUserInfo; ++iUI ) {
    int ot = useObjType ->at( iUI );
    int io = useObjIndex->at( iUI );
    int it = useInfoType->at( iUI );
    std::vector<number>& v = uInfos[ot][it];
    if ( v.size() == 0 ) {
      switch ( ot ) {
      case PDEnumString::recJet:
        v.resize( nJets     , 0.0 );
        break;
      case PDEnumString::recMuon:
        v.resize( nMuons    , 0.0 );
        break;
      case PDEnumString::recElectron:
        v.resize( nElectrons, 0.0 );
        break;
      case PDEnumString::recTau:
        v.resize( nTaus     , 0.0 );
        break;
      }
    }
    v[io] = useInfoValue->at( iUI );
/*
    std::map<int,std::vector<number> > uiMap ;
 uInfos[r];
    std::map<int,std::vector<number>*>::iterator iter =
                                                 uiMap.find( useInfoType );
    std::map<int,std::vector<number>*>::iterator iend = uiMap.end();
    if ( iter == iend ) {
      int nObj = 0;
      switch ( useObjType ) {
      case PDEnumString::recJet:
        nObj = nJets;
        break;
      case PDEnumString::recMuon:
        nObj = nMuons;
        break;
      case PDEnumString::recElectron:
        nObj = nElectrons;
        break;
      case PDEnumString::recTau:
        nObj = nTaus;
        break;
      default:
        nObj = 0;
        break;
      }
      uiMap.insert( std::make_pair( useInfoType,
                                    new std::vector<number>( nObj ) ) );
    }
*/
  }
//  typedef std::vector<number> svn;
//  typedef std::map<int,svn> ivm;
//  typedef std::map<int,ivm> imm;
//  imm::iterator r_iter =
//                                                            uInfos.find( r );
//  imm::iterator r_iend =
//                                                            uInfos.end();
  std::map< int,std::map< int,std::vector<number> > >::iterator r_iter =
                                                       uInfos.find( r );
  std::map< int,std::map< int,std::vector<number> > >::iterator r_iend =
                                                       uInfos.end();
  if ( r_iter != r_iend ) {
    std::map< int,std::vector<number> >& tmp = r_iter->second;
    std::map< int,std::vector<number> >::iterator t_iter = tmp.find( t );
    std::map< int,std::vector<number> >::iterator t_iend = tmp.end();
    if ( t_iter != t_iend ) return ( &( t_iter->second ) );
  }
  return 0;
}


int PDAnalyzerUtil::findSVtx( int trkIndex, int prevSVtx ) {
  int svtIndex;
  int tipIndex;
  int tvpIndex;
  for ( tvpIndex = 0; tvpIndex < nVtxPs; ++tvpIndex ) {
    tipIndex = tvpTrk->at( tvpIndex );
    if ( tipIndex < 0 ) continue;
    if ( ( ( svtIndex = tipSVtx->at( tipIndex ) ) > prevSVtx ) &&
         (              tipTrk ->at( tipIndex )  == trkIndex ) )
       return svtIndex;
  }
  return -1;
}


void PDAnalyzerUtil::grAssoc() {
  if ( (   runNumber == lastAssoc.  run ) &&
       ( eventNumber == lastAssoc.event ) ) return;
  lastAssoc.  run =   runNumber;
  lastAssoc.event = eventNumber;
  static float ptFactor = 12.0;
  pfcGenP.resize( nPF );
  genReco.resize( nGenP );
  std::vector< std::map<float,int> > rgMap( nPF );
  std::vector< std::map<float,int> > grMap( nGenP );
  int iPF;
  int iGenP;
  int cha;
  float pt;
  float pc;
  float eta;
  float phi;
  float distR;
  float distP;
  for ( iPF = 0; iPF < nPF; ++iPF ) {
    cha = pfcCharge->at( iPF );
    pt  = pfcPt    ->at( iPF );
    eta = pfcEta   ->at( iPF );
    phi = pfcPhi   ->at( iPF );
    for ( iGenP = 0; iGenP < nGenP; ++iGenP ) {
      if ( genCharge->at( iGenP ) != cha ) continue;
      distR = dRSqua( eta, phi, genEta->at( iGenP ), genPhi->at( iGenP ) );
      pc = genPt->at( iGenP );
      distP = ptFactor * fabs( pt - pc ) / ( pt + pc );
      rgMap[iPF][ distR + distP ] = iGenP;
    }
    std::map<float,int>::iterator iter = rgMap[iPF].begin();
    std::cout << iPF << " : " << iter->first << " " << iter->second << std::endl;
    ++iter;
    std::cout << iPF << " : " << iter->first << " " << iter->second << std::endl;
    ++iter;
    std::cout << iPF << " : " << iter->first << " " << iter->second << std::endl;
    ++iter;
    std::cout << iPF << " : " << iter->first << " " << iter->second << std::endl;
    pfcGenP[iPF] = ( rgMap[iPF].size() ?
                     rgMap[iPF].begin()->second : -1 );
  }
//  std::cout << "rg done " << nPF << " " << nGenP << std::endl;
  for ( iGenP = 0; iGenP < nGenP; ++iGenP ) {
    cha = genCharge->at( iGenP );
    pt  = genPt    ->at( iGenP );
    eta = genEta   ->at( iGenP );
    phi = genPhi   ->at( iGenP );
    for ( iPF = 0; iPF < nPF; ++iPF ) {
      if ( pfcCharge->at( iPF ) != cha ) continue;
      distR = dRSqua( eta, phi, pfcEta->at( iPF ), pfcPhi->at( iPF ) );
      pc = pfcPt->at( iPF );
      distP = ptFactor * fabs( pt - pc ) / ( pt + pc );
      grMap[iGenP][ distR + distP ] = iPF;
    }
    genReco[iGenP] = ( grMap[iGenP].size() ?
                       grMap[iGenP].begin()->second : -1 );
  }
//  std::cout << "gr done" << std::endl;
  int ichk;
  for ( iPF = 0; iPF < nPF; ++iPF ) {
    iGenP = pfcGenP[iPF];
    if ( iGenP < 0 ) continue;
    if ( ( ichk = genReco[iGenP] ) != iPF ) {
      std::cout << "pfc mismatch: "
                << iPF   << " -> "
                << iGenP << "(" << rgMap[iPF  ].begin()->first << ") -> "
                << ichk  << "(" << grMap[iGenP].begin()->first << ")"
                << std::endl;
    }
  }
  for ( iGenP = 0; iGenP < nGenP; ++iGenP ) {
    iPF = genReco[iGenP];
    if ( iPF < 0 ) continue;
    if ( ( ichk = pfcGenP[iPF] ) != iGenP ) {
      std::cout << "gen mismatch: "
                << iGenP << " -> "
                << iPF   << "(" << grMap[iGenP].begin()->first << ") -> "
                << ichk  << "(" << rgMap[iPF  ].begin()->first << ")"
                << std::endl;
    }
  }
  return;
}

