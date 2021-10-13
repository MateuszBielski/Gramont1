#include "nazwa.h"


Nazwa::Nazwa(int n):intNazwa(n)
{

}
Nazwa::Nazwa(const char* c):sNazwa(c)
{
    
}
bool Nazwa::operator==(Nazwa& on)
{
    
    return (intNazwa == on.intNazwa) && (sNazwa == on.sNazwa) ;
}
bool Nazwa::operator== (Nazwa&& on)
{
    return (intNazwa == on.intNazwa) && (sNazwa == on.sNazwa) ;
}
bool Nazwa::operator< (const Nazwa on) const
{
    
    return (intNazwa < on.intNazwa) || (sNazwa < on.sNazwa) ;
}
//bool Nazwa::operator< (Nazwa&& on)
//{
//    return (intNazwa < on.intNazwa) && (sNazwa < on.sNazwa) ;
//}
