#ifndef TreeLightReader_H
#define TreeLightReader_H

#include "TTree.h"

#include <iostream>
#include <sstream>

class TreeLightReader {

 public:

  TreeLightReader() { analyzedEvts = acceptedEvts = 0; dum = ""; };
  virtual ~TreeLightReader() {};
  TTree* currentTree;
  std::string currentFile;
  std::string treeName;

  int analyzedEvents() { return analyzedEvts; }
  int acceptedEvents() { return acceptedEvts; }
  virtual void plot() { return; }

  virtual void setConfiguration( const std::string& file ) {
    std::ifstream cfg( file.c_str() );
    int length;
    int lenMax = 1000;
    char* line = new char[lenMax];
    char* lptr;
    while ( cfg.getline( line, lenMax ) ) {
      lptr = line;
      while ( *lptr == ' ' ) ++lptr;
      if    ( *lptr == '#' ) continue;
      std::string key( lptr );
      length = key.find( " " );
      if ( length < 0 ) {
        std::cout << "invalid configuration input: " << line << std::endl;
        continue;
      }
      key = key.substr( 0, length );
      lptr += length;
      while ( *lptr == ' ' ) ++lptr;
      std::string val( lptr );
      length = val.find( " " );
      if ( length >= 0 )
	val = val.substr( 0, length );
      setUserParameter( key, val );
    }
    delete[] line;
    return;
  }

  void setUserParameter( const std::string& key,
                         const std::string& val ) {
    std::map<std::string,std::string>::iterator
                                       iter = userParameters.find( key );
    std::map<std::string,std::string>::iterator
                                       iend = userParameters.end();
    if ( iter != iend ) iter->second = val;
    else                userParameters.insert( make_pair( key, val ) );
    return;
  }

  const
  std::string& getUserParameter( const std::string& key ) {
//    static std::string dum = "";
    std::map<std::string,std::string>::iterator
                                       iter = userParameters.find( key );
    std::map<std::string,std::string>::iterator
                                       iend = userParameters.end();
    if ( iter != iend ) return iter->second;
    return dum;
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
  std::string dum;
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

