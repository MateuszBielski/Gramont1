#ifndef Obrot_H
#define Obrot_H
#include <iostream>
//#include <memory>
//#include "polecenie.h"
#include "transformacja.h"
#include "obslugapolecen.h"


using namespace std;

class Obrot : public Transformacja
{
    
public:
   Obrot(){};
   Obrot(RuchNaEkranie&& );
    virtual
    void WykonajW(ObslugaPolecen& ) override;



protected:

private: 
};

#endif // Obrot_H
