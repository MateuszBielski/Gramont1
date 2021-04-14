#include "przerysuj.h"
#include "../Shared/donarysowania.h"



Przerysuj::~Przerysuj()
{

}
void Przerysuj::WykonajW(ObslugaPolecen& obs)
{	
	
    obs.FunPrzerysuj(make_shared<DoNarysowania>());
}
