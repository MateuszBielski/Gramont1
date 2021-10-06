#ifndef KolejkaPolecen_H
#define KolejkaPolecen_H
#include <memory>
#include <queue>
#include <mutex>
#include <condition_variable>
#include "polecenie.h"


using namespace std;

template<typename T>
class KolejkaMiedzyWatkami
{
    
    public:
    void push(T); 
    T wait_and_pop();
    
      
    size_t size();
    bool empty();
    
    protected:
    queue<T> data_queue;
    
    mutable std::mutex mut;
    condition_variable data_cond;
};


class KolejkaPolecen : public KolejkaMiedzyWatkami<upPolecenie>
{
public:
    template<typename T>
    T wait_and_pop_T();
};

template<typename T>
T KolejkaPolecen::wait_and_pop_T()
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

