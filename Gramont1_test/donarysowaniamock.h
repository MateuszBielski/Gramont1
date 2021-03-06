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
    virtual const float* MacierzObrotu() override;
    virtual const float* Przesuniecie() override;
    virtual l_PolecenieIgeometria& Polecenia() override;
    virtual l_PolecenieIgeometriaAktywna& PoleceniaAktywne() override;
    virtual void PoleceniaWybierzIwstawWdobrejKolejnosci() override;
    virtual void ListePolecenResetuj() override;
    virtual void AktualizujMojePolecenia() override;
    void JestObrot(bool b);
    void JestPrzesuniecie(bool b);
    
    int id = 0;
    bool macierzObrotuIsUsed = false;
    bool poleceniaIsUsed = false;
    bool poleceniaAktywneIsUsed = false;
    bool przesuniecieIsUsed = false;
    bool aktualizujMojePoleceniaIsUsed = false;
    bool poleceniaWybierzIwstawWdobrejKolejnosciIsUsed = false;
    bool listePolecenResetujIsUsed = false;
    protected:

    private:
        
};

#endif // DoNarysowaniaMock_H
