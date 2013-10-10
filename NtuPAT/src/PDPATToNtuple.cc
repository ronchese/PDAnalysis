#include "PDAnalysis/NtuPAT/interface/PDPATToNtuple.h"
#include "PDAnalysis/NtuPAT/interface/PDEnumString.h"
#include "TFile.h"
#include "TROOT.h"

#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
//#include "DataFormats/HLTReco/interface/TriggerObject.h"
//#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"

#include "DataFormats/PatCandidates/interface/TriggerEvent.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "PhysicsTools/PatUtils/interface/TriggerHelper.h"

#include "DataFormats/PatCandidates/interface/MET.h"

#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Muon.h"

//#include "DataFormats/PatCandidates/interface/PFParticle.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"

#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
//#include "EGamma/EGammaAnalysisTools/interface/ElectronEffectiveArea.h"

#include "DataFormats/PatCandidates/interface/Tau.h"

#include "DataFormats/PatCandidates/interface/Jet.h"

//#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/BTauReco/interface/SecondaryVertexTagInfo.h"
#include "DataFormats/GeometryVector/interface/GlobalVector.h"
#include "DataFormats/GeometryCommonDetAlgo/interface/Measurement1D.h"

#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"
#include "TrackingTools/Records/interface/TransientTrackRecord.h"
#include "RecoVertex/KalmanVertexFit/interface/KalmanVertexFitter.h"
#include "RecoVertex/VertexPrimitives/interface/TransientVertex.h"

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include <iostream>
#include <sstream>
#include <map>


using edm::TriggerResults;
using pat::MET;
using pat::Muon;
using pat::Electron;
using pat::Tau;
using pat::Jet;
//using pat::PFParticle;
using reco::Candidate;
using reco::PFCandidate;
using reco::PFCandidatePtr;
using reco::Track;
using reco::TrackRef;
using reco::TrackBaseRef;
using reco::HitPattern;
using reco::Vertex;
using reco::SecondaryVertexTagInfo;
using reco::GenParticle;

using namespace std;

PDPATToNtuple::PDPATToNtuple( const edm::ParameterSet& ps ) {

  parameterSet = &ps;
  ntuName = ps.getUntrackedParameter<string>( "ntuName" );
  dumpNtuple = ( ntuName != "" );

  setUserParameter( "labelTrigResults"   ,
                     labelTrigResults    = ps.getParameter<string>(
                    "labelTrigResults"   ) );
  setUserParameter( "use_hlts"      ,
                  ( read_hlts       = (
  getUserParameter( "labelTrigResults"   ) != "" ) ) ? "t" : "f" );
  if ( ps.exists( "write_hlts"      ) &&
                    read_hlts         )
  setUserParameter( "use_hlts"           , ps.getParameter<string>(
                  "write_hlts"      ) );

  setUserParameter( "labelTrigEvent"     ,
                     labelTrigEvent      = ps.getParameter<string>(
                    "labelTrigEvent"     ) );
  setUserParameter( "use_hlto"      ,
		  ( read_hlto       = (
  getUserParameter( "labelTrigEvent"     ) != "" ) ) ? "t" : "f" );
  if ( ps.exists( "write_hlto"      ) &&
                    read_hlto         )
  setUserParameter( "use_hlto"           , ps.getParameter<string>(
                  "write_hlto"      ) );

  setUserParameter( "labelBeamSpot"      ,
                     labelBeamSpot       = ps.getParameter<string>(
                    "labelBeamSpot"      ) );
  setUserParameter( "use_bspot"     ,
                  ( read_bspot      = (
  getUserParameter( "labelBeamSpot"      ) != "" ) ) ? "t" : "f" );
  if ( ps.exists( "write_bspot"     ) &&
                    read_bspot        )
  setUserParameter( "use_bspot"          , ps.getParameter<string>(
                  "write_bspot"     ) );

  setUserParameter( "labelMets"          ,
                     labelMets           = ps.getParameter<string>(
                    "labelMets"          ) );
  setUserParameter( "use_met"       ,
                  ( read_met        = (
  getUserParameter( "labelMets"          ) != "" ) ) ? "t" : "f" );
  if ( ps.exists( "write_met"       ) &&
                    read_met          )
  setUserParameter( "use_met"            , ps.getParameter<string>(
                  "write_met"       ) );

  setUserParameter( "labelMuons"         ,
                     labelMuons          = ps.getParameter<string>(
                    "labelMuons"         ) );
  setUserParameter( "use_muons"     ,
                  ( read_muons      = (
  getUserParameter( "labelMuons"         ) != "" ) ) ? "t" : "f" );
  if ( ps.exists( "write_muons"     ) &&
                    read_muons        )
  setUserParameter( "use_muons"          , ps.getParameter<string>(
                  "write_muons"     ) );

  setUserParameter( "labelElectrons"     ,
                     labelElectrons      = ps.getParameter<string>(
                    "labelElectrons"     ) );
  setUserParameter( "use_electrons" ,
                  ( read_electrons  = (
  getUserParameter( "labelElectrons"     ) != "" ) ) ? "t" : "f" );
  if ( ps.exists( "write_electrons" ) &&
                    read_electrons    )
  setUserParameter( "use_electrons"      , ps.getParameter<string>(
                  "write_electrons" ) );

  setUserParameter( "labelTaus"          ,
                     labelTaus           = ps.getParameter<string>(
                    "labelTaus"           ) );
  setUserParameter( "use_taus"      ,
                  ( read_taus       = (
  getUserParameter( "labelTaus"          ) != "" ) ) ? "t" : "f" );
  if ( ps.exists( "write_taus"      ) &&
                    read_taus         )
  setUserParameter( "use_taus"           , ps.getParameter<string>(
                  "write_taus"      ) );

  setUserParameter( "labelJets"          ,
                     labelJets           = ps.getParameter<string>(
                    "labelJets"          ) );
  setUserParameter( "use_jets"      ,
                  ( read_jets       = (
  getUserParameter( "labelJets"          ) != "" ) ) ? "t" : "f" );
  if ( ps.exists( "write_jets"      ) &&
                    read_jets         )
  setUserParameter( "use_jets"           , ps.getParameter<string>(
                  "write_jets"      ) );

  setUserParameter( "labelPFCandidates"  ,
                     labelPFCandidates   = ps.getParameter<string>(
                    "labelPFCandidates"  ) );
  setUserParameter( "use_pflow"     ,
                  ( read_pflow      = (
  getUserParameter( "labelPFCandidates"  ) != "" ) ) ? "t" : "f" );
  if ( ps.exists( "write_pflow"     ) &&
                    read_pflow        )
  setUserParameter( "use_pflow"          , ps.getParameter<string>(
                  "write_pflow"     ) );

  setUserParameter( "labelGeneralTracks" ,
                     labelGeneralTracks  = ps.getParameter<string>(
                    "labelGeneralTracks" ) );
  setUserParameter( "use_tracks"    ,
                  ( read_tracks     = (
  getUserParameter( "labelGeneralTracks" ) != "" ) ) ? "t" : "f" );
  if ( ps.exists( "write_tracks"    ) &&
                    read_tracks       )
  setUserParameter( "use_tracks"         , ps.getParameter<string>(
                  "write_tracks"    ) );

  setUserParameter( "labelPVertices"     ,
                     labelPVertices      = ps.getParameter<string>(
                    "labelPVertices"     ) );
  setUserParameter( "use_pvts"      ,
                  ( read_pvts       = (
  getUserParameter( "labelPVertices"     ) != "" ) ) ? "t" : "f" );
  if ( ps.exists( "write_pvts"      ) &&
                    read_pvts         )
  setUserParameter( "use_pvts"           , ps.getParameter<string>(
                  "write_pvts"      ) );

  setUserParameter( "labelSVertices"     ,
                     labelSVertices      = ps.getParameter<string>(
                    "labelSVertices"     ) );
  setUserParameter( "use_svts"      ,
                  ( read_svts       = (
  getUserParameter( "labelSVertices"     ) != "" ) ) ? "t" : "f" );
  if ( ps.exists( "write_svts"      ) &&
                    read_svts         )
  setUserParameter( "use_svts"           , ps.getParameter<string>(
                  "write_svts"      ) );

  setUserParameter( "labelGen"           ,
                     labelGen            = ps.getParameter<string>(
                    "labelGen"           ) );
  setUserParameter( "use_gen"       ,
                  ( read_gen        = (
  getUserParameter( "labelGen"           ) != "" ) ) ? "t" : "f" );
  if ( ps.exists( "write_gen"       ) &&
                    read_gen          )
  setUserParameter( "use_gen"            , ps.getParameter<string>(
                  "write_gen"       ) );

  setUserParameter( "use_tkips", getUserParameter( "use_svts" ) );
  if ( ps.exists( "write_tkips"   ) &&
                    read_svts  )
  setUserParameter( "use_tkips", ps.getParameter<string>(
                  "write_tkips" ) );

  setUserParameter( "use_vtxps", getUserParameter( "use_svts" ) );
  if ( ps.exists( "write_vtxps" ) &&
                     use_tkips   )
  setUserParameter( "use_vtxps", ps.getParameter<string>(
                  "write_vtxps" ) );

  if ( ps.exists( "write_hlto_cart"     ) )
  setUserParameter( "use_hlto_cart"     , ps.getParameter<string>(
                  "write_hlto_cart"     ) );
  if ( ps.exists( "write_hlto_sphe"     ) )
  setUserParameter( "use_hlto_sphe"     , ps.getParameter<string>(
                  "write_hlto_sphe"     ) );
  if ( ps.exists( "write_muons_cart"    ) )
  setUserParameter( "use_muons_cart"    , ps.getParameter<string>(
                  "write_muons_cart"    ) );
  if ( ps.exists( "write_muons_sphe"    ) )
  setUserParameter( "use_muons_sphe"    , ps.getParameter<string>(
                  "write_muons_sphe"     ) );
  if ( ps.exists( "write_electrons_cart" ) )
  setUserParameter( "use_electrons_cart", ps.getParameter<string>(
                  "write_electrons_cart" ) );
  if ( ps.exists( "write_electrons_sphe" ) )
  setUserParameter( "use_electrons_sphe", ps.getParameter<string>(
                  "write_electrons_sphe" ) );
  if ( ps.exists( "write_taus_cart"      ) )
  setUserParameter( "use_taus_cart"     , ps.getParameter<string>(
                  "write_taus_cart"      ) );
  if ( ps.exists( "write_taus_sphe"      ) )
  setUserParameter( "use_taus_sphe"     , ps.getParameter<string>(
                  "write_taus_sphe"      ) );
  if ( ps.exists( "write_jets_cart"      ) )
  setUserParameter( "use_jets_cart"     , ps.getParameter<string>(
                  "write_jets_cart"      ) );
  if ( ps.exists( "write_jets_sphe"      ) )
  setUserParameter( "use_jets_sphe"     , ps.getParameter<string>(
                  "write_jets_sphe"      ) );
  if ( ps.exists( "write_pflow_cart"     ) )
  setUserParameter( "use_pflow_cart"    , ps.getParameter<string>(
                  "write_pflow_cart"     ) );
  if ( ps.exists( "write_pflow_sphe"     ) )
  setUserParameter( "use_pflow_sphe"    , ps.getParameter<string>(
                  "write_pflow_sphe"     ) );
  if ( ps.exists( "write_tracks_cart"    ) )
  setUserParameter( "use_tracks_cart"   , ps.getParameter<string>(
                  "write_tracks_cart"    ) );
  if ( ps.exists( "write_tracks_sphe"    ) )
  setUserParameter( "use_tracks_sphe"   , ps.getParameter<string>(
                  "write_tracks_sphe"    ) );
  if ( ps.exists( "write_vtxps_cart"     ) )
  setUserParameter( "use_vtxps_cart"    , ps.getParameter<string>(
                  "write_vtxps_cart"     ) );
  if ( ps.exists( "write_vtxps_sphe"     ) )
  setUserParameter( "use_gen_sphe"      , ps.getParameter<string>(
                  "write_gen_sphe"       ) );
  if ( ps.exists( "write_gen_cart"       ) )
  setUserParameter( "use_gen_cart"      , ps.getParameter<string>(
                  "write_gen_cart"       ) );

  if ( ps.exists( "savedTriggerPaths"   ) )
                   savedTriggerPaths    = ps.getParameter< vector<string> >(
                  "savedTriggerPaths"   );
  if ( ps.exists( "savedTriggerObjects" ) )
                   savedTriggerObjects  = ps.getParameter< vector<string> >(
                  "savedTriggerObjects" );

  char sPF = *ps.getParameter<string>( "selectAssociatedPF" ).c_str();
  char sTk = *ps.getParameter<string>( "selectAssociatedTk" ).c_str();
  selectAssociatedPF = ( sPF != 'f' ) && ( sPF != 'F' );
  selectAssociatedTk = ( sTk != 'f' ) && ( sTk != 'F' );

  jetPtMin  = ps.getParameter<double>( "jetPtMin"  );
  jetEtaMax = ps.getParameter<double>( "jetEtaMax" );
  trkDzMax  = ps.getParameter<double>( "trkDzMax"  );
  trkPtMin  = ps.getParameter<double>( "trkPtMin"  );
  trkEtaMax = ps.getParameter<double>( "trkEtaMax" );
  dRmatchHLT = ps.getParameter<double>( "dRmatchHLT" );
  dPmatchHLT = ps.getParameter<double>( "dPmatchHLT" );

  if ( ps.exists( "eventList" ) )
  setUserParameter( "eventList", ps.getParameter<string>( "eventList" ) );

  setUserParameter( "verbose",
                    ps.getUntrackedParameter<string>( "verbose" ) );

}


