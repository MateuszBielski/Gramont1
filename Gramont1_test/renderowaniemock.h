#ifndef RenderowanieMock_H
#define RenderowanieMock_H
#include "../src/Process/renderowanie.h"

using namespace std;
//using namespace Gtk;


class RenderowanieMock : public Renderowanie
{
public:
    virtual void FunPrzerysuj(spDoNarysowania ) override;
    virtual void RysujScene() override;
    spDoNarysowania DoNarysowania(){return doNarysowania;};
    void InnePolecenie(spGeometriaModelu);
    protected:

private:
    spDoNarysowania doNarysowania = nullptr;
        
};

#endif // RenderowanieMock_H
