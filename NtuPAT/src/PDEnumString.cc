#include "PDAnalysis/NtuPAT/interface/PDEnumString.h"

#include <iostream>

//using namespace std;

std::string PDEnumString::defaultString;
std::map<int,std::string> PDEnumString::trigPathMapIS;
std::map<std::string,int> PDEnumString::trigPathMapSI;
std::map<int,std::string> PDEnumString::trigObjectMapIS;
std::map<std::string,int> PDEnumString::trigObjectMapSI;
std::map<int,std::string> PDEnumString::recoObjectMapIS;
std::map<std::string,int> PDEnumString::recoObjectMapSI;
std::map<int,std::string> PDEnumString::recoUITypeMapIS;
std::map<std::string,int> PDEnumString::recoUITypeMapSI;
std::map<int,std::string> PDEnumString::vertexTypeMapIS;
std::map<std::string,int> PDEnumString::vertexTypeMapSI;

static PDEnumString pdEnumString;

#define mP( NAME ) std::make_pair( #NAME, NAME )

PDEnumString::PDEnumString() {

  defaultString = "";

  trigPathMapSI.clear();
//  trigPathMapSI.insert(
//      mP( dummy ) );
  trigPathMapSI.insert(
      mP( HLT_Mu17_Mu8_v ) );
  trigPathMapSI.insert(
      mP( HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v ) );
  trigPathMapSI.insert(
      mP( HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v ) );
  trigPathMapSI.insert(
      mP( HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v ) );
  trigPathMapSI.insert(
      mP( HLT_IsoMu24_v ) );
  trigPathMapSI.insert(
      mP( HLT_IsoMu24_eta2p1_v ) );
  trigPathMapSI.insert(
      mP( HLT_Ele27_WP80_v ) );
  trigPathMapSI.insert(
      mP( HLT_Ele25_CaloIdVT_CaloIsoVL_TrkIdVL_TrkIsoT_TriCentralPFNoPUJet30_v ) );
//  trigPathMapSI.insert(
//      mP( HLT_Mu40_eta2p1_v ) );
//  trigPathMapSI.insert(
//      mP( HLT_Mu12_eta2p1_DiCentral_40_20_DiBTagIP3D1stTrack_v ) );
//  trigPathMapSI.insert(
//      mP( HLT_Mu12_eta2p1_DiCentral_40_20_BTagIP3D1stTrack_v ) );
//  trigPathMapSI.insert(
//      mP( HLT_Mu12_eta2p1_DiCentral_40_20_v ) );
//  trigPathMapSI.insert(
//      mP( HLT_Mu12_eta2p1_DiCentral_20_v ) );
//  trigPathMapSI.insert(
//      mP( HLT_Mu12_eta2p1_L1Mu10erJetC12WdEtaPhi1DiJetsC_v ) );
//  trigPathMapSI.insert(
//      mP( HLT_Mu12_DoubleCentralJet65_v ) );
//  trigPathMapSI.insert(
//      mP( HLT_Mu12_v ) );
//  trigPathMapSI.insert(
//      mP( HLT_Mu15_eta2p1_TriCentral_40_20_20_DiBTagIP3D1stTrack_v ) );
//  trigPathMapSI.insert(
//      mP( HLT_Mu15_eta2p1_TriCentral_40_20_20_BTagIP3D1stTrack_v ) );
//  trigPathMapSI.insert(
//      mP( HLT_Mu15_eta2p1_TriCentral_40_20_20_v ) );
//  trigPathMapSI.insert(
//      mP( HLT_Mu15_eta2p1_L1Mu10erJetC12WdEtaPhi1DiJetsC_v ) );
//  trigPathMapSI.insert(
//      mP( HLT_DoubleMu4_Jpsi_Displaced_v ) );
//  trigPathMapSI.insert(
//      mP( HLT_DoubleMu4_JpsiTk_Displaced_v ) );
//  trigPathMapSI.insert(
//      mP( HLT_DoubleMu3p5_LowMassNonResonant_Displaced_v ) );
//  trigPathMapSI.insert(
//      mP( HLT_DoubleMu3p5_LowMass_Displaced_v ) );
//  trigPathMapSI.insert(
//      mP( HLT_DoubleDisplacedMu4_DiPFJet40Neutral_v ) );

  revertMap( trigPathMapSI,
             trigPathMapIS );

  trigObjectMapSI.clear();
  trigObjectMapSI.insert( mP( hltJet      ) );
  trigObjectMapSI.insert( mP( hltMuon     ) );
  trigObjectMapSI.insert( mP( hltElectron ) );
  trigObjectMapSI.insert( mP( hltTau      ) );
  revertMap( trigObjectMapSI,
             trigObjectMapIS );

  recoObjectMapSI.clear();
  recoObjectMapSI.insert( mP( recJet      ) );
  recoObjectMapSI.insert( mP( recMuon     ) );
  recoObjectMapSI.insert( mP( recElectron ) );
  recoObjectMapSI.insert( mP( recTau      ) );
  revertMap( recoObjectMapSI,
             recoObjectMapIS );

  recoUITypeMapSI.clear();
  recoUITypeMapSI.insert( mP( puBeta      ) );
  recoUITypeMapSI.insert( mP( puBetaStar  ) );
  revertMap( recoUITypeMapSI,
             recoUITypeMapIS );

  vertexTypeMapSI.clear();
  vertexTypeMapSI.insert( mP( svtTagInfo ) );
  vertexTypeMapSI.insert( mP( svtFitPair ) );
  revertMap( vertexTypeMapSI,
             vertexTypeMapIS );

}


