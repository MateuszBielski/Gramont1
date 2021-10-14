#ifndef DoNarysowaniaMock_H
#define DoNarysowaniaMock_H
#include "../src/Shared/donarysowania.h"

using namespace std;
using namespace Gtk;


class DoNarysowaniaMock : public DoNarysowania
{
public:
    DoNarysowaniaMock() = default;
    DoNarysowaniaMock(int i):id(i){};
    virtual float* MacierzObrotu() override;
    virtual float* Przesuniecie() override;
    virtual l_PolecenieIgeometria& Polecenia() override;
    virtual void PoleceniaWybierzIwstawWdobrejKolejnosci() override;
    virtual void AktualizujMojePolecenia() override;
    int id = 0;
    bool macierzObrotuIsUsed = false;
    bool poleceniaIsUsed = false;
    bool przesuniecieIsUsed = false;
    bool aktualizujMojePoleceniaIsUsed = false;
    bool poleceniaWybierzIwstawWdobrejKolejnosciIsUsed = false;
   
    protected:

    private:
        
};

#endif // DoNarysowaniaMock_H
