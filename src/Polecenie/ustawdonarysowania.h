#ifndef UstawDoNarysowania_H
#define UstawDoNarysowania_H
#include "polecenie.h"
#include "obslugapolecen.h"

using namespace std;


class UstawDoNarysowania : public Polecenie
{
    spDoNarysowania doNarysowania = nullptr;
public:
    UstawDoNarysowania(spDoNarysowania rys):doNarysowania(rys){};
    virtual void WykonajW(ObslugaPolecen& ) override ;
   
    protected:

    private:
        
};

#endif // UstawDoNarysowania_H
