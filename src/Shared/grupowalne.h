#ifndef Grupowalne_H
#define Grupowalne_H
#include <memory>
#include <vector>
#include <iterator>

using namespace std;


class Grupowalne
{
public:
    virtual ~Grupowalne() = default;
    using spGrupowalne = shared_ptr<Grupowalne>;
    int IleDzieci();
    void DodajDziecko(spGrupowalne );
    bool UsunDziecko(spGrupowalne);
protected:
    vector<spGrupowalne> dzieci;
    iterator<random_access_iterator_tag,double> pozycja;//=dzieci.end();
private:
        
};

#endif // Grupowalne_H
