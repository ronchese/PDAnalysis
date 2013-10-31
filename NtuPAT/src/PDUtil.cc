#include <iostream>
#include <sstream>
#include <string>
#include <math.h>

#include "PDAnalysis/NtuPAT/interface/PDUtil.h"

#include "TDirectory.h"
#include "TBranch.h"
#include "TTree.h"
#include "TCanvas.h"
//#include "Math/LorentzVector.h"

PDUtil::PDUtil() {
}


PDUtil::~PDUtil() {
}


PDUtil::number PDUtil::energy( number px, number py, number pz, number mm ) {
  return sqrt( ( px * px ) + ( py * py ) + ( pz * pz ) + ( mm * mm ) );
}


PDUtil::number PDUtil::invMass( number px1, number py1,
                                number pz1, number mm1,
                                number px2, number py2,
                                number pz2, number mm2 ) {
  number pxt = px1 + px2;
  number pyt = py1 + py2;
  number pzt = pz1 + pz2;
  number eet = energy( px1, py1, pz1, mm1 ) +
               energy( px2, py2, pz2, mm2 );
  return sqrt( ( eet * eet ) -
             ( ( pxt * pxt ) + ( pyt * pyt ) + ( pzt * pzt ) ) );
}


PDUtil::number PDUtil::invMass( number px1, number py1,
                                number pz1, number mm1,
                                number px2, number py2,
                                number pz2, number mm2,
                                number px3, number py3,
                                number pz3, number mm3 ) {
  number pxt = px1 + px2 + px3;
  number pyt = py1 + py2 + py3;
  number pzt = pz1 + pz2 + pz3;
  number eet = energy( px1, py1, pz1, mm1 ) +
               energy( px2, py2, pz2, mm2 ) +
               energy( px3, py3, pz3, mm3 );
  return sqrt( ( eet * eet ) -
             ( ( pxt * pxt ) + ( pyt * pyt ) + ( pzt * pzt ) ) );
}


PDUtil::number PDUtil::invMass( number px1, number py1,
                                number pz1, number mm1,
                                number px2, number py2,
                                number pz2, number mm2,
                                number px3, number py3,
                                number pz3, number mm3,
                                number px4, number py4,
                                number pz4, number mm4 ) {
  number pxt = px1 + px2 + px3 + px4;
  number pyt = py1 + py2 + py3 + py4;
  number pzt = pz1 + pz2 + pz3 + pz4;
  number eet = energy( px1, py1, pz1, mm1 ) +
               energy( px2, py2, pz2, mm2 ) +
               energy( px3, py3, pz3, mm3 ) +
               energy( px4, py4, pz4, mm4 );
  return sqrt( ( eet * eet ) -
             ( ( pxt * pxt ) + ( pyt * pyt ) + ( pzt * pzt ) ) );
}


PDUtil::number PDUtil::invMSph( number  pt1, number eta1,
                                number phi1, number  mm1,
                                number  pt2, number eta2,
                                number phi2, number  mm2 ) {
  number px1;
  number py1;
  number pz1;
  number px2;
  number py2;
  number pz2;
  convSpheCart( pt1, eta1, phi1, px1, py1, pz1 );
  convSpheCart( pt2, eta2, phi2, px2, py2, pz2 );
  return invMass( px1, py1, pz1, mm1,
                  px2, py2, pz2, mm2 );
}


PDUtil::number PDUtil::invMSph( number  pt1, number eta1,
                                number phi1, number  mm1,
                                number  pt2, number eta2,
                                number phi2, number  mm2,
                                number  pt3, number eta3,
                                number phi3, number  mm3 ) {
  number px1;
  number py1;
  number pz1;
  number px2;
  number py2;
  number pz2;
  number px3;
  number py3;
  number pz3;
  convSpheCart( pt1, eta1, phi1, px1, py1, pz1 );
  convSpheCart( pt2, eta2, phi2, px2, py2, pz2 );
  convSpheCart( pt3, eta3, phi3, px3, py3, pz3 );
  return invMass( px1, py1, pz1, mm1,
                  px2, py2, pz2, mm2,
                  px3, py3, pz3, mm3 );
}


PDUtil::number PDUtil::invMSph( number  pt1, number eta1,
                                number phi1, number  mm1,
                                number  pt2, number eta2,
                                number phi2, number  mm2,
                                number  pt3, number eta3,
                                number phi3, number  mm3,
                                number  pt4, number eta4,
                                number phi4, number  mm4 ) {
  number px1;
  number py1;
  number pz1;
  number px2;
  number py2;
  number pz2;
  number px3;
  number py3;
  number pz3;
  number px4;
  number py4;
  number pz4;
  convSpheCart( pt1, eta1, phi1, px1, py1, pz1 );
  convSpheCart( pt2, eta2, phi2, px2, py2, pz2 );
  convSpheCart( pt3, eta3, phi3, px3, py3, pz3 );
  convSpheCart( pt4, eta4, phi4, px4, py4, pz4 );
  return invMass( px1, py1, pz1, mm1,
                  px2, py2, pz2, mm2,
                  px3, py3, pz3, mm3,
                  px4, py4, pz4, mm4 );
}


PDUtil::number PDUtil::dSqua( number a1, number b1,
                              number a2, number b2 ) {
  number aD = a1 - a2;
  number bD = b1 - b2;
  return ( ( aD * aD ) + ( bD * bD ) );
}


PDUtil::number PDUtil::dSqua( number a1, number b1, number c1,
                              number a2, number b2, number c2 ) {
  number aD = a1 - a2;
  number bD = b1 - b2;
  number cD = c1 - c2;
  return ( ( aD * aD ) + ( bD * bD ) + ( cD * cD ) );
}


PDUtil::number PDUtil::delta( number a1, number b1,
                              number a2, number b2 ) {
  number aD = a1 - a2;
  number bD = b1 - b2;
  return sqrt( ( aD * aD ) + ( bD * bD ) );
}


PDUtil::number PDUtil::delta( number a1, number b1, number c1,
                              number a2, number b2, number c2 ) {
  number aD = a1 - a2;
  number bD = b1 - b2;
  number cD = c1 - c2;
  return sqrt( ( aD * aD ) + ( bD * bD ) + ( cD * cD ) );
}


PDUtil::number PDUtil::dRSqua( number eta1, number phi1,
                               number eta2, number phi2 ) {
  number etaD = eta1 - eta2;
  number phiD = phi1 - phi2;
  phiD = fabs( M_PI - fabs( M_PI - fabs( phiD ) ) );
  return ( etaD * etaD ) + ( phiD * phiD );
}

PDUtil::number PDUtil::deltaR( number eta1, number phi1,
                               number eta2, number phi2 ) {
  number etaD = eta1 - eta2;
  number phiD = phi1 - phi2;
  phiD = fabs( M_PI - fabs( M_PI - fabs( phiD ) ) );
  return sqrt( ( etaD * etaD ) + ( phiD * phiD ) );
}

void PDUtil::convCartSphe( number  x, number  y, number  z,
                           number& t, number& e, number& p ) {
  t = sqrt( ( x * x ) + ( y * y ) );
  number
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

