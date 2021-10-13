#ifndef Nazwa_H
#define Nazwa_H
#include "string"

using namespace std;


class Nazwa
{
public:
    Nazwa(){};
    Nazwa(int);
    Nazwa(const char*);
    bool operator== (Nazwa& );
    bool operator== (Nazwa&& );
    bool operator< (const Nazwa ) const;
//    bool operator< (Nazwa&& );
   
    protected:

private:
    int intNazwa = 0;
    string sNazwa = "";
        
};

#endif // Nazwa_H
