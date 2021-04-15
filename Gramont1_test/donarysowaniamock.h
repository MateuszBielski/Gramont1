#ifndef DoNarysowaniaMock_H
#define DoNarysowaniaMock_H
#include "../src/Shared/donarysowania.h"

using namespace std;
using namespace Gtk;


class DoNarysowaniaMock : public DoNarysowania
{
public:
    DoNarysowaniaMock() = default;
    DoNarysowaniaMock(int i):id(i){};
//    virtual ~DoNarysowaniaMock(){};
    int id = 0;
   
    protected:

    private:
        
};

#endif // DoNarysowaniaMock_H
