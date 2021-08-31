#include "poleceniarenderowania.h"

PoleceniaRenderowania::PoleceniaRenderowania()
{

}

PoleceniaRenderowania::~PoleceniaRenderowania()
{

}

void PoleceniaRenderowania::PrzedGeometria(spDoNarysowania)
{
    cout<<"PoleceniaRenderowania::PrzedGeometria"<<endl;
}

void PoleceniaRenderowania::RysujGeometrie(spDoNarysowania rys)
{
    cout<<"PoleceniaRenderowania::RysujGeometrie"<<endl;
    cout<<"IleVertexow"<<rys->ileVertexow<<endl;
}

void PoleceniaRenderowania::PoGeometrii(spDoNarysowania)
{
    cout<<"PoleceniaRenderowania::PoGeometrii"<<endl;
}
