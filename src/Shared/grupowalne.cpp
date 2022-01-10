#include "grupowalne.h"
#include <exception>
#include "rodzajakcji.cpp"
#include "donarysowania.h"//na potrzeby linkera - na końcu pliku

template<class T>
int Grupowalne_T<T>::IleDzieci()
{
	return dzieci.size();
}
template<class T>
void Grupowalne_T<T>::DodajDziecko(spGrupowalne_T dz)
{
    if(dz.get() == this)return;
    auto poprzedniRodzic = dz->rodzic;
    if(!poprzedniRodzic.expired())
        poprzedniRodzic.lock()->OdejmijDziecko(dz);
    
    dzieci.push_back(dz);
    dz->pozycja = --dzieci.end();
    dz->rodzic = static_pointer_cast<T>(shared_from_this());
    PodczasDodajDziecko();
}
template<class T>
bool Grupowalne_T<T>::OdejmijDziecko(spGrupowalne_T dz)
{
    if(CzyJestMoimDzieckiem(dz))
    {
        dzieci.erase(dz->pozycja);
        dz->rodzic.reset();
        PodczasOdejmijDziecko();
        return true;
    }
    return false;
}
template<class T>
bool Grupowalne_T<T>::CzyJestMoimDzieckiem(spGrupowalne_T doSprawdzenia)
{
    auto iter = dzieci.begin();
    
    while(iter != dzieci.end())
    {
        if(doSprawdzenia->pozycja == iter++)return true;
    }
    return false;
}
template<class T>
weak_ptr<T> Grupowalne_T<T>::Rodzic()
{
    return rodzic;
}
template<class T>
size_t Grupowalne_T<T>::StrukturaJakoLista_Wezly_dlugosc()
{
    size_t mojaDlugosc = 1;
    if(!IleDzieci())return mojaDlugosc;
    for(auto& dziecko :  dzieci)mojaDlugosc += dziecko->StrukturaJakoLista_Wezly_dlugosc();
    return mojaDlugosc;
}
template<class T>
const list<shared_ptr<T>>& Grupowalne_T<T>::StrukturaJakoLista_Wezly()
{
    GenerujStruktureJakoListe_Wezly(strukturaJakoLista_Wezly);
    return strukturaJakoLista_Wezly;
}
template<class T>
shared_ptr<T> Grupowalne_T<T>::WskaznikNaMnie()
{
    return static_pointer_cast<T>(shared_from_this());
}
template<class T>
weak_ptr<T> Grupowalne_T<T>::WskaznikNaMnieSlaby()
{
    
    return weak_ptr<T>(static_pointer_cast<T>(shared_from_this()));
}
template<class T>
void Grupowalne_T<T>::GenerujStruktureJakoListe_Wezly(list<spGrupowalne_T>& calaLista)
{
    calaLista.push_back(static_pointer_cast<T>(shared_from_this()));
     for(auto& dziecko :  dzieci)
    {
        dziecko->GenerujStruktureJakoListe_Wezly(calaLista);
    }
}
template<class T>
const list<RodzajAkcji>& Grupowalne_T<T>::StrukturaJakoLista_RodzajAkcji()
{
    GenerujStruktureJakoListe_RodzajAkcji(strukturaJakoLista_RodzajAkcji);
    return strukturaJakoLista_RodzajAkcji;
}
template<class T>
void Grupowalne_T<T>::GenerujStruktureJakoListe_RodzajAkcji(list<RodzajAkcji>& calaLista)
{
    calaLista.push_back(RodzajAkcji::wezel); 
    if(!IleDzieci())return;
    calaLista.push_back(RodzajAkcji::wejscie);
    for(auto& dziecko :  dzieci)
    {
        dziecko->GenerujStruktureJakoListe_RodzajAkcji(calaLista);
    }
    calaLista.push_back(RodzajAkcji::powrot);
}
template<class T>
Grupowalne_T<T>::~Grupowalne_T()
{
//    int g = 1;
}

//na potrzeby linkera
template class Grupowalne_T<Grupowalne>;
template class Grupowalne_T<DoNarysowania>;
