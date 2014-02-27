#ifndef PDUtil_H
#define PDUtil_H

#include "PDAnalysis/Ntu/interface/PDNtupleData.h"
#include "map"
#include "math.h"

//
// PDNtupleData is used only to get number typedef
// any other utility based on ntuple structure must stay elsewhere
//

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

  static number modSqua( number x, number y, number z );
  static number modSqua( number t, number e );
  static number modCart( number x, number y, number z )
    { return sqrt( modSqua( x, y, z ) ); }
  static number modSphe( number t, number e )
    { return sqrt( modSqua( t, e ) ); }

  static number angleCart( number x1, number y1, number z1,
                           number x2, number y2, number z2 );
  static number angleSphe( number t1, number e1, number p1,
                           number t2, number e2, number p2 );
  static number angle( number x1, number y1, number z1,
                       number x2, number y2, number z2 ) 
    { return angleCart( x1, y1, z1, x2, y2, z2 ); }
  static number angle( number e1, number p1,
                       number e2, number p2 )
    { return angleSphe( 1.0, e1, p1, 1.0, e2, p2 ); }

  static number ptCart( number px, number py, number pz,
                        number qx, number qy, number qz );
  static number ptSphe( number pt, number pe, number pp,
                                   number qe, number qp );
  static number ptRel ( number px, number py, number pz,
                        number qx, number qy, number qz )
    { return ptCart( px, py, pz, qx, qy, qz ); }
  static number ptRel ( number pt, number pe, number pp,
                                   number qe, number qp )
    { return ptSphe( pt, pe, pp, qe, qp ); }
  static number plCart( number px, number py, number pz,
                        number qx, number qy, number qz );
  static number plSphe( number pt, number pe, number pp,
                                   number qe, number qp );
  static number plRel ( number px, number py, number pz,
                        number qx, number qy, number qz )
    { return plCart( px, py, pz, qx, qy, qz ); }
  static number plRel ( number pt, number pe, number pp,
                                   number qe, number qp )
    { return plSphe( pt, pe, pp, qe, qp ); }

  static number transf( number  px, number  py, number  pz, number  ep,
                        number  qx, number  qy, number  qz, number  eq,
                        number& tx, number& ty, number& tz, number& et );

  static number ptCMin( number px, number py, number pz,
                        number qx, number qy, number qz );
  static number ptSMin( number pt, number pe, number pp,
                        number qt, number qe, number qp );
  static number ptCMax( number px, number py, number pz,
                        number qx, number qy, number qz );
  static number ptSMax( number pt, number pe, number pp,
                        number qt, number qe, number qp );

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

  struct ObjectAssociation {
    int iObj;
    float dist;
  };
  class ObjectSelection {
   public:
    virtual bool operator()( int obj ) { return true; }
  };
  static ObjectSelection dummySel;
  class ObjectDistance {
   public:
    virtual number operator()( number lObjPt , number lObjEta, number lObjPhi,
                               number lObjPx , number lObjPy , number lObjPz ,
                               number rObjPt , number rObjEta, number rObjPhi,
                               number rObjPx , number rObjPy , number rObjPz  )
                               = 0;
    virtual number dMax() { return 1.0e+37; }
  };
  static void associateObjects( const std::vector<number>& lObjPt,
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
                                std::vector<ObjectAssociation>& assoc );

 private:

  // dummy copy and assignment constructors
  PDUtil( const PDUtil& );
  PDUtil& operator=( const PDUtil& );

};


template<class Key,class Val>
class ConstMap {
 public:
  ConstMap<Key,Val>() { cmp = 0; }
  ConstMap<Key,Val>( const Val& v ) { cmp = 0; val = v; }
  ConstMap<Key,Val>( const std::map<Key,Val>& map ) { cmp = &map; }
  ConstMap<Key,Val>( const std::map<Key,Val>& map, const Val& v ) {
    cmp = &map; val = v; }
  const Val& operator[]( Key key ) {
    if ( cmp == 0 ) return val;
    typename std::map<Key,Val>::const_iterator iter = cmp->find( key );
    typename std::map<Key,Val>::const_iterator iend = cmp->end();
    if ( iter != iend ) return iter->second;
    return val;
  }
  ConstMap& operator=( ConstMap& map ) {
    cmp = map.cmp;
    return *this;
  }
  ConstMap& operator=( const std::map<Key,Val>& map ) {
    cmp = &map;
    return *this;
  }
 private:
  const std::map<Key,Val>* cmp;
  Val val;
};


#endif

