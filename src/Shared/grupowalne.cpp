#include "grupowalne.h"
#include <exception>
#include "rodzajakcji.cpp"
//#include <stack>

int Grupowalne::IleDzieci()
{
	return dzieci.size();
}
void Grupowalne::DodajDziecko(spGrupowalne dz)
{
    if(dz.get() == this)return;
    auto poprzedniRodzic = dz->Rodzic();
    if(poprzedniRodzic)poprzedniRodzic->OdejmijDziecko(dz);
    dzieci.push_back(dz);
    dz->pozycja = --dzieci.end();
//    auto wsk = 
    dz->rodzic = shared_from_this();
}
bool Grupowalne::OdejmijDziecko(spGrupowalne dz)
{
    if(CzyJestMoimDzieckiem(dz))
    {
        dzieci.erase(dz->pozycja);
        dz->rodzic = nullptr;
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
spGrupowalne Grupowalne::Rodzic()
{
	return rodzic;
}
size_t Grupowalne::StrukturaJakoLista_Wezly_dlugosc()
{
    size_t mojaDlugosc = 1;
    if(!IleDzieci())return mojaDlugosc;
    for(auto& dziecko :  dzieci)mojaDlugosc += dziecko->StrukturaJakoLista_Wezly_dlugosc();
    return mojaDlugosc;
}
const list<spGrupowalne>& Grupowalne::StrukturaJakoLista_Wezly()
{
    GenerujStruktureJakoListe_Wezly(strukturaJakoLista_Wezly);
    return strukturaJakoLista_Wezly;
}

void Grupowalne::GenerujStruktureJakoListe_Wezly(list<spGrupowalne>& calaLista)
{
    calaLista.push_back(shared_from_this());
     for(auto& dziecko :  dzieci)
    {
        dziecko->GenerujStruktureJakoListe_Wezly(calaLista);
    }
}
const list<RodzajAkcji>& Grupowalne::StrukturaJakoLista_RodzajAkcji()
{
    GenerujStruktureJakoListe_RodzajAkcji(strukturaJakoLista_RodzajAkcji);
    return strukturaJakoLista_RodzajAkcji;
}
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