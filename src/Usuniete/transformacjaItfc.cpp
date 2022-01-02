#include "transformacjaItfc.h"
#include "trackball.h"

TransformacjaItfc::TransformacjaItfc()
{

}

TransformacjaItfc::~TransformacjaItfc()
{

}
void TransformacjaItfc::Transformowalne(spTransformowalne t)
{
	transformowalne = t;
}
void TransformacjaItfc::Obracaj(RuchNaEkranie&& r)
{
	Trackball::trackball(transformowalne->QuatDiff(),
                       r.p1x,
                       r.p1y,
                       r.p2x,
                       r.p2y);
//    if(aktualneSterowanie == wybranegoObiektu)KorekcjaOsiObrotuWybranegoModelu();
    Trackball::add_quats(transformowalne->QuatDiff(), transformowalne->Quat(), transformowalne->Quat());
//    cout<<"\nXXXXXXXXXXXQuat\n";
//    for(short i = 0 ; i < 4 ; i++)cout<<transformowalne->Quat()[i]<<" ";
    
//    float macierz[4][4];
    Trackball::build_rotmatrix(transformowalne->ppMacierzObrotu(), transformowalne->Quat());
//    Trackball::build_rotmatrix(macierz, transformowalne->Quat());
}
