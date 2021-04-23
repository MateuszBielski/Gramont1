#include "grupowalne.h"
#include <exception>

int Grupowalne::IleDzieci()
{
	return dzieci.size();
}
void Grupowalne::DodajDziecko(spGrupowalne dz)
{
    dzieci.push_back(dz);
//    dz->pozycja = --dzieci.end();
}
bool Grupowalne::UsunDziecko(spGrupowalne dz)
{
	try{
//       dzieci.erase(dz->pozycja);
       return true;
    }catch(exception & e)
    {
        return false;
        
    }
}
