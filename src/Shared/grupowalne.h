#ifndef Grupowalne_H
#define Grupowalne_H
#include <memory>
#include <list>
#include <iterator>

using namespace std;


class Grupowalne : public enable_shared_from_this<Grupowalne>
{
public:
    virtual ~Grupowalne() = default;
    using spGrupowalne = shared_ptr<Grupowalne>;
    int IleDzieci();
    void DodajDziecko(spGrupowalne );
    bool OdejmijDziecko(spGrupowalne);
    bool CzyJestMoimDzieckiem(spGrupowalne);
    spGrupowalne Rodzic();
    void Rodzic(spGrupowalne);//?
    size_t StrukturaJakoLista_dlugosc();
protected:
    list<spGrupowalne> dzieci;
    list<spGrupowalne>::iterator pozycja;
private:
    spGrupowalne rodzic = nullptr;
};
using spGrupowalne = shared_ptr<Grupowalne>;
#endif // Grupowalne_H
