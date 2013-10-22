#ifndef PDUtil_H
#define PDUtil_H

#include <vector>

class PDUtil {

 public:

  typedef float number;

  PDUtil();
  virtual ~PDUtil();

  static number energy( number px, number py, number pz, number mm );
  static number invMass( number px1, number  py1, number  pz1, number mm1,
                         number px2, number  py2, number  pz2, number mm2 );
  static number invMass( number px1, number  py1, number  pz1, number mm1,
                         number px2, number  py2, number  pz2, number mm2,
                         number px3, number  py3, number  pz3, number mm3 );
  static number invMass( number px1, number  py1, number  pz1, number mm1,
                         number px2, number  py2, number  pz2, number mm2,
                         number px3, number  py3, number  pz3, number mm3,
                         number px4, number  py4, number  pz4, number mm4 );
  static number invMSph( number pt1, number eta1, number phi1, number mm1,
                         number pt2, number eta2, number phi2, number mm2 );
  static number invMSph( number pt1, number eta1, number phi1, number mm1,
                         number pt2, number eta2, number phi2, number mm2,
                         number pt3, number eta3, number phi3, number mm3 );
  static number invMSph( number pt1, number eta1, number phi1, number mm1,
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

