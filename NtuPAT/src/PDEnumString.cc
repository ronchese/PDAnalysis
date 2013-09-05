#include "PDAnalysis/NtuPAT/interface/PDEnumString.h"

#include <iostream>

std::string PDEnumString::defaultString;
std::map<int,std::string> PDEnumString::trigObjectMapIS;
std::map<std::string,int> PDEnumString::trigObjectMapSI;
std::map<int,std::string> PDEnumString::trigPathMapIS;
std::map<std::string,int> PDEnumString::trigPathMapSI;
std::map<int,std::string> PDEnumString::vertexTypeMapIS;
std::map<std::string,int> PDEnumString::vertexTypeMapSI;

static PDEnumString pdEnumString;

PDEnumString::PDEnumString() {

  defaultString = "";

  trigObjectMapSI.clear();
  trigObjectMapSI.insert( std::make_pair( "hltJet"     ,
                                           hltJet       ) );
  trigObjectMapSI.insert( std::make_pair( "hltMuon"    ,
                                           hltMuon      ) );
  trigObjectMapSI.insert( std::make_pair( "hltElectron",
                                           hltElectron  ) );
  trigObjectMapSI.insert( std::make_pair( "hltTau"     ,
                                           hltTau       ) );
  revertMap( trigObjectMapSI,
             trigObjectMapIS );

  trigPathMapSI.clear();
  trigPathMapSI.insert( std::make_pair(
                "HLT_Mu40_eta2p1_v",
                 HLT_Mu40_eta2p1_v ) );
  trigPathMapSI.insert( std::make_pair(
                "HLT_Mu12_eta2p1_DiCentral_40_20_DiBTagIP3D1stTrack_v",
                 HLT_Mu12_eta2p1_DiCentral_40_20_DiBTagIP3D1stTrack_v ) );
  trigPathMapSI.insert( std::make_pair(
                "HLT_Mu12_eta2p1_DiCentral_40_20_BTagIP3D1stTrack_v",
                 HLT_Mu12_eta2p1_DiCentral_40_20_BTagIP3D1stTrack_v ) );
  trigPathMapSI.insert( std::make_pair(
                "HLT_Mu12_eta2p1_DiCentral_40_20_v",
                 HLT_Mu12_eta2p1_DiCentral_40_20_v ) );
  trigPathMapSI.insert( std::make_pair(
                "HLT_Mu12_eta2p1_DiCentral_20_v",
                 HLT_Mu12_eta2p1_DiCentral_20_v ) );
  trigPathMapSI.insert( std::make_pair(
                "HLT_Mu12_eta2p1_L1Mu10erJetC12WdEtaPhi1DiJetsC_v",
                 HLT_Mu12_eta2p1_L1Mu10erJetC12WdEtaPhi1DiJetsC_v ) );
  trigPathMapSI.insert( std::make_pair(
                "HLT_Mu12_DoubleCentralJet65_v",
                 HLT_Mu12_DoubleCentralJet65_v ) );
  trigPathMapSI.insert( std::make_pair(
                "HLT_Mu12_v",
                 HLT_Mu12_v ) );
  trigPathMapSI.insert( std::make_pair(
                "HLT_Mu15_eta2p1_TriCentral_40_20_20_DiBTagIP3D1stTrack_v",
                 HLT_Mu15_eta2p1_TriCentral_40_20_20_DiBTagIP3D1stTrack_v ) );
  trigPathMapSI.insert( std::make_pair(
                "HLT_Mu15_eta2p1_TriCentral_40_20_20_BTagIP3D1stTrack_v",
                 HLT_Mu15_eta2p1_TriCentral_40_20_20_BTagIP3D1stTrack_v ) );
  trigPathMapSI.insert( std::make_pair(
                "HLT_Mu15_eta2p1_TriCentral_40_20_20_v",
                 HLT_Mu15_eta2p1_TriCentral_40_20_20_v ) );
  trigPathMapSI.insert( std::make_pair(
                "HLT_Mu15_eta2p1_L1Mu10erJetC12WdEtaPhi1DiJetsC_v",
                 HLT_Mu15_eta2p1_L1Mu10erJetC12WdEtaPhi1DiJetsC_v ) );
  trigPathMapSI.insert( std::make_pair(
                "HLT_DoubleMu4_Jpsi_Displaced_v",
                 HLT_DoubleMu4_Jpsi_Displaced_v ) );
  trigPathMapSI.insert( std::make_pair(
                "HLT_DoubleMu4_JpsiTk_Displaced_v",
                 HLT_DoubleMu4_JpsiTk_Displaced_v ) );
  trigPathMapSI.insert( std::make_pair(
                "HLT_DoubleMu3p5_LowMassNonResonant_Displaced_v",
                 HLT_DoubleMu3p5_LowMassNonResonant_Displaced_v ) );
  trigPathMapSI.insert( std::make_pair(
                "HLT_DoubleMu3p5_LowMass_Displaced_v",
                 HLT_DoubleMu3p5_LowMass_Displaced_v ) );
  trigPathMapSI.insert( std::make_pair(
                "HLT_DoubleDisplacedMu4_DiPFJet40Neutral_v",
                 HLT_DoubleDisplacedMu4_DiPFJet40Neutral_v ) );

  revertMap( trigPathMapSI,
             trigPathMapIS );

  vertexTypeMapSI.clear();
  vertexTypeMapSI.insert( std::make_pair( "svtTagInfo",
                                           svtTagInfo ) );
  vertexTypeMapSI.insert( std::make_pair( "svtFitPair",
                                           svtFitPair ) );
  revertMap( vertexTypeMapSI,
             vertexTypeMapIS );

}


