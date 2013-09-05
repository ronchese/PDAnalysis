#include <iostream>

#include "PDAnalysis/NtuPAT/interface/PDNtupleData.h"

PDNtupleData::PDNtupleData() {

  // hlt status
  use_hlts = false;
  hltPath         = new std::vector<int >;
  hltVersion      = new std::vector<int >;
  hltScale        = new std::vector<int >;
  hltRun          = new std::vector<bool>;
  hltAccept       = new std::vector<bool>;

  // hlt objects
  use_hlto      = false;
  use_hlto_sphe = true;
  use_hlto_cart = false;
  hltObjType      = new std::vector<int   >;
  hltPt           = new std::vector<number>;
  hltEta          = new std::vector<number>;
  hltPhi          = new std::vector<number>;
  hltPx           = new std::vector<number>;
  hltPy           = new std::vector<number>;
  hltPz           = new std::vector<number>;
  hltE            = new std::vector<number>;

  // beam spot
  use_bspot = false;

  // met
  use_met = false;

  // muons
  use_muons      = false;
  use_muons_sphe = true;
  use_muons_cart = false;
  nMuons = 0;
  muoPt           = new std::vector<number>;
  muoEta          = new std::vector<number>;
  muoPhi          = new std::vector<number>;
  muoPx           = new std::vector<number>;
  muoPy           = new std::vector<number>;
  muoPz           = new std::vector<number>;
  muoE            = new std::vector<number>;
  muoCharge       = new std::vector<int   >;
  muoTrk          = new std::vector<int   >;
  muoTrg          = new std::vector<int   >;
  muoChaIso       = new std::vector<number>;
  muoNeuIso       = new std::vector<number>;
  muoPhoIso       = new std::vector<number>;
  muoSumCHpt      = new std::vector<number>;
  muoSumCPpt      = new std::vector<number>;
  muoSumNHet      = new std::vector<number>;
  muoSumPHet      = new std::vector<number>;
  muoSumPUpt      = new std::vector<number>;
  muoNumMatches   = new std::vector<number>;
  muoDb           = new std::vector<number>;
  muoNumValidHits = new std::vector<int   >;
  muoNormChi2     = new std::vector<number>;
  muoNumMuHits    = new std::vector<int   >;
  muoNumPixHits   = new std::vector<int   >;
  muoNumTkHits    = new std::vector<int   >;

  // electrons
  use_electrons      = false;
  use_electrons_sphe = true;
  use_electrons_cart = false;
  nElectrons = 0;
  elePt           = new std::vector<number>;
  eleEta          = new std::vector<number>;
  elePhi          = new std::vector<number>;
  elePx           = new std::vector<number>;
  elePy           = new std::vector<number>;
  elePz           = new std::vector<number>;
  eleE            = new std::vector<number>;
  eleCharge       = new std::vector<int   >;
  eleTrk          = new std::vector<int   >;
  eleTrg          = new std::vector<int   >;
  eleChaIso       = new std::vector<number>;
  eleNeuIso       = new std::vector<number>;
  elePhoIso       = new std::vector<number>;
  eleAbsEta       = new std::vector<number>;
  eleAEff         = new std::vector<number>;
  eleID           = new std::vector<int   >;
  eleConsCha      = new std::vector<bool  >;
  eleEBEEGap      = new std::vector<bool  >;
  eleDb           = new std::vector<number>;

  // taus
  use_taus      = false;
  use_taus_sphe = true;
  use_taus_cart = false;
  nTaus = 0;
  tauPt           = new std::vector<number>;
  tauEta          = new std::vector<number>;
  tauPhi          = new std::vector<number>;
  tauPx           = new std::vector<number>;
  tauPy           = new std::vector<number>;
  tauPz           = new std::vector<number>;
  tauE            = new std::vector<number>;
  tauCharge       = new std::vector<int   >;
  tauTrg          = new std::vector<int   >;

  // jets
  use_jets      = false;
  use_jets_sphe = true;
  use_jets_cart = false;
  nJets = 0;
  jetPt           = new std::vector<number>;
  jetEta          = new std::vector<number>;
  jetPhi          = new std::vector<number>;
  jetPx           = new std::vector<number>;
  jetPy           = new std::vector<number>;
  jetPz           = new std::vector<number>;
  jetE            = new std::vector<number>;
  jetCSV          = new std::vector<number>;
  jetTCHE         = new std::vector<number>;
  jetTrg          = new std::vector<int   >;
  jetPF           = new std::vector<bool  >;
  jetNDau         = new std::vector<int   >;
  jetNHF          = new std::vector<number>;
  jetNEF          = new std::vector<number>;
  jetCHF          = new std::vector<number>;
  jetCEF          = new std::vector<number>;
  jetNCH          = new std::vector<number>;

  // particle flow
  use_pflow      = false;
  use_pflow_sphe = true;
  use_pflow_cart = false;
  nPF = 0;
  pfcPt           = new std::vector<number>;
  pfcEta          = new std::vector<number>;
  pfcPhi          = new std::vector<number>;
  pfcPx           = new std::vector<number>;
  pfcPy           = new std::vector<number>;
  pfcPz           = new std::vector<number>;
  pfcE            = new std::vector<number>;
  pfcCharge       = new std::vector<int   >;
  pfcJet          = new std::vector<int   >;
  pfcTrk          = new std::vector<int   >;

  // tracks
  use_tracks      = false;
  use_tracks_sphe = true;
  use_tracks_cart = false;
  nTracks = 0;
  trkPt           = new std::vector<number>;
  trkEta          = new std::vector<number>;
  trkPhi          = new std::vector<number>;
  trkPx           = new std::vector<number>;
  trkPy           = new std::vector<number>;
  trkPz           = new std::vector<number>;
  trkCharge       = new std::vector<int   >;
  trkPFC          = new std::vector<int   >;
  trkJet          = new std::vector<int   >;
  trkPVtx         = new std::vector<int   >;
//  trkSVtx         = new std::vector<int   >;
  trkQuality      = new std::vector<int   >;
  trkNormChi2     = new std::vector<number>;
  trkDxy          = new std::vector<number>;
  trkDz           = new std::vector<number>;

  // primary vertices
  use_pvts =  false;
  nPVertices = 0;
  pvtX            = new std::vector<number>;
  pvtY            = new std::vector<number>;
  pvtZ            = new std::vector<number>;
  pvtSxx          = new std::vector<number>;
  pvtSyy          = new std::vector<number>;
  pvtSzz          = new std::vector<number>;
  pvtSxy          = new std::vector<number>;
  pvtSxz          = new std::vector<number>;
  pvtSyz          = new std::vector<number>;
//  pvtCovariance   = new std::vector<
//                        std::vector<number>
//                                          >;
  pvtNTracks      = new std::vector<int   >;
  pvtNormChi2     = new std::vector<number>;
  pvtBadQuality   = new std::vector<int   >;

  // secondary vertices
  use_svts = false;
  nSVertices = 0;
  svtX          = new std::vector<number>;
  svtY          = new std::vector<number>;
  svtZ          = new std::vector<number>;
  svtSxx        = new std::vector<number>;
  svtSyy        = new std::vector<number>;
  svtSzz        = new std::vector<number>;
  svtSxy        = new std::vector<number>;
  svtSxz        = new std::vector<number>;
  svtSyz        = new std::vector<number>;
  svtDirX       = new std::vector<number>;
  svtDirY       = new std::vector<number>;
  svtDirZ       = new std::vector<number>;
  svtType       = new std::vector<int   >;
  svtNTracks    = new std::vector<int   >;
  svtNormChi2   = new std::vector<number>;
  svtMass       = new std::vector<number>;
  svtDist2D     = new std::vector<number>;
  svtSign2D     = new std::vector<number>;
  svtDist3D     = new std::vector<number>;
  svtSign3D     = new std::vector<number>;
  svtJet        = new std::vector<int   >;
  svtBadQuality = new std::vector<int   >;

  // impact parameters
  use_tkips = false;
  nTkIPs = 0;
  tipTrk          = new std::vector<int   >;
  tipSVtx         = new std::vector<int   >;
  tipDxy          = new std::vector<number>;
  tipDz           = new std::vector<number>;

  // momenta at vertices
  use_vtxps      = false;
  use_vtxps_sphe = true;
  use_vtxps_cart = false;
  nVtxPs = 0;
  tvpTrk          = new std::vector<int   >;
  tvpPt           = new std::vector<number>;
  tvpEta          = new std::vector<number>;
  tvpPhi          = new std::vector<number>;
  tvpPx           = new std::vector<number>;
  tvpPy           = new std::vector<number>;
  tvpPz           = new std::vector<number>;

  // gen particles
  use_gen      = false;
  use_gen_sphe = true;
  use_gen_cart = false;
  nGenP = 0;
  genId           = new std::vector<int   >;
  genStatus       = new std::vector<int   >;
  genMother       = new std::vector<int   >;
  genPt           = new std::vector<number>;
  genEta          = new std::vector<number>;
  genPhi          = new std::vector<number>;
  genPx           = new std::vector<number>;
  genPy           = new std::vector<number>;
  genPz           = new std::vector<number>;
  genE            = new std::vector<number>;
  genCharge       = new std::vector<int   >;
  genMass         = new std::vector<number>;

}

PDNtupleData::~PDNtupleData() {
}


