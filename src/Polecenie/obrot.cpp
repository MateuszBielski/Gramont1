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
    float quat_diff[4];
    float quat[4];
    for(short i = 0 ; i < 4 ;i++)
        {
            quat_diff[i] = transformowalne->QuatDiff()[i];
            quat[i] = transformowalne->Quat()[i];
        }
    Trackball::trackball(quat_diff,
                       ruch.p1x,
                       ruch.p1y,
                       ruch.p2x,
                       ruch.p2y);
//    if(aktualneSterowanie == wybranegoObiektu)KorekcjaOsiObrotuWybranegoModelu();
    float quatNew[4];
    Trackball::add_quats(quat_diff, quat, quatNew);
    
//    cout<<"\nXXXXXXXXXXXQuat\n";
//    for(short i = 0 ; i < 4 ; i++)cout<<transformowalne->Quat()[i]<<" ";
    
    float macierz[4][4];
    Trackball::build_rotmatrix(macierz,quatNew);
    transformowalne->Quat(quatNew);
    transformowalne->MacierzObrotu(macierz[0]);
    obs.PowiadomionyOzakonczeniuTransformacji();
//    obs.WyslijPoleceniePrzerysuj();
}
