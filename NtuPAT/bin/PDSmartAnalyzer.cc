#define UTIL_USE FULL
#include "PDAnalyzer.h"
#include "NtuTool/Read/interface/TreeReader.h"

class PDSmartAnalyzer: public PDAnalyzer, public TreeReader {
 public:
  virtual bool getEntry( int ientry );
};

bool PDSmartAnalyzer::getEntry( int ientry ) {
  return PDAnalyzer::getEntry( ientry );
}


