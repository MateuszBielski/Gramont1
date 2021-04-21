#include "prostytrojkat.h"

ProstyTrojkat::ProstyTrojkat():m_indeksyVertexow{0,1,2},m_wspolrzedneVrtx{-1,0,0,1,0,0,0,1,0},
                    m_normalne{0,0,1},m_schematNormalnych{3}
{
    ileVertexow = 3;
    ileNormalnych = 1;
    indeksyVertexow = &m_indeksyVertexow[0];
    wspolrzedneVrtx = &m_wspolrzedneVrtx[0];
    normalne = &m_normalne[0];
    schematNormalnych = &m_schematNormalnych[0];
}

ProstyTrojkat::~ProstyTrojkat()
{

}

