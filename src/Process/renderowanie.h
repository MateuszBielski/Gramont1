#ifndef Renderowanie_H
#define Renderowanie_H
#include <gtkmm.h>
#include <gtkglmm.h>
#include <iostream>
#include <memory>

using namespace std;
using namespace Gtk;


class Renderowanie
{
  public:
    Renderowanie();
    virtual ~Renderowanie();
	
protected:

private:
        
};
using spRenderowanie = shared_ptr<Renderowanie>;
using upRenderowanie = unique_ptr<Renderowanie>;
#endif // Renderowanie_H
