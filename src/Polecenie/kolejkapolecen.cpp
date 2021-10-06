#include "kolejkapolecen.h"
#include "../Process/zarzadzaniemodelami.h"

template<class T>
size_t KolejkaMiedzyWatkami<T>::size()
{
	return data_queue.size();
}
template<class T>
bool KolejkaMiedzyWatkami<T>::empty()
{
    return data_queue.empty();
}
template<class T>
void KolejkaMiedzyWatkami<T>::push(T p)
{
	lock_guard<mutex> lk(mut);
    data_queue.push(move(p));
    data_cond.notify_one();
}

template<class T>
T KolejkaMiedzyWatkami<T>::wait_and_pop()
{
    unique_lock<mutex> lk(mut);
    data_cond.wait(lk,[this]{return !data_queue.empty();});
    T res(std::move(data_queue.front()));
    data_queue.pop();
    return res;
}

template class KolejkaMiedzyWatkami<upPolecenie>;
template class KolejkaMiedzyWatkami<void (ZarzadzanieModelami::*)()>;
