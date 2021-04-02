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
    
    public:
    Transformowalne();
    virtual ~Transformowalne();
    float* QuatDiff();
    void QuatDiff(float* );
    float* Quat();
    void    Quat(float* );
    float* MacierzObrotu();
    pf4 ppMacierzObrotu();
    
    void MacierzObrotu(float*);
	
protected:

private:
        
};
using spTransformowalne = shared_ptr<Transformowalne>;
using upTransformowalne = unique_ptr<Transformowalne>;
#endif // Transformowalne_H