#include "obslugasygnalow.h"
#include "../Polecenie/transformacja.h"
#include "../Polecenie/obrot.h"
#include "probneprzelaczenie.h"
//#include "../src/Polecenie/transformacja.h"

void ObslugaSygnalow::ObslugujEkran(spEkranGL ekran)
{
	ekranGL = ekran;
}
void ObslugaSygnalow::UstawRenderowanie(spRenderowanie r)
{
	renderowanie = r;
}
void ObslugaSygnalow::UstawZarzadzanie(ZarzadzanieModelami * const z)
{
	zarzadzanie = z;
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
        ekranGL->set_events(Gdk::BUTTON1_MOTION_MASK|Gdk::BUTTON_PRESS_MASK|Gdk::SCROLL_MASK|Gdk::BUTTON2_MOTION_MASK
        |Gdk::BUTTON3_MOTION_MASK);//lub add_events
        ekranGL->signal_button_press_event().connect(sigc::mem_fun(*this,&ObslugaSygnalow::signal_button_press_event));
        ekranGL->signal_motion_notify_event().connect(sigc::mem_fun(*this,&ObslugaSygnalow::on_motion_notify_event));
        
        ekranGL->get_parent()->get_parent()->set_events(Gdk::KEY_PRESS_MASK);  
        ekranGL->get_parent()->get_parent()->signal_key_press_event().connect(sigc::mem_fun(*this, &ObslugaSygnalow::on_key_press_event),false);
        auto okno = ekranGL->get_parent()->get_parent();
        okno->signal_delete_event().connect(sigc::mem_fun(*this,&ObslugaSygnalow::on_delete_event));
//        auto okno = *ekranGL->get_parent());
    }
    
}
bool ObslugaSygnalow::signal_button_press_event(GdkEventButton* e)
{
	if(renderowanie != nullptr)
    {
//        renderowanie->ZarejestrujBezKontekstuRysujWlasnaWkontekscie();
    }
    kursor2D.PobierzPierwotnePolozenie(e->x,e->y);
//    cout<<"\nXXXsignal_button_press_event "<<ekranGL->get_width()<<" "<<ekranGL->get_height();

    kursor2D.PobierzWymiaryEkranu(ekranGL->get_width(),ekranGL->get_height());
}
bool ObslugaSygnalow::on_motion_notify_event(GdkEventMotion* e)
{
//    cout<<"\nObslugaSygnalow::on_motion_notify_event";
    upTransformacja transformacja;
    
    auto ruch = kursor2D.ObliczRuch(e->x,e->y);
    transformacja= make_unique<Obrot>(move(ruch));
    
    nadawanieDoZarzadzaniaObiektami->push(move(transformacja));
}
void ObslugaSygnalow::NadawanieDoZarzadzaniaObiektami(spKolejkaPolecen kolejka)
{
	nadawanieDoZarzadzaniaObiektami = kolejka;
}
void ObslugaSygnalow::NadawanieDoRenderowania(spKolejkaPolecen k)
{
	nadawanieDoRenderowania = k;
}
bool ObslugaSygnalow::on_delete_event(GdkEventAny* any_event)
{
//    cout<<"\nzamykanie okna";
    if(nadawanieDoZarzadzaniaObiektami)nadawanieDoZarzadzaniaObiektami->push(make_unique<PolecenieKoniec>());
    if(nadawanieDoRenderowania)nadawanieDoRenderowania->push(make_unique<PolecenieKoniec>());
    return false;
}
bool ObslugaSygnalow::on_key_press_event(GdkEventKey* event)
{
	//ProbnePrzelaczenie przelacz(zarzadzanie,event);
    return false;
}

