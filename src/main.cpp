#include <gtkglmm.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "Shared/oknogtk.h"
#include "Shared/ekrangl.h"
#include "Process/obslugasygnalow.h"

using namespace std;

int main(int argc, char **argv)
{
    Gtk::Main app(argc,argv);
    GL::init(argc, argv);

//    które z tych jest częściej używane przez inne moduły?
    spOknoGtk okno = make_shared<OknoGtk>(800,600);
    spEkranGL ekran = make_shared<EkranGL>();
    
    spObslugaSygnalow obslugaSygnalow = make_shared<ObslugaSygnalow>();
    
    okno->ZamontujEkran(ekran);
	obslugaSygnalow->ObslugujEkran(ekran);
    
   
    app.run(*okno);
    
    return 0;
}
