#ifndef Transformowalne_H
#define Transformowalne_H
#include <gtkmm.h>
#include <gtkglmm.h>
#include <iostream>
#include <memory>

using namespace std;
using namespace Gtk;

typedef float (*pf4)[4];

class Transformowalne
{
    float m_quatDiff[4];
    float m_quat[4];
    float m_macierzObrotu[4][4];
    float m_pozycja[3];//pojęcie niejasne i nie praktyczne
    float m_przesuniecie[3];
    
    public:
    Transformowalne();
    virtual ~Transformowalne();
    float* QuatDiff();
    void QuatDiff(float* );
    float* Quat();
    void    Quat(float* );
    virtual float* MacierzObrotu();
    pf4 ppMacierzObrotu();
    
    void MacierzObrotu(float*);
    virtual float* Przesuniecie();
    void UstawPrzesuniecie(float* );
    void DodajPrzesuniecie(float* );
    bool jestTransformacja ;
	
protected:
    bool jestPrzesuniecie = false;
    bool jestObrot = false;
private:
    
        
};
using spTransformowalne = shared_ptr<Transformowalne>;
using upTransformowalne = unique_ptr<Transformowalne>;
#endif // Transformowalne_H
