#ifndef PoleceniaRenderowania_H
#define PoleceniaRenderowania_H
#include <iostream>
#include <memory>
#include "../Shared/donarysowania.h"

using namespace std;
//using namespace Gtk;


class PoleceniaRenderowania
{
  public:
    PoleceniaRenderowania();
    virtual ~PoleceniaRenderowania();
        
    void PrzedGeometria(spDoNarysowania);
    void RysujGeometrie(spDoNarysowania);
    void PoGeometrii(spDoNarysowania);
	
protected:

private:
        
};
using spPoleceniaRenderowania = shared_ptr<PoleceniaRenderowania>;
using upPoleceniaRenderowania = unique_ptr<PoleceniaRenderowania>;
#endif // PoleceniaRenderowania_H
