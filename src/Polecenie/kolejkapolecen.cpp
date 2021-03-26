#include "kolejkapolecen.h"



void KolejkaPolecen::push(upPolecenie&& p)
{
	queue.push_back(move(p));
}
size_t KolejkaPolecen::size()
{
	return queue.size();
}
