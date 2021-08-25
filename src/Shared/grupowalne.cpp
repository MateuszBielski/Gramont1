#include "grupowalne.h"
#include <exception>
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
size_t Grupowalne::StrukturaJakoLista_dlugosc()
{
    /*
    spGrupowalne aktualnyWezel = this;
	stack<int> galazLiczbaDzieci; 
    stack<spGrupowalne> wezlyGalezi;

    galazLiczbaDzieci.push(aktualnyWezel->IleDzieci());
    wezlyGalezi.push(aktualnyWezel);
    
    int wysokoscStosu = 1;
    bool koniec = false;
    
    while(!koniec)
    {
        //Akcje Wprowadzajace
        int& pozostalaLiczbaDzieciNaTymPoziomie = galazLiczbaDzieci.top();
        if(pozostalaLiczbaDzieciNaTymPoziomie){
            
        }
        aktualnyWezel->IleDzieci()
        //Akcje Wyprowadzajace
    }
    */
    size_t mojaDlugosc = 1;
    if(!IleDzieci())return mojaDlugosc;
    for(auto& dziecko :  dzieci)mojaDlugosc += dziecko->StrukturaJakoLista_dlugosc();
    return mojaDlugosc;
}
const list<WpisStrukturyJakoListy<spGrupowalne>>& Grupowalne::StrukturaJakoLista()
{
    return strukturaJakoLista;
}
void Grupowalne::GenerujStruktureJakoListe(listaWpisySpGrupowalne& calaLista)
{
   
    WpisStrukturyJakoListy<spGrupowalne> wpis{RodzajAkcji::wejscie,shared_from_this()};
    calaLista.emplace_back(wpis);
        
    for(auto& dziecko :  dzieci)
    {
        dziecko->GenerujStruktureJakoListe(calaLista);
    }
}
