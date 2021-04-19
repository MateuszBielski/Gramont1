#ifndef DoNarysowania_H
#define DoNarysowania_H
//#include <gtkmm.h>
//#include <gtkglmm.h>
#include <iostream>
#include <memory>
#include "transformowalne.h"

using namespace std;
//using namespace Gtk;


class DoNarysowania : public Transformowalne
{
  public:
    DoNarysowania();
    virtual ~DoNarysowania();
    
    unsigned short* indeksyNaroznikow = nullptr;
    float * wspolrzedne = nullptr;
    unsigned short ileNaroznikow = 0;
	
protected:

private:
        
};
using spDoNarysowania = shared_ptr<DoNarysowania>;
using upDoNarysowania = unique_ptr<DoNarysowania>;
#endif // DoNarysowania_H
