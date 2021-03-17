#include "obslugasygnalow.h"

bool OnButtonPressEvent(GdkEventButton* event)
{
    printf("\nnaciśnięto klawisz myszy");
    return true;
}

ObslugaSygnalow::ObslugaSygnalow()
{

}

ObslugaSygnalow::~ObslugaSygnalow()
{

}
void ObslugaSygnalow::ObslugujEkran(spEkranGL ekran)
{
	ekranGL = ekran;
    ekranGL->set_events(Gdk::BUTTON1_MOTION_MASK|Gdk::BUTTON_PRESS_MASK|Gdk::SCROLL_MASK|Gdk::BUTTON2_MOTION_MASK|Gdk::BUTTON3_MOTION_MASK);//lub add_events
    ekranGL->signal_button_press_event().connect(sigc::ptr_fun(&OnButtonPressEvent));
}
