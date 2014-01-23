#include "PDAnalysis/Ntu/interface/PDAnalyzerFW.h"
#include "NtuTool/Read/interface/TreeReader.h"

class PDSmartAnalyzer: public PDAnalyzer, public TreeReader {
 public:
  virtual bool getEntry( int ientry ){
    return PDAnalyzer::getEntry( ientry );
  };
};

//bool PDSmartAnalyzer::getEntry( int ientry ) {
//  return PDAnalyzer::getEntry( ientry );
//}