PDPATToNtuple::~PDPATToNtuple() {
}


void PDPATToNtuple::beginJob() {
//  cout << "PDPATToNtuple::beginJob()" << endl;
  TDirectory* current = gDirectory;
  gROOT->cd();
  PDAnalyzer::beginJob();
  openNtuple( ntuName );
  hltConfigProvider = 0;
  gROOT->cd();
  book();
  current->cd();
  return;
}


void PDPATToNtuple::beginRun() {
  if ( currentEvSetup != 0 ) {
    try {
      bool changed;
      hltConfigProvider = new HLTConfigProvider;
      hltConfigProvider->init( *currentRun, *currentEvSetup, "HLT", changed );
//      std::cout << "hltConfigProvider->size(): "
//                <<  hltConfigProvider->size() << std::endl;
      const std::string tableName = hltConfigProvider->tableName();
//      std::cout << "tableName: " << tableName << std::endl;
      std::vector<std::string> triggerNames =
            hltConfigProvider->triggerNames();
//      unsigned int n = triggerNames.size();
//      std::cout << "n: " << n << std::endl;
    }
    catch ( cms::Exception e ) {
      hltConfigProvider = 0;
    }
  }
  return;
}


void PDPATToNtuple::openNtuple( const string& name ) {
  TDirectory* current = gDirectory;
  file = ( dumpNtuple ? new TFile( name.c_str(), "CREATE" ) : 0 );
  initWrite( file );
  current->cd();
  return;
}


void PDPATToNtuple::analyze( const edm::EventBase& ev,
                             int ientry, int event_file ) {

  if ( verbose ) {
    cout << " =========================== " << endl;
    cout << "event "
         << ev.id().run() << " / "
         << ev.id().event() << endl;
  }

  // function provided by the tool to automatically reset all variables
  autoReset();

  // store event id
  runNumber   = ev.id().run();
  lumiSection = ev.id().luminosityBlock();
  eventNumber = ev.id().event();

  if ( !find( runNumber, eventNumber ) ) return;
  read( ev );
  if ( PDAnalyzer::analyze( ientry, event_file ) ) writeNtuple();

  return;

}

void PDPATToNtuple::read( const edm::EventBase& ev ) {

  currentEvBase = &ev;

  // store event id
  runNumber   = ev.id().run();
  lumiSection = ev.id().luminosityBlock();
  eventNumber = ev.id().event();

  nHLTStatus  = 0;
  nHLTObjects = 0;
  nMuons      = 0;
  nElectrons  = 0;
  nTaus       = 0;
  nJets       = 0;
  nPF         = 0;
  nTracks     = 0;
  nPVertices  = 0;
  nSVertices  = 0;
  nTkIPs      = 0;
  nVtxPs      = 0;
  nGenP       = 0;
  if ( read_hlts      ) fillHLTStatus   ();
  if ( read_hlto      ) fillHLTObjects  ();
  if ( read_bspot     ) fillBeamSpot    ();
  if ( read_met       ) fillMet         ();
  if ( read_muons     ) fillMuons       ();
  if ( read_electrons ) fillElectrons   ();
  if ( read_taus      ) fillTaus        ();
  if ( read_jets      ) fillJets        ();
  if ( read_pvts      ) fillVtxTrkMap   ();
  if ( read_pflow     ) fillPFCandidates();
  if ( read_tracks    ) fillTracks      ();
  if ( read_pvts      ) fillPVertices   ();
  if ( read_svts      ) fillSVertices   ();
  if ( read_gen       ) fillGenParticles();

  if ( read_muons && read_tracks ) linkMTracks();
//  if ( read_pflow && read_jets   ) linkPFJets ();
  if ( read_pflow && read_tracks ) linkPTracks();

  return;

}


void PDPATToNtuple::writeNtuple() {

  if ( !dumpNtuple ) return;
  // function provided by the tool to actually fill the tree
//  cout << "fill" << endl;
  fill();

  return;

}


void PDPATToNtuple::closeNtuple() {
  if ( !dumpNtuple ) return;
  close();
  file->Close();
  return;
}


void PDPATToNtuple::endRun() {
  return;
}


void PDPATToNtuple::endJob() {
  PDAnalyzer::endJob();
  closeNtuple();
  cout << endl << analyzedEvents() << " events read, "
               << acceptedEvents() << " accepted" << endl;
  return;
}


void PDPATToNtuple::fillHLTStatus() {

  nHLTStatus = 0;
  hltPath   ->resize( 0 );
  hltVersion->resize( 0 );
  hltScale  ->resize( 0 );
  hltRun    ->resize( 0 );
  hltAccept ->resize( 0 );

  currentEvBase->getByLabel( getUserParameter( "labelTrigResults" ),
                             trigResults );
  if ( !trigResults.isValid() ) {
    cout << "invalid trigResults" << endl;
    triggerNames = 0;
    return;
  }
  else {
    triggerNames = &( currentEvBase->triggerNames( *trigResults ) );
  }


  int nObj = triggerNames->size();
  int iObj;
  int iTrg;
  int iPath;
  int iVers;
  int lVers;
  int lSave;
  int iPres;
  int nTrg = savedTriggerPaths.size();
  for ( iObj = 0; iObj < nObj; ++iObj ) {
    const string& hltPathName = triggerNames->triggerName( iObj );
    int index = triggerNames->triggerIndex( hltPathName );
    iPath = -1;
    iVers = -1;
    iPres = -1;
    stringstream sstr;
    for ( iTrg = 0; iTrg < nTrg; ++iTrg ) {
      const string& name = savedTriggerPaths[iTrg];
      if ( ( name != "*" ) &&
           ( hltPathName.find( name, 0 ) == string::npos ) ) continue;
      if ( ( iPath = PDEnumString::findTrigPath( hltPathName ) ) < 0 )
          continue;
      lSave =        name.length();
      lVers = hltPathName.length() - lSave;
      sstr.clear();
      sstr.str(  hltPathName.substr( lSave, lVers ) );
      sstr >> iVers;
      if ( hltConfigProvider != 0 ) {
//        cout << "look prescale for " << hltPathName << endl;
        try {
          pair<int,int> pathPS = hltConfigProvider->prescaleValues(
                                 *currentEvent, *currentEvSetup, hltPathName );
          iPres = pathPS.first * pathPS.second;
//          cout << "factors: " << pathPS.first << " " << pathPS.second << endl;
        }
        catch ( cms::Exception e ) {
          iPres = -1;
        }
      }
      ++nHLTStatus;
      hltPath   ->push_back( iPath );
      hltVersion->push_back( iVers );
      hltScale  ->push_back( iPres );
      hltRun    ->push_back( trigResults->wasrun( index ) );
      hltAccept ->push_back( trigResults->accept( index ) );
    }
  }

  return;

}


void PDPATToNtuple::fillHLTObjects() {

  currentEvBase->getByLabel( getUserParameter( "labelTrigEvent" ),
                             trigEvent );
  bool vHLTo = trigEvent.isValid();

  hltObjType->resize( 0 );
  hltPt     ->resize( 0 );
  hltEta    ->resize( 0 );
  hltPhi    ->resize( 0 );
  hltPx     ->resize( 0 );
  hltPy     ->resize( 0 );
  hltPz     ->resize( 0 );
  hltE      ->resize( 0 );

  if ( !vHLTo ) {
    cout << "invalid trigEvent" << endl;
    return;
  }

  int iTrg;
  int nTrg = savedTriggerObjects.size();
  int triggerObjectType;
  nHLTObjects = 0;
  for ( iTrg = 0; iTrg < nTrg; ++iTrg ) {
    const string& name = savedTriggerObjects[iTrg];
    if      ( name == "hltMuon" ) triggerObjectType = trigger::TriggerMuon;
    else if ( name == "hltJet"  ) triggerObjectType = trigger::TriggerJet;
    else continue;
    const pat::TriggerObjectRefVector
          trigRefs( trigEvent->objects( triggerObjectType ) );
    pat::TriggerObjectRefVector::const_iterator iter = trigRefs.begin();
    pat::TriggerObjectRefVector::const_iterator iend = trigRefs.end();
    while ( iter != iend ) {
      const pat::TriggerObject& obj = **iter++;
      hltObjType->push_back( PDEnumString::findTrigObject( name ) );
      const Candidate::LorentzVector p4 = obj.p4();
      hltPt          ->push_back( p4.pt    () );
      hltEta         ->push_back( p4.eta   () );
      hltPhi         ->push_back( p4.phi   () );
      hltPx          ->push_back( p4.px    () );
      hltPy          ->push_back( p4.py    () );
      hltPz          ->push_back( p4.pz    () );
      hltE           ->push_back( p4.energy() );
      ++nHLTObjects;
    }
  }

  return;

}


void PDPATToNtuple::fillBeamSpot() {

  bwX         = -999.999;
  bwY         = -999.999;
  bwXError    = -999.999;
  bwYError    = -999.999;
  bsX         = -999.999;
  bsY         = -999.999;
  bsZ         = -999.999;
  bsXError    = -999.999;
  bsYError    = -999.999;
  bsZError    = -999.999;
  bsdXdZ      = -999.999;
  bsdYdZ      = -999.999;
  bsdXdZError = -999.999;
  bsdYdZError = -999.999;
  currentEvBase->getByLabel( getUserParameter( "labelBeamSpot" ),
                             beamSpot );
  if ( !beamSpot.isValid() ) {
    cout << "invalid beam spot" << endl;
    return;
  }

  bwX         = beamSpot->BeamWidthX();
  bwY         = beamSpot->BeamWidthY();
  bwXError    = beamSpot->BeamWidthXError();
  bwYError    = beamSpot->BeamWidthYError();
  bsX         = beamSpot->x0();
  bsY         = beamSpot->y0();
  bsZ         = beamSpot->z0();
  bsXError    = beamSpot->x0Error();
  bsYError    = beamSpot->y0Error();
  bsZError    = beamSpot->z0Error();
  bsdXdZ      = beamSpot->dxdz();
  bsdYdZ      = beamSpot->dydz();
  bsdXdZError = beamSpot->dxdzError();
  bsdYdZError = beamSpot->dydzError();

  return;

}


void PDPATToNtuple::fillMet() {

  mEt = -999.999;
  mEx = -999.999;
  mEy = -999.999;
  currentEvBase->getByLabel( getUserParameter( "labelMets" ),
                             mets );
  if ( !mets.isValid() ) {
    cout << "invalid mets" << endl;
    return;
  }

  // store mEt info

  mEt    = mets->at( 0 ).pt();
  mEx    = mets->at( 0 ).px();
  mEy    = mets->at( 0 ).py();
  mEsign = mets->at( 0 ).mEtSig();

  return;

}


void PDPATToNtuple::fillMuons() {

  currentEvBase->getByLabel( getUserParameter( "labelMuons" ),
                             muons );
  bool vMuons = muons.isValid();

  // store muons info

  int iObj;
  int nObj = nMuons = ( vMuons ? muons->size() : 0 );
  muoPt          ->resize( nObj );
  muoEta         ->resize( nObj );
  muoPhi         ->resize( nObj );
  muoPx          ->resize( nObj );
  muoPy          ->resize( nObj );
  muoPz          ->resize( nObj );
  muoE           ->resize( nObj );
  muoCharge      ->resize( nObj );
  muoTrk         ->resize( nObj );
  muoTrg         ->resize( nObj );
  muoChaIso      ->resize( nObj );
  muoNeuIso      ->resize( nObj );
  muoPhoIso      ->resize( nObj );
  muoSumCHpt     ->resize( nObj );
  muoSumCPpt     ->resize( nObj );
  muoSumNHet     ->resize( nObj );
  muoSumPHet     ->resize( nObj );
  muoSumPUpt     ->resize( nObj );
  muoNumMatches  ->resize( nObj );
  muoDb          ->resize( nObj );
  muoNumValidHits->resize( nObj );
  muoNormChi2    ->resize( nObj );
  muoNumMuHits   ->resize( nObj );
  muoNumPixHits  ->resize( nObj );
  muoNumTkHits   ->resize( nObj );
  if ( !vMuons ) {
    cout << "invalid muons" << endl;
    return;
  }

  vector<const Muon*> muonPtr;
  muonPtr.resize( nObj );
  for ( iObj = 0; iObj < nObj; ++iObj ) {
    muonPtr[iObj] = &( muons->at( iObj ) );
  }

  compareByPt<Muon> muoComp;
  sort( muonPtr.begin(), muonPtr.end(), muoComp );

  muoMap.clear();
//  pcmMap.clear();
  tkmMap.clear();
  for ( iObj = 0; iObj < nObj; ++iObj ) {

    const Muon& muon = *muonPtr[iObj];
    muoMap.insert( make_pair( &muon, iObj ) );
    try {
      const reco::PFCandidateRef& pcr = muon.pfCandidateRef();
      if ( !pcr.isNull() ) {
//      pcmMap.insert( make_pair( &(*pcr), iObj ) );
        const TrackRef& tkr = pcr->trackRef();
        if ( !tkr.isNull() ) tkmMap.insert( make_pair( &(*tkr), iObj ) );
      }
    }
    catch ( edm::Exception e ) {
    }

    const Candidate::LorentzVector p4 = muon.p4();
    muoPt          ->at( iObj ) = p4.pt    ();
    muoEta         ->at( iObj ) = p4.eta   ();
    muoPhi         ->at( iObj ) = p4.phi   ();
    muoPx          ->at( iObj ) = p4.px    ();
    muoPy          ->at( iObj ) = p4.py    ();
    muoPz          ->at( iObj ) = p4.pz    ();
    muoE           ->at( iObj ) = p4.energy();
    muoCharge      ->at( iObj ) = muon.charge();
    muoTrk         ->at( iObj ) = -1;
    muoTrg         ->at( iObj ) = nearestHLT( PDEnumString::hltMuon,
                                              p4.pt(), p4.eta(), p4.phi() );

    muoChaIso      ->at( iObj ) = muon.chargedHadronIso();
    muoNeuIso      ->at( iObj ) = muon.neutralHadronIso();
    muoPhoIso      ->at( iObj ) = muon.photonIso();
    const reco::MuonPFIsolation& pfIsolationR04 = muon.pfIsolationR04();
    muoSumCHpt     ->at( iObj ) = pfIsolationR04.sumChargedHadronPt;
    muoSumCPpt     ->at( iObj ) = pfIsolationR04.sumChargedParticlePt;
    muoSumNHet     ->at( iObj ) = pfIsolationR04.sumNeutralHadronEt;
    muoSumPHet     ->at( iObj ) = pfIsolationR04.sumPhotonEt;
    muoSumPUpt     ->at( iObj ) = pfIsolationR04.sumPUPt;

    muoNumMatches  ->at( iObj ) = muon.numberOfMatchedStations();
    muoDb          ->at( iObj ) = muon.dB();

    muoNumValidHits->at( iObj ) = 0;
    muoNormChi2    ->at( iObj ) = 0.0;
    muoNumMuHits   ->at( iObj ) = 0;
    muoNumPixHits  ->at( iObj ) = 0;
    muoNumTkHits   ->at( iObj ) = 0;

    if ( !( muon. isGlobalMuon() ) ) continue;
    if ( !( muon.isTrackerMuon() ) ) continue;
    const TrackRef&  innerTrack = muon. innerTrack();
    const TrackRef& globalTrack = muon.globalTrack();
    const HitPattern& hitPattern = globalTrack->hitPattern();
    try {
    muoNumValidHits->at( iObj ) =  innerTrack->numberOfValidHits();
    }
    catch ( edm::Exception e ) {
    muoNumValidHits->at( iObj ) = 0;
    }
    muoNormChi2    ->at( iObj ) = globalTrack->normalizedChi2();
    muoNumMuHits   ->at( iObj ) = hitPattern.numberOfValidMuonHits();
    muoNumPixHits  ->at( iObj ) = hitPattern.numberOfValidPixelHits();
    muoNumTkHits   ->at( iObj ) = hitPattern.numberOfValidTrackerHits();
  }

  return;

}


