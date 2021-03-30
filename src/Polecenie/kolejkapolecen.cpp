#include "kolejkapolecen.h"


size_t KolejkaPolecen::size()
{
	return data_queue.size();
}

bool KolejkaPolecen::empty()
{
    return data_queue.empty();
}
void KolejkaPolecen::push(upPolecenie p)
{
	lock_guard<mutex> lk(mut);
    data_queue.push(move(p));
    data_cond.notify_one();
}


upPolecenie KolejkaPolecen::wait_and_pop()
{
    unique_lock<mutex> lk(mut);
    data_cond.wait(lk,[this]{return !data_queue.empty();});
    upPolecenie res(std::move(data_queue.front()));
    data_queue.pop();
    return res;
}
