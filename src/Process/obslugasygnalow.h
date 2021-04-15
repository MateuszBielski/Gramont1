#ifndef ObslugaSygnalow_H
#define ObslugaSygnalow_H
#include <gtkmm.h>
#include <gtkglmm.h>
#include <iostream>
#include <memory>
#include "../Shared/ekrangl.h"
#include "../Shared/kursor2d.h"
//#include "../Shared/transformacjaItfc.h"
#include "../Polecenie/kolejkapolecen.h"
#include "renderowanie.h"

using namespace std;
using namespace Gtk;


class ObslugaSygnalow
{
    spEkranGL ekranGL = nullptr;
    spRenderowanie renderowanie = nullptr;
    Kursor2D kursor2D;
//    spTransformacjaItfc transformacja = nullptr;
    spKolejkaPolecen nadawanieDoZarzadzaniaObiektami = nullptr;
  
  public:
    void ObslugujEkran(spEkranGL );
    void UstawRenderowanie(spRenderowanie);//?
//    void UstawTransformacje(spTransformacjaItfc );?
    void WlaczPolaczenia();
    void NadawanieDoZarzadzaniaObiektami(spKolejkaPolecen);
    
    
    bool signal_button_press_event(GdkEventButton* );
    bool on_motion_notify_event(GdkEventMotion* );
	
  protected:
    
  private:
    
    
    
    
        
};
using spObslugaSygnalow = shared_ptr<ObslugaSygnalow>;
using upObslugaSygnalow = unique_ptr<ObslugaSygnalow>;
#endif // ObslugaSygnalow_H
