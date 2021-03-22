#include <gtkglmm.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "Shared/oknogtk.h"
#include "Shared/ekrangl.h"
#include "Shared/transformacjaItfc.h"
#include "Process/obslugasygnalow.h"
#include "Process/renderowanie.h"

using namespace std;

int main(int argc, char **argv)
{
    Gtk::Main app(argc,argv);
    GL::init(argc, argv);

//    które z tych jest częściej używane przez inne moduły?
    spOknoGtk okno = make_shared<OknoGtk>(800,600);
    spEkranGL ekran = make_shared<EkranGL>();
    spTransformacja transformacja = make_shared<
    
    spObslugaSygnalow obslugaSygnalow = make_shared<ObslugaSygnalow>();
    spRenderowanie renderowanie = make_shared<Renderowanie>();
    
    okno->ZamontujEkran(ekran);
	obslugaSygnalow->ObslugujEkran(ekran);
    obslugaSygnalow->UstawRenderowanie(renderowanie);
    obslugaSygnalow->UstawTransformacje()
    renderowanie->UstawEkran(ekran);
    
    obslugaSygnalow->WlaczPolaczenia();
    app.run(*okno);
    
    return 0;
}