PDEnumString::~PDEnumString() {
}


int
PDEnumString::findTrigObject( const std::string& trigObject ) {
  std::map<std::string,int>::const_iterator
    iter = trigObjectMapSI.find( trigObject );
  std::map<std::string,int>::const_iterator
    iend = trigObjectMapSI.end();
  if ( iter != iend ) return iter->second;
  return -1;
}


const std::string&
PDEnumString::findTrigObject( int trigObject ) {
  std::map<int,std::string>::const_iterator
    iter = trigObjectMapIS.find( trigObject );
  std::map<int,std::string>::const_iterator
    iend = trigObjectMapIS.end();
  if ( iter != iend ) return iter->second;
  return defaultString;
}


int
PDEnumString::findTrigPath( const std::string& trigPath ) {
//  std::map<std::string,int>::const_iterator
//    iter = trigPathMapSI.find( trigPath );
  std::map<std::string,int>::const_iterator
    iter = trigPathMapSI.find( trigBase( trigPath ) );
  std::map<std::string,int>::const_iterator
    iend = trigPathMapSI.end();
  if ( iter != iend ) return iter->second;
  return -1;
}


const std::string&
PDEnumString::findTrigPath( int trigPath ) {
  std::map<int,std::string>::const_iterator
    iter = trigPathMapIS.find( trigPath );
  std::map<int,std::string>::const_iterator
    iend = trigPathMapIS.end();
  if ( iter != iend ) return iter->second;
  return defaultString;
}


int
PDEnumString::findVertexType( const std::string& vtxType ) {
  std::map<std::string,int>::const_iterator
    iter = vertexTypeMapSI.find( vtxType );
  std::map<std::string,int>::const_iterator
    iend = vertexTypeMapSI.end();
  if ( iter != iend ) return iter->second;
  return -1;
}


const std::string&
PDEnumString::findVertexType( int vtxType ) {
  std::map<int,std::string>::const_iterator
    iter = vertexTypeMapIS.find( vtxType );
  std::map<int,std::string>::const_iterator
    iend = vertexTypeMapIS.end();
  if ( iter != iend ) return iter->second;
  return defaultString;
}


void PDEnumString::revertMap( const std::map<std::string,int>& mapSI,
                                     std::map<int,std::string>& mapIS ) {
  mapIS.clear();
  std::map<std::string,int>::const_iterator iter = mapSI.begin();
  std::map<std::string,int>::const_iterator iend = mapSI.end();
  while ( iter != iend ) {
    const std::pair<std::string,int>& entry = *iter++;
    mapIS.insert( std::make_pair( entry.second, entry.first ) );
  }
  return;
}


std::string PDEnumString::trigBase( const std::string& trigPath ) {
  int pathLength = trigPath.length();
  const char* str = trigPath.c_str() + pathLength - 1;
  while ( ( *str >= '0' ) && ( *str <= '9' ) ) {
    --str;
    --pathLength;
  }
  return trigPath.substr( 0, pathLength );
}

