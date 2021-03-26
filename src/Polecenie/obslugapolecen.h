#ifndef ObslugaPolecen_H
#define ObslugaPolecen_H
//#include <gtkmm.h>
//#include <gtkglmm.h>
#include <iostream>
#include <memory>
//#include "kolejkapolecen.h"

using namespace std;
//using namespace Gtk;


class ObslugaPolecen
{
//    using Kolejka = KolejkaPolecen<ObslugaPolecen>;
//    KolejkaPolecen<ObslugaPolecen> kolejka;
//    public:
//    ObslugaPolecen();
//    virtual ~ObslugaPolecen();
//    KolejkaPolecen<ObslugaPolecen>& KolejkaRef(){};//return kolejka;
    
	
protected:

private:
        
};
using spObslugaPolecen = shared_ptr<ObslugaPolecen>;
using upObslugaPolecen = unique_ptr<ObslugaPolecen>;
#endif // ObslugaPolecen_H
