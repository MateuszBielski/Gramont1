#include "szescian.h"

Szescian::Szescian():m_indeksyVertexow{3,2,0,1,4,5,7,6,5,1,6,2,7,3,4,0},
                    m_wspolrzedneVrtx{  0,0,1,
                                        1,0,1,
                                        1,0,0,
                                        0,0,0,
                                        0,1,1,
                                        1,1,1,
                                        1,1,0,
                                        0,1,0}
{
    indeksyVertexow = &m_indeksyVertexow[0];
    ileVertexow = 16;
    wspolrzedneVrtx = &m_wspolrzedneVrtx[0];
}

Szescian::~Szescian()
{
    
}

