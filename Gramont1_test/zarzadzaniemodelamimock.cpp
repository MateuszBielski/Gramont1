#include "zarzadzaniemodelamimock.h"

ZarzadzanieModelamiMock::ZarzadzanieModelamiMock()
{

}

ZarzadzanieModelamiMock::~ZarzadzanieModelamiMock()
{

}
spTransformowalne ZarzadzanieModelamiMock::DoTransformacji()
{
    doTransformacjiUsed = true;
    return make_shared<Transformowalne>();
}
void ZarzadzanieModelamiMock::PowiadomionyOzakonczeniuTransformacji()
{
	powiadomionyOzakonczeniuTransformacji = true;
}
