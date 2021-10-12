#include "nazwa.h"


Nazwa::Nazwa(int n):intNazwa(n)
{

}
bool Nazwa::operator==(Nazwa& on)
{
    return intNazwa == on.intNazwa;
}
