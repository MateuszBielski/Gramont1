#ifndef Obrot_H
#define Obrot_H
#include <iostream>
#include <memory>
//#include "polecenie.h"
#include "transformacja.h"

using namespace std;

class Obrot : public Transformacja
{
public:
   Obrot(){};
    virtual
    void WykonajW(ObslugaPolecen& ) override;



protected:

private: 
};

template<typename T>
class ObrotTemplate : public TemplatePolecenie<T>
{
    public:
    explicit ObrotTemplate(shared_ptr<T> obslugujacy):TemplatePolecenie<T>::TemplatePolecenie(obslugujacy)
    {
        
        };
    virtual ~ObrotTemplate(){};
    virtual void Wykonaj()
    {
        TemplatePolecenie<T>::obslugujacy->DoTransformacji();
    };
	
protected:

private:
        
};
#endif // Obrot_H
