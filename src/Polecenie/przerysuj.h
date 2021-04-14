#ifndef Przerysuj_H
#define Przerysuj_H
//#include <gtkmm.h>
//#include <gtkglmm.h>
#include <iostream>
#include <memory>
#include "polecenie.h"
#include "obslugapolecen.h"

using namespace std;
//using namespace Gtk;


    


class Przerysuj : public Polecenie
{
  public:
    Przerysuj(){};
    virtual ~Przerysuj();
    virtual void WykonajW(ObslugaPolecen& ) override ;
	
protected:

private:
        
};
using spPrzerysuj = shared_ptr<Przerysuj>;
using upPrzerysuj = unique_ptr<Przerysuj>;


#endif // Przerysuj_H
