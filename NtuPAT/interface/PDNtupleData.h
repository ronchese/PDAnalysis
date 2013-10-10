#ifndef PDNtupleData_H
#define PDNtupleData_H

#include <string>
#include <vector>

class PDNtupleData {

 public:

  PDNtupleData();
  virtual ~PDNtupleData();

  typedef float number;

 protected:

  // Declaration of leaf types

  // header
  unsigned int runNumber;
  unsigned int lumiSection;
  unsigned int eventNumber;

  // hlt status
  bool use_hlts;
  int nHLTStatus;
  std::vector<int >* hltPath;
  std::vector<int >* hltVersion;
  std::vector<int >* hltScale;
  std::vector<bool>* hltRun;
  std::vector<bool>* hltAccept;

  // hlt objects
  bool use_hlto;
  bool use_hlto_sphe;
  bool use_hlto_cart;
  int nHLTObjects;
  std::vector<int   >* hltObjType;
  std::vector<number>* hltPt;
  std::vector<number>* hltEta;
  std::vector<number>* hltPhi;
  std::vector<number>* hltPx;
  std::vector<number>* hltPy;
  std::vector<number>* hltPz;
  std::vector<number>* hltE;

  // beam spot
  bool use_bspot;
  number bwX;         // beam width
  number bwY;
  number bwXError;
  number bwYError;
  number bsX;         // beam spot
  number bsY;
  number bsZ;
  number bsXError;
  number bsYError;
  number bsZError;
  number bsdXdZ;      // beam slope
  number bsdYdZ;
  number bsdXdZError;
  number bsdYdZError;

  // met
  bool use_met;
  number mEt;
  number mEx;
  number mEy;
  number mEsign;

  // muons
  bool use_muons;
  bool use_muons_sphe;
  bool use_muons_cart;
  int nMuons;
  std::vector<number>* muoPt;
  std::vector<number>* muoEta;
  std::vector<number>* muoPhi;
  std::vector<number>* muoPx;
  std::vector<number>* muoPy;
  std::vector<number>* muoPz;
  std::vector<number>* muoE;
  std::vector<int   >* muoCharge;
  std::vector<int   >* muoTrk;        // track index
  std::vector<int   >* muoTrg;        // trigger object index
  std::vector<number>* muoChaIso;     //.chargedHadronIso()
  std::vector<number>* muoNeuIso;     //.neutralHadronIso()
  std::vector<number>* muoPhoIso;     //.photonIso()
  std::vector<number>* muoSumCHpt;    //.pfIsolationR04().sumChargedHadronPt
  std::vector<number>* muoSumCPpt;    //.pfIsolationR04().sumChargedParticlePt
  std::vector<number>* muoSumNHet;    //.pfIsolationR04().sumNeutralHadronEt
  std::vector<number>* muoSumPHet;    //.pfIsolationR04().sumPhotonEt
  std::vector<number>* muoSumPUpt;    //.pfIsolationR04().sumPUPt
  std::vector<number>* muoNumMatches; //.numberOfMatchedStations()
  std::vector<number>* muoDb;         //.dB()
  std::vector<int   >* muoNumValidHits; //. innerTrack()->numberOfValidHits()
  std::vector<number>* muoNormChi2;     //.globalTrack()->normalizedChi2()
  std::vector<int   >* muoNumMuHits;    //.globalTrack()->hitPattern().numberOfValidMuonHits()
  std::vector<int   >* muoNumPixHits;   //.globalTrack()->hitPattern().numberOfValidPixelHits()
  std::vector<int   >* muoNumTkHits;    //.globalTrack()->hitPattern().numberOfValidTrackerHits()

  // electrons
  bool use_electrons;
  bool use_electrons_sphe;
  bool use_electrons_cart;
  int nElectrons;
  std::vector<number>* elePt;
  std::vector<number>* eleEta;
  std::vector<number>* elePhi;
  std::vector<number>* elePx;
  std::vector<number>* elePy;
  std::vector<number>* elePz;
  std::vector<number>* eleE;
  std::vector<int   >* eleCharge;
  std::vector<int   >* eleTrk;     // track index
  std::vector<int   >* eleTrg;     // trigger object index
  std::vector<number>* eleChaIso;  //.chargedHadronIso()
  std::vector<number>* eleNeuIso;  //.neutralHadronIso()
  std::vector<number>* elePhoIso;  //.photonIso()
  std::vector<number>* eleAbsEta;  //fabs(.superCluster()->eta())
  std::vector<number>* eleAEff;
    //ElectronEffectiveArea::GetElectronEffectiveArea(
    //ElectronEffectiveArea::kEleGammaAndNeutralHadronIso03, absEta,
    //ElectronEffectiveArea::kEleEAData2011 )
  std::vector<int   >* eleID;      //.electronID( "eidMediumMC" );
  std::vector<bool  >* eleConsCha; //.isGsfCtfScPixChargeConsistent();
  std::vector<bool  >* eleEBEEGap; //.isEBEEGap();
  std::vector<number>* eleDb;      //.dB();

  // taus
  bool use_taus;
  bool use_taus_sphe;
  bool use_taus_cart;
  int nTaus;
  std::vector<number>* tauPt;
  std::vector<number>* tauEta;
  std::vector<number>* tauPhi;
  std::vector<number>* tauPx;
  std::vector<number>* tauPy;
  std::vector<number>* tauPz;
  std::vector<number>* tauE;
  std::vector<int   >* tauCharge;
  std::vector<int   >* tauTrg;     // trigger object index

