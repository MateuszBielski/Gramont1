#ifndef DoNarysowania_H
#define DoNarysowania_H
#include <gtkmm.h>
#include <gtkglmm.h>
#include <iostream>
#include <memory>

using namespace std;
using namespace Gtk;


class DoNarysowania
{
  public:
    DoNarysowania();
    virtual ~DoNarysowania();
	
protected:

private:
        
};
using spDoNarysowania = shared_ptr<DoNarysowania>;
using upDoNarysowania = unique_ptr<DoNarysowania>;
#endif // DoNarysowania_H
