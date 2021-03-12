#include <gtkglmm.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "Shared/oknogtk.h"
#include "Shared/ekrangl.h"

using namespace std;

int main(int argc, char **argv)
{
    Gtk::Main app(argc,argv);
    GL::init(argc, argv);

//    które z tych jest częściej używane przez inne moduły?
    spOknoGtk okno = make_shared<OknoGtk>(800,600);
    spEkranGL ekran = make_shared<EkranGL>();
	
    okno->ZamontujEkran(ekran);
   
    app.run(*okno);
    
    return 0;
}
