#include "grupowalne.h"
#include <exception>

int Grupowalne::IleDzieci()
{
	return dzieci.size();
}
void Grupowalne::DodajDziecko(spGrupowalne dz)
{
    dzieci.push_back(dz);
    dz->pozycja = --dzieci.end();
}
bool Grupowalne::OdejmijDziecko(spGrupowalne dz)
{
    if(CzyJestMoimDzieckiem(dz))
    {
        dzieci.erase(dz->pozycja);
        return true;
    }
    return false;
}
bool Grupowalne::CzyJestMoimDzieckiem(spGrupowalne doSprawdzenia)
{
    auto iter = dzieci.begin();
    
    while(iter != dzieci.end())
    {
        if(doSprawdzenia->pozycja == iter++)return true;
    }
    return false;
}
