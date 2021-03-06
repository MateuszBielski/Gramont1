#ifndef ObslugaSygnalow_H
#define ObslugaSygnalow_H
#include <gtkmm.h>
#include <gtkglmm.h>
#include <iostream>
#include <memory>
#include "../Shared/ekrangl.h"
#include "../Shared/kursor2d.h"
#include "../Polecenie/kolejkapolecen.h"
#include "renderowanie.h"
#include "zarzadzaniemodelami.h"

using namespace std;
using namespace Gtk;


class ObslugaSygnalow
{
    spEkranGL ekranGL = nullptr;
    spRenderowanie renderowanie = nullptr;
    ZarzadzanieModelami * zarzadzanie = nullptr;
    Kursor2D kursor2D;
    spKolejkaPolecen nadawanieDoZarzadzaniaObiektami = nullptr;
    spKolejkaPolecen nadawanieDoRenderowania = nullptr;
  
  public:
    void ObslugujEkran(spEkranGL );
    void UstawRenderowanie(spRenderowanie);//?
    void UstawZarzadzanie(ZarzadzanieModelami * const);
    void WlaczPolaczenia();
    void NadawanieDoZarzadzaniaObiektami(spKolejkaPolecen);
    void NadawanieDoRenderowania(spKolejkaPolecen);
    
    
    bool signal_button_press_event(GdkEventButton* );
    bool on_motion_notify_event(GdkEventMotion* );
    bool on_delete_event(GdkEventAny*);
    bool on_key_press_event(GdkEventKey* event);
	
  protected:
    
private:
  
    
    
    
    
        
};
using spObslugaSygnalow = shared_ptr<ObslugaSygnalow>;
using upObslugaSygnalow = unique_ptr<ObslugaSygnalow>;
#endif // ObslugaSygnalow_H
