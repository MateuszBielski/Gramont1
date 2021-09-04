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
    auto poprzedniRodzic = dz->Rodzic();
    if(poprzedniRodzic)poprzedniRodzic->OdejmijDziecko(dz);
    dzieci.push_back(dz);
    dz->pozycja = --dzieci.end();
//    auto wsk = 
    dz->rodzic = static_pointer_cast<T>(shared_from_this());
}
template<class T>
bool Grupowalne_T<T>::OdejmijDziecko(spGrupowalne_T dz)
{
    if(CzyJestMoimDzieckiem(dz))
    {
        dzieci.erase(dz->pozycja);
        dz->rodzic = nullptr;
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
shared_ptr<T> Grupowalne_T<T>::Rodzic()
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

//na potrzeby linkera
template class Grupowalne_T<Grupowalne>;
template class Grupowalne_T<DoNarysowania>;
/*
void Grupowalne::GenerujStruktureJakoListe(listaWpisySpGrupowalne& calaLista)
{
   
    WpisStrukturyJakoListy<spGrupowalne> wpis{RodzajAkcji::wejscie,shared_from_this()};
    calaLista.emplace_back(wpis);
    pozycjaWliscie = --calaLista.end();
    if(!IleDzieci())
    {
        (*pozycjaWliscie).akcjaPo = RodzajAkcji::powrot;
        return;
    }
    alistaWpisySpGrupowalneuto iter = dzieci.begin();
    auto aktualny = iter;
//    auto 
    for(auto& dziecko :  dzieci)
    {   
        aktualny = iter++;
        dziecko->GenerujStruktureJakoListe(calaLista);
        auto aktuPozycjaWliscie = (*aktualny)->pozycjaWliscie;
        (*aktuPozycjaWliscie).akcjaPo = RodzajAkcji::obok;
//        calaLista.emplace_back(WpisStrukturyJakoListy<spGrupowalne>{RodzajAkcji::powrot,nullptr});
    }
    //czyli ostatni
    auto aktuPozycjaWliscie = (*aktualny)->pozycjaWliscie;
    (*aktuPozycjaWliscie).akcjaPo = RodzajAkcji::powrot;
}
*/