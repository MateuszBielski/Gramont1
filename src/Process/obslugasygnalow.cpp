#include "obslugasygnalow.h"


ObslugaSygnalow::ObslugaSygnalow()
{

}

ObslugaSygnalow::~ObslugaSygnalow()
{

}
void ObslugaSygnalow::ObslugujEkran(spEkranGL ekran)
{
	ekranGL = ekran;
}
void ObslugaSygnalow::UstawRenderowanie(spRenderowanie r)
{
	renderowanie = r;
}
void ObslugaSygnalow::WlaczPolaczenia()
{
    if(ekranGL)
    {
        ekranGL->set_events(Gdk::BUTTON1_MOTION_MASK|Gdk::BUTTON_PRESS_MASK|Gdk::SCROLL_MASK|Gdk::BUTTON2_MOTION_MASK|Gdk::BUTTON3_MOTION_MASK);//lub add_events
//        ekranGL->signal_button_press_event().connect(sigc::ptr_fun(&OnButtonPressEvent));
    }
    if(renderowanie && ekranGL)
    {
//        ekranGL->signal_button_press_event().connect(sigc::mem_fun(*renderowanie,&Renderowanie::ZarejestrujListeIprzerysujEkran));
//        ekranGL->signal_button_press_event().connect(sigc::mem_fun(*renderowanie,&Renderowanie::ZarejestrujListeIrysujScene));
        ekranGL->signal_button_press_event().connect(sigc::mem_fun(*this,&ObslugaSygnalow::signal_button_press_event));
        ekranGL->signal_motion_notify_event().connect(sigc::mem_fun(*this,&ObslugaSygnalow::on_motion_notify_event));
    }
}
bool ObslugaSygnalow::signal_button_press_event(GdkEventButton* e)
{
	renderowanie->ZarejestrujBezKontekstuRysujWlasnaWkontekscie();
    obracanie.PobierzPierwotnePolozenie(e->x,e->y);
    obracanie.PobierzWymiaryEkranu(ekranGL->get_width(),ekranGL->get_height());
}
bool ObslugaSygnalow::on_motion_notify_event(GdkEventMotion* e)
{
    obracanie.PobierzPolozenieAktualne(e->x,e->y);
    obracanie.ObliczWektorPrzesuniecia();
}
