#include <iostream>
#include <sstream>
#include <string>
#include <math.h>

#include "PDAnalysis/NtuPAT/interface/PDUtil.h"

#include "TDirectory.h"
#include "TBranch.h"
#include "TTree.h"
#include "TCanvas.h"
#include "Math/LorentzVector.h"

PDUtil::PDUtil() {
}


PDUtil::~PDUtil() {
}


float PDUtil::energy( float px, float py, float pz, float mm ) {
  return sqrt( ( px * px ) + ( py * py ) + ( pz * pz ) + ( mm * mm ) );
}


float PDUtil::invMass( float px1, float py1,
                       float pz1, float mm1,
                       float px2, float py2,
                       float pz2, float mm2 ) {
  float pxt = px1 + px2;
  float pyt = py1 + py2;
  float pzt = pz1 + pz2;
  float eet = energy( px1, py1, pz1, mm1 ) +
              energy( px2, py2, pz2, mm2 );
  return sqrt( ( eet * eet ) -
             ( ( pxt * pxt ) + ( pyt * pyt ) + ( pzt * pzt ) ) );
}


float PDUtil::invMass( float px1, float py1,
                       float pz1, float mm1,
                       float px2, float py2,
                       float pz2, float mm2,
                       float px3, float py3,
                       float pz3, float mm3 ) {
  float pxt = px1 + px2 + px3;
  float pyt = py1 + py2 + py3;
  float pzt = pz1 + pz2 + pz3;
  float eet = energy( px1, py1, pz1, mm1 ) +
              energy( px2, py2, pz2, mm2 ) +
              energy( px3, py3, pz3, mm3 );
  return sqrt( ( eet * eet ) -
             ( ( pxt * pxt ) + ( pyt * pyt ) + ( pzt * pzt ) ) );
}


float PDUtil::invMass( float px1, float py1,
                       float pz1, float mm1,
                       float px2, float py2,
                       float pz2, float mm2,
                       float px3, float py3,
                       float pz3, float mm3,
                       float px4, float py4,
                       float pz4, float mm4 ) {
  float pxt = px1 + px2 + px3 + px4;
  float pyt = py1 + py2 + py3 + py4;
  float pzt = pz1 + pz2 + pz3 + pz4;
  float eet = energy( px1, py1, pz1, mm1 ) +
              energy( px2, py2, pz2, mm2 ) +
              energy( px3, py3, pz3, mm3 ) +
              energy( px4, py4, pz4, mm4 );
  return sqrt( ( eet * eet ) -
             ( ( pxt * pxt ) + ( pyt * pyt ) + ( pzt * pzt ) ) );
}


float PDUtil::invMSph( float  pt1, float eta1,
                       float phi1, float  mm1,
                       float  pt2, float eta2,
                       float phi2, float  mm2 ) {
  float px1;
  float py1;
  float pz1;
  float px2;
  float py2;
  float pz2;
  convSpheCart( pt1, eta1, phi1, px1, py1, pz1 );
  convSpheCart( pt2, eta2, phi2, px2, py2, pz2 );
  return invMass( px1, py1, pz1, mm1,
                  px2, py2, pz2, mm2 );
}


float PDUtil::invMSph( float  pt1, float eta1,
                       float phi1, float  mm1,
                       float  pt2, float eta2,
                       float phi2, float  mm2,
                       float  pt3, float eta3,
                       float phi3, float  mm3 ) {
  float px1;
  float py1;
  float pz1;
  float px2;
  float py2;
  float pz2;
  float px3;
  float py3;
  float pz3;
  convSpheCart( pt1, eta1, phi1, px1, py1, pz1 );
  convSpheCart( pt2, eta2, phi2, px2, py2, pz2 );
  convSpheCart( pt3, eta3, phi3, px3, py3, pz3 );
  return invMass( px1, py1, pz1, mm1,
                  px2, py2, pz2, mm2,
                  px3, py3, pz3, mm3 );
}