PDEnumString::~PDEnumString() {
}


void
PDEnumString::resetTrigMap() {
  trigPathMapIS.clear();
  trigPathMapSI.clear();
  return;
}


void
PDEnumString::revertTrigMap() {
  revertMap( trigPathMapSI,
             trigPathMapIS );
  return;
}


const std::map<int,std::string>&
PDEnumString::trigMap() {
  return trigPathMapIS;
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


int
PDEnumString::findTrigPath( const std::string& trigPath,
                            bool fixedList, int code ) {
//  std::string trigName = trigBase( trigPath );
//  std::map<std::string,int>::const_iterator
//    iter = trigPathMapSI.find( trigName );
  std::map<std::string,int>::const_iterator
    iter = trigPathMapSI.find( trigPath );
  std::map<std::string,int>::const_iterator
    iend = trigPathMapSI.end();
  if ( iter != iend ) return iter->second;
  if ( fixedList ) return -1;
  int nextSlot = ( code < 0 ? trigPathMapIS.rbegin()->first + 1 : code );
//  std::cout << "add " << nextSlot << " " << trigPath << std::endl;
//  trigPathMapSI.insert( std::make_pair( trigName, nextSlot ) );
//  trigPathMapIS.insert( std::make_pair( nextSlot, trigName ) );
  trigPathMapSI.insert( std::make_pair( trigPath, nextSlot ) );
  trigPathMapIS.insert( std::make_pair( nextSlot, trigPath ) );
  return nextSlot;
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
PDEnumString::findRecoUIType( const std::string& recoUIType ) {
  std::map<std::string,int>::const_iterator
    iter = recoUITypeMapSI.find( recoUIType );
  std::map<std::string,int>::const_iterator
    iend = recoUITypeMapSI.end();
  if ( iter != iend ) return iter->second;
  return -1;
}


const std::string&
PDEnumString::findRecoUIType( int recoUIType ) {
  std::map<int,std::string>::const_iterator
    iter = recoUITypeMapIS.find( recoUIType );
  std::map<int,std::string>::const_iterator
    iend = recoUITypeMapIS.end();
  if ( iter != iend ) return iter->second;
  return defaultString;
}


int
PDEnumString::findRecoObject( const std::string& recoObject ) {
  std::map<std::string,int>::const_iterator
    iter = recoObjectMapSI.find( recoObject );
  std::map<std::string,int>::const_iterator
    iend = recoObjectMapSI.end();
  if ( iter != iend ) return iter->second;
  return -1;
}


const std::string&
PDEnumString::findRecoObject( int recoObject ) {
  std::map<int,std::string>::const_iterator
    iter = recoObjectMapIS.find( recoObject );
  std::map<int,std::string>::const_iterator
    iend = recoObjectMapIS.end();
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

