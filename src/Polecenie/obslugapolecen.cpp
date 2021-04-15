#include "obslugapolecen.h"



void ObslugaPolecen::Run()
{
    upPolecenie polecenie;
    while(run)
    {
         polecenie = kolejka->wait_and_pop();
         polecenie->WykonajW(*this);
        ++protLicznikRun;
        WykonajStan();
    }
}
ObslugaPolecen::ObslugaPolecen():kolejka(make_shared<KolejkaPolecen>())
{
//	 = ;
}
void ObslugaPolecen::StopRun()
{
	run = false;
    UstawStanNic();
}
