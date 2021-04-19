#include "prostytrojkat.h"

ProstyTrojkat::ProstyTrojkat():m_indeksyNaroznikow{0,1,2},m_wspolrzedne{-1,0,0,1,0,0,0,1,0}
{
    indeksyNaroznikow = &m_indeksyNaroznikow[0];
    ileNaroznikow = 3;
    wspolrzedne = &m_wspolrzedne[0];
}

ProstyTrojkat::~ProstyTrojkat()
{

}

