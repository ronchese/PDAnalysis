#include <iostream>
#include <sstream>
#include <string>
#include <set>
#include <math.h>

#include "PDAnalysis/Ntu/interface/PDUtil.h"

#include "TDirectory.h"
#include "TBranch.h"
#include "TTree.h"
#include "TCanvas.h"
//#include "Math/LorentzVector.h"

PDUtil::ObjectSelection PDUtil::dummySel;

PDUtil::PDUtil() {
}


PDUtil::~PDUtil() {
}


PDUtil::number PDUtil::energy( number px, number py, number pz, number mm ) {
  return sqrt( ( px * px ) + ( py * py ) + ( pz * pz ) + ( mm * mm ) );
}


PDUtil::number PDUtil::invMass( number px, number py, number pz, number ee ) {
  float mq = ( px * px ) + ( py * py ) + ( pz * pz ) - ( ee * ee );
  if ( mq > 0.0 ) return 0.0;
  return sqrt( -mq );
}


PDUtil::number PDUtil::invMass( number px1, number py1,
                                number pz1, number ee1,
                                number px2, number py2,
                                number pz2, number ee2 ) {
  number pxt = px1 + px2;
  number pyt = py1 + py2;
  number pzt = pz1 + pz2;
  number eet = ee1 + ee2;
  return sqrt( ( eet * eet ) -
             ( ( pxt * pxt ) + ( pyt * pyt ) + ( pzt * pzt ) ) );
}


PDUtil::number PDUtil::invMass( number px1, number py1,
                                number pz1, number ee1,
                                number px2, number py2,
                                number pz2, number ee2,
                                number px3, number py3,
                                number pz3, number ee3 ) {
  number pxt = px1 + px2 + px3;
  number pyt = py1 + py2 + py3;
  number pzt = pz1 + pz2 + pz3;
  number eet = ee1 + ee2 + ee3;
  return sqrt( ( eet * eet ) -
             ( ( pxt * pxt ) + ( pyt * pyt ) + ( pzt * pzt ) ) );
}


PDUtil::number PDUtil::invMass( number px1, number py1,
                                number pz1, number ee1,
                                number px2, number py2,
                                number pz2, number ee2,
                                number px3, number py3,
                                number pz3, number ee3,
                                number px4, number py4,
                                number pz4, number ee4 ) {
  number pxt = px1 + px2 + px3 + px4;
  number pyt = py1 + py2 + py3 + py4;
  number pzt = pz1 + pz2 + pz3 + pz4;
  number eet = ee1 + ee2 + ee3 + ee4;
  return sqrt( ( eet * eet ) -
             ( ( pxt * pxt ) + ( pyt * pyt ) + ( pzt * pzt ) ) );
}


PDUtil::number PDUtil::invMSph( number  pt, number eta,
                                number phi, number  ee ) {
  float px;
  float py;
  float pz;
  convSpheCart( pt, eta, phi, px, py, pz );
  float mq = ( px * px ) + ( py * py ) + ( pz * pz ) - ( ee * ee );
  if ( mq > 0.0 ) return 0.0;
  return sqrt( -mq );
}


PDUtil::number PDUtil::invMSph( number  pt1, number eta1,
                                number phi1, number  ee1,
                                number  pt2, number eta2,
                                number phi2, number  ee2 ) {
  number px1;
  number py1;
  number pz1;
  number px2;
  number py2;
  number pz2;
  convSpheCart( pt1, eta1, phi1, px1, py1, pz1 );
  convSpheCart( pt2, eta2, phi2, px2, py2, pz2 );
  return invMass( px1, py1, pz1, ee1,
                  px2, py2, pz2, ee2 );
}


PDUtil::number PDUtil::invMSph( number  pt1, number eta1,
                                number phi1, number  ee1,
                                number  pt2, number eta2,
                                number phi2, number  ee2,
                                number  pt3, number eta3,
                                number phi3, number  ee3 ) {
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
  return invMass( px1, py1, pz1, ee1,
                  px2, py2, pz2, ee2,
                  px3, py3, pz3, ee3 );
}


PDUtil::number PDUtil::invMSph( number  pt1, number eta1,
                                number phi1, number  ee1,
                                number  pt2, number eta2,
                                number phi2, number  ee2,
                                number  pt3, number eta3,
                                number phi3, number  ee3,
                                number  pt4, number eta4,
                                number phi4, number  ee4 ) {
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
  return invMass( px1, py1, pz1, ee1,
                  px2, py2, pz2, ee2,
                  px3, py3, pz3, ee3,
                  px4, py4, pz4, ee4 );
}


