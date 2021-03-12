#include "oknogtk.h"

OknoGtk::OknoGtk()
{

}

OknoGtk::~OknoGtk()
{

}
OknoGtk::OknoGtk(int w, int h)
{	
	set_default_size(w,h);
}
void OknoGtk::ZamontujEkran(spEkranGL ekran)
{
    add(vBox);
    vBox.pack_start(*ekran);
    vBox.show_all();
}
