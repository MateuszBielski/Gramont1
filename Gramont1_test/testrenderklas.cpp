#include "testrenderklas.h"
#include <sstream>
#include <iomanip>//set precision


string ToString(float v,short pr)
{
    stringstream stream; 
    stream << fixed << setprecision(pr) << v;
    return stream.str();
}


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

TestRenderKlas::TestRenderKlas()
{
    st_ciagWywolanOpenGl = "";
}

bool TestRenderKlas::UstawZastepczeOpenGlDla(Renderowanie& rend)
{
	rend.p_glVertex3fv =&test_glVertex3fv;
	rend.p_glNormal3fv =&test_glNormal3fv;
    return rend.p_glVertex3fv && rend.p_glNormal3fv;
}
string TestRenderKlas::CiagWywolanOpenGl()
{
	string result = st_ciagWywolanOpenGl;
    return result;
}