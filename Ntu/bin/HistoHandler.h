#ifndef HistoHandler_H
#define HistoHandler_H

#include "TH1.h"
#include "TH2.h"

#include <map>
#include <string>

class HistoHandler {

 public:

  static TH1F* book1F( const std::string& name, int id,
                        int nb, float xmin, float xmax ) {
    return book1<TH1F>( name, name, id, nb, xmin, xmax );
  }
  static TH1F* book1F( const std::string& name,
                        const std::string& title, int id,
                        int nb, float xmin, float xmax ) {
    return book1<TH1F>( name, title, id, nb, xmin, xmax );
  }
  static TH2F* book2F( const std::string& name, int id,
                        int nx, float xmin, float xmax,
                        int ny, float ymin, float ymax ) {
    return book2<TH2F>( name, name, id, nx, xmin, xmax, ny, ymin, ymax );
  }
  static TH2F* book2F( const std::string& name,
                        const std::string& title, int id,
                        int nx, float xmin, float xmax,
                        int ny, float ymin, float ymax ) {
    return book2<TH2F>( name, title, id, nx, xmin, xmax, ny, ymin, ymax );
  }
  static TH1D* book1D( const std::string& name, int id,
                        int nb, float xmin, float xmax ) {
    return book1<TH1D>( name, name, id, nb, xmin, xmax );
  }
  static TH1D* book1D( const std::string& name,
                        const std::string& title, int id,
                        int nb, float xmin, float xmax ) {
    return book1<TH1D>( name, title, id, nb, xmin, xmax );
  }
  static TH2D* book2D( const std::string& name, int id,
                        int nx, float xmin, float xmax,
                        int ny, float ymin, float ymax ) {
    return book2<TH2D>( name, name, id, nx, xmin, xmax, ny, ymin, ymax );
  }
  static TH2D* book2D( const std::string& name,
                        const std::string& title, int id,
                        int nx, float xmin, float xmax,
                        int ny, float ymin, float ymax ) {
    return book2<TH2D>( name, title, id, nx, xmin, xmax, ny, ymin, ymax );
  }

  static TH1F* get1F( const std::string& name, int id ) {
    return dynamic_cast<TH1F*>( histoMap()[name][id] );
  }
  static TH1D* get1D( const std::string& name, int id ) {
    return dynamic_cast<TH1D*>( histoMap()[name][id] );
  }
  static TH2F* get2F( const std::string& name, int id ) {
    return dynamic_cast<TH2F*>( histoMap()[name][id] );
  }
  static TH2D* get2D( const std::string& name, int id ) {
    return dynamic_cast<TH2D*>( histoMap()[name][id] );
  }


 private:

  typedef std::map<int,TObject*> obj_map;
  typedef std::map<std::string,obj_map> list_map;

  static list_map& histoMap() {
    static list_map hm;
    return hm;
  }

  template<class T>
  static T* book1( const std::string& name, const std::string& title, int id,
                   int nb, float xmin, float xmax ) {
    std::stringstream tstream;
    tstream.clear();
    tstream.str( "" );
    tstream << title;
    if ( id > 0 ) tstream << id;
    else          id = -id;
    std::stringstream nstream;
    nstream.clear();
    nstream.str( "" );
    nstream << name << id;
    T* hh = new T( nstream.str().c_str(), tstream.str().c_str(),
                   nb, xmin, xmax );
    histoMap()[name][id] = hh;
    return hh;
  }
  template<class T>
  static T* book2( const std::string& name, const std::string& title, int id,
                   int nx, float xmin, float xmax,
                   int ny, float ymin, float ymax ) {
    std::stringstream tstream;
    tstream.clear();
    tstream.str( "" );
    tstream << title;
    if ( id > 0 ) tstream << id;
    else          id = -id;
    std::stringstream nstream;
    nstream.clear();
    nstream.str( "" );
    nstream << name << id;
    T* hh = new T( nstream.str().c_str(), tstream.str().c_str(),
                   nx, xmin, xmax, ny, ymin, ymax );
    histoMap()[name][id] = hh;
    return hh;
  }

};

#endif
