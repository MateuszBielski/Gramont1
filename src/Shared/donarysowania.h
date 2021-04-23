#ifndef DoNarysowania_H
#define DoNarysowania_H
//#include <gtkmm.h>
//#include <gtkglmm.h>
#include <iostream>
#include <memory>
#include "transformowalne.h"
#include "grupowalne.h"

using namespace std;
//using namespace Gtk;


class DoNarysowania : public Transformowalne, public Grupowalne
{

public:
    DoNarysowania();
    virtual ~DoNarysowania();
    
    
    unsigned short* indeksyVertexow = nullptr;
    unsigned short* schematNormalnych = nullptr;
    float * wspolrzedneVrtx = nullptr;
    float * normalne = nullptr;
    unsigned short ileVertexow = 0;
    unsigned short ileNormalnych = 0;
	
protected:
    
private:
    
};
using spDoNarysowania = shared_ptr<DoNarysowania>;
using upDoNarysowania = unique_ptr<DoNarysowania>;
#endif // DoNarysowania_H
