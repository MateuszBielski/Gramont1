#include <stdio.h>
#include "../src/Shared/donarysowania.h"
#include "../src/Shared/prostytrojkat.h"

int main(int argc, char **argv)
{
	auto rys1(make_shared<DoNarysowania>());
    auto rys2(make_shared<DoNarysowania>());
    auto rys3(make_shared<DoNarysowania>());
    rys1->DodajDziecko(rys2);
    rys2->DodajDziecko(rys3);
    rys1->PoleceniaWybierzIwstawWdobrejKolejnosci();
    
    /***/
    int a1 = rys1.use_count();
    int a2 = rys2.use_count();
//    int b = rys1.weak_count();
    /***/

    float przes[] = {1.3,0,0};
    rys2->DodajPrzesuniecie(przes);
    rys2->AktualizujMojePolecenia();
    int b1 = rys1.use_count();//**
    int b2 = rys2.use_count();//**
    
    auto adrGeom1 = &(*rys1);
}
