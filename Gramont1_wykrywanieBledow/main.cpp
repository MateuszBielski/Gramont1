#include <stdio.h>
#include "../src/Shared/donarysowania.h"
#include "../src/Shared/prostytrojkat.h"

int main(int argc, char **argv)
{
	
    printf("sizeof(DoNarysowania) %d\n",sizeof(DoNarysowania));
    auto rys(make_shared<DoNarysowania>());
    printf("auto urys(make_unique<DoNarysowania>()) sizeof *urys %d\n",sizeof *rys);
    printf("rys.use_count() %d\n",rys.use_count());
    
//    auto trojkat(ProstyTrojkat::Create());
//    printf("ile vertexow %d\n",trojkat->ileVertexow);
    
    /*
    shared_ptr<Transformowalne> trans(make_shared<DoNarysowania>());
    printf("shared_ptr<Transformowalne> trans(make_shared<DoNarysowania>()) sizeof *trans %d\n",sizeof *trans);
    shared_ptr<Transformowalne> trans2 = make_shared<DoNarysowania>();
    printf("shared_ptr<Transformowalne> trans2 = make_shared<DoNarysowania>() sizeof *trans2 %d\n",sizeof *trans2);
    shared_ptr<Transformowalne> trans3 = rys;
    printf("shared_ptr<Transformowalne> trans3 = rys sizeof *trans3 %d\n",sizeof *trans3);
    printf("sizeof(Transformowalne) %d\n",sizeof(Transformowalne));
     * */
	return 0;
}
