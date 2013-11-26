#ifndef PDEnumString_H
#define PDEnumString_H

#include <map>
#include <string>

class PDEnumString {

 public:

  PDEnumString();
  virtual ~PDEnumString();

//  enum trigPath   { dummy = 0 };
  enum trigPath   { HLT_Mu17_Mu8_v = 1,
                    HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v,
                    HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v,
                    HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v,
                    HLT_IsoMu24_v,
                    HLT_IsoMu24_eta2p1_v,
                    HLT_Ele27_WP80_v,
                    HLT_Ele25_CaloIdVT_CaloIsoVL_TrkIdVL_TrkIsoT_TriCentralPFNoPUJet30_v };
//  enum trigPath   { HLT_Mu40_eta2p1_v = 1,
//                    HLT_Mu12_eta2p1_DiCentral_40_20_DiBTagIP3D1stTrack_v,
//                    HLT_Mu12_eta2p1_DiCentral_40_20_BTagIP3D1stTrack_v,
//                    HLT_Mu12_eta2p1_DiCentral_40_20_v,
//                    HLT_Mu12_eta2p1_DiCentral_20_v,
//                    HLT_Mu12_eta2p1_L1Mu10erJetC12WdEtaPhi1DiJetsC_v,
//                    HLT_Mu12_DoubleCentralJet65_v,
//                    HLT_Mu12_v,
//                    HLT_Mu15_eta2p1_TriCentral_40_20_20_DiBTagIP3D1stTrack_v,
//                    HLT_Mu15_eta2p1_TriCentral_40_20_20_BTagIP3D1stTrack_v,
//                    HLT_Mu15_eta2p1_TriCentral_40_20_20_v,
//                    HLT_Mu15_eta2p1_L1Mu10erJetC12WdEtaPhi1DiJetsC_v,
//                    HLT_DoubleMu4_Jpsi_Displaced_v,
//                    HLT_DoubleMu4_JpsiTk_Displaced_v,
//                    HLT_DoubleMu3p5_LowMassNonResonant_Displaced_v,
//                    HLT_DoubleMu3p5_LowMass_Displaced_v,
//                    HLT_DoubleDisplacedMu4_DiPFJet40Neutral_v };
  enum trigObject { hltJet = 1,
                    hltMuon,
                    hltElectron,
                    hltTau };
  enum recoObject { recJet = 1,
                    recMuon,
                    recElectron,
                    recTau };
  enum infoType   { puBeta = 1,
                    puBetaStar };
  enum vertexType { svtTagInfo = 1,
                    svtFitPair };

  static void  resetTrigMap();
  static void revertTrigMap();
  static const std::map<int,std::string>& trigMap();
  static std::string trigBase( const std::string& trigPath );

  static int                findTrigPath  ( const std::string& trigPath,
                                            bool fixedList = true,
                                            int code = -1 );
  static const std::string& findTrigPath  ( int                trigPath   );
  static int                findTrigObject( const std::string& trigObject );
  static const std::string& findTrigObject( int                trigObject );
  static int                findRecoObject( const std::string& recoObject );
  static const std::string& findRecoObject( int                recoObject );
  static int                findRecoUIType( const std::string& recoUIType );
  static const std::string& findRecoUIType( int                recoUIType );
  static int                findVertexType( const std::string& vtxType    );
  static const std::string& findVertexType( int                vtxType    );

 private:

  static std::string defaultString;
  static std::map<int,std::string> trigPathMapIS;
  static std::map<std::string,int> trigPathMapSI;
  static std::map<int,std::string> trigObjectMapIS;
  static std::map<std::string,int> trigObjectMapSI;
  static std::map<int,std::string> recoObjectMapIS;
  static std::map<std::string,int> recoObjectMapSI;
  static std::map<int,std::string> recoUITypeMapIS;
  static std::map<std::string,int> recoUITypeMapSI;
  static std::map<int,std::string> vertexTypeMapIS;
  static std::map<std::string,int> vertexTypeMapSI;

  static void revertMap( const std::map<std::string,int>& mapSI,
                               std::map<int,std::string>& mapIS );

};


#endif

