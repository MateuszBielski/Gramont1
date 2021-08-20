#ifndef Grupowalne_H
#define Grupowalne_H
#include <memory>
#include <list>
#include <iterator>

using namespace std;


class Grupowalne
{
public:
    virtual ~Grupowalne() = default;
    using spGrupowalne = shared_ptr<Grupowalne>;
    int IleDzieci();
    void DodajDziecko(spGrupowalne );
    bool OdejmijDziecko(spGrupowalne);
    bool CzyJestMoimDzieckiem(spGrupowalne);
protected:
    list<spGrupowalne> dzieci;
//    iterator<random_access_iterator_tag,double> pozycja;=dzieci.end();
    list<spGrupowalne>::iterator pozycja;
private:
        
};
using spGrupowalne = shared_ptr<Grupowalne>;
#endif // Grupowalne_H
