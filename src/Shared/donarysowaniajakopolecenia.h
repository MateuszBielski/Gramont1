#ifndef DoNarysowaniaJakoPolecenia_H
#define DoNarysowaniaJakoPolecenia_H
//#include <gtkmm.h>
//#include <gtkglmm.h>
//#include <iostream>
#include <list>
#include <memory>
#include "donarysowania.h"
#include "../Polecenie/poleceniarenderowania.h"

using namespace std;
//using namespace Gtk;

//using PtrMemRend = void(PoleceniaRenderowania::*)();

class DoNarysowaniaJakoPolecenia
{
    using PtrMemRend_doNarys = void(PoleceniaRenderowania::*)(spDoNarysowania);
    
    spDoNarysowania doNarysowania;
    list<PtrMemRend_doNarys> mojePolecenia;
public:
    DoNarysowaniaJakoPolecenia();
    virtual ~DoNarysowaniaJakoPolecenia();
    void PoleceniaWybierzIwstawWdobrejKolejnosci(spDoNarysowania);
    list<PtrMemRend_doNarys> Polecenia();
    
	
protected:

private:
        
};
using spDoNarysowaniaJakoPolecenia = shared_ptr<DoNarysowaniaJakoPolecenia>;
using upDoNarysowaniaJakoPolecenia = unique_ptr<DoNarysowaniaJakoPolecenia>;
#endif // DoNarysowaniaJakoPolecenia_H
