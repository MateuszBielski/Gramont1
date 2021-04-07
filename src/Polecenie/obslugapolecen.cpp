#include "obslugapolecen.h"



void ObslugaPolecen::Run()
{
    upPolecenie polecenie;
    while(run)
    {
         polecenie = kolejka->wait_and_pop();
         polecenie->WykonajW(*this);
//         if(++protLicznikRun >= 4)run = false;
        ++protLicznikRun;
    }
}
ObslugaPolecen::ObslugaPolecen()
{
	kolejka = make_shared<KolejkaPolecen>();
}
void ObslugaPolecen::StopRun()
{
	run = false;
}
