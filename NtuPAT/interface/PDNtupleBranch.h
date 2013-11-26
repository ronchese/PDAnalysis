#ifndef PDNtupleBranch_H
#define PDNtupleBranch_H

#include "PDAnalysis/NtuPAT/interface/PDNtupleData.h"
#include <string>
#include <vector>

class TBranch;

template <class T>
class PDNtupleBranch: public virtual PDNtupleData, public virtual T {

 public:

  PDNtupleBranch();
  virtual ~PDNtupleBranch();

  void initTree();

 protected:

  std::string numberType;

  // List of branches

  // header
  TBranch* b_runNumber;
  TBranch* b_lumiSection;
  TBranch* b_eventNumber;

  // hlt path names
  void setBranches_hltlist();
  TBranch* b_nHLTPaths;
  TBranch* b_hltCode;
  TBranch* b_hltName;

  // hlt status
  void setBranches_hlts();
  TBranch* b_nHLTStatus;
  TBranch* b_hltPath;
  TBranch* b_hltVersion;
  TBranch* b_hltScale;
  TBranch* b_hltRun;
  TBranch* b_hltAccept;

  // hlt objects
  void setBranches_hlto();
  TBranch* b_nHLTObjects;
  TBranch* b_hltObjType;
  TBranch* b_hltPt;
  TBranch* b_hltEta;
  TBranch* b_hltPhi;
  TBranch* b_hltPx;
  TBranch* b_hltPy;
  TBranch* b_hltPz;
  TBranch* b_hltE;

  // beam spot
  void setBranches_bspot();
  TBranch* b_bwX;         // beam width
  TBranch* b_bwY;
  TBranch* b_bwXError;
  TBranch* b_bwYError;
  TBranch* b_bsX;         // beam spot
  TBranch* b_bsY;
  TBranch* b_bsZ;
  TBranch* b_bsXError;
  TBranch* b_bsYError;
  TBranch* b_bsZError;
  TBranch* b_bsdXdZ;      // beam slope
  TBranch* b_bsdYdZ;
  TBranch* b_bsdXdZError;
  TBranch* b_bsdYdZError;

  // met
  void setBranches_met();
  TBranch* b_mEt;
  TBranch* b_mEx;
  TBranch* b_mEy;
  TBranch* b_mEsign;

  // muons
  void setBranches_muons();
  TBranch* b_nMuons;
  TBranch* b_muoPt;
  TBranch* b_muoEta;
  TBranch* b_muoPhi;
  TBranch* b_muoPx;
  TBranch* b_muoPy;
  TBranch* b_muoPz;
  TBranch* b_muoE;
  TBranch* b_muoCharge;
  TBranch* b_muoTrk;
  TBranch* b_muoTrg;
  TBranch* b_muoChaIso;
  TBranch* b_muoNeuIso;
  TBranch* b_muoPhoIso;
  TBranch* b_muoSumCHpt;
  TBranch* b_muoSumCPpt;
  TBranch* b_muoSumNHet;
  TBranch* b_muoSumPHet;
  TBranch* b_muoSumPUpt;
  TBranch* b_muoNumMatches;
  TBranch* b_muoDb;
  TBranch* b_muoNumValidHits;
  TBranch* b_muoNormChi2;
  TBranch* b_muoNumMuHits;
  TBranch* b_muoNumPixHits;
  TBranch* b_muoNumTkHits;

  // electrons
  void setBranches_electrons();
  TBranch* b_nElectrons;
  TBranch* b_elePt;
  TBranch* b_eleEta;
  TBranch* b_elePhi;
  TBranch* b_elePx;
  TBranch* b_elePy;
  TBranch* b_elePz;
  TBranch* b_eleE;
  TBranch* b_eleCharge;
  TBranch* b_eleTrk;
  TBranch* b_eleTrg;
  TBranch* b_eleChaIso;
  TBranch* b_eleNeuIso;
  TBranch* b_elePhoIso;
  TBranch* b_elePCHIso;
  TBranch* b_eleAbsEta;
  TBranch* b_eleAEff;
  TBranch* b_eleID;
  TBranch* b_eleConsCha;
  TBranch* b_eleEBEEGap;
  TBranch* b_eleDb;

  // taus
  void setBranches_taus();
  TBranch* b_nTaus;
  TBranch* b_tauPt;
  TBranch* b_tauEta;
  TBranch* b_tauPhi;
  TBranch* b_tauPx;
  TBranch* b_tauPy;
  TBranch* b_tauPz;
  TBranch* b_tauE;
  TBranch* b_tauCharge;
  TBranch* b_tauTrg;

  // jets
  void setBranches_jets();
  TBranch* b_nJets;
  TBranch* b_jetPt;
  TBranch* b_jetEta;
  TBranch* b_jetPhi;
  TBranch* b_jetPx;
  TBranch* b_jetPy;
  TBranch* b_jetPz;
  TBranch* b_jetE;
  TBranch* b_jetCSV;
  TBranch* b_jetTCHE;
  TBranch* b_jetTrg;
  TBranch* b_jetPF;
  TBranch* b_jetNDau;
  TBranch* b_jetNHF;
  TBranch* b_jetNEF;
  TBranch* b_jetCHF;
  TBranch* b_jetCEF;
  TBranch* b_jetNCH;

