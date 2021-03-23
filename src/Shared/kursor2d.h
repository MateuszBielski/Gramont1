#ifndef Kursor2D_H
#define Kursor2D_H
#include "ruchnaekranie.h"

using namespace std;
//using namespace Gtk;


class Kursor2D
{

    int x = 0,y = 0,prev_x = 0,prev_y = 0,przesuniecie_x = 0,przesuniecie_y = 0;
    int w = 1, h = 1;
  public:
    void PobierzPierwotnePolozenie(int,int);
    void PobierzWymiaryEkranu(int,int);
    RuchNaEkranie ObliczRuch(int,int);
   
    protected:

    private:
        
};

#endif // Kursor2D_H
