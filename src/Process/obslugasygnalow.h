#ifndef ObslugaSygnalow_H
#define ObslugaSygnalow_H
#include <gtkmm.h>
#include <gtkglmm.h>
#include <iostream>
#include <memory>
#include "../Shared/ekrangl.h"

using namespace std;
using namespace Gtk;


class ObslugaSygnalow
{
  public:
    ObslugaSygnalow();
    virtual ~ObslugaSygnalow();
    void ObslugujEkran(spEkranGL );
	
protected:

private:
    spEkranGL ekranGL;
    
        
};
using spObslugaSygnalow = shared_ptr<ObslugaSygnalow>;
using upObslugaSygnalow = unique_ptr<ObslugaSygnalow>;
#endif // ObslugaSygnalow_H
