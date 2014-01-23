#ifndef PDUtil_H
#define PDUtil_H

#include "PDAnalysis/Ntu/interface/PDNtupleData.h"

class PDUtil: public virtual PDNtupleData {

 public:

  PDUtil();
  virtual ~PDUtil();

  static number energy( number px, number py, number pz, number mm );
  static number invMass( number px , number  py , number  pz,  number ee );
  static number invMass( number px1, number  py1, number  pz1, number ee1,
                         number px2, number  py2, number  pz2, number ee2 );
  static number invMass( number px1, number  py1, number  pz1, number ee1,
                         number px2, number  py2, number  pz2, number ee2,
                         number px3, number  py3, number  pz3, number ee3 );
  static number invMass( number px1, number  py1, number  pz1, number ee1,
                         number px2, number  py2, number  pz2, number ee2,
                         number px3, number  py3, number  pz3, number ee3,
                         number px4, number  py4, number  pz4, number ee4 );
  static number invMSph( number pt , number eta , number phi,  number ee );
  static number invMSph( number pt1, number eta1, number phi1, number ee1,
                         number pt2, number eta2, number phi2, number ee2 );
  static number invMSph( number pt1, number eta1, number phi1, number ee1,
                         number pt2, number eta2, number phi2, number ee2,
                         number pt3, number eta3, number phi3, number ee3 );
  static number invMSph( number pt1, number eta1, number phi1, number ee1,
                         number pt2, number eta2, number phi2, number ee2,
                         number pt3, number eta3, number phi3, number ee3,
                         number pt4, number eta4, number phi4, number ee4 );
  static number invMass_M( number px1, number  py1, number  pz1, number mm1,
                           number px2, number  py2, number  pz2, number mm2 );
  static number invMass_M( number px1, number  py1, number  pz1, number mm1,
                           number px2, number  py2, number  pz2, number mm2,
                           number px3, number  py3, number  pz3, number mm3 );
  static number invMass_M( number px1, number  py1, number  pz1, number mm1,
                           number px2, number  py2, number  pz2, number mm2,
                           number px3, number  py3, number  pz3, number mm3,
                           number px4, number  py4, number  pz4, number mm4 );
  static number invMSph_M( number pt1, number eta1, number phi1, number mm1,
                           number pt2, number eta2, number phi2, number mm2 );
  static number invMSph_M( number pt1, number eta1, number phi1, number mm1,
                           number pt2, number eta2, number phi2, number mm2,
                           number pt3, number eta3, number phi3, number mm3 );
  static number invMSph_M( number pt1, number eta1, number phi1, number mm1,
                           number pt2, number eta2, number phi2, number mm2,
                           number pt3, number eta3, number phi3, number mm3,
                           number pt4, number eta4, number phi4, number mm4 );
  static number dSqua( number a1, number b1,
                       number a2, number b2 );
  static number dSqua( number a1, number b1, number c1,
                       number a2, number b2, number c2 );
  static number delta( number a1, number b1,
                       number a2, number b2 );
  static number delta( number a1, number b1, number c1,
                       number a2, number b2, number c2 );
  static number dRSqua( number eta1, number phi1,
                        number eta2, number phi2 );
  static number deltaR( number eta1, number phi1,
                        number eta2, number phi2 );

  static number modCart( number x, number y, number z );
  static number modSphe( number t, number e );

  static number angleCart( number x1, number y1, number z1,
                           number x2, number y2, number z2 );
  static number angleSphe( number t1, number e1, number p1,
                           number t2, number e2, number p2 );

  static void convCartSphe( number  x, number  y, number  z,
                            number& t, number& e, number& p );
  static void convSpheCart( number  t, number  e, number  p,
                            number& x, number& y, number& z );
  static void convCartSphe( const std::vector<number>* x,
                            const std::vector<number>* y,
                            const std::vector<number>* z,
                                  std::vector<number>* t,
                                  std::vector<number>* e,
                                  std::vector<number>* p, int i = -1 );
  static void convSpheCart( const std::vector<number>* t,
                            const std::vector<number>* e,
                            const std::vector<number>* p,
                                  std::vector<number>* x,
                                  std::vector<number>* y,
                                  std::vector<number>* z, int i = -1 );

 private:

  // dummy copy and assignment constructors
  PDUtil( const PDUtil& );
  PDUtil& operator=( const PDUtil& );

};


#endif

