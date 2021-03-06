#include "ekrangl.h"
#include "../Pomocnicze/FunkcjeIstruktury.h"



EkranGL::EkranGL()
{
    KonfiguracjaGL();
    RysujScene = [](){};
//    RysujScene = [this](){Proby();};
    
}

EkranGL::~EkranGL()
{

}
bool EkranGL::KonfiguracjaGL()
{
    glconfig = Gdk::GL::Config::create(Gdk::GL::MODE_RGB|Gdk::GL::MODE_DEPTH|Gdk::GL::MODE_DOUBLE);
    if (!glconfig) {
      std::cerr << "*** Cannot find the double-buffered visual.\n"
                << "*** Trying single-buffered visual.\n";

      glconfig = Gdk::GL::Config::create(Gdk::GL::MODE_RGB   |
                                         Gdk::GL::MODE_DEPTH);
        return true;
      if (!glconfig) {
        std::cerr << "*** Cannot find any OpenGL-capable visual.\n";
        return false;
      }
    }
    set_gl_capability(glconfig);
    
    return true;
}
bool EkranGL::on_configure_event(GdkEventConfigure* e)
{
//    cout<<"\nEkranGL::on_configure_event"<<endl;
//    GL::DrawingArea::on_configure_event(e);
    szerokosc = get_width(), wysokosc = get_height();
	auto gldrawable = get_gl_drawable();
    if(!gldrawable)return false;
	if (!gldrawable->gl_begin(get_gl_context()))
    return false;
    UstawienieSceny();
    UstawienieOswietlenia();
    
        if (gldrawable->is_double_buffered())
    {
//      gldrawable->swap_buffers();
//      cout<<"\nswap_buffers()";
    }
    else
    {
      glFlush();
//      cout<<"\nglFlush()";
    }
    gldrawable->gl_end();
//    cout<<"\nEkranGL::on_configure_event koniec"<<endl;
	return true;
}
bool EkranGL::on_expose_event(GdkEventExpose* event)
{
//    cout<<"\nEkranGL::on_expose_event"<<endl;
//    GL::DrawingArea::on_expose_event(event);
    auto gldrawable = get_gl_drawable();
    if (!gldrawable->gl_begin(get_gl_context()))
      return false;

	RysujScene();
    
	if (gldrawable->is_double_buffered())
      gldrawable->swap_buffers();
    else
      glFlush();

	gldrawable->gl_end();
	return true;
}
void EkranGL::UstawienieSceny()
{
	glViewport(0, 0, szerokosc, wysokosc);
    glShadeModel(GL_SMOOTH);//cieniowanie kolorem GK_SMOOTH, GL_FLAT
    glEnable(GL_DEPTH_TEST);
    
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_BLEND);
    glEnable(GL_POINT_SMOOTH);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (szerokosc > wysokosc) {
      float aspect = static_cast<float>(szerokosc) / static_cast<float>(wysokosc);
      glFrustum(-aspect, aspect, -1.0, 1.0, planBliski, planDaleki);
//      glFrustum(-0.1, 0.1, wsp*-0.1, wsp * 0.1, nearDoKorektySceny, 400.0);
    } else {
      float aspect = static_cast<float>(wysokosc) / static_cast<float>(szerokosc);
      glFrustum(-1.0, 1.0, -aspect, aspect, planBliski, planDaleki);
    }
	
	/***antyaliasing***/
//	glEnable(GL_POLYGON_SMOOTH);
//    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    cout<<"\nRenderGL::UstawienieSceny() koniec"<<endl;
}
void EkranGL::UstawienieOswietlenia()
{
	glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
    //??wiat??o punktowe
    float kolorZrodla[] = {0.7,0.7,0.9,1.0};
    float pozycjaZrodlaSwiatla[] = {0.0,1.0,3.0,1.0};//obowi??zkowo 1 na ko??cu
    glLightfv(GL_LIGHT1,GL_POSITION,pozycjaZrodlaSwiatla); 
    glLightfv(GL_LIGHT1,GL_DIFFUSE,kolorZrodla);
    glEnable(GL_LIGHT1);
}
void EkranGL::Proby()
{
    auto pokaz = [](float * v){
		g_print("\n ");
		for(int i = 0; i < 4 ; i++)g_print("  %2.3f",v[i]);
	};
    glLoadIdentity();
    float macierzModelWidok[16];
//    glTranslatef(0,1,0);
    glRotatef(44,0,0,1);
    float punkt[] = {1,1,0,1};
    float punktTransf[4];
    glGetFloatv(GL_MODELVIEW_MATRIX,macierzModelWidok);
//    for(short i = 0 ; i < 4 ; i++)
//    {
//        for(short j = 0 ; j < 4 ; j++)
//        {
//            cout<<macierzModelWidok[4*j+i]<<" ";
//        }
//        cout<<endl;
//    }
    
    IloczynMacierzyIwektora4f(macierzModelWidok,punkt,punktTransf);
    pokaz(punktTransf);
    RysujScene = [](){};
}
//void EkranGL::PrzypiszRysujScene(function<void()> fun)
//{
//	RysujScene = fun;
//}
