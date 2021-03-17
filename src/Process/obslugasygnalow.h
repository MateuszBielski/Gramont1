#ifndef ObslugaSygnalow_H
#define ObslugaSygnalow_H
#include <gtkmm.h>
#include <gtkglmm.h>
#include <iostream>
#include <memory>
#include "../Shared/ekrangl.h"
#include "renderowanie.h"

using namespace std;
using namespace Gtk;


class ObslugaSygnalow
{
  public:
    ObslugaSygnalow();
    virtual ~ObslugaSygnalow();
    void ObslugujEkran(spEkranGL );
    void UstawRenderowanie(spRenderowanie);
    void WlaczPolaczenia();
	
protected:

private:
    spEkranGL ekranGL = nullptr;
    spRenderowanie renderowanie = nullptr;
    
        
};
using spObslugaSygnalow = shared_ptr<ObslugaSygnalow>;
using upObslugaSygnalow = unique_ptr<ObslugaSygnalow>;
#endif // ObslugaSygnalow_H