void PDPATToNtuple::fillElectrons() {

  currentEvBase->getByLabel( getUserParameter( "labelElectrons" ),
                             electrons );
  bool vElectrons = electrons.isValid();

  // store electrons info

  int iObj;
  int nObj = nElectrons = ( vElectrons ? electrons->size() : 0 );
  elePt     ->resize( nObj );
  eleEta    ->resize( nObj );
  elePhi    ->resize( nObj );
  elePx     ->resize( nObj );
  elePy     ->resize( nObj );
  elePz     ->resize( nObj );
  eleE      ->resize( nObj );
  eleCharge ->resize( nObj );
  eleTrk    ->resize( nObj );
  eleTrg    ->resize( nObj );
  eleChaIso ->resize( nObj );
  eleNeuIso ->resize( nObj );
  elePhoIso ->resize( nObj );
  eleAbsEta ->resize( nObj );
  eleAEff   ->resize( nObj );
  eleID     ->resize( nObj );
  eleConsCha->resize( nObj );
  eleEBEEGap->resize( nObj );
  eleDb     ->resize( nObj );
  if ( !vElectrons ) {
    cout << "invalid electrons" << endl;
    return;
  }

  vector<const Electron*> electronPtr;
  electronPtr.resize( nObj );
  for ( iObj = 0; iObj < nObj; ++iObj ) {
    electronPtr[iObj] = &( electrons->at( iObj ) );
  }

  compareByPt<Electron> eleComp;
  sort( electronPtr.begin(), electronPtr.end(), eleComp );

  eleMap.clear();
  tkeMap.clear();
  for ( iObj = 0; iObj < nObj; ++iObj ) {

    const Electron& electron = *electronPtr[iObj];
    eleMap.insert( make_pair( &electron, iObj ) );
    try {
      const reco::PFCandidateRef& pcr = electron.pfCandidateRef();
      if ( !pcr.isNull() ) {
        const TrackRef& tkr = pcr->trackRef();
        if ( !tkr.isNull() ) tkeMap.insert( make_pair( &(*tkr), iObj ) );
      }
    }
    catch ( edm::Exception e ) {
    }

    const Candidate::LorentzVector p4 = electron.p4();
    elePt     ->at( iObj ) = p4.pt    ();
    eleEta    ->at( iObj ) = p4.eta   ();
    elePhi    ->at( iObj ) = p4.phi   ();
    elePx     ->at( iObj ) = p4.px    ();
    elePy     ->at( iObj ) = p4.py    ();
    elePz     ->at( iObj ) = p4.pz    ();
    eleE      ->at( iObj ) = p4.energy();
    eleCharge ->at( iObj ) = electron.charge();
    eleTrk    ->at( iObj ) = -1;
    eleTrg    ->at( iObj ) = nearestHLT( PDEnumString::hltElectron,
                                         p4.pt(), p4.eta(), p4.phi() );

    eleChaIso ->at( iObj ) = electron.chargedHadronIso();
    eleNeuIso ->at( iObj ) = electron.neutralHadronIso();
    elePhoIso ->at( iObj ) = electron.photonIso();
//    double absEta =
    eleAbsEta ->at( iObj ) = fabs( electron.superCluster()->eta() );
    eleAEff   ->at( iObj ) = -999.999;
//    eleAEff   ->at( iObj ) =
//      ElectronEffectiveArea::GetElectronEffectiveArea(
//      ElectronEffectiveArea::kEleGammaAndNeutralHadronIso03, absEta,
//      ElectronEffectiveArea::kEleEAData2011 );

    eleID     ->at( iObj ) = 0;//electron.electronID( "eidMediumMC" );
    eleConsCha->at( iObj ) = electron.isGsfCtfScPixChargeConsistent();
    eleEBEEGap->at( iObj ) = electron.isEBEEGap();
    eleDb     ->at( iObj ) = electron.dB();

  }

  return;

}



void PDPATToNtuple::fillTaus() {

  currentEvBase->getByLabel( getUserParameter( "labelTaus" ),
                             taus );
  bool vTaus = taus.isValid();

  // store taus info

  int iObj;
  int nObj = nTaus = ( vTaus ? taus->size() : 0 );
  tauPt    ->resize( nObj );
  tauEta   ->resize( nObj );
  tauPhi   ->resize( nObj );
  tauPx    ->resize( nObj );
  tauPy    ->resize( nObj );
  tauPz    ->resize( nObj );
  tauE     ->resize( nObj );
  tauCharge->resize( nObj );
  tauTrg   ->resize( nObj );
  if ( !vTaus ) {
    cout << "invalid taus" << endl;
    return;
  }

  vector<const Tau*> tauPtr;
  tauPtr.resize( nObj );
  for ( iObj = 0; iObj < nObj; ++iObj ) {
    tauPtr[iObj] = &( taus->at( iObj ) );
  }

  compareByPt<Tau> tauComp;
  sort( tauPtr.begin(), tauPtr.end(), tauComp );

  tauMap.clear();
  for ( iObj = 0; iObj < nObj; ++iObj ) {

    const Tau& tau = *tauPtr[iObj];
    tauMap.insert( make_pair( &tau, iObj ) );

    const Candidate::LorentzVector p4 = tau.p4();
    tauPt    ->at( iObj ) = p4.pt    ();
    tauEta   ->at( iObj ) = p4.eta   ();
    tauPhi   ->at( iObj ) = p4.phi   ();
    tauPx    ->at( iObj ) = p4.px    ();
    tauPy    ->at( iObj ) = p4.py    ();
    tauPz    ->at( iObj ) = p4.pz    ();
    tauE     ->at( iObj ) = p4.energy();
    tauCharge->at( iObj ) = tau.charge();
    tauTrg   ->at( iObj ) = nearestHLT( PDEnumString::hltTau,
                                        p4.pt(), p4.eta(), p4.phi() );;

  }

  return;

}


void PDPATToNtuple::fillJets() {

  currentEvBase->getByLabel( getUserParameter( "labelJets" ),
                             jets );
  currentEvBase->getByLabel( getUserParameter( "labelSVertices"     ),
                             sVertices     );
  bool vJets = jets.isValid();
  bool vSvts = sVertices.isValid();

  // store jets info

  int iObj;
  int nObj = 0;
  jetPt  ->resize( 0 );
  jetEta ->resize( 0 );
  jetPhi ->resize( 0 );
  jetPx  ->resize( 0 );
  jetPy  ->resize( 0 );
  jetPz  ->resize( 0 );
  jetE   ->resize( 0 );
  jetCSV ->resize( 0 );
  jetTCHE->resize( 0 );
  jetPF  ->resize( 0 );
  jetTrg ->resize( 0 );
  jetNDau->resize( 0 );
  jetNHF ->resize( 0 );
  jetNEF ->resize( 0 );
  jetCHF ->resize( 0 );
  jetCEF ->resize( 0 );
  jetNCH ->resize( 0 );
  if ( !vJets ) {
    cout << "invalid jets" << endl;
    return;
  }
  else {
    nObj = jets->size();
  }

  map<const Jet*,int> jhiMap;
  vector<const Jet*> jetPtr;
  jetPtr.resize( nObj );
  for ( iObj = 0; iObj < nObj; ++iObj ) 
    jhiMap.insert( make_pair( jetPtr[iObj] = &( jets->at( iObj ) ), iObj ) );

  compareByPt<Jet> jetComp;
  sort( jetPtr.begin(), jetPtr.end(), jetComp );

  string labelCSV  = "combinedSecondaryVertexBJetTags";
  string labelTCHE = "trackCountingHighEffBJetTags";
  jetMap.clear();
  pcjMap.clear();
  ptjMap.clear();
  nJets = 0;
  bool select;
  int jhiIndex;
  map<const Jet*,int>::const_iterator j_iter = jhiMap.begin();
  map<const Jet*,int>::const_iterator j_iend = jhiMap.end();
  for ( iObj = 0; iObj < nObj; ++iObj ) {

    select = false;

    const Jet* jPtr = jetPtr[iObj];
    const Jet& jet = *jPtr;

    if ( fabs( jet.eta() ) < jetEtaMax ) select = true;
    if (       jet.pt ()   > jetPtMin  ) select = true;
    if ( !select ) {
      if ( !vSvts ) continue;
      j_iter = jhiMap.find( jPtr );
      if ( j_iter == j_iend ) continue;
      jhiIndex = j_iter->second;
      if ( sVertices->at( jhiIndex ).nVertices() ) select = true;
    }
    if ( !select ) continue;

    jetMap.insert( make_pair( &jet, nJets ) );
    const vector<PFCandidatePtr>& jPFC = jet.getPFConstituents();
    int nPFC = jPFC.size();
    int iPFC;
    for ( iPFC = 0; iPFC < nPFC; ++iPFC ) {
      const PFCandidatePtr& pfp = jPFC.at( iPFC );
      try {
        if ( pcjMap.find( &(*pfp) ) ==
             pcjMap.end() ) pcjMap.insert( make_pair( &(*pfp), nJets ) );
        const TrackRef   & tkr = pfp->trackRef();
        const Track      * tkp = ( tkr.isNull() ? 0 : &(*tkr) );
        if ( ptjMap.find( tkp ) ==
             ptjMap.end() ) ptjMap.insert( make_pair( tkp, nJets ) );
      }
      catch ( edm::Exception e ) {
      }
    }

    jetPt  ->push_back( jet.pt    () );
    jetEta ->push_back( jet.eta   () );
    jetPhi ->push_back( jet.phi   () );
    jetPx  ->push_back( jet.px    () );
    jetPy  ->push_back( jet.py    () );
    jetPz  ->push_back( jet.pz    () );
    jetE   ->push_back( jet.energy() );
    jetCSV ->push_back( jet.bDiscriminator( labelCSV  )   );
    jetTCHE->push_back( jet.bDiscriminator( labelTCHE )   );
    jetTrg ->push_back( nearestHLT( PDEnumString::hltJet,
                                    jet.pt(), jet.eta(), jet.phi() ) );
    jetPF  ->push_back( jet.isPFJet()                     );
    jetNDau->push_back( jet.numberOfDaughters()           );
    jetNHF ->push_back( jet.neutralHadronEnergyFraction() );
    jetNEF ->push_back( jet.neutralEmEnergyFraction()     );
    jetCHF ->push_back( jet.chargedHadronEnergyFraction() );
    jetCEF ->push_back( jet.chargedEmEnergyFraction()     );
    jetNCH ->push_back( jet.chargedMultiplicity()         );

    ++nJets;

  }

  return;

}