  // user info
  void setBranches_userinfo();
  TBranch* b_nUserInfo;
  TBranch* b_useObjType;
  TBranch* b_useObjIndex;
  TBranch* b_useInfoType;
  TBranch* b_useInfoValue;

  // particle flow
  void setBranches_pflow();
  TBranch* b_nPF;
  TBranch* b_pfcPt;
  TBranch* b_pfcEta;
  TBranch* b_pfcPhi;
  TBranch* b_pfcPx;
  TBranch* b_pfcPy;
  TBranch* b_pfcPz;
  TBranch* b_pfcE;
  TBranch* b_pfcCharge;
  TBranch* b_pfcJet;
  TBranch* b_pfcTrk;

  // tracks
  void setBranches_tracks();
  TBranch* b_nTracks;
  TBranch* b_trkPt;
  TBranch* b_trkEta;
  TBranch* b_trkPhi;
  TBranch* b_trkPx;
  TBranch* b_trkPy;
  TBranch* b_trkPz;
  TBranch* b_trkCharge;
  TBranch* b_trkPFC;
  TBranch* b_trkJet;
  TBranch* b_trkPVtx;
//  TBranch* b_trkSVtx;
  TBranch* b_trkQuality;
  TBranch* b_trkNormChi2;
  TBranch* b_trkDxy;
  TBranch* b_trkDz;

  // primary vertices
  void setBranches_pVertices();
  TBranch* b_nPVTotal;
  TBranch* b_nPVertices;
  TBranch* b_pvtX;
  TBranch* b_pvtY;
  TBranch* b_pvtZ;
  TBranch* b_pvtSxx;
  TBranch* b_pvtSyy;
  TBranch* b_pvtSzz;
  TBranch* b_pvtSxy;
  TBranch* b_pvtSxz;
  TBranch* b_pvtSyz;
//  TBranch* b_pvtCovariance;
  TBranch* b_pvtNTracks;
  TBranch* b_pvtNormChi2;
  TBranch* b_pvtBadQuality;

  // secondary vertices
  void setBranches_sVertices();
  TBranch* b_nSVertices;
  TBranch* b_svtX;
  TBranch* b_svtY;
  TBranch* b_svtZ;
  TBranch* b_svtSxx;
  TBranch* b_svtSyy;
  TBranch* b_svtSzz;
  TBranch* b_svtSxy;
  TBranch* b_svtSxz;
  TBranch* b_svtSyz;
  TBranch* b_svtDirX;
  TBranch* b_svtDirY;
  TBranch* b_svtDirZ;
  TBranch* b_svtType;
  TBranch* b_svtNTracks;
  TBranch* b_svtNormChi2;
  TBranch* b_svtMass;
  TBranch* b_svtDist2D;
  TBranch* b_svtSign2D;
  TBranch* b_svtDist3D;
  TBranch* b_svtSign3D;
  TBranch* b_svtJet;
  TBranch* b_svtBadQuality;

  // impact parameters
  void setBranches_tkips();
  TBranch* b_nTkIPs;
  TBranch* b_tipTrk;
  TBranch* b_tipSVtx;
  TBranch* b_tipDxy;
  TBranch* b_tipDz;

  // momenta at vertices
  void setBranches_vtxps();
  TBranch* b_nVtxPs;
  TBranch* b_tvpTrk;
  TBranch* b_tvpPt;
  TBranch* b_tvpEta;
  TBranch* b_tvpPhi;
  TBranch* b_tvpPx;
  TBranch* b_tvpPy;
  TBranch* b_tvpPz;

  // PU weight
  void setBranches_puwgt();
  TBranch* b_puWeight;

  // gen particles
  void setBranches_gen();
  TBranch* b_nGenP;
  TBranch* b_genId;
  TBranch* b_genStatus;
  TBranch* b_genMother;
  TBranch* b_genPartner;
  TBranch* b_genPt;
  TBranch* b_genEta;
  TBranch* b_genPhi;
  TBranch* b_genPx;
  TBranch* b_genPy;
  TBranch* b_genPz;
  TBranch* b_genE;
  TBranch* b_genCharge;
  TBranch* b_genMass;
//  TBranch* b_genJet;

  // gen jets
  void setBranches_gpj();
  TBranch* b_nGenJets;
  TBranch* b_gpjPt;
  TBranch* b_gpjEta;
  TBranch* b_gpjPhi;
  TBranch* b_gpjPx;
  TBranch* b_gpjPy;
  TBranch* b_gpjPz;
  TBranch* b_gpjE;
  TBranch* b_gpjNDau;
  TBranch* b_gpjReco;

 private:

  PDNtupleBranch( const PDNtupleBranch& td );
  PDNtupleBranch& operator=( const PDNtupleBranch& td );

  const char* bCat( const std::string& name, const std::string& type );

};

#include "PDNtupleBranch.icc"

#endif

