#include "obracanie.h"
#include "trackball.h"
//../../lib/

void Obracanie::PobierzPierwotnePolozenie(int x, int y)
{
	prev_x = x; prev_y = y;
    cout<<"\npierwotne położenie "<<x<<" "<<y;
}
void Obracanie::PobierzPolozenieAktualne(int ex, int ey)
{
	x = ex;
    y = ey;
}
void Obracanie::PobierzWymiaryEkranu(int ew, int eh)
{
	w = ew; h = eh;
    cout<<"\nwymiary ekranu "<<w<<" "<<h;
}

void Obracanie::ObliczWektorPrzesuniecia()
{
	przesuniecie_x = x - prev_x;
	przesuniecie_y = y - prev_y;
    prev_x = x;
    prev_y = y;
    cout<<"\n przesunięcie" <<przesuniecie_x<<" "<<przesuniecie_y;
}
void Obracanie::ObliczMacierzObrotu()
{
	/*
    Trackball::trackball(aktualneSterowanie->m_QuatDiff,
                       (2.0 * aktualneSterowanie->m_BeginX - w) / w,
                       (h - 2.0 * aktualneSterowanie->m_BeginY) / h,
                       (2.0 * x - w) / w,
                       (h - 2.0 * y) / h);
//    if(aktualneSterowanie == wybranegoObiektu)KorekcjaOsiObrotuWybranegoModelu();
    Trackball::add_quats(aktualneSterowanie->m_QuatDiff, aktualneSterowanie->m_Quat, aktualneSterowanie->m_Quat);
    Trackball::build_rotmatrix(aktualneSterowanie->macierzObrotu, aktualneSterowanie->m_Quat);
    */
    //należy uzyskać dostęp do zmiennych:
//    m_QuatDiff
//    m_Quat
//    wymiary ekranu
//    macierz_obrotu
}

