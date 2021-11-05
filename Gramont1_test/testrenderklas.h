#ifndef TestRenderKlas_H
#define TestRenderKlas_H
#include <string>
#include <map>
#include <list>
#include "../src/Process/renderowanie.h"


using namespace std;
//using namespace Gtk;

static string st_ciagWywolanOpenGl("");

void test_glVertex3fv(const float *);
void test_glNormal3fv(const float *);
void testUzytaFunkcja(const char*);

class TestRenderKlas 
{
public:
    TestRenderKlas();
    string CiagWywolanOpenGl();
    bool UstawZastepczeOpenGlDla(Renderowanie&);
    bool CzyMaTenSamDoNarysowania(Renderowanie&, spDoNarysowania);
    void UstawMonitorujaceFunkcjeDla(Renderowanie&);
    static map<string,unsigned> uzyteFunkcje;
    static list<string> funkcjeWkolejnosci;
    void UstawPrzyszloscDla(future<void>*, Renderowanie&); 
};

#endif // TestRenderKlas_H
