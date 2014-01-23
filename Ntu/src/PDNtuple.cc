#include <iostream>

#include "PDAnalysis/Ntu/interface/PDNtuple.h"

PDNtuple::PDNtuple() {
  // "treeName" must be assigned the name chosen by the user for the tree
  // the TTree object is created by the utility
  treeName = "PDtree";
}


PDNtuple::~PDNtuple() {
}


void PDNtuple::reset() {
  // calling "autoReset" all variables and vectors are automatically reset
  autoReset();
  return;
}


