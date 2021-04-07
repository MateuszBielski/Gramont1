#include "polecenie.h"
#include "obslugapolecen.h"
void PolecenieKoniec::WykonajW(ObslugaPolecen& obsl)
{
    obsl.StopRun();
}