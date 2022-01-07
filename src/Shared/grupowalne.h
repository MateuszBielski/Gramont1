#ifndef Grupowalne_H
#define Grupowalne_H
#include <memory>
#include <list>
#include <iterator>

using namespace std;

enum class RodzajAkcji: int;//{wejscie,wezel,powrot};

template<class T>
class Grupowalne_T : public enable_shared_from_this<Grupowalne_T<T>>
{
    //potrzebne dla shared_from_this w pliku .cpp - bo klasa template
    using enable_shared_from_this<Grupowalne_T<T>>::shared_from_this;
public:
    virtual ~Grupowalne_T(){};
    int IleDzieci();
    
    using spGrupowalne_T = shared_ptr<T>;
    void DodajDziecko(spGrupowalne_T );
    bool OdejmijDziecko(spGrupowalne_T);
    bool CzyJestMoimDzieckiem(spGrupowalne_T);
    spGrupowalne_T Rodzic();
    size_t StrukturaJakoLista_Wezly_dlugosc();
    const list<spGrupowalne_T>& StrukturaJakoLista_Wezly();
    const list<RodzajAkcji>& StrukturaJakoLista_RodzajAkcji();
protected:
    list<spGrupowalne_T> dzieci;
    typename list<shared_ptr<T>>::iterator pozycja;
    typename list<shared_ptr<T>>::iterator pozycjaWliscie;
    shared_ptr<T> WskaznikNaMnie();
    weak_ptr<T> WskaznikNaMnieSlaby();
private:
    spGrupowalne_T rodzic = nullptr;
    list<spGrupowalne_T> strukturaJakoLista_Wezly;
    list<RodzajAkcji> strukturaJakoLista_RodzajAkcji;
    void GenerujStruktureJakoListe_Wezly(list<spGrupowalne_T>& );
    void GenerujStruktureJakoListe_RodzajAkcji(list<RodzajAkcji>&);
    virtual void PodczasDodajDziecko(){};
    virtual void PodczasOdejmijDziecko(){};
};

//na potrzeby testów napisanych przed wyodrębnieniem powyższej klasy szablonowej
class Grupowalne : public Grupowalne_T<Grupowalne>
{
    
};

using spGrupowalne = shared_ptr<Grupowalne>;
#endif // Grupowalne_H
