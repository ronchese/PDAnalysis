
#ifndef PDPATAnalyzer_h
#define PDPATAnalyzer_h

#include "PDAnalysis/NtuPAT/interface/PDPATToNtuple.h"

#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"

#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include <string>
#include <iostream>
#include <fstream>

//
// class declaration
//

class PDPATAnalyzer: public edm::EDAnalyzer,
                      public PDPATToNtuple {

 public:

  explicit PDPATAnalyzer( const edm::ParameterSet& ps );
  ~PDPATAnalyzer();

  static void fillDescriptions( edm::ConfigurationDescriptions& descriptions );
  virtual void beginJob();
  virtual void endJob();

 private:

  int analyzedFile;
  std::string histName;

  virtual void beginRun( const edm::Run& run , const edm::EventSetup& es );
  virtual void endRun(   const edm::Run& run , const edm::EventSetup& es );
  virtual void analyze(  const edm::Event& ev, const edm::EventSetup& es );

};

#endif
