#include "testrenderklas.h"
#include "../src/Pomocnicze/FunkcjeIstruktury.h"


void test_glVertex3fv(const float* v)
{
    st_ciagWywolanOpenGl += "v";
    for(short i = 0; i < 3; i++)st_ciagWywolanOpenGl += ToString(v[i],1)+",";
   
}
void test_glNormal3fv(const float* n)
{
	st_ciagWywolanOpenGl += "n";
    for(short i = 0; i < 3; i++)st_ciagWywolanOpenGl += ToString(n[i],1)+",";
}
void testUzytaFunkcja(const char* nazwaFunkcji)
{
	TestRenderKlas::uzyteFunkcje[nazwaFunkcji] += 1;
    TestRenderKlas::funkcjeWkolejnosci.push_back(nazwaFunkcji);
}

map<string,unsigned> TestRenderKlas::uzyteFunkcje = {};//{"x",10}
list<string> TestRenderKlas::funkcjeWkolejnosci = {};

TestRenderKlas::TestRenderKlas()
{
    st_ciagWywolanOpenGl = "";
    uzyteFunkcje.clear();
    funkcjeWkolejnosci.clear();
}

bool TestRenderKlas::UstawZastepczeOpenGlDla(Renderowanie& rend)
{
	rend.p_glVertex3fv =&test_glVertex3fv;
	rend.p_glNormal3fv =&test_glNormal3fv;
    return rend.p_glVertex3fv && rend.p_glNormal3fv;
}
void TestRenderKlas::UstawMonitorujaceFunkcjeDla(Renderowanie& rend)
{
	rend.ptrFunkcjaMonitorujaca = &testUzytaFunkcja;
}

string TestRenderKlas::CiagWywolanOpenGl()
{
	string result = st_ciagWywolanOpenGl;
    return result;
}
bool TestRenderKlas::CzyMaTenSamDoNarysowania(Renderowanie& rend, spDoNarysowania rys)
{
	return rend.doNarysowania == rys;
}
void TestRenderKlas::UstawPrzyszloscDla(future<void>&& fu, Renderowanie& r)
{
	r.fut = move(fu);
}
future<void> TestRenderKlas::PrzyszloscZobietnicy(Renderowanie& r)
{
	return move(r.prom.get_future());
}
