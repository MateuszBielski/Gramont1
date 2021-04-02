#ifndef Transformacja_H
#define Transformacja_H
//#include <gtkmm.h>
//#include <gtkglmm.h>
#include <iostream>
#include <memory>
#include "polecenie.h"
#include "../Shared/ruchnaekranie.h"

using namespace std;
//using namespace Gtk;


class Transformacja : public Polecenie
{
public:
    virtual
    void WykonajW(ObslugaPolecen& ) override{};
    RuchNaEkranie& Ruch();


protected:
    RuchNaEkranie ruch;

private:

};
//using spTransformacja = shared_ptr<Transformacja>;
using upTransformacja = unique_ptr<Transformacja>;
#endif // Transformacja_H
