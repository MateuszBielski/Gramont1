#ifndef TransformacjaItfc_H
#define TransformacjaItfc_H
//#include <gtkmm.h>
//#include <gtkglmm.h>
#include <iostream>
#include <memory>
#include "ruchnaekranie.h"
#include "transformowalne.h"

using namespace std;
//using namespace Gtk;


class TransformacjaItfc
{
    spTransformowalne transformowalne;
  public:
    TransformacjaItfc();
    virtual ~TransformacjaItfc();
    virtual void Obracaj(RuchNaEkranie&& );
    void Transformowalne(spTransformowalne );
	
protected:

private:
        
};
using spTransformacjaItfc = shared_ptr<TransformacjaItfc>;
using upTransformacjaItfc = unique_ptr<TransformacjaItfc>;
#endif // Transformacja_H
