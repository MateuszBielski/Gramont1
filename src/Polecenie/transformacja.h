#ifndef Transformacja_H
#define Transformacja_H
//#include <gtkmm.h>
//#include <gtkglmm.h>
#include <iostream>
#include <memory>
#include "polecenie.h"

using namespace std;
//using namespace Gtk;


template<typename T>
class Transformacja : public TemplatePolecenie<T>
{
public:
    Transformacja();
    virtual ~Transformacja();
    
    

protected:

private:

};
//using spTransformacja = shared_ptr<Transformacja>;
//using upTransformacja = unique_ptr<Transformacja>;
#endif // Transformacja_H
