#include <gtest/gtest.h>
#include <GL/gl.h>
#include <thread>
#include <future>
#include <gtkglmm.h>
#include "../src/Polecenie/kolejkapolecen.h"
#include "../src/Process/obslugasygnalow.h"
#include "../src/Polecenie/obrot.h"
#include "ekranglmock.h"
//#include "../src/Process/zarzadzaniemodelami.h"
//#include "zarzadzaniemodelamimock.h"

TEST(ObslugaSygnalow,DodajeDoKolejki)
{
    auto kolejka = make_shared<KolejkaPolecen>();
    ObslugaSygnalow sygnaly;
    sygnaly.NadawanieDoZarzadzaniaObiektami(kolejka);
    GdkEventMotion e;
    sygnaly.on_motion_notify_event(&e);
    ASSERT_EQ(1,kolejka->size());
}
TEST(ObslugaSygnalow,RuchMyszyDajePolecenieZparmetramiRuchu)
{
    auto kolejka = make_shared<KolejkaPolecen>();
    ObslugaSygnalow sygnaly;
    spEkranGLMock ekran = make_shared<EkranGLMock>(200,200);
    
//    cout<<"\nXXXXX "<<ekran->get_width();
    
    sygnaly.ObslugujEkran(ekran);
    sygnaly.NadawanieDoZarzadzaniaObiektami(kolejka);
    GdkEventButton e1;
    e1.x = 100;
    e1.y = 100;
    
    GdkEventMotion e2;
    e2.x = 90;
    e2.y = 110;
    sygnaly.signal_button_press_event(&e1);
    sygnaly.on_motion_notify_event(&e2);

    Transformacja transformacja;
    transformacja = kolejka->wait_and_pop<Transformacja>();
    
    auto ruch = transformacja.Ruch();
    ASSERT_NE(ruch.p1x,ruch.p2x);
    ASSERT_NE(ruch.p1y,ruch.p2y);
}
TEST(ObslugaSygnalow,zamkniecieOknaWysylaPolecenieKoniec)
{
    ObslugaSygnalow sygnaly;
    auto kolejka = make_shared<KolejkaPolecen>();
    sygnaly.NadawanieDoZarzadzaniaObiektami(kolejka);
    
    GdkEventAny* event;
    sygnaly.on_delete_event(event);
    auto polecenie = kolejka->wait_and_pop();

    string expect("15PolecenieKoniec");
    string result(typeid(*polecenie).name());
    
    ASSERT_EQ(expect,result);
}
//czy po wykonaniu obsluga sygnałów::on_notify_event w kolejce jest polecenie zawierające ruch