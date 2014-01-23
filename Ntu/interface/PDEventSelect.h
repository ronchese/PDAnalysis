#ifndef PDEventSelect_H
#define PDEventSelect_H

#include <set>
#include <string>

class PDEventSelect {

 public:

  PDEventSelect();
  virtual ~PDEventSelect();

  virtual bool read( const std::string& name );
  virtual bool find( unsigned int run, unsigned int event );

 private:

  // dummy copy and assignment constructors
  PDEventSelect( const PDEventSelect& );
  PDEventSelect& operator=( const PDEventSelect& );

  struct ev_id {
    unsigned int run;
    unsigned int event;
  };
  class ev_compare {
   public:
    bool operator()( const ev_id& l, const ev_id& r ) const {
      if ( l.run   < r.run   ) return true;
      if ( l.run   > r.run   ) return false;
      if ( l.event < r.event ) return true;
      return false;
    }
    static ev_compare instance;
  };
  std::set<ev_id, ev_compare> eventSet;

};


#endif

