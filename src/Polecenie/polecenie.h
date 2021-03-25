#ifndef Polecenie_H
#define Polecenie_H
//#include <gtkmm.h>
//#include <gtkglmm.h>
#include <iostream>
#include <memory>

using namespace std;
//using namespace Gtk;

//template
class Polecenie
{
  public:
    Polecenie();
    virtual ~Polecenie();
    
    template<typename T_Obsluga>
    void PobierzDane(T_Obsluga obsluga);
    
	
protected:

private:
        
};
template<typename T_Obsluga>
void Polecenie::PobierzDane(T_Obsluga obsluga)
{
    obsluga.DoTransformacji();
}
using spPolecenie = shared_ptr<Polecenie>;
using upPolecenie = unique_ptr<Polecenie>;
#endif // Polecenie_H
