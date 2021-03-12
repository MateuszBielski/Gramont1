#ifndef EkranGL_H
#define EkranGL_H
//#include <gtkmm.h>
#include <gtkglmm.h>
#include <iostream>
#include <memory>

using namespace std;
using namespace Gtk;

using ptrConf = Glib::RefPtr<Gdk::GL::Config>;

class EkranGL : public  GL::DrawingArea
{
  public:
    EkranGL();
    virtual ~EkranGL();
    virtual bool on_configure_event(GdkEventConfigure* ) override;
    virtual bool on_expose_event(GdkEventExpose* event) override;
    void UstawienieSceny();
    void UstawienieOswietlenia();
    void RysujScene();
	
protected:

private:
    bool KonfiguracjaGL();
    
    
    ptrConf glconfig;
    int szerokosc = 1, wysokosc = 1;
    float planBliski = 5.0, planDaleki = 60.0;
        
};
using spEkranGL = shared_ptr<EkranGL>;
using upEkranGL = unique_ptr<EkranGL>;
#endif // EkranGL_H