  // jets
  bool use_jets;
  bool use_jets_sphe;
  bool use_jets_cart;
  int nJets;
  std::vector<number>* jetPt;
  std::vector<number>* jetEta;
  std::vector<number>* jetPhi;
  std::vector<number>* jetPx;
  std::vector<number>* jetPy;
  std::vector<number>* jetPz;
  std::vector<number>* jetE;
  std::vector<number>* jetCSV;  //.bDiscriminator( "combinedSecondaryVertexBJetTags" )
  std::vector<number>* jetTCHE; //.bDiscriminator( "trackCountingHighEffBJetTags" )
  std::vector<int   >* jetTrg;  // trigger object index
  std::vector<bool  >* jetPF;   //.isPFJet()
  std::vector<int   >* jetNDau; //.numberOfDaughters()
  std::vector<number>* jetNHF;  //.neutralHadronEnergyFraction()
  std::vector<number>* jetNEF;  //.neutralEmEnergyFraction()
  std::vector<number>* jetCHF;  //.chargedHadronEnergyFraction()
  std::vector<number>* jetCEF;  //.chargedEmEnergyFraction()
  std::vector<number>* jetNCH;  //.chargedMultiplicity()

  // particle flow
  bool use_pflow;
  bool use_pflow_sphe;
  bool use_pflow_cart;
  int nPF;
  std::vector<number>* pfcPt;
  std::vector<number>* pfcEta;
  std::vector<number>* pfcPhi;
  std::vector<number>* pfcPx;
  std::vector<number>* pfcPy;
  std::vector<number>* pfcPz;
  std::vector<number>* pfcE;
  std::vector<int   >* pfcCharge;
  std::vector<int   >* pfcJet;      //   jet index
  std::vector<int   >* pfcTrk;      // track index

  // tracks
  bool use_tracks;
  bool use_tracks_sphe;
  bool use_tracks_cart;
  int nTracks;
  std::vector<number>* trkPt;
  std::vector<number>* trkEta;
  std::vector<number>* trkPhi;
  std::vector<number>* trkPx;
  std::vector<number>* trkPy;
  std::vector<number>* trkPz;
  std::vector<int   >* trkCharge;
  std::vector<int   >* trkPFC;      // PFCandidate index
  std::vector<int   >* trkJet;      //         jet index
  std::vector<int   >* trkPVtx;     //   primary vertex index
//  std::vector<int   >* trkSVtx;     // secondary vertex index
  std::vector<int   >* trkQuality;  // qualityMask()
  std::vector<number>* trkNormChi2; // normalizedChi2()
  std::vector<number>* trkDxy;      // dxy()
  std::vector<number>* trkDz;       // dz()

  // primary vertices
  bool use_pvts;
  int nPVertices;
  std::vector<number>* pvtX;
  std::vector<number>* pvtY;
  std::vector<number>* pvtZ;
  std::vector<number>* pvtSxx;
  std::vector<number>* pvtSyy;
  std::vector<number>* pvtSzz;
  std::vector<number>* pvtSxy;
  std::vector<number>* pvtSxz;
  std::vector<number>* pvtSyz;
//  std::vector<
//  std::vector<number>
//                    >* pvtCovariance;
  std::vector<int   >* pvtNTracks;
  std::vector<number>* pvtNormChi2;
  std::vector<int   >* pvtBadQuality; // 0=good, 1=fake, 2=invalid

  // secondary vertices
  bool use_svts;
  int nSVertices;
  std::vector<number>* svtX;
  std::vector<number>* svtY;
  std::vector<number>* svtZ;
  std::vector<number>* svtSxx;
  std::vector<number>* svtSyy;
  std::vector<number>* svtSzz;
  std::vector<number>* svtSxy;
  std::vector<number>* svtSxz;
  std::vector<number>* svtSyz;
  std::vector<number>* svtDirX;
  std::vector<number>* svtDirY;
  std::vector<number>* svtDirZ;
  std::vector<int   >* svtType;
  std::vector<int   >* svtNTracks;
  std::vector<number>* svtNormChi2;
  std::vector<number>* svtMass;
  std::vector<number>* svtDist2D;
  std::vector<number>* svtSign2D;
  std::vector<number>* svtDist3D;
  std::vector<number>* svtSign3D;
  std::vector<int   >* svtJet;
  std::vector<int   >* svtBadQuality; // 0=good, 1=fake, 2=invalid

  // impact parameters
  bool use_tkips;
  int nTkIPs;
  std::vector<int   >* tipTrk;      // track index
  std::vector<int   >* tipSVtx;     // secondary vertex index
  std::vector<number>* tipDxy;      // dxy()
  std::vector<number>* tipDz;       // dz()

  // momenta at vertices
  bool use_vtxps;
  bool use_vtxps_sphe;
  bool use_vtxps_cart;
  int nVtxPs;
  std::vector<int   >* tvpTrk;      // impact parameter index
  std::vector<number>* tvpPt;
  std::vector<number>* tvpEta;
  std::vector<number>* tvpPhi;
  std::vector<number>* tvpPx;
  std::vector<number>* tvpPy;
  std::vector<number>* tvpPz;

  // gen particles
  bool use_gen;
  bool use_gen_sphe;
  bool use_gen_cart;
  int nGenP;
  std::vector<int   >* genId;
  std::vector<int   >* genStatus;
  std::vector<int   >* genMother;  // mother  index
  std::vector<int   >* genPartner; // partner index
  std::vector<number>* genPt;
  std::vector<number>* genEta;
  std::vector<number>* genPhi;
  std::vector<number>* genPx;
  std::vector<number>* genPy;
  std::vector<number>* genPz;
  std::vector<number>* genE;
  std::vector<int   >* genCharge;
  std::vector<number>* genMass;

 private:

  PDNtupleData( const PDNtupleData& td );
  PDNtupleData& operator=( const PDNtupleData& td );

};

#endif

