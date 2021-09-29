#ifndef GemoetriaModelu_H
#define GemoetriaModelu_H
//#include <gtkmm.h>
//#include <gtkglmm.h>
#include <iostream>
#include <memory>
#include "transformowalne.h"
#include "grupowalne.h"


using namespace std;
//using namespace Gtk;

class GeometriaModelu : public Transformowalne
{

public:
    GeometriaModelu();
    virtual ~GeometriaModelu();
    
    
    unsigned short* indeksyVertexow = nullptr;
    unsigned short* schematNormalnych = nullptr;
    float * wspolrzedneVrtx = nullptr;
    float * normalne = nullptr;
    unsigned short ileVertexow = 0;
    unsigned short ileNormalnych = 0;
    void DoVertexowDodajWektor(float *);
	
protected:
    
private:
    
    
};
using spGeometriaModelu = shared_ptr<GeometriaModelu>;
using upGeometriaModelu = unique_ptr<GeometriaModelu>;
#endif // DoNarysowania_H
