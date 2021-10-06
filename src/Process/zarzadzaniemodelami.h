#ifndef ZarzadzanieModelami_H
#define ZarzadzanieModelami_H
//#include <gtkmm.h>
//#include <gtkglmm.h>
#include <iostream>
#include <queue>
#include <memory>
#include <thread>

#include "../Shared/transformowalne.h"
#include "../Polecenie/obslugapolecen.h"
#include "../Polecenie/kolejkapolecen.h"

#define PRZEKAZ_DO_NARYSOWANIA true


using namespace std;


class ZarzadzanieModelami : public ObslugaPolecen
{
    spTransformowalne doTrasformacji = nullptr;
    spDoNarysowania doNarysowania = nullptr;
    spKolejkaPolecen kolejkaRenderowania = nullptr;
    int licznikTransformacjiDoPrzerysowania = 0;
    int przerysujPoTyluTransformacjach = 1;
    
    using PtrMemZarz = void(ZarzadzanieModelami::*)();
    using spKolejkaPolecenZarzadzania = shared_ptr<KolejkaMiedzyWatkami<PtrMemZarz>>;
    
  public:
    ZarzadzanieModelami();
    virtual ~ZarzadzanieModelami(){};
	virtual spTransformowalne DoTransformacji() override {return doTrasformacji;};
    virtual void PowiadomionyOzakonczeniuTransformacji() override;
    virtual void WyslijPoleceniePrzerysuj() override ;
    virtual void UstawStanNic() override;
    
    int LicznikTransformacjiAkumulowanych();
    void NadawanieDoRenderowania(spKolejkaPolecen,bool ustawicDoNarysowania = false);
    void LiczbaTransformacjiDoAkumulowania(int);
    void WysylaniePrzerysujPoTransformacji();
    
    void DoTransformacji(spDoNarysowania );
    void DoNarysowania(spDoNarysowania);
    void DoNarysowaniaItransformacji(spDoNarysowania);
    void Aktualizuj();
    
    thread AsynchronicznePrzetwarzanieModeliUruchom();
    void AsynchronicznePrzetwarzanieModeliZatrzymaj();
    spKolejkaPolecenZarzadzania KolejkaPrzetwarzaniaAsynchronicznego();
    
protected:
    virtual void WykonajStan() override {(this->*Stan)();};
private:
    void (ZarzadzanieModelami::*Stan)();
    void PrzetwarzajModele();
    thread przetwarzanieModeliWatek;
    
    spKolejkaPolecenZarzadzania kolejkaPrzetwarzaniaAsynchronicznego;
        
};
using spZarzadzanieModelami = shared_ptr<ZarzadzanieModelami>;
using upZarzadzanieModelami = unique_ptr<ZarzadzanieModelami>;
#endif // ZarzadzanieModelami_H
