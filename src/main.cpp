#include <gtkglmm.h>
#include <GL/gl.h>
#include <GL/glu.h>
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
    Gtk::Main app(argc,argv);
    GL::init(argc, argv);

//    które z tych jest częściej używane przez inne moduły?
    OknoGtk okno(800,600);
    spEkranGL ekran = make_shared<EkranGL>();
//    spTransformacjaItfc transformacja = make_shared<TransformacjaItfc>();
    
    ObslugaSygnalow obslugaSygnalow;
    Renderowanie renderowanie;
    ZarzadzanieModelami zarzadzanie; 
    
    okno.ZamontujEkran(ekran);
	obslugaSygnalow.ObslugujEkran(ekran);
    renderowanie.UstawEkran(ekran);
    obslugaSygnalow.NadawanieDoZarzadzaniaObiektami(zarzadzanie.getKolejkaPolecen());
    zarzadzanie.NadawanieDoRenderowania(renderowanie.getKolejkaPolecen());
    zarzadzanie.WysylaniePrzerysujPoTransformacji();
    
    thread t_zarzadzanie(&ZarzadzanieModelami::Run,&zarzadzanie);
    thread t_renderowanie(&Renderowanie::Run,&renderowanie);
    
    obslugaSygnalow.WlaczPolaczenia();
    app.run(okno);
    t_zarzadzanie.join();
    t_renderowanie.join();
    return 0;
}
