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
    return nullptr;
}
