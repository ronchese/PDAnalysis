#ifndef PDAnalyzerUtil_H
#define PDAnalyzerUtil_H

#define FULL 2
#define BARE 3

namespace edm {
  class ParameterSet;
  class Run;
  class Event;
  class EventBase;
  class EventSetup;
}

#include "PDAnalysis/Ntu/interface/PDEventSelect.h"
#include "PDAnalysis/Ntu/interface/PDEnumString.h"

#  if UTIL_USE == FULL

#include "PDAnalysis/Ntu/interface/PDNtuple.h"
class PDAnalyzerUtil: public PDNtuple,
                      public PDEventSelect {

#elif UTIL_USE == BARE

// get the bare ntuple definition, with no usage of other utilities
// in addition to PD specific ones
// "TreeLightReader" simply forward calls directly to ROOT with no 
// additional operation
#include "PDLightNtuple.h"
class PDAnalyzerUtil: public PDLightNtuple,
                      public PDEventSelect {

#else
#error use -D UTIL_USE=FULL or -D UTIL_USE=BARE
#endif

 public:

  PDAnalyzerUtil();
  virtual ~PDAnalyzerUtil();

 protected:

  const edm::ParameterSet* parameterSet ;
  const edm::Run         * currentRun;
  const edm::Event       * currentEvent;
  const edm::EventBase   * currentEvBase;
  const edm::EventSetup  * currentEvSetup;

  virtual void beginJob();

  virtual bool getEntry( int ientry );
  virtual void getEvPre( int ientry );
  virtual void getEntry( TBranch* branch, int ientry );
  virtual void getHeader( int ientry );

  int findSVtx( int trkIndex, int prevSVtx = -1 );
  bool goodJet( unsigned int iJet );

  bool hlt( PDEnumString::trigPath path );
  std::vector<number>* userInfo( PDEnumString::recoObject r,
                                 PDEnumString::infoType   t );

 private:

  // flag to use event list as skip list
  bool skipList;

  // cuts to select good jets
  int    jetNDaumin;
  int    jetNDaumax;
  double jetNHFmin;
  double jetNHFmax;
  double jetNEFmin;
  double jetNEFmax;
  double jetCHFmin;
  double jetCHFmax;
  double jetCEFmin;
  double jetCEFmax;
  double jetNCHmin;
  double jetNCHmax;
  double jetEtaCut;

  struct Id {
    unsigned int run;
    unsigned int event;
  };
  Id lastHLT;
  std::map<int,bool> hFlags;
  Id lastInfo;
  std::map< int,std::map< int,std::vector<number> > > uInfos;
  Id lastAssoc;
  std::vector<int> pfcGenP;
  std::vector<int> genReco;

  void grAssoc();

  // dummy copy and assignment constructors
  PDAnalyzerUtil( const PDAnalyzerUtil& );
  PDAnalyzerUtil& operator=( const PDAnalyzerUtil& );

};


#endif

