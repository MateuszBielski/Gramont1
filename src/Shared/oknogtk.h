#ifndef OknoGtk_H
#define OknoGtk_H
#include <gtkmm.h>
#include <gtkglmm.h>
#include <iostream>
#include <memory>
#include "ekrangl.h"

using namespace std;
using namespace Gtk;


class OknoGtk : public Gtk::Window
{
  public:
    OknoGtk();
    OknoGtk(int,int);
    virtual ~OknoGtk();
    void ZamontujEkran(spEkranGL);
	
protected:

private:
    VBox vBox;    
};
using spOknoGtk = shared_ptr<OknoGtk>;
using upOknoGtk = unique_ptr<OknoGtk>;
#endif // OknoGtk_H