void PDPATToNtuple::fillVtxTrkMap() {

  currentEvBase->getByLabel( getUserParameter( "labelGeneralTracks" ),
                             generalTracks );
  currentEvBase->getByLabel( getUserParameter( "labelPVertices"     ),
                             pVertices     );
  int iTrk;
  int nTrk = ( generalTracks.isValid() ? generalTracks->size() : 0 );
  int iPVt;
  int nPVt = ( pVertices    .isValid() ? pVertices    ->size() : 0 );
  int iSVt;
  int nSVt = ( sVertices    .isValid() ? sVertices    ->size() : 0 );

  map<const Track*,int>::const_iterator it_m = tkmMap.begin();
  map<const Track*,int>::const_iterator ie_m = tkmMap.end();
  map<const Track*,int>::const_iterator it_e = tkeMap.begin();
  map<const Track*,int>::const_iterator ie_e = tkeMap.end();
  map<const Track*,int>::const_iterator it_p = ptjMap.begin();
  map<const Track*,int>::const_iterator ie_p = ptjMap.end();
  vtxList.resize( 0 );
  allPTk.clear();
  for ( iPVt = 0; iPVt < nPVt; ++iPVt ) {
    const Vertex& vtx = pVertices->at( iPVt );
    bool found = false;
    try {
      Vertex::trackRef_iterator it_v = vtx.tracks_begin();
      Vertex::trackRef_iterator ie_v = vtx.tracks_end();
      while ( it_v != ie_v ) {
        const reco::TrackBaseRef& tkr = *it_v++;
        const Track* tkp = &(*tkr);
        if ( allPTk.find( tkp ) == allPTk.end() ) allPTk.insert( tkp );
        it_m = tkmMap.find( tkp );
        it_e = tkeMap.find( tkp );
        it_p = ptjMap.find( tkp );
        if ( it_m != ie_m ) found = true;
        if ( it_e != ie_e ) found = true;
        if ( it_p != ie_p ) found = true;
      }
    }
    catch ( edm::Exception e ) {
    }
    if ( found ) vtxList.push_back( &vtx );
  }

  nPVt = vtxList.size();

  tkvMap.clear();
  for ( iPVt = 0; iPVt < nPVt; ++iPVt ) {
    const Vertex& vtx = *vtxList[iPVt];
    try {
      Vertex::trackRef_iterator it_v = vtx.tracks_begin();
      Vertex::trackRef_iterator ie_v = vtx.tracks_end();
      while ( it_v != ie_v ) {
        const reco::TrackBaseRef& tkr = *it_v++;
        if ( fabs( tkr->eta() ) > trkEtaMax ) continue;
        if (       tkr->pt ()   < trkPtMin  ) continue;
        tkvMap.insert( make_pair( &(*tkr), iPVt ) );
      }
    }
    catch ( edm::Exception e ) {
    }
  }

  // recover tracks not linked to any primary vertex
  tkrSet.clear();
  set<const Track*>::const_iterator a_iend = allPTk.end();
  for ( iTrk = 0; iTrk < nTrk; ++iTrk ) {
    const Track& trk = generalTracks->at( iTrk );
    const Track* tkp = &trk;
    // skip tracks linked to a primary vertex
    if ( allPTk.find( tkp ) != a_iend ) continue;
    if ( fabs( tkp->eta() ) > trkEtaMax ) continue;
    if (       tkp->pt ()   < trkPtMin  ) continue;
    for ( iPVt = 0; iPVt < nPVt; ++iPVt ) {
      const Vertex& vtx = *vtxList[iPVt];
      const Vertex::Point& pos = vtx.position();
      if ( fabs( tkp->dz( pos ) ) < trkDzMax ) tkrSet.insert( tkp );
    }
  }

  // recover tracks linked to a secondary vertex
  for ( iSVt = 0; iSVt < nSVt; ++iSVt ) {
    const SecondaryVertexTagInfo& secVtxTagInfo = sVertices->at( iSVt );
    int iVtx;
    int nVtx = secVtxTagInfo.nVertices();
    for ( iVtx = 0; iVtx < nVtx; ++iVtx ) {
      const        Vertex& vtx = secVtxTagInfo.secondaryVertex( iVtx );
      Vertex::trackRef_iterator v_iter = vtx.tracks_begin();
      Vertex::trackRef_iterator v_iend = vtx.tracks_end();
      while ( v_iter != v_iend ) {
        const reco::TrackBaseRef& tkr = *v_iter++;
        const Track* tkp = &(*tkr);
        if ( tkrSet.find( tkp ) == tkrSet.end() ) tkrSet.insert( tkp );
      }
    }
  }

  return;

}


void PDPATToNtuple::fillPFCandidates() {

  currentEvBase->getByLabel( getUserParameter( "labelPFCandidates" ),
                             pfCandidates );
  bool vPF = pfCandidates.isValid();

  // store particle flow info

  int iObj;
  int nObj = 0;
  pfcPt      ->resize( 0 );
  pfcEta     ->resize( 0 );
  pfcPhi     ->resize( 0 );
  pfcPx      ->resize( 0 );
  pfcPy      ->resize( 0 );
  pfcPz      ->resize( 0 );
  pfcE       ->resize( 0 );
  pfcCharge  ->resize( 0 );
  pfcJet     ->resize( 0 );
  pfcTrk     ->resize( 0 );
  if ( !vPF ) {
    cout << "invalid particle flow" << endl;
    return;
  }
  else {
    nObj = pfCandidates->size();
  }

  pfcMap.clear();
  tkpMap.clear();
  nPF = 0;
  set<const Track      *    >::const_iterator r_iend = tkrSet.end();
  map<const Track      *,int>::const_iterator m_iter = tkmMap.begin();
  map<const Track      *,int>::const_iterator m_iend = tkmMap.end();
  map<const Track      *,int>::const_iterator e_iter = tkeMap.begin();
  map<const Track      *,int>::const_iterator e_iend = tkeMap.end();
  map<const Track      *,int>::const_iterator v_iter = tkvMap.begin();
  map<const Track      *,int>::const_iterator v_iend = tkvMap.end();
  map<const PFCandidate*,int>::const_iterator j_iter = pcjMap.begin();
  map<const PFCandidate*,int>::const_iterator j_iend = pcjMap.end();
  for ( iObj = 0; iObj < nObj; ++iObj ) {

    const PFCandidate& pfc = pfCandidates->at( iObj );
    const TrackRef   & tkr = pfc.trackRef();
    const Track      * tkp = 0;
    try {
      tkp = ( tkr.isNull() ? 0 : &(*tkr) );
    }
    catch ( edm::Exception e ) {
    }

    int muoIndex = ( ( m_iter = tkmMap.find( tkp  ) ) != m_iend ?
                       m_iter->second : -1 );
    int eleIndex = ( ( e_iter = tkeMap.find( tkp  ) ) != e_iend ?
                       e_iter->second : -1 );
    int vtxIndex = ( ( v_iter = tkvMap.find( tkp  ) ) != v_iend ?
                       v_iter->second : -1 );
    int jetIndex = ( ( j_iter = pcjMap.find( &pfc ) ) != j_iend ?
                       j_iter->second : -1 );
    if ( selectAssociatedPF &&
         ( muoIndex < 0 ) &&
         ( eleIndex < 0 ) &&
         ( vtxIndex < 0 ) &&
         ( jetIndex < 0 ) &&
         ( tkrSet.find( tkp ) == r_iend ) ) continue;

    if ( tkp != 0 )
    tkpMap.insert( make_pair(  tkp, nPF ) );
    pfcMap.insert( make_pair( &pfc, nPF ) );
    const Candidate::LorentzVector p4 = pfc.p4();

    pfcPt      ->push_back( p4.pt    () );
    pfcEta     ->push_back( p4.eta   () );
    pfcPhi     ->push_back( p4.phi   () );
    pfcPx      ->push_back( p4.px    () );
    pfcPy      ->push_back( p4.py    () );
    pfcPz      ->push_back( p4.pz    () );
    pfcE       ->push_back( p4.energy() );
    pfcCharge  ->push_back( pfc.charge() );
//    pfcJet     ->push_back( -1 );
    pfcJet     ->push_back( jetIndex );
    pfcTrk     ->push_back( -1 );

//    const reco::TrackRef& trk = pfc.trackRef();
//    pftMap.insert( make_pair( &(*trk), iObj ) );

    ++nPF;

  }

  return;

}

void PDPATToNtuple::fillTracks() {

  bool vTracks = generalTracks.isValid();

  // store tracks info

  int iObj;
  int nObj = 0;
  trkPt      ->resize( 0 );
  trkEta     ->resize( 0 );
  trkPhi     ->resize( 0 );
  trkPx      ->resize( 0 );
  trkPy      ->resize( 0 );
  trkPz      ->resize( 0 );
  trkCharge  ->resize( 0 );
  trkPFC     ->resize( 0 );
  trkJet     ->resize( 0 );
  trkPVtx    ->resize( 0 );
//  trkSVtx    ->resize( 0 );
  trkQuality ->resize( 0 );
  trkNormChi2->resize( 0 );
  trkDxy     ->resize( 0 );
  trkDz      ->resize( 0 );
  if ( !vTracks ) {
    cout << "invalid tracks" << endl;
    return;
  }
  else {
    nObj = generalTracks->size();
  }

  trkMap.clear();
  nTracks = 0;
  set<const Track      *    >::const_iterator r_iend = tkrSet.end();
  map<const Track      *,int>::const_iterator m_iter = tkmMap.begin();
  map<const Track      *,int>::const_iterator m_iend = tkmMap.end();
  map<const Track      *,int>::const_iterator e_iter = tkeMap.begin();
  map<const Track      *,int>::const_iterator e_iend = tkeMap.end();
  map<const Track      *,int>::const_iterator p_iter = tkpMap.begin();
  map<const Track      *,int>::const_iterator p_iend = tkpMap.end();
  map<const Track      *,int>::const_iterator v_iter = tkvMap.begin();
  map<const Track      *,int>::const_iterator v_iend = tkvMap.end();
  for ( iObj = 0; iObj < nObj; ++iObj ) {

    const Track& trk = generalTracks->at( iObj );
    const Track* tkp = &trk;

    int muoIndex = ( ( m_iter = tkmMap.find( tkp ) ) != m_iend ?
                       m_iter->second : -1 );
    int eleIndex = ( ( e_iter = tkeMap.find( tkp ) ) != e_iend ?
                       e_iter->second : -1 );
    int pfcIndex = ( ( p_iter = tkpMap.find( tkp ) ) != p_iend ?
                       p_iter->second : -1 );
    int vtxIndex = ( ( v_iter = tkvMap.find( tkp ) ) != v_iend ?
                       v_iter->second : -1 );
    if ( selectAssociatedTk &&
         ( muoIndex < 0 ) &&
         ( eleIndex < 0 ) &&
         ( pfcIndex < 0 ) &&
         ( vtxIndex < 0 ) &&
         ( tkrSet.find( tkp ) == r_iend ) ) continue;

    trkMap.insert( make_pair( tkp, nTracks ) );

    trkPt      ->push_back( trk.pt    () );
    trkEta     ->push_back( trk.eta   () );
    trkPhi     ->push_back( trk.phi   () );
    trkPx      ->push_back( trk.px    () );
    trkPy      ->push_back( trk.py    () );
    trkPz      ->push_back( trk.pz    () );
    trkCharge  ->push_back( trk.charge() );
    trkPFC     ->push_back( -1 );
    trkJet     ->push_back( -1 );
    trkPVtx    ->push_back( -1 );
//    trkSVtx    ->push_back( -1 );
    trkQuality ->push_back( trk.qualityMask() );
    trkNormChi2->push_back( trk.normalizedChi2() );
    trkDxy     ->push_back( trk.dxy() );
    trkDz      ->push_back( trk.dz () );

    ++nTracks;

  }

  return;

}


void PDPATToNtuple::fillPVertices() {

  // store primary vertices info

  int iObj;
  int nObj = 0;
  pvtX         ->resize( 0 );
  pvtY         ->resize( 0 );
  pvtZ         ->resize( 0 );
  pvtSxx       ->resize( 0 );
  pvtSyy       ->resize( 0 );
  pvtSzz       ->resize( 0 );
  pvtSxy       ->resize( 0 );
  pvtSxz       ->resize( 0 );
  pvtSyz       ->resize( 0 );
//  pvtCovariance->resize( 0 );
  pvtNormChi2  ->resize( 0 );
  pvtBadQuality->resize( 0 );

  nObj = vtxList.size();
  map<const Track*,int>::const_iterator it_p = trkMap.begin();
  map<const Track*,int>::const_iterator ie_p = trkMap.end();
  nPVertices = 0;
  for ( iObj = 0; iObj < nObj; ++iObj ) {

    const Vertex& vtx = *vtxList[iObj];
    const Vertex::Point& pos = vtx.position();

    bool found = false;
    try {
      Vertex::trackRef_iterator iter = vtx.tracks_begin();
      Vertex::trackRef_iterator iend = vtx.tracks_end();
      while ( iter != iend ) {
        const reco::TrackBaseRef& tkr = *iter++;
        it_p = trkMap.find( &(*tkr) );
        if ( it_p != ie_p ) {
          found = true;
          int trkIndex = it_p->second;
          int& trkLink = trkPVtx->at( trkIndex );
          if ( trkLink < 0 ) {
            trkLink = nPVertices;
            trkDxy->at( trkIndex ) = tkr->dxy( pos );
            trkDz ->at( trkIndex ) = tkr->dz ( pos );
          }
        }
      }
    }
    catch ( edm::Exception e ) {
    }

    if ( !found ) continue;

    pvtX         ->push_back( pos.X() );
    pvtY         ->push_back( pos.Y() );
    pvtZ         ->push_back( pos.Z() );
    pvtSxx       ->push_back( vtx.covariance( 0, 0 ) );
    pvtSyy       ->push_back( vtx.covariance( 1, 1 ) );
    pvtSzz       ->push_back( vtx.covariance( 2, 2 ) );
    pvtSxy       ->push_back( vtx.covariance( 0, 1 ) );
    pvtSxz       ->push_back( vtx.covariance( 0, 2 ) );
    pvtSyz       ->push_back( vtx.covariance( 1, 2 ) );
//    vector<double> covariance;
//    covariance.resize( 6 );
//    covariance[0] = vtx.covariance( 0, 0 );
//    covariance[1] = vtx.covariance( 1, 1 );
//    covariance[2] = vtx.covariance( 2, 2 );
//    covariance[3] = vtx.covariance( 0, 1 );
//    covariance[4] = vtx.covariance( 0, 2 );
//    covariance[5] = vtx.covariance( 1, 2 );
//    pvtCovariance->push_back( covariance );
    pvtNTracks   ->push_back( vtx.nTracks() );
    pvtNormChi2  ->push_back( vtx.normalizedChi2() );
    pvtBadQuality->push_back( vtx.isValid() ? 0 : ( vtx.isFake() ? 1 : 2 ) );

    ++nPVertices;

  }


  return;

}


