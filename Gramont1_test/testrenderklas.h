#ifndef TestRenderKlas_H
#define TestRenderKlas_H
#include <string>
#include "../src/Process/renderowanie.h"

using namespace std;
//using namespace Gtk;

static string st_ciagWywolanOpenGl("");

void test_glVertex3fv(const float *);
void test_glNormal3fv(const float *);

class TestRenderKlas 
{
public:
    TestRenderKlas();
    string CiagWywolanOpenGl();
    bool UstawZastepczeOpenGlDla(Renderowanie&);
};

#endif // TestRenderKlas_H
