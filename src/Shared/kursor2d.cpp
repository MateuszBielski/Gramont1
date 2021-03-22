#include "kursor2d.h"



void Kursor2D::PobierzPierwotnePolozenie(int x, int y)
{
    prev_x = x; prev_y = y;
}

void Kursor2D::PobierzWymiaryEkranu(int ew, int eh)
{
    w = ew; h = eh;
}

void Kursor2D::ObliczRuch(int x, int y)
{
    przesuniecie_x = x - prev_x;
	przesuniecie_y = y - prev_y;
    prev_x = x;
    prev_y = y;
}