PDUtil::number PDUtil::invMass_M( number px1, number py1,
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


PDUtil::number PDUtil::invMass_M( number px1, number py1,
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


PDUtil::number PDUtil::invMass_M( number px1, number py1,
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


PDUtil::number PDUtil::invMSph_M( number  pt1, number eta1,
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
  return invMass_M( px1, py1, pz1, mm1,
                    px2, py2, pz2, mm2 );
}


PDUtil::number PDUtil::invMSph_M( number  pt1, number eta1,
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
  return invMass_M( px1, py1, pz1, mm1,
                    px2, py2, pz2, mm2,
                    px3, py3, pz3, mm3 );
}


PDUtil::number PDUtil::invMSph_M( number  pt1, number eta1,
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
  return invMass_M( px1, py1, pz1, mm1,
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

PDUtil::number PDUtil::modSqua( number x, number y, number z ) {
  return ( x * x ) + ( y * y ) + ( z * z );
}

PDUtil::number PDUtil::modSqua( number t, number e ) {
  number z = t / tan( 2 * atan( exp( -e ) ) );
  return ( t * t ) + ( z * z );
}

PDUtil::number PDUtil::angleCart( number x1, number y1, number z1,
                                  number x2, number y2, number z2 ) {
  number s = ( x1 * x2 ) + ( y1 * y2 ) + ( z1 * z2 );
  number p = modCart( x1, y1, z1 ) * modCart( x2, y2, z2 );
  if ( fabs( p ) <= fabs( s ) ) return ( s * p > 0 ? 0 : M_PI );
  return acos( s / p );
}

PDUtil::number PDUtil::angleSphe( number t1, number e1, number p1,
                                  number t2, number e2, number p2 ) {
  number x1;
  number y1;
  number z1;
  number x2;
  number y2;
  number z2;
  convSpheCart( t1, e1, p1, x1, y1, z1 );
  convSpheCart( t2, e2, p2, x2, y2, z2 );
  return angleCart( x1, y1, z1, x2, y2, z2 );
}

PDUtil::number PDUtil::ptCart( number px, number py, number pz,
                               number qx, number qy, number qz ) {
  number s = ( px * qx ) + ( py * qy ) + ( pz * qz );
  number p = modSqua( px, py, pz );
  number q = modSqua( qx, qy, qz );
//  number p = v * z;
  number z = ( s * s ) / ( p * q );
  number f = ( z < 1.0 ? sqrt( 1.0 - z ) : 0.0 );
//  number f = ( p > fabs( s ) ? sqrt( 1.0 - ( ( s * s ) / ( p * q ) ) ) : 0.0 );
  return sqrt( p ) * f;
}

PDUtil::number PDUtil::ptSphe( number pt, number pe, number pp,
                                          number qe, number qp ) {
  number px;
  number py;
  number pz;
  number qx;
  number qy;
  number qz;
  convSpheCart(  pt, pe, pp, px, py, pz );
  convSpheCart( 1.0, qe, qp, qx, qy, qz );
  return ptCart( px, py, pz, qx, qy, qz );
}

PDUtil::number PDUtil::plCart( number px, number py, number pz,
                               number qx, number qy, number qz ) {
  return ( ( px * qx ) + ( py * qy ) + ( pz * qz ) ) / modCart( qx, qy, qz );
}

PDUtil::number PDUtil::plSphe( number pt, number pe, number pp,
                                          number qe, number qp ) {
  number px;
  number py;
  number pz;
  number qx;
  number qy;
  number qz;
  convSpheCart(  pt, pe, pp, px, py, pz );
  convSpheCart( 1.0, qe, qp, qx, qy, qz );
  return plCart( px, py, pz, qx, qy, qz );
}

PDUtil::number PDUtil::transf( number  px, number  py,
                               number  pz, number  ep,
                               number  qx, number  qy,
                               number  qz, number  eq,
                               number& tx, number& ty,
                               number& tz, number& et ) {
  number s = ( px * qx ) + ( py * qy ) + ( pz * qz );
  number p = modSqua( px, py, pz );
  number q = modSqua( qx, qy, qz );
  number z = ( s * s ) / ( p * q );
  number f = ( z < 1.0 ? sqrt( 1.0 - z ) : 0.0 );
  p = sqrt( p );
  q = sqrt( q );
//  std::cout << p << " " << q << std::endl;
//  std::cout << ep << " " << eq << std::endl;
  number b = q / eq;
//  std::cout << b << std::endl;
  number g = 1.0 / sqrt( 1.0 - ( b * b ) );
//  std::cout << g << std::endl;
  number pt = p * f;
  number pl = s / q;
//  std::cout << pt << " " << pl << std::endl;
  number tl = g * ( pl - ( b * ep ) );
//  std::cout << tl << std::endl;
  number at = atan( pt / tl );
//  std::cout << at << std::endl;
  et = g * ( ep - ( b * pl ) );
//  std::cout << et << std::endl;
  if ( at < 0.0 ) at += M_PI;
  tx = px + ( ( tl - pl ) * qx / q );
  ty = py + ( ( tl - pl ) * qy / q );
  tz = pz + ( ( tl - pl ) * qz / q );
//  std::cout << "---->" << std::endl;
  return at;
}

PDUtil::number PDUtil::ptCMin( number px, number py, number pz,
                               number qx, number qy, number qz ) {
  number s = ( px * qx ) + ( py * qy ) + ( pz * qz );
  number p = modSqua( px, py, pz );
  number q = modSqua( qx, qy, qz );
  number t = p * q;
  number f = ( fabs ( t ) > fabs( s ) ? sqrt( 1.0 - ( s * s / t ) ) : 1.0 );
  return ( p < q ? sqrt( p ) * f : sqrt( q ) * f );
}

PDUtil::number PDUtil::ptSMin( number pt, number pe, number pp,
                               number qt, number qe, number qp ) {
  number px;
  number py;
  number pz;
  number qx;
  number qy;
  number qz;
  convSpheCart(  pt, pe, pp, px, py, pz );
  convSpheCart( 1.0, qe, qp, qx, qy, qz );
  return ptCMin( px, py, pz, qx, qy, qz );
}

PDUtil::number PDUtil::ptCMax( number px, number py, number pz,
                               number qx, number qy, number qz ) {
  number s = ( px * qx ) + ( py * qy ) + ( pz * qz );
  number p = modSqua( px, py, pz );
  number q = modSqua( qx, qy, qz );
  number t = p * q;
  number f = ( fabs ( t ) > fabs( s ) ? sqrt( 1.0 - ( s * s / t ) ) : 1.0 );
  return ( p > q ? sqrt( p ) * f : sqrt( q ) * f );
}

PDUtil::number PDUtil::ptSMax( number pt, number pe, number pp,
                               number qt, number qe, number qp ) {
  number px;
  number py;
  number pz;
  number qx;
  number qy;
  number qz;
  convSpheCart(  pt, pe, pp, px, py, pz );
  convSpheCart( 1.0, qe, qp, qx, qy, qz );
  return ptCMax( px, py, pz, qx, qy, qz );
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


void PDUtil::associateObjects( const std::vector<number>& lObjPt,
                               const std::vector<number>& lObjEta,
                               const std::vector<number>& lObjPhi,
                               const std::vector<number>& lObjPx,
                               const std::vector<number>& lObjPy,
                               const std::vector<number>& lObjPz,
                               const std::vector<number>& rObjPt,
                               const std::vector<number>& rObjEta,
                               const std::vector<number>& rObjPhi,
                               const std::vector<number>& rObjPx,
                               const std::vector<number>& rObjPy,
                               const std::vector<number>& rObjPz,
                               ObjectDistance& objDist,
                               ObjectSelection& lObjSel,
                               ObjectSelection& rObjSel,
                               bool singleAssociation,
                               std::vector<ObjectAssociation>& assoc ) {
  int nl = lObjPt.size();
  int nr = rObjPt.size();
  int il;
  int ir;
  number lPt;
  number lEta;
  number lPhi;
  number lPx;
  number lPy;
  number lPz;
  number dMin;
  number dCur;
  int iAss;
  ObjectAssociation noAss;
  noAss.iObj = -1;
  noAss.dist = objDist.dMax();
  assoc.clear();
  assoc.resize( nl, noAss );
  std::set<int> used;
  for ( il = 0; il < nl; ++il ) {
    if ( !lObjSel( il ) ) continue;
    iAss = -1;
    dMin = objDist.dMax();
    lPt  = lObjPt [il];
    lEta = lObjEta[il];
    lPhi = lObjPhi[il];
    lPx  = lObjPx [il];
    lPy  = lObjPy [il];
    lPz  = lObjPz [il];
    for ( ir = 0; ir < nr; ++ir ) {
      if ( !rObjSel( ir ) ) continue;
      if ( singleAssociation && ( used.find( ir ) != used.end() ) ) continue;
      dCur = objDist(    lPt    ,     lEta    ,    lPhi,
                         lPx    ,     lPy     ,    lPz,
                      rObjPt [ir], rObjEta[ir], rObjPhi[ir],
                      rObjPx [ir], rObjPy [ir], rObjPz [ir] );
      if ( dCur < dMin ) {
        iAss = ir;
        dMin = dCur;
      }
    }
    if ( iAss < 0 ) continue;
    used.insert( iAss );
    assoc[il].dist = dMin;
    assoc[il].iObj = iAss;
  }
  return;
}

