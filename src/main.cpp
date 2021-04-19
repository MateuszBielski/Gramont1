#include <gtkglmm.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <X11/Xlib.h>
#include "Shared/oknogtk.h"
#include "Shared/ekrangl.h"
//#include "Shared/transformacjaItfc.h"
#include "Process/obslugasygnalow.h"
#include "Process/renderowanie.h"
#include "Process/zarzadzaniemodelami.h"
#include <thread>

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
    
    zarzadzanie.NadawanieDoRenderowania(renderowanie.getKolejkaPolecen());
    zarzadzanie.WysylaniePrzerysujPoTransformacji();
    zarzadzanie.DoNarysowaniaItransformacji(make_shared<DoNarysowania>());
    
    obslugaSygnalow.WlaczPolaczenia();
    
    thread t_zarzadzanie(&ZarzadzanieModelami::Run,&zarzadzanie);
    thread t_renderowanie(&Renderowanie::Run,&renderowanie);//musi być adres, bo inaczej następuje kopiowanie i każdy wątek operuje na innym obiekcie renderowanie
    thread t_app([&](){app.run(okno);});
    
    
    t_zarzadzanie.join();
    t_renderowanie.join();
    t_app.join();
    return 0;
}
