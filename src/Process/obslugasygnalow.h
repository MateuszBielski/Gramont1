#ifndef ObslugaSygnalow_H
#define ObslugaSygnalow_H
#include <gtkmm.h>
#include <gtkglmm.h>
#include <iostream>
#include <memory>
#include "../Shared/ekrangl.h"
#include "../Shared/obracanie.h"
#include "renderowanie.h"

using namespace std;
using namespace Gtk;


class ObslugaSygnalow
{
  public:
    ObslugaSygnalow();
    virtual ~ObslugaSygnalow();
    void ObslugujEkran(spEkranGL );
    void UstawRenderowanie(spRenderowanie);
    void WlaczPolaczenia();
	
protected:

private:
    bool signal_button_press_event(GdkEventButton* );
    bool on_motion_notify_event(GdkEventMotion* );
    spEkranGL ekranGL = nullptr;
    spRenderowanie renderowanie = nullptr;
    
    Obracanie obracanie;
    
    
        
};
using spObslugaSygnalow = shared_ptr<ObslugaSygnalow>;
using upObslugaSygnalow = unique_ptr<ObslugaSygnalow>;
#endif // ObslugaSygnalow_H
