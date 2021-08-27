#ifndef Grupowalne_H
#define Grupowalne_H
#include <memory>
#include <list>
#include <iterator>
//#include "wpisstrukturyjakolisty.h"

using namespace std;

enum class RodzajAkcji: int;//{wejscie,wezel,powrot};

class Grupowalne : public enable_shared_from_this<Grupowalne>
{
public:
    virtual ~Grupowalne() = default;
    int IleDzieci();
    
    using spGrupowalne = shared_ptr<Grupowalne>;
    void DodajDziecko(spGrupowalne );
    bool OdejmijDziecko(spGrupowalne);
    bool CzyJestMoimDzieckiem(spGrupowalne);
    spGrupowalne Rodzic();
    size_t StrukturaJakoLista_Wezly_dlugosc();
//    using listaWpisySpGrupowalne = list<WpisStrukturyJakoListy<spGrupowalne>>;
    const list<spGrupowalne>& StrukturaJakoLista_Wezly();
    const list<RodzajAkcji>& StrukturaJakoLista_RodzajAkcji();
protected:
    list<spGrupowalne> dzieci;
    list<spGrupowalne>::iterator pozycja;
    list<spGrupowalne>::iterator pozycjaWliscie;
private:
    spGrupowalne rodzic = nullptr;
    list<spGrupowalne> strukturaJakoLista_Wezly;
    list<RodzajAkcji> strukturaJakoLista_RodzajAkcji;
    void GenerujStruktureJakoListe_Wezly(list<spGrupowalne>& );
};
using spGrupowalne = shared_ptr<Grupowalne>;
#endif // Grupowalne_H
