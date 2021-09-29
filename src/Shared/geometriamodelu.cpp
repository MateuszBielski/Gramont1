#include "geometriamodelu.h"

GeometriaModelu::GeometriaModelu()
{

}

GeometriaModelu::~GeometriaModelu()
{

}
void GeometriaModelu::DoVertexowDodajWektor(float* wektor)
{
	for (short i = 0 ; i < ileVertexow ; i++)
    {
        wspolrzedneVrtx[3*i] += wektor[0];
        wspolrzedneVrtx[3*i + 1] += wektor[1];
        wspolrzedneVrtx[3*i + 2] += wektor[2];
    }
}
