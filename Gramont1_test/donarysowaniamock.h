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
    virtual float* MacierzObrotu() override;
    int id = 0;
    bool macierzObrotuIsUsed = false;
   
    protected:

    private:
        
};

#endif // DoNarysowaniaMock_H
