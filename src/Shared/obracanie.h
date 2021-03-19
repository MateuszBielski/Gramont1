#ifndef Obracanie_H
#define Obracanie_H
#include <gtkmm.h>
#include <gtkglmm.h>
#include <iostream>
//#include <memory>

using namespace std;
using namespace Gtk;


class Obracanie 
{
public:
        Obracanie() = default;
        void PobierzWymiaryEkranu(int w, int h);
        void PobierzPierwotnePolozenie(int x, int y);
        void PobierzPolozenieAktualne(int x, int y);
        void ObliczWektorPrzesuniecia();
        void ObliczMacierzObrotu();
protected:

private:
        int x = 0,y = 0,prev_x = 0,prev_y = 0,przesuniecie_x = 0,przesuniecie_y = 0;
        int w = 1, h = 1;
        
};
//using spObracanie = shared_ptr<Obracanie>;
//using upObracanie = unique_ptr<Obracanie>;
#endif // Obracanie_H
