#define UTIL_USE FULL
#include "PDAnalyzer.h"
#include "NtuTool/Read/interface/TreeReader.h"
#include "NtuTool/Read/bin/treeAnalyze.cc"

class PDAnalyzerInstance: public PDAnalyzer, public TreeReader {
  virtual bool getEntry( int ientry );
};

bool PDAnalyzerInstance::getEntry( int ientry ) {
  return PDAnalyzer::getEntry( ientry );
}

static PDAnalyzerInstance ai;

