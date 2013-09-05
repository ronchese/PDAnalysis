#ifndef TreeLightReader_H
#define TreeLightReader_H

#include "TTree.h"

#include <iostream>
#include <sstream>

class TreeLightReader {

 public:

  TreeLightReader() { analyzedEvts = acceptedEvts = 0; };
  virtual ~TreeLightReader() {};
  TTree* currentTree;
  std::string currentFile;
  std::string treeName;

  int analyzedEvents() { return analyzedEvts; }
  int acceptedEvents() { return acceptedEvts; }

  virtual void setUserParameter( const std::string& key,
                                 const std::string& val ) {
    std::map<std::string,std::string>::iterator
                                       iter = userParameters.find( key );
    std::map<std::string,std::string>::iterator
                                       iend = userParameters.end();
    if ( iter != iend ) iter->second = val;
    else                userParameters.insert( make_pair( key, val ) );
    return;
  }

  virtual std::string getUserParameter( const std::string& key ) {
    std::map<std::string,std::string>::iterator
                                       iter = userParameters.find( key );
    std::map<std::string,std::string>::iterator
                                       iend = userParameters.end();
    if ( iter != iend ) return iter->second;
    return "";
  }


  template<class T>
  void getUserParameter( const std::string& key, T& val ) {
    std::stringstream sstr;
    sstr.str( getUserParameter( key ) );
    sstr >> val;
    return;
  }

  void getUserParameter( const std::string& key, bool& val ) {
    const char* flag = getUserParameter( key ).c_str();
    val = (   ( *flag == 't' ) || ( *flag == 'T' ) ||
            ( ( *flag >= '1' ) && ( *flag <= '9' ) ) );
    return;
  }

 protected:

  TObject* autoSavedObject;
  const char* dummyString;
  int dummySize;
  int dummyLevel;

  int analyzedEvts;
  int acceptedEvts;

  void setBranch( const char* branchName, void* dataPtr,
                  const char* branchData ) {
    if ( currentTree == 0 ) return;
    currentTree->SetBranchAddress( branchName, dataPtr  );
    dummyString = branchData;
    return;
  }
  void setBranch( const char* branchName, void* dataPtr,
                  const char* branchData,
                  TBranch** branchPtr ) {
    if ( currentTree == 0 ) return;
    currentTree->SetBranchAddress( branchName, dataPtr, branchPtr );
    dummyString = branchData;
    return;
  }

/*
*/
/*
  template<class T>
  void setBranch( const char* branchName, T* dataPtr,
                  int bufferSize = 32000,
                  int splitLevel = 99 ) {
    if ( currentTree == 0 ) return;
    currentTree->SetBranchAddress( branchName, dataPtr  );
    dummySize  = bufferSize;
    dummyLevel = splitLevel;
    return;
  }
  template<class T>
  void setBranch( const char* branchName, T* dataPtr,
                  int bufferSize,
                  int splitLevel,
                  TBranch** branchPtr ) {
    if ( currentTree == 0 ) return;
    currentTree->SetBranchAddress( branchName, dataPtr, branchPtr );
    dummySize  = bufferSize;
    dummyLevel = splitLevel;
    return;
  }
*/
/*
*/
  template<class T>
  void setBranch( const char* branchName, T** dataPtr,
                  int bufferSize = 32000,
                  int splitLevel = 99 ) {
    if ( currentTree == 0 ) return;
    currentTree->SetBranchAddress( branchName, dataPtr  );
    dummySize  = bufferSize;
    dummyLevel = splitLevel;
    return;
  }
  template<class T>
  void setBranch( const char* branchName, T** dataPtr,
                  int bufferSize,
                  int splitLevel,
                  TBranch** branchPtr ) {
    if ( currentTree == 0 ) return;
    currentTree->SetBranchAddress( branchName, dataPtr, branchPtr );
    dummySize  = bufferSize;
    dummyLevel = splitLevel;
    return;
  }

 private:

  std::map<std::string,std::string> userParameters;

};

#endif

