#include "prostytrojkat.h"

ProstyTrojkat::ProstyTrojkat():m_indeksyVertexow{0,1,2},m_wspolrzedneVrtx{-1,0,0,1,0,0,0,1,0}
{
    indeksyVertexow = &m_indeksyVertexow[0];
    ileVertexow = 3;
    wspolrzedneVrtx = &m_wspolrzedneVrtx[0];
}

ProstyTrojkat::~ProstyTrojkat()
{

}

