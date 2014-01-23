#ifndef PDGenealogy_h
#define PDGenealogy_h

#include <vector>
#include <set>
#include <map>
#include <string>

#include "PDAnalysis/Ntu/interface/PDNtupleData.h"

class PDGenealogy: public virtual PDNtupleData {

 public:

  PDGenealogy();
  ~PDGenealogy();

  static void print( const std::vector<int>* genId,
                     const std::vector<int>* genMother );

  void reshuffleFw( std::vector<int>* newMother,
		    std::vector<int>* newPartner );
  void reshuffleBw( std::vector<int>* newMother,
                    std::vector<int>* newPartner );

  const std::map< int, std::vector<int> >& allMothers();
  const std::map< int, std::vector<int> >& allDaughters();
  const std::map< int, std::vector<int> >& finalDescendants();

  int ancestors( int iGen );
  class TypeSelect {
   public:
    TypeSelect() { sel = 0; m = '\0'; }
    TypeSelect( int id, char mode = 't' ) { sel = id; m = mode; }
    virtual bool operator()( int id ) const {
      switch ( m ) {
      case 't': return genId->at( id ) == sel;
      case 'p': return id == sel;
      }
      return false;
    }
    virtual int dmax() const { return -1; }
    static std::vector<int>* genId;
   private:
    int sel;
    char m;
  };
  std::multimap<int,int>& findAncestor( int iGen, const TypeSelect& sel );
  bool hasAncestors( int iGen, int ns, const TypeSelect** sel );
  std::multimap<int,int>& findDescendant( int iGen, const TypeSelect& sel );
//  bool hasDescendants( int iGen, int ns, const TypeSelect** sel );

  int sameMother( int iGen );
  int sameDaughter( int iGen );

 private:

  static void print( const std::string& head, int iPart, int level = 0 );

  void newEvent();
  void addDaughters( int iGen, std::set<int>& dSet ); 

  unsigned int lastRun;
  unsigned int lastLumi;
  unsigned int lastEvent;

  bool   mothersFound;
  bool daughtersFound;
  bool     finalFound;
  std::map< int, std::vector<int> >   mothersCache;
  std::map< int, std::vector<int> > daughtersCache;
  std::map< int, std::vector<int> >     finalCache;
  std::map< const TypeSelect*, std::map< int, std::multimap<int,int> > >
      ancestorsCache;
  std::map< const TypeSelect*, std::map< int, std::multimap<int,int> > >
    descendantsCache;
//  std::map< int, std::map< const TypeSelect*, std::multimap<int,int> > >
//      ancestorsCache;
//  std::map< int, std::map< const TypeSelect*, std::multimap<int,int> > >
//    descendantsCache;

  const static std::vector<int>* ids;
  const static std::vector<int>* mothers;
  static std::map< int, std::vector<int> > daughters;

  PDGenealogy           ( const PDGenealogy& a );
  PDGenealogy& operator=( const PDGenealogy& a );

};

#endif

