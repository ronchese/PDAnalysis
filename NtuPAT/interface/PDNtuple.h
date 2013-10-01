#ifndef PDNtuple_H
#define PDNtuple_H

#include "NtuTool/Common/interface/TreeWrapper.h"
#include "PDAnalysis/NtuPAT/interface/PDNtupleBranch.h"
#include "PDAnalysis/NtuPAT/interface/PDUtil.h"
#include <string>
#include <vector>

// The class with the tree definition must inherit from "TreeWrapper"

class PDNtuple: public virtual PDNtupleBranch<TreeWrapper>,
                public PDUtil,
                public virtual TreeWrapper {

 public:

  PDNtuple();
  virtual ~PDNtuple();
  virtual void reset();

 private:

  PDNtuple( const PDNtuple& td );
  PDNtuple& operator=( const PDNtuple& td );

};

#endif

