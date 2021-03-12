#ifndef Watki_H
#define Watki_H
#include <gtkmm.h>
#include <gtkglmm.h>
#include <iostream>
#include <memory>

using namespace std;
using namespace Gtk;


class Watki
{
  public:
    Watki();
    virtual ~Watki();
	
protected:

private:
        
};
using spWatki = shared_ptr<Watki>;
using upWatki = unique_ptr<Watki>;
#endif // Watki_H
