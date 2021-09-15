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
    
    
    OknoGtk okno(200,200);
    
    spEkranGL ekran = make_shared<EkranGL>();
    okno.ZamontujEkran(ekran);
    ekran->UstawienieSceny();


    app.run(okno);
    
    return 0;
}
