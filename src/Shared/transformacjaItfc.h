#ifndef Transformacja_H
#define Transformacja_H
#include <gtkmm.h>
#include <gtkglmm.h>
#include <iostream>
#include <memory>

using namespace std;
using namespace Gtk;


class TransformacjaItfc
{
  public:
    TransformacjaItfc();
    virtual ~TransformacjaItfc();
    void Obracaj(RuchNaEkranie&& );
	
protected:

private:
        
};
using spTransformacjaItfc = shared_ptr<TransformacjaItfc>;
using upTransformacjaItfc = unique_ptr<TransformacjaItfc>;
#endif // Transformacja_H