void PDPATToNtuple::fillSVertices() {

//  currentEvBase->getByLabel( getUserParameter( "labelSVertices" ),
//                             sVertices );
  bool vSvts = sVertices.isValid();

  // store secondary vertices info

  int iObj;
  int nObj = 0;
  svtX         ->resize( 0 );
  svtY         ->resize( 0 );
  svtZ         ->resize( 0 );
  svtSxx       ->resize( 0 );
  svtSyy       ->resize( 0 );
  svtSzz       ->resize( 0 );
  svtSxy       ->resize( 0 );
  svtSxz       ->resize( 0 );
  svtSyz       ->resize( 0 );
  svtDirX      ->resize( 0 );
  svtDirY      ->resize( 0 );
  svtDirZ      ->resize( 0 );
  svtNormChi2  ->resize( 0 );
  svtMass      ->resize( 0 );
  svtDist2D    ->resize( 0 );
  svtSign2D    ->resize( 0 );
  svtDist3D    ->resize( 0 );
  svtSign3D    ->resize( 0 );
  svtJet       ->resize( 0 );
  svtNTracks   ->resize( 0 );
  svtBadQuality->resize( 0 );

  tipTrk       ->resize( 0 );
  tipSVtx      ->resize( 0 );
  tipDxy       ->resize( 0 );
  tipDz        ->resize( 0 );

  tvpTrk       ->resize( 0 );
  tvpPx        ->resize( 0 );
  tvpPy        ->resize( 0 );
  tvpPz        ->resize( 0 );

  if ( !vSvts ) {
    cout << "invalid sVertices" << endl;
    return;
  }
  else {
    nObj = sVertices->size();
  }

  map<const Jet  *,int>::const_iterator j_iter = jetMap.begin();
  map<const Jet  *,int>::const_iterator j_iend = jetMap.end();
//  map<const Track*,int>::const_iterator t_iter = trkMap.begin();
//  map<const Track*,int>::const_iterator t_iend = trkMap.end();
  nSVertices = 0;
  nTkIPs     = 0;
  nVtxPs     = 0;
  for ( iObj = 0; iObj < nObj; ++iObj ) {
    const Jet* jet = &( jets->at( iObj ) );
    j_iter = jetMap.find( jet );
    if ( j_iter == j_iend ) continue;
    const SecondaryVertexTagInfo& secVtxTagInfo = sVertices->at( iObj );
    int iVtx;
    int nVtx = secVtxTagInfo.nVertices();
    for ( iVtx = 0; iVtx < nVtx; ++iVtx ) {
      const        Vertex& vtx = secVtxTagInfo.secondaryVertex( iVtx );
      const  GlobalVector& dir = secVtxTagInfo.flightDirection( iVtx );
      const Measurement1D& d2d = secVtxTagInfo.flightDistance(  iVtx, true  );
      const Measurement1D& d3d = secVtxTagInfo.flightDistance(  iVtx, false );
      addSecondaryVertex( vtx, dir, d2d, d3d, "svtTagInfo", j_iter->second );
      if ( currentEvSetup == 0 ) continue;
      try {
        Vertex::trackRef_iterator v_iter = vtx.tracks_begin();
        Vertex::trackRef_iterator v_iend = vtx.tracks_end();
//        if ( distance( v_iter, v_iend ) <= 2 ) continue;
        edm::ESHandle<TransientTrackBuilder> builder;
        currentEvSetup->get<  TransientTrackRecord  >()
                       .get( "TransientTrackBuilder", builder );
        while ( v_iter != v_iend ) {
          const reco::TrackBaseRef& tkr = *v_iter++;
          if ( tkr->charge() != +1 ) continue;
          Vertex::trackRef_iterator w_iter = vtx.tracks_begin();
          Vertex::trackRef_iterator w_iend = vtx.tracks_end();
          while ( w_iter != w_iend ) {
            const reco::TrackBaseRef& tks = *w_iter++;
            if ( tks->charge() != -1 ) continue;
            vector<reco::TransientTrack> vTracks;
            vTracks.push_back( builder->build( &(*tkr) ) );
            vTracks.push_back( builder->build( &(*tks) ) );
            KalmanVertexFitter kvf;
            TransientVertex tVertex = kvf.vertex( vTracks );    
            if ( !tVertex.isValid() ) continue;
            Vertex vtr( tVertex );
            const  GlobalVector dir;
            const Measurement1D d2d;
            const Measurement1D d3d;
            addSecondaryVertex( vtr, dir, d2d, d3d, "svtFitPair",
                                j_iter->second );
          }
        }
      }
      catch ( edm::Exception e ) {
      }
      catch ( cms::Exception e ) {
      }
//      catch ( eventsetup::NoRecordException<T> e ) {
//      }
/*
      int currentVtxId = addSecondaryVertex( vtx, dir, d2d, d3d,
                                             "tagInfo", j_iter->second );
      std::map<const Track*,int> tipMap;
      try {
        t_iter = trkMap.begin();
        while ( t_iter != t_iend ) {
          const pair<const Track*,int>& entry = *t_iter++;
          const Track* tkp = entry.first;
          int trkIndex     = entry.second;
          tipMap.insert( make_pair( tkp, addTrackIP( trkIndex, *tkp,
                                                     currentVtxId, vtx ) ) );
        }
        map<const Track*,int>::const_iterator i_iter = tipMap.begin();
        map<const Track*,int>::const_iterator i_iend = tipMap.end();
        Vertex::trackRef_iterator v_iter = vtx.tracks_begin();
        Vertex::trackRef_iterator v_iend = vtx.tracks_end();
        while ( v_iter != v_iend ) {
          const reco::TrackBaseRef& tkr = *v_iter++;
          const Track* tkp = &(*tkr);
//          t_iter = trkMap.find( tkp );
          i_iter = tipMap.find( tkp );
          int tipTrk = ( i_iter != i_iend ? i_iter->second : -1 );
          addTrackVtxP( tipTrk, *tkp, vtx );
//          if ( it_p != ie_p ) trkSVtx->at( it_p->second ) = currentVtxId;
//          if ( tkr->charge() != +1 ) continue;
//          Vertex::trackRef_iterator jter = vtx.tracks_begin();
//          while ( jter != iend ) {
//            const reco::TrackBaseRef& tkp = *jter++;
//            if ( tkp->charge() != -1 ) continue;
//            
//          }
        }
      }
      catch ( edm::Exception e ) {
      }
*/
    }
  }

  return;

}


void PDPATToNtuple::fillGenParticles() {

  currentEvBase->getByLabel( getUserParameter( "labelGen" ),
                             particles );
  bool vGen = particles.isValid();

  // store gen particles info

  int iObj;
  int nObj = ( vGen ? particles->size() : 0 );
  genId     ->resize( nObj );
  genStatus ->resize( nObj );
  genMother ->resize( nObj );
  genPartner->resize( nObj );
  genPt     ->resize( nObj );
  genEta    ->resize( nObj );
  genPhi    ->resize( nObj );
  genPx     ->resize( nObj );
  genPy     ->resize( nObj );
  genPz     ->resize( nObj );
  genE      ->resize( nObj );
  genCharge ->resize( nObj );
  genMass   ->resize( nObj );
  if ( !vGen ) {
    cout << "invalid particles" << endl;
    return;
  }

  map<const Candidate*,int> genMap;
  nGenP = nObj;
  for ( iObj = 0; iObj < nObj; ++iObj ) {

    const GenParticle& gen = particles->at( iObj );
    genMap.insert( make_pair( &gen, iObj ) );

    genId     ->at( iObj ) = gen.pdgId();
    genStatus ->at( iObj ) = gen.status();
    genMother ->at( iObj ) = -1;
    genPartner->at( iObj ) = -1;
    genPt     ->at( iObj ) = gen.pt    ();
    genEta    ->at( iObj ) = gen.eta   ();
    genPhi    ->at( iObj ) = gen.phi   ();
    genPx     ->at( iObj ) = gen.px    ();
    genPy     ->at( iObj ) = gen.py    ();
    genPz     ->at( iObj ) = gen.pz    ();
    genE      ->at( iObj ) = gen.energy();
    genCharge ->at( iObj ) = gen.charge();
    genMass   ->at( iObj ) = gen.mass  ();

  }

  vector< vector<int> > motherTable;
  motherTable.resize( nObj );
  for ( iObj = 0; iObj < nObj; ++iObj ) {
    const GenParticle& gen = particles->at( iObj );
    int iM;
    int nM = gen.numberOfMothers();
    vector<int>& mList = motherTable[iObj];
    mList.resize( nM, -1 );
    int id;
    cout << iObj << " has " << nM << " mothers:";// << endl;
    for ( iM = 0; iM < nM; ++iM ) {
      map<const Candidate*,int>::const_iterator iter = genMap.find(
                                                       gen.mother( iM ) );
      map<const Candidate*,int>::const_iterator iend = genMap.end();
      if ( iter != iend ) mList[iM] = iter->second;
      id = ( iter != iend ? iter->second : -1 );
      cout << " " << id;
    }
    cout << endl;
    sort( mList.begin(), mList.end() );
    if ( mList.size() ) genMother->at( iObj ) = mList[0];
//    cout << "gen particle: " << iObj << " "
//                             << &(particles->at( iObj )) << " "
//                             << &gen << " " << genMother->at( iObj ) << " "
//                             << gen.mother() << endl;
  }

  map<int,int> motherMap;
  map< int, vector<int> > motherListMap;
  for ( iObj = 0; iObj < nObj; ++iObj ) {
    vector<int>& mList = motherTable[iObj];
    if ( !mList.size() ) continue;
    int fm = mList[0];
    motherMap[fm] = iObj;
    motherListMap[fm].push_back( iObj );
  }

  map<int,int>::const_iterator m_iter = motherMap.begin();
  map<int,int>::const_iterator m_iend = motherMap.end();
  int iMot;
  while ( m_iter != m_iend ) {
    const pair<int,int>& entry = *m_iter++;
    iMot = entry.first;
    iObj = entry.second;
    const vector<int>& mList = motherTable[iObj];
    int next;
    int iM;
    int nM = mList.size();
    for ( iM = 1; iM < nM; ++iM ) {
      genPartner->at( iMot ) = next = mList[iM];
      iMot = next;
    }
  }

/*
// debugging part
  map< int, vector<int> >::const_iterator ml_iter = motherListMap.begin();
  map< int, vector<int> >::const_iterator ml_iend = motherListMap.end();
  while ( ml_iter != ml_iend ) {
    const pair< int, vector<int> >& entry = *ml_iter++;
    const vector<int>& iList = entry.second;
    iObj = entry.first;
    const vector<int>& mList = motherTable[iList[0]];
    if ( iObj != mList[0] ) cout << "******** wrong map ********" << endl;
    int iM;
    int nM = iList.size();
    for ( iM = 1; iM < nM; ++iM ) {
      const vector<int>& cList = motherTable[iList[iM]];
      if ( iObj != cList[0] ) cout << "******** wrong map ********" << endl;
      if ( mList != cList ) {
        cout << "****** different mother lists ******"
             << iList[0] << " " << iList[iM] << endl;
        int i;
        int n = mList.size();
        int m = cList.size();
        for ( i = 0; i < n; ++i ) cout << " " << mList[i];
        cout << endl;
        for ( i = 0; i < m; ++i ) cout << " " << cList[i];
        cout << endl;
      }
    }
  }
*/

  return;

}


int PDPATToNtuple::addSecondaryVertex( const        Vertex& vtx,
                                       const  GlobalVector& dir,
                                       const Measurement1D& d2d,
                                       const Measurement1D& d3d,
                                       const string& type, int jetId ) {
  svtX         ->push_back( vtx.x() );
  svtY         ->push_back( vtx.y() );
  svtZ         ->push_back( vtx.z() );
  svtSxx       ->push_back( vtx.covariance( 0, 0 ) );
  svtSyy       ->push_back( vtx.covariance( 1, 1 ) );
  svtSzz       ->push_back( vtx.covariance( 2, 2 ) );
  svtSxy       ->push_back( vtx.covariance( 0, 1 ) );
  svtSxz       ->push_back( vtx.covariance( 0, 2 ) );
  svtSyz       ->push_back( vtx.covariance( 1, 2 ) );
  svtDirX      ->push_back( dir.x() );
  svtDirY      ->push_back( dir.y() );
  svtDirZ      ->push_back( dir.z() );
  svtType      ->push_back( PDEnumString::findVertexType( type ) );
  svtNTracks   ->push_back( vtx.nTracks() );
  svtNormChi2  ->push_back( vtx.normalizedChi2() );
  double vMass = 0;
  try                        { vMass = vtx.p4().M(); }
  catch ( edm::Exception e ) { vMass = -1.0; }
  svtMass      ->push_back( vMass );
  svtDist2D    ->push_back( d2d.value() );
  svtSign2D    ->push_back( d2d.significance() );
  svtDist3D    ->push_back( d3d.value() );
  svtSign3D    ->push_back( d3d.significance() );
  svtJet       ->push_back( jetId );
  svtBadQuality->push_back( vtx.isValid() ? 0 : ( vtx.isFake() ? 1 : 2 ) );

  std::map<const Track*,int> tipMap;
  map<const Track*,int>::const_iterator t_iter = trkMap.begin();
  map<const Track*,int>::const_iterator t_iend = trkMap.end();
  try {
//    t_iter = trkMap.begin();
    while ( t_iter != t_iend ) {
      const pair<const Track*,int>& entry = *t_iter++;
      const Track* tkp = entry.first;
      int trkIndex     = entry.second;
      tipMap.insert( make_pair( tkp, addTrackIP( trkIndex, *tkp,
                                                 nSVertices, vtx ) ) );
    }
    map<const Track*,int>::const_iterator i_iter = tipMap.begin();
    map<const Track*,int>::const_iterator i_iend = tipMap.end();
    Vertex::trackRef_iterator v_iter = vtx.tracks_begin();
    Vertex::trackRef_iterator v_iend = vtx.tracks_end();
    while ( v_iter != v_iend ) {
      const reco::TrackBaseRef& tkr = *v_iter++;
      const Track* tkp = &(*tkr);
      i_iter = tipMap.find( tkp );
      int tipTrk = ( i_iter != i_iend ? i_iter->second : -1 );
      addTrackVtxP( tipTrk, *tkp, vtx );
    }
  }
  catch ( edm::Exception e ) {
  }

  return nSVertices++;
}


int PDPATToNtuple::addTrackIP( int trkIndex, const reco::Track & trk,
                               int vtxIndex, const reco::Vertex& vtx ) {
  tipTrk     ->push_back( trkIndex );
  tipSVtx    ->push_back( vtxIndex );
  const Vertex::Point& pos = vtx.position();
  tipDxy     ->push_back( trk.dxy( pos ) );
  tipDz      ->push_back( trk.dz ( pos ) );
  return nTkIPs++;
}


int PDPATToNtuple::addTrackVtxP( int tipIndex, const reco::Track & trk,
                                               const reco::Vertex& vtx ) {
  tvpTrk     ->push_back( tipIndex );
//  tvpPt      ->push_back( trk.pt    () );
//  tvpEta     ->push_back( trk.eta   () );
//  tvpPhi     ->push_back( trk.phi   () );
//  const math::XYZVector& mom = trk.innerMomentum();
//  tvpPx      ->push_back( mom.X() );
//  tvpPy      ->push_back( mom.Y() );
//  tvpPz      ->push_back( mom.Z() );
  tvpPx      ->push_back( 0.0 );
  tvpPy      ->push_back( 0.0 );
  tvpPz      ->push_back( 0.0 );
  return nVtxPs++;
}


void PDPATToNtuple::linkMTracks() {

  map<const Muon*,int>::const_iterator m_iter = muoMap.begin();
  map<const Muon*,int>::const_iterator m_iend = muoMap.end();
  while ( m_iter != m_iend ) {
    const pair<const Muon*,int>& entry = *m_iter++;
    const Muon* muon = entry.first;
    int iMuon        = entry.second;
    try {
      if ( muon->pfCandidateRef().isNull() ) continue;
      const PFCandidate& pfm = *muon->pfCandidateRef();
      if ( pfm.trackRef().isNull() ) continue;
      const reco::TrackRef& trk = pfm.trackRef();
      map<const Track*,int>::const_iterator t_iter = trkMap.find( &(*trk) );
      map<const Track*,int>::const_iterator t_iend = trkMap.end();
      if ( t_iter != t_iend ) muoTrk->at( iMuon ) = t_iter->second;
    }
    catch ( edm::Exception e ) {
      cout << "muon trk lost" << endl;
    }
  }

/*
*/
/*
  int nmu = muons->size();
  int imu;
  for ( imu = 0; imu < nmu; ++imu ) {
    cout << "link muon " << imu << endl;

    const Muon& muon = muons->at( imu );
    cout << "reloaded muons: " << imu << " " << &muon << endl;
    const Candidate::LorentzVector m4 = muon.p4();
    try {
    const PFCandidate& pfm = *muon.pfCandidateRef();
    map<const Track*,int>::const_iterator it_p = trkMap.find( &(*pfm.trackRef()) );
    map<const Track*,int>::const_iterator iend = trkMap.end();
    if ( it_p != iend ) {
      const Track& gtk = generalTracks->at( it_p->second );
      float dist = sqrt( pow( m4.px() - gtk.px(), 2 ) +
                         pow( m4.py() - gtk.py(), 2 ) +
                         pow( m4.pz() - gtk.pz(), 2 ) );
      cout << "trk match: " << it_p->second << " " << dist << endl;
    }
    }
    catch ( edm::Exception e ) {
      cout << "no trk match " << endl;
    }
  }
*/
/*
*/

  return;

}

/*
void PDPATToNtuple::linkPFJets() {

  map<const Jet*,int>::const_iterator j_iter = jetMap.begin();
  map<const Jet*,int>::const_iterator j_iend = jetMap.end();
  while ( j_iter != j_iend ) {
    const pair<const Jet*,int>& entry = *j_iter++;
    const Jet* jet = entry.first;
    int iJet       = entry.second;
    map<const PFCandidate*,int>::const_iterator p_iter = pfcMap.begin();
    map<const PFCandidate*,int>::const_iterator p_iend = pfcMap.end();
    const vector<PFCandidatePtr>& jPFC = jet->getPFConstituents();
    int nPFC = jPFC.size();
    int iPFC;
    for ( iPFC = 0; iPFC < nPFC; ++iPFC ) {
      const PFCandidatePtr& pfp = jPFC.at( iPFC );
      p_iter = pfcMap.find( &(*pfp) );
      if ( p_iter != p_iend ) pfcJet->at( p_iter->second ) = iJet;
    }
  }
  return;

}
*/

void PDPATToNtuple::linkPTracks() {

  map<const PFCandidate*,int>::const_iterator p_iter = pfcMap.begin();
  map<const PFCandidate*,int>::const_iterator p_iend = pfcMap.end();
  while ( p_iter != p_iend ) {
    const pair<const PFCandidate*,int>& entry = *p_iter++;
    const PFCandidate* pfc = entry.first;
    int iPFC               = entry.second;
    if ( !pfc->charge() ) continue;
    try {
      const TrackRef& trk = pfc->trackRef();
      map<const Track*,int>::const_iterator t_iter = trkMap.find( &(*trk) );
      map<const Track*,int>::const_iterator t_iend = trkMap.end();
      if ( t_iter == t_iend ) continue;
      int iTrk = t_iter->second;
      pfcTrk->at( iPFC ) = iTrk;
      trkPFC->at( iTrk ) = iPFC;
      trkJet->at( iTrk ) = pfcJet->at( iPFC );
    }
    catch ( edm::Exception e ) {
    }
  }

  return;

}

int PDPATToNtuple::nearestHLT( PDEnumString::trigObject type,
                               double pt, double eta, double phi ) {
  int iHLT;
  int jHLT = -1;
  float dRmin = 1.0e+37;
  float dRcur;
  for ( iHLT = 0; iHLT < nHLTObjects; ++iHLT ) {
    if ( hltObjType->at( iHLT ) != type )
         continue;
    double diffEta =       eta - hltEta->at( iHLT );
    double diffPhi = fabs( phi - hltPhi->at( iHLT ) );
    while ( diffPhi > M_PI ) diffPhi -= ( 2.0 * M_PI );
    dRcur = sqrt( ( diffEta * diffEta ) + ( diffPhi * diffPhi ) );
    if ( dRcur < dRmin ) {
      jHLT = iHLT;
      dRmin = dRcur;
    }
  }
  if ( dRmin < dRmatchHLT ) {
    if ( type == PDEnumString::hltJet ) return jHLT;
    double diffPt  = ( pt - hltPt->at( jHLT ) ) /
                     ( pt + hltPt->at( jHLT ) );
    if ( fabs( diffPt ) < dPmatchHLT ) return jHLT;
  }
  return -1;
}


