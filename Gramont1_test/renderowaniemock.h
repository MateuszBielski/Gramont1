#ifndef RenderowanieMock_H
#define RenderowanieMock_H
#include "../src/Process/renderowanie.h"

using namespace std;
//using namespace Gtk;


class RenderowanieMock : public Renderowanie
{
public:
    virtual void FunPrzerysuj(spDoNarysowania ) override;
    protected:

    private:
        
};

#endif // RenderowanieMock_H
