#include "szescian.h"

Szescian::Szescian():m_indeksyNaroznikow{3,2,0,1,4,5,7,6,5,1,6,2,7,3,4,0}
{
    indeksyNaroznikow = &m_indeksyNaroznikow[0];
    ileNaroznikow = 16;
}

Szescian::~Szescian()
{
    
}

