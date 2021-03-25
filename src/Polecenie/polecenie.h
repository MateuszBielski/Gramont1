#ifndef Polecenie_H
#define Polecenie_H
//#include <iostream>
//#include <memory>

using namespace std;

class Polecenie
{
public:
    virtual void Wykonaj() = 0;
    
};

using spPolecenie = shared_ptr<Polecenie>;
using upPolecenie = unique_ptr<Polecenie>;

template<typename T>
class TemplatePolecenie : public Polecenie
{
public:
    explicit TemplatePolecenie(shared_ptr<T> o):obslugujacy(o){
        
        };
protected:
    shared_ptr<T> obslugujacy = nullptr;
};
#endif // Polecenie_H
