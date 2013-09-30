#ifndef PDProofAnalyzer_h
#define PDProofAnalyzer_h

#include "TROOT.h"
#include "TChain.h"
#include "TFile.h"
#include "TSelector.h"
#include "TProofServ.h"
#include "TH1.h"
#include <string>
#include <vector>

#include "PDAnalysis/NtuPAT/bin/PDSmartAnalyzer.cc"

class PDProofAnalyzer: public TSelector,
                       public PDSmartAnalyzer {

 public:

  PDProofAnalyzer( TTree* tree = 0 );
  virtual ~PDProofAnalyzer();
  virtual Int_t   Version() const { return 2; }
  virtual void    Begin( TTree *tree );
  virtual void    SlaveBegin( TTree *tree );
  virtual void    Init( TTree *tree );
  virtual Bool_t  Notify();
  virtual Bool_t  Process(Long64_t entry);
  virtual void    SetOption(const char *option) { fOption = option; }
  virtual void    SetObject(TObject *obj) { fObject = obj; }
  virtual void    SetInputList(TList *input) { fInput = input; }
  virtual TList  *GetOutputList() const { return fOutput; }
  virtual void    Terminate();

  ClassDef(PDProofAnalyzer,0);

};

#endif

