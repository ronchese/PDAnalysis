#include <iostream>

#include "PDLightNtuple.h"

PDLightNtuple::PDLightNtuple() {
  currentTree = 0;
  treeName = "PDtree";
}


PDLightNtuple::~PDLightNtuple() {
}


//void PDLightNtuple::initTree() {
//  PDNtupleBranch<TreeLightReader>::initTree();
//}


void PDLightNtuple::openTree( TTree* tree ) {
  currentTree = tree;
  initTree();
  return;
}

/*
void PDLightNtuple::reset() {

// ...reset all variables...
  return;

}
*/


