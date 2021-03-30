#ifndef KolejkaPolecen_H
#define KolejkaPolecen_H
#include <memory>
#include <queue>
#include <mutex>
#include <condition_variable>
#include "polecenie.h"


using namespace std;
//using namespace Gtk;
class KolejkaPolecen
{
    queue<upPolecenie> data_queue;
    
    mutable std::mutex mut;
    condition_variable data_cond;
    
    public:
    void push(upPolecenie); 
    upPolecenie wait_and_pop();
    size_t size();
    bool empty();
};

using upKolejkaPolecen = unique_ptr<KolejkaPolecen>;
using spKolejkaPolecen = shared_ptr<KolejkaPolecen>;
/*
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
*/

#endif // KolejkaPolecen_H
