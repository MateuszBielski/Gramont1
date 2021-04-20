#include "renderowaniemock.h"


void RenderowanieMock::FunPrzerysuj(spDoNarysowania rys)
{
	if(!rys)return;
    przerysujDostaloDoNarysowania = true;
    doNarysowania = rys;
}
void RenderowanieMock::RysujScene()
{	
//	for()/
}
