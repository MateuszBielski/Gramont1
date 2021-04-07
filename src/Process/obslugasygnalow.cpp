#include "obslugasygnalow.h"
#include "../Polecenie/transformacja.h"
#include "../Polecenie/obrot.h"
//#include "../src/Polecenie/transformacja.h"

void ObslugaSygnalow::ObslugujEkran(spEkranGL ekran)
{
	ekranGL = ekran;
}
void ObslugaSygnalow::UstawRenderowanie(spRenderowanie r)
{
	renderowanie = r;
}
/*
void ObslugaSygnalow::UstawTransformacje(spTransformacjaItfc tr)
{
    transformacja = tr;
}*/
void ObslugaSygnalow::WlaczPolaczenia()
{
    if(ekranGL)
    {
        ekranGL->set_events(Gdk::BUTTON1_MOTION_MASK|Gdk::BUTTON_PRESS_MASK|Gdk::SCROLL_MASK|Gdk::BUTTON2_MOTION_MASK|Gdk::BUTTON3_MOTION_MASK);//lub add_events
        ekranGL->signal_button_press_event().connect(sigc::mem_fun(*this,&ObslugaSygnalow::signal_button_press_event));
        ekranGL->signal_motion_notify_event().connect(sigc::mem_fun(*this,&ObslugaSygnalow::on_motion_notify_event));
    }
    
}
bool ObslugaSygnalow::signal_button_press_event(GdkEventButton* e)
{
	if(renderowanie != nullptr)
    {
        renderowanie->ZarejestrujBezKontekstuRysujWlasnaWkontekscie();
    }
    kursor2D.PobierzPierwotnePolozenie(e->x,e->y);
//    cout<<"\nXXXsignal_button_press_event "<<ekranGL->get_width()<<" "<<ekranGL->get_height();

    kursor2D.PobierzWymiaryEkranu(ekranGL->get_width(),ekranGL->get_height());
}
bool ObslugaSygnalow::on_motion_notify_event(GdkEventMotion* e)
{
    upTransformacja transformacja;
    
    auto ruch = kursor2D.ObliczRuch(e->x,e->y);
    transformacja= make_unique<Obrot>(move(ruch));
    
    nadawanieDoZarzadzaniaObiektami->push(move(transformacja));
}
void ObslugaSygnalow::NadawanieDoZarzadzaniaObiektami(spKolejkaPolecen kolejka)
{
	nadawanieDoZarzadzaniaObiektami = kolejka;
}
