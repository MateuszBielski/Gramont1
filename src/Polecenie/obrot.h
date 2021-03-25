#ifndef Obrot_H
#define Obrot_H
//#include <gtkmm.h>
//#include <gtkglmm.h>
#include <iostream>
#include <memory>
//#include "transformacja.h"
#include "polecenie.h"

using namespace std;
//using namespace Gtk;

template<typename T>
class Obrot : public TemplatePolecenie<T>//public Transformacja
{
//    sTransformowalne doTransformacji
    public:
    explicit Obrot(shared_ptr<T> obslugujacy):TemplatePolecenie<T>::TemplatePolecenie(obslugujacy)
    {
        
        };
    virtual ~Obrot(){};
    virtual void Wykonaj()
    {
        TemplatePolecenie<T>::obslugujacy->DoTransformacji();
    };
	
protected:

private:
        
};
//using spObrot = shared_ptr<Obrot>;
//using upObrot = unique_ptr<Obrot>;
#endif // Obrot_H
