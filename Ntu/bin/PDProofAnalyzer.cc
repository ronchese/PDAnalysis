#define UTIL_USE FULL
#include "PDProofAnalyzer.h"
#include "NtuTool/Read/interface/TreeReader.h"
#include "TH1.h"
#include "TStyle.h"
#include <iostream>


#include "NtuTool/Common/src/TreeTypeNames.cc"
#include "NtuTool/Common/src/TreeTypeManager.cc"
#include "NtuTool/Common/src/TreeTypeWriterTS.cc"
#include "NtuTool/Common/src/DataConvert.cc"
#include "NtuTool/Common/src/DataHandler.cc"
#include "NtuTool/Common/src/DataHandlerManager.cc"
#include "NtuTool/Common/src/DataHandlerMap.cc"
#include "NtuTool/Common/src/DataReset.cc"
#include "NtuTool/Common/src/DataResetString.cc"
#include "NtuTool/Common/src/TreeWrapper.cc"
#include "NtuTool/Read/src/TreeReader.cc"
#include "PDAnalysis/Ntu/src/PDNtupleData.cc"
#include "PDAnalysis/Ntu/src/PDEventSelect.cc"
#include "PDAnalysis/Ntu/src/PDUtil.cc"
#include "PDAnalysis/Ntu/src/PDNtuple.cc"
#include "PDAnalysis/Ntu/src/PDEnumString.cc"
#include "PDAnalysis/Ntu/src/PDGenHandler.cc"
#include "PDAnalysis/Ntu/bin/PDAnalyzer.cc"
#include "TFile.h"
#include "TChain.h"
#include <fstream>

using namespace std;

PDProofAnalyzer::PDProofAnalyzer( TTree* tree ) {
}


PDProofAnalyzer::~PDProofAnalyzer() {
}


void PDProofAnalyzer::Init( TTree* tree ) {

  // SlaveBegin() is a good place to create histograms. 
  // For PROOF, this is called for each worker.

  // Set branch addresses and branch pointers
  if ( !tree ) return;
  cout << "initRead" << endl;
  initRead( tree );

  return;

}


Bool_t PDProofAnalyzer::Notify() {
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.
   return kTRUE;
}


void PDProofAnalyzer::Begin(TTree * /*tree*/) {
  cout << "Begin" << endl;
  TString option = GetOption();
  book();
  return;
}

// The following methods are defined in this file:
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// Root > T->Process("ProofEventSelector.C")
// Root > T->Process("ProofEventSelector.C","some options")
// Root > T->Process("ProofEventSelector.C+")
//


void PDProofAnalyzer::SlaveBegin(TTree * /*tree*/) {

  // The SlaveBegin() function is called after the Begin() function.
  // When running with PROOF SlaveBegin() is called on each slave server.
  // The tree argument is deprecated (on PROOF 0 is passed).

  TString option = GetOption();

  beginJob();

  cout << "book" << endl;
  cout << endl << "book dir: " << gDirectory->GetName() << endl;
  book();

  AutoSavedObject::obj_iter o_iter = autoSavedObject.objBegin();
  AutoSavedObject::obj_iter o_iend = autoSavedObject.objEnd();
  std::string type;
  while ( o_iter != o_iend ) {
    TObject* obj = const_cast<TObject*>( *o_iter++ );
    if ( writable( obj ) ) fOutput->Add( obj );
  }
  return;

}

Bool_t PDProofAnalyzer::Process( Long64_t ientry ) {

   // The Process() function is called for each entry in the tree to be 
   // processed. The entry argument specifies which entry in the currently
   // loaded tree is to be processed.
   // It can be passed to either EventSelector::GetEntry() or TBranch::GetEntry()
   // to read either all or the required parts of the TTree.
   //
   // This function should contain the "body" of the analysis: select relevant
   // tree entries, run algorithms on the tree entry and typically fill histograms.
   //
   // The processing can be stopped by calling Abort().
   //
   // Use fStatus to set the return value of TTree::Process().
   //
   // The return value is currently not used.

   // *** 1. *** Tell the tree to load the data for this entry:
  cout << "getEntry " << ientry << endl;
  if ( !getEntry( ientry ) ) return false;

  // *** 2. *** Do the actual analysis

  cout << "process " << ientry << endl;
  process( ientry );
  cout << "analyze " << ientry << endl;
  return analyze( ientry, 0, 0 );

}

void PDProofAnalyzer::SlaveTerminate() {
//  endJob();
  return;
}

void PDProofAnalyzer::Terminate() {

   // The Terminate() function is the last function to be called during the
   // analysis of a tree with a selector. It always runs on the client, it can
   // be used to present the results graphically or save the results to file.

  endJob();
  TFile* fout;
  fout = TFile::Open( "histo.root", "RECREATE" );

  autoSave( GetOutputList() );

  cout << "write file" << endl;
  fout->Write();

  cout << "close histo file" << endl;
  fout->Close();

//  GetOutputList()->FindObject("hptmu")->Draw();
  return;

}
