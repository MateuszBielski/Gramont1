#ifndef Grupowalne_H
#define Grupowalne_H
#include <memory>
#include <list>
#include <iterator>
#include "wpisstrukturyjakolisty.h"

using namespace std;


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
    size_t StrukturaJakoLista_dlugosc();
    using listaWpisySpGrupowalne = list<WpisStrukturyJakoListy<spGrupowalne>>;
    const listaWpisySpGrupowalne& StrukturaJakoLista();
    void GenerujStruktureJakoListe(listaWpisySpGrupowalne& );
protected:
    list<spGrupowalne> dzieci;
    list<spGrupowalne>::iterator pozycja;
private:
    spGrupowalne rodzic = nullptr;
    listaWpisySpGrupowalne strukturaJakoLista;
};
using spGrupowalne = shared_ptr<Grupowalne>;
#endif // Grupowalne_H
