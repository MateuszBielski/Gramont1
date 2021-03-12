#ifndef ObslugaSygnalow_H
#define ObslugaSygnalow_H
#include <gtkmm.h>
#include <gtkglmm.h>
#include <iostream>
#include <memory>

using namespace std;
using namespace Gtk;


class ObslugaSygnalow
{
  public:
    ObslugaSygnalow();
    virtual ~ObslugaSygnalow();
	
protected:

private:
        
};
using spObslugaSygnalow = shared_ptr<ObslugaSygnalow>;
using upObslugaSygnalow = unique_ptr<ObslugaSygnalow>;
#endif // ObslugaSygnalow_H
