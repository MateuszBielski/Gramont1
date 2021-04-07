#ifndef ObslugaPolecenMock_H
#define ObslugaPolecenMock_H

#include "../src/Polecenie/obslugapolecen.h"

using namespace std;


class ObslugaPolecenMock : public ObslugaPolecen
{
public:
    ObslugaPolecenMock():licznikRun(protLicznikRun) {};
    int& licznikRun;
    virtual spTransformowalne DoTransformacji() override {};
    virtual void PowiadomionyOzakonczeniuTransformacji() override {};
    protected:

    private:
        
};

#endif // ObslugaPolecenMock_H
