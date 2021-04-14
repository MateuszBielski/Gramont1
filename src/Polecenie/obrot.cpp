#include "obrot.h"
#include "../Shared/trackball.h"


Obrot::Obrot(RuchNaEkranie&& r)
{
    ruch = move(r);
}
void Obrot::WykonajW(ObslugaPolecen& obs)
{
    
    auto transformowalne = obs.DoTransformacji();
    if (!transformowalne)return;
    Trackball::trackball(transformowalne->QuatDiff(),
                       ruch.p1x,
                       ruch.p1y,
                       ruch.p2x,
                       ruch.p2y);
//    if(aktualneSterowanie == wybranegoObiektu)KorekcjaOsiObrotuWybranegoModelu();
    Trackball::add_quats(transformowalne->QuatDiff(), transformowalne->Quat(), transformowalne->Quat());
//    cout<<"\nXXXXXXXXXXXQuat\n";
//    for(short i = 0 ; i < 4 ; i++)cout<<transformowalne->Quat()[i]<<" ";
    
//    float macierz[4][4];
    Trackball::build_rotmatrix(transformowalne->ppMacierzObrotu(), transformowalne->Quat());
    obs.PowiadomionyOzakonczeniuTransformacji();
    obs.WyslijPoleceniePrzerysuj();
}
