#include <iostream>
#include <sstream>
#include <string>
#include <math.h>

#include "PDAnalyzerUtil.h"

#include "TDirectory.h"
#include "TBranch.h"
#include "TTree.h"
#include "TCanvas.h"
#include "Math/LorentzVector.h"

using namespace std;

PDAnalyzerUtil::PDAnalyzerUtil() {

  parameterSet = 0;
  currentRun     = 0;
  currentEvent   = 0;
  currentEvBase  = 0;
  currentEvSetup = 0;

  // user parameters are set as names associated to a string, 
  // default values can be set in the analyzer class contructor

  setUserParameter( "use_hlts"     , "true"  );
  setUserParameter( "use_hlto"     , "true"  );
  setUserParameter( "use_bspot"    , "true"  );
  setUserParameter( "use_met"      , "true"  );
  setUserParameter( "use_muons"    , "true"  );
  setUserParameter( "use_electrons", "false" );
  setUserParameter( "use_taus"     , "false" );
  setUserParameter( "use_jets"     , "true"  );
  setUserParameter( "use_pflow"    , "true"  );
  setUserParameter( "use_tracks"   , "true"  );
  setUserParameter( "use_pvts"     , "true"  );
  setUserParameter( "use_svts"     , "true"  );
  setUserParameter( "use_tkips"    , "true"  );
  setUserParameter( "use_vtxps"    , "true"  );
  setUserParameter( "use_gen"      , "false" );

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

  getUserParameter( "use_hlts"     , use_hlts      );
  getUserParameter( "use_hlto"     , use_hlto      );
  getUserParameter( "use_bspot"    , use_bspot     );
  getUserParameter( "use_met"      , use_met       );
  getUserParameter( "use_muons"    , use_muons     );
  getUserParameter( "use_electrons", use_electrons );
  getUserParameter( "use_taus"     , use_taus      );
  getUserParameter( "use_jets"     , use_jets      );
  getUserParameter( "use_pflow"    , use_pflow     );
  getUserParameter( "use_tracks"   , use_tracks    );
  getUserParameter( "use_pvts"     , use_pvts      );
  getUserParameter( "use_svts"     , use_svts      );
  getUserParameter( "use_tkips"    , use_tkips     );
  getUserParameter( "use_vtxps"    , use_vtxps     );
  getUserParameter( "use_gen"      , use_gen       );
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

  initTree();
  read( getUserParameter( "eventList" ) );

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
  if ( !find( runNumber, eventNumber ) ) return false;
  getEvPre( ientry );
  return true;
}


bool PDAnalyzerUtil::getEvPre( int ientry ) {
  currentTree->GetEntry( ientry );
  return true;
}


void PDAnalyzerUtil::getEntry( TBranch* branch, int ientry ) {
  if ( currentEvBase != 0 ) return;
  if ( currentEvent  != 0 ) return;
  branch->GetEntry( ientry );
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

