#include <stdio.h>
#include "../src/Shared/donarysowania.h"

int main(int argc, char **argv)
{
	
    printf("sizeof(DoNarysowania) %d\n",sizeof(DoNarysowania));
    auto rys(make_shared<DoNarysowania>());
    printf("auto rys(make_shared<DoNarysowania>()) sizeof *rys %d\n",sizeof *rys);
    shared_ptr<Transformowalne> trans(make_shared<DoNarysowania>());
    printf("shared_ptr<Transformowalne> trans(make_shared<DoNarysowania>()) sizeof *trans %d\n",sizeof *trans);
    shared_ptr<Transformowalne> trans2 = make_shared<DoNarysowania>();
    printf("shared_ptr<Transformowalne> trans2 = make_shared<DoNarysowania>() sizeof *trans2 %d\n",sizeof *trans2);
    shared_ptr<Transformowalne> trans3 = rys;
    printf("shared_ptr<Transformowalne> trans3 = rys sizeof *trans3 %d\n",sizeof *trans3);
    printf("sizeof(Transformowalne) %d\n",sizeof(Transformowalne));
	return 0;
}
