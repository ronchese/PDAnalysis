#ifndef PDPATToNtuple_h
#define PDPATToNtuple_h

#include "PDAnalysis/Ntu/interface/PDNtuple.h"
#include "PDAnalysis/Ntu/interface/PDAnalyzerFW.h"
#include "PDAnalysis/Ntu/interface/PDEnumString.h"

#include "NtuTool/Common/interface/TreeWriter.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/GeometryVector/interface/GlobalVector.h"
#include "DataFormats/GeometryCommonDetAlgo/interface/Measurement1D.h"

#include <string>
#include <vector>
class TFile;

namespace edm {
  class TriggerResults;
  class TriggerNames;
  class LumiReWeighting;
}

namespace pat {
  class TriggerEvent;
  class MET;
  class Muon;
  class Electron;
  class Tau;
//  class PFParticle;
  class Jet;
}

namespace reco {
  class BeamSpot;
  class PFCandidate;
  class Track;
  class Vertex;
  class SecondaryVertexTagInfo;
  class GenParticle;
  class GenJet;
  class Candidate;
}

class HLTConfigProvider;
class PileupSummaryInfo;

class PDPATToNtuple: public PDAnalyzer,
                     public TreeWriter {

 public:

  PDPATToNtuple( const edm::ParameterSet& ps );
  virtual ~PDPATToNtuple();

  virtual void beginJob();
  virtual void beginRun();
  virtual void openNtuple( const std::string& ntuName );
  virtual void analyze( const edm::EventBase& ev,
                        int ientry, int event_file );
  virtual void read( const edm::EventBase& ev );
  virtual void writeNtuple();
  virtual void closeNtuple();
  virtual void endRun();
  virtual void endJob();

 private:

  std::string ntuName;
  TFile* file;

  template<class PATObject> class CompareByPt {
   public:
    bool operator()( const PATObject* l, const PATObject* r ) {
      return l->pt() > r->pt();
    }
  };

  std::string labelTrigResults;
  std::string labelTrigEvent;
  std::string labelBeamSpot;
  std::string labelMets;
  std::string labelMuons;
  std::string labelElectrons;
  std::string labelTaus;
  std::string labelJets;
  std::string labelPFCandidates;
  std::string labelGeneralTracks;
  std::string labelPVertices;
  std::string labelSVertices;
  std::string labelPUInfo;
  std::string labelGen;
  std::string labelGPJ;

  bool selectAssociatedPF;
  bool selectAssociatedTk;
  bool recoverMuonTracks;
  bool writeAllPrimaryVertices;

  bool read_hlts;
  bool read_hlto;
  bool read_bspot;
  bool read_met;
  bool read_muons;
  bool read_electrons;
  bool read_taus;
  bool read_jets;
  bool read_pflow;
  bool read_tracks;
  bool read_pvts;
  bool read_svts;
  bool read_puwgt;
  bool read_gen;
  bool read_gpj;

  edm::Handle< edm::TriggerResults                       > trigResults;
  edm::Handle< pat::TriggerEvent                         > trigEvent;
  edm::Handle< reco::BeamSpot                            > beamSpot;
  edm::Handle< std::vector<pat::MET                    > > mets;
  edm::Handle< std::vector<pat::Muon                   > > muons;
  edm::Handle< std::vector<pat::Electron               > > electrons;
  edm::Handle< std::vector<pat::Tau                    > > taus;
  edm::Handle< std::vector<pat::Jet                    > > jets;
//  edm::Handle< std::vector<pat::PFParticle             > > pfParticles;
  edm::Handle< std::vector<reco::PFCandidate           > > pfCandidates;
  edm::Handle< std::vector<reco::Track                 > > generalTracks;
  edm::Handle< std::vector<reco::Vertex                > > pVertices;
  edm::Handle< std::vector<reco::SecondaryVertexTagInfo> > sVertices;
  edm::Handle< std::vector<PileupSummaryInfo           > > PUInfo;
  edm::Handle< std::vector<reco::GenParticle           > > genParticles;
  edm::Handle< std::vector<reco::GenJet                > > genJets;

//  edm::InputTag genjets_;

  const edm::TriggerNames* triggerNames;
  std::vector<std::string> savedTriggerPaths;
  std::vector<std::string> savedTriggerObjects;
  std::vector<std::string> savedJetInfo;
  HLTConfigProvider* hltConfigProvider;

  std::vector<double> puWgt_mc;
  std::vector<double> puWgt_data;
  edm::LumiReWeighting* LumiWeights;

  bool fixedTrigPathList;
  int lastTrigMapSize;

  float jetPtMin;
  float jetEtaMax;
  float trkDzMax;
  float trkPtMin;
  float trkEtaMax;

  float dRmatchHLT;
  float dPmatchHLT;

  std::map<const pat::Muon        *,int> muoMap;
  std::map<const pat::Electron    *,int> eleMap;
  std::map<const pat::Tau         *,int> tauMap;
  std::map<const pat::Jet         *,int> jetMap;
  std::map<const reco::PFCandidate*,int> pcjMap;
  std::map<const reco::PFCandidate*,int> pfcMap;
  std::map<const reco::Track      *,int> tkmMap;
  std::map<const reco::Track      *,int> tkeMap;
  std::map<const reco::Track      *,int> tkpMap;
  std::map<const reco::Track      *,int> ptjMap;
  std::map<const reco::Track      *,int> tkvMap;
  std::map<const reco::Track      *,int> trkMap;
  std::map<const reco::Candidate  *,int> genMap;
  std::map<const reco::GenJet     *,int> gpjMap;
  std::set<const reco::Track      *    > tkrSet;
  std::set<const reco::Track      *    > allPTk;
  std::vector<const reco::Track *> muoGTrk;
  std::vector<const reco::Vertex*> vtxList;

  bool dumpNtuple;
  void fillHLTStatus   ();
  void fillHLTObjects  ();
  void fillBeamSpot    ();
  void fillMet         ();
  void fillMuons       ();
  void fillElectrons   ();
  void fillTaus        ();
  void fillJets        ();
  void fillVtxTrkMap   ();
  void fillPFCandidates();
  void fillTracks      ();
  void fillPVertices   ();
  void fillSVertices   ();
  void fillPUWeight    ();
  void fillGenParticles();
  void fillGenJets     ();
//  void fillUserInfo( PDEnumString::recoObject obj, int index,
//                     PDEnumString::infoType info , number value );
  void fillUserInfo( int obj, int index,
                     int info , number value );

  int addSecondaryVertex( const reco::Vertex& vtx,
                          const  GlobalVector& dir,
                          const Measurement1D& d2d,
                          const Measurement1D& d3d,
                          const std::string& type, int jetId );
  int addTrackIP(   int trkIndex, const reco::Track & trk,
                    int vtxIndex, const reco::Vertex& vtx );
  int addTrackVtxP( int tipIndex, const reco::Track & trk,
                                  const reco::Vertex& vtx );

  void linkMTracks();
//  void linkPFJets ();
  void linkPTracks();

  int nearestHLT( PDEnumString::trigObject type,
                  double pt, double eta, double phi );

  bool wildMatch( const std::string& name, std::string model );

};

#endif
