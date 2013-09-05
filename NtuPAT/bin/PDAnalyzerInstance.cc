#define UTIL_USE FULL
#include "PDAnalyzer.h"
#include "NtuTool/Read/interface/TreeReader.h"
#include "NtuTool/Read/bin/treeAnalyze.cc"

class PDAnalyzerInstance: public PDAnalyzer, public TreeReader {
  virtual void getEntry( int ientry );
};

void PDAnalyzerInstance::getEntry( int ientry ) {
  PDAnalyzer::getEntry( ientry );
}

static PDAnalyzerInstance ai;

