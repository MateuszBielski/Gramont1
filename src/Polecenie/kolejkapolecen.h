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
    template<typename T>
    T wait_and_pop();
    size_t size();
    bool empty();
};
template<typename T>
T KolejkaPolecen::wait_and_pop()
{
    unique_lock<mutex> lk(mut);
    data_cond.wait(lk,[this]{return !data_queue.empty();});
    upPolecenie polecenie(move(data_queue.front()));
    data_queue.pop();
    return *(static_cast<T*>(polecenie.get()));
}
using upKolejkaPolecen = unique_ptr<KolejkaPolecen>;
using spKolejkaPolecen = shared_ptr<KolejkaPolecen>;


#endif // KolejkaPolecen_H

