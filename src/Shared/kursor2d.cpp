#include "kursor2d.h"



void Kursor2D::PobierzPierwotnePolozenie(int x, int y)
{
    prev_x = x; prev_y = y;
}

void Kursor2D::PobierzWymiaryEkranu(int ew, int eh)
{
    w = ew; h = eh;
}

RuchNaEranie Kursor2D::ObliczRuch(int x, int y)
{
    RuchNaEranie ruch;
    ruch.x = x - prev_x;
	ruch.y = y - prev_y;
    
    ruch.p1x = (2.0 * prev_x - w)/w;
    ruch.p1y = (h - 2.0 * prev_y)/h;
    ruch.p2x = (2.0 * x - w)/w;
    ruch.p2y = (h - 2.0 * y)/h;
    
    prev_x = x;
    prev_y = y;
    return ruch;
}
