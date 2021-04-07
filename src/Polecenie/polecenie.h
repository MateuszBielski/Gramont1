#ifndef Polecenie_H
#define Polecenie_H
//#include <iostream>
#include <memory>

using namespace std;

class ObslugaPolecen;

class Polecenie
{
public:
    virtual void WykonajW(ObslugaPolecen& ) = 0;//
    
};

using spPolecenie = shared_ptr<Polecenie>;
using upPolecenie = unique_ptr<Polecenie>;

class PoleceniePuste : public Polecenie
{
public:
    PoleceniePuste(int _id):id(_id){};
    virtual void WykonajW(ObslugaPolecen& ) override {};
    int id = 0;
};
class PolecenieKoniec : public Polecenie
{
    public:
    virtual void WykonajW(ObslugaPolecen& ) override;
};
/*
template<typename T>
class TemplatePolecenie : public Polecenie
{
public:
    explicit TemplatePolecenie(shared_ptr<T> o):obslugujacy(o){
        
        };
protected:
    shared_ptr<T> obslugujacy = nullptr;
    
};
 */
#endif // Polecenie_H