float PDUtil::invMSph( float  pt1, float eta1,
                       float phi1, float  mm1,
                       float  pt2, float eta2,
                       float phi2, float  mm2,
                       float  pt3, float eta3,
                       float phi3, float  mm3,
                       float  pt4, float eta4,
                       float phi4, float  mm4 ) {
  float px1;
  float py1;
  float pz1;
  float px2;
  float py2;
  float pz2;
  float px3;
  float py3;
  float pz3;
  float px4;
  float py4;
  float pz4;
  convSpheCart( pt1, eta1, phi1, px1, py1, pz1 );
  convSpheCart( pt2, eta2, phi2, px2, py2, pz2 );
  convSpheCart( pt3, eta3, phi3, px3, py3, pz3 );
  convSpheCart( pt4, eta4, phi4, px4, py4, pz4 );
  return invMass( px1, py1, pz1, mm1,
                  px2, py2, pz2, mm2,
                  px3, py3, pz3, mm3,
                  px4, py4, pz4, mm4 );
}


float PDUtil::dSqua( float a1, float b1,
                     float a2, float b2 ) {
  float aD = a1 - a2;
  float bD = b1 - b2;
  return ( ( aD * aD ) + ( bD * bD ) );
}


float PDUtil::dSqua( float a1, float b1, float c1,
                     float a2, float b2, float c2 ) {
  float aD = a1 - a2;
  float bD = b1 - b2;
  float cD = c1 - c2;
  return ( ( aD * aD ) + ( bD * bD ) + ( cD * cD ) );
}


float PDUtil::delta( float a1, float b1,
                     float a2, float b2 ) {
  float aD = a1 - a2;
  float bD = b1 - b2;
  return sqrt( ( aD * aD ) + ( bD * bD ) );
}


float PDUtil::delta( float a1, float b1, float c1,
                     float a2, float b2, float c2 ) {
  float aD = a1 - a2;
  float bD = b1 - b2;
  float cD = c1 - c2;
  return sqrt( ( aD * aD ) + ( bD * bD ) + ( cD * cD ) );
}


void PDUtil::convCartSphe( number  x, number  y, number  z,
                           number& t, number& e, number& p ) {
  t = sqrt( ( x * x ) + ( y * y ) );
  float
  r = sqrt( ( x * x ) + ( y * y ) + ( z * z ) );
  e = -log( ( r + z ) / ( r - z ) ) / 2.0;
  p = atan2( y, x );
  return;
}


void PDUtil::convSpheCart( number  t, number  e, number  p,
                           number& x, number& y, number& z ) {
  x = t * cos( p );
  y = t * sin( p );
  z = t / tan( 2 * atan( exp( -e ) ) );
  return;
}


void PDUtil::convCartSphe( const std::vector<number>* x,
                           const std::vector<number>* y,
                           const std::vector<number>* z,
                                 std::vector<number>* t,
                                 std::vector<number>* e,
                                 std::vector<number>* p,
                                 int i ) {
  if ( i < 0 ) {
    int j;
    int n = x->size();
    t->resize( n );
    e->resize( n );
    p->resize( n );
    for ( j = 0; j < n; ++j )
    convCartSphe( x->at( j ), y->at( j ), z->at( j ),
                  t->at( j ), e->at( j ), p->at( j ) );
  }
  else {
    convCartSphe( x->at( i ), y->at( i ), z->at( i ),
                  t->at( i ), e->at( i ), p->at( i ) );
  }
  return;
}


void PDUtil::convSpheCart( const std::vector<number>* t,
                           const std::vector<number>* e,
                           const std::vector<number>* p,
                                 std::vector<number>* x,
                                 std::vector<number>* y,
                                 std::vector<number>* z,
                                 int i ) {
  if ( i < 0 ) {
    int j;
    int n = t->size();
    x->resize( n );
    y->resize( n );
    z->resize( n );
    for ( j = 0; j < n; ++j )
    convSpheCart( t->at( j ), e->at( j ), p->at( j ),
                  x->at( j ), y->at( j ), z->at( j ) );
  }
  else {
    convSpheCart( t->at( i ), e->at( i ), p->at( i ),
                  x->at( i ), y->at( i ), z->at( i ) );
  }
  return;
}

