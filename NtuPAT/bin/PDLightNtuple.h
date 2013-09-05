#ifndef PDLightNtuple_H
#define PDLightNtuple_H

#include "PDAnalysis/NtuPAT/interface/PDNtupleBranch.h"
#include "PDAnalysis/NtuPAT/interface/PDUtil.h"
#include "TreeLightReader.h"
#include <string>
#include <vector>

// The class with the tree definition must inherit from "TreeLightReader"

class PDLightNtuple: public virtual PDNtupleBranch<TreeLightReader>,
                      public PDUtil,
                      public virtual TreeLightReader {

 public:

  PDLightNtuple();
  virtual ~PDLightNtuple();

//  void initTree();
  void openTree( TTree* tree );
//  virtual void reset();

 private:

  PDLightNtuple( const PDLightNtuple& td );
  PDLightNtuple& operator=( const PDLightNtuple& td );

};

#endif

