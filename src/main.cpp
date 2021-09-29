#include <gtkglmm.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <X11/Xlib.h>
#include <thread>
#include "Shared/oknogtk.h"
#include "Shared/ekrangl.h"
//#include "Shared/transformacjaItfc.h"
#include "Process/obslugasygnalow.h"
#include "Process/renderowanie.h"
#include "Process/zarzadzaniemodelami.h"
#include "Shared/prostytrojkat.h"
#include "Shared/szescian.h"


using namespace std;

int main(int argc, char **argv)
{
    XInitThreads();
    Gtk::Main app(argc,argv);
    GL::init(argc, argv);

//    które z tych jest częściej używane przez inne moduły? ekran
    OknoGtk okno(800,600);
    spEkranGL ekran = make_shared<EkranGL>();
    
    ObslugaSygnalow obslugaSygnalow;
    Renderowanie renderowanie;
    ZarzadzanieModelami zarzadzanie; 
    
    okno.ZamontujEkran(ekran);
	obslugaSygnalow.ObslugujEkran(ekran);
    renderowanie.UstawEkran(ekran);
    
    obslugaSygnalow.NadawanieDoZarzadzaniaObiektami(zarzadzanie.getKolejkaPolecen());
    obslugaSygnalow.NadawanieDoRenderowania(renderowanie.getKolejkaPolecen());
    
    auto rys = make_shared<DoNarysowania>();
    auto szescian1 = make_shared<Szescian>();
    auto szescian2 = make_shared<Szescian>();
    auto szescian3 = make_shared<Szescian>();
    
    float przes2[] = {1.1,0.0,0.0};
    float przes3[] = {-1.3,0.0,0.0};
    szescian2->DoVertexowDodajWektor(przes2);
    szescian3->DoVertexowDodajWektor(przes3);
    
    rys->DodajDziecko(szescian1);
    rys->DodajDziecko(szescian2);
    rys->DodajDziecko(szescian3);
    
    zarzadzanie.DoNarysowaniaItransformacji(rys);
    zarzadzanie.NadawanieDoRenderowania(renderowanie.getKolejkaPolecen(),PRZEKAZ_DO_NARYSOWANIA);//
    zarzadzanie.WysylaniePrzerysujPoTransformacji();
//    zarzadzanie.DoNarysowaniaItransformacji(make_shared<DoNarysowania>());
    
    obslugaSygnalow.WlaczPolaczenia();
    
    thread t_zarzadzanie(&ZarzadzanieModelami::Run,&zarzadzanie);
    thread t_renderowanie(&Renderowanie::Run,&renderowanie);//musi być adres, bo inaczej następuje kopiowanie i każdy wątek operuje na innym obiekcie renderowanie
    thread t_app([&](){app.run(okno);});
    
    
    t_zarzadzanie.join();
    t_renderowanie.join();
    t_app.join();
    return 0;
}
