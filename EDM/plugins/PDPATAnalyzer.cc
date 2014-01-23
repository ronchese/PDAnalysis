#include "PDAnalysis/EDM/plugins/PDPATAnalyzer.h"

// system include files
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/MET.h"

#include "TFile.h"

PDPATAnalyzer::PDPATAnalyzer( const edm::ParameterSet& ps ):
  PDPATToNtuple( ps ) {
  histName = ps.getUntrackedParameter<std::string>( "histName" );
}

PDPATAnalyzer::~PDPATAnalyzer() {
}

void PDPATAnalyzer::beginJob() {
  PDPATToNtuple::beginJob();
  analyzedFile = 0;
  return;
}

void PDPATAnalyzer::endJob()  {
  PDPATToNtuple::endJob();
  TreeWrapper::save( histName );
  return;
}

void PDPATAnalyzer::fillDescriptions( edm::ConfigurationDescriptions&
                                           descriptions ) {
  // The following says we do not know what parameters are allowed 
  // so do no validation
  // Please change this to state exactly what you do use, even 
  // if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault( desc );
  return;
}


void PDPATAnalyzer::beginRun( const edm::Run& run,
                              const edm::EventSetup& es ) {
  currentRun     = &run;
  currentEvSetup = &es;
  PDPATToNtuple::beginRun();
  return;
}


void PDPATAnalyzer::endRun(   const edm::Run& run,
                              const edm::EventSetup& es ) {
  PDPATToNtuple::endRun();
  return;
}


void PDPATAnalyzer::analyze( const edm::Event& ev,
                             const edm::EventSetup& es ) {
  currentEvent   = &ev;
  currentEvSetup = &es;
  int ientry = 0;
  PDPATToNtuple::analyze( ev, ientry, analyzedFile++ );
  return;
}

//define this as a plug-in
DEFINE_FWK_MODULE( PDPATAnalyzer );
