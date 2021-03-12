#ifndef ZarzadzanieModelami_H
#define ZarzadzanieModelami_H
#include <gtkmm.h>
#include <gtkglmm.h>
#include <iostream>
#include <memory>

using namespace std;
using namespace Gtk;


class ZarzadzanieModelami
{
  public:
    ZarzadzanieModelami();
    virtual ~ZarzadzanieModelami();
	
protected:

private:
        
};
using spZarzadzanieModelami = shared_ptr<ZarzadzanieModelami>;
using upZarzadzanieModelami = unique_ptr<ZarzadzanieModelami>;
#endif // ZarzadzanieModelami_H
