#ifndef KolejkaPolecen_H
#define KolejkaPolecen_H
#include <memory>
#include <deque>
#include "polecenie.h"


using namespace std;
//using namespace Gtk;
class KolejkaPolecen : public deque<upPolecenie>
{
    deque<upPolecenie> queue;
    public:
    void push(upPolecenie&& );
    size_t size();
};

using upKolejkaPolecen = unique_ptr<KolejkaPolecen>;
using spKolejkaPolecen = shared_ptr<KolejkaPolecen>;
template<typename Wlasciciel>
class KolejkaPolecenTemplate
{
    using spWlasciciel = shared_ptr<Wlasciciel>;
    spWlasciciel wlasciciel = nullptr;
    
public:
    KolejkaPolecenTemplate(spWlasciciel w):wlasciciel(w){};
    spWlasciciel getWlasciciel(){return wlasciciel;};
   
    protected:

    private:
        
};


#endif // KolejkaPolecen_H
