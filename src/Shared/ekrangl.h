#ifndef EkranGL_H
#define EkranGL_H
//#include <gtkmm.h>
#include <gtkglmm.h>
#include <iostream>
#include <memory>
#include <functional>

using namespace std;
using namespace Gtk;

using ptrConf = Glib::RefPtr<Gdk::GL::Config>;



class EkranGL : public  GL::DrawingArea
{
  public:
    EkranGL();
    virtual ~EkranGL();
    virtual bool on_configure_event(GdkEventConfigure* ) override;
    virtual bool on_expose_event(GdkEventExpose* event) override;
    void UstawienieSceny();
    void UstawienieOswietlenia();
    
    template<typename T>
    bool WykonajWkontekscieGL(void (T::*Func)(),T& );
//    template<typename T>
//    bool WykonajWkontekscieGL(void (T::*Func)(),T& );
//    void PrzypiszRysujScene(function<void()> );
    function<void()> RysujScene;
	
    GLuint* listid;
protected:

private:
    bool KonfiguracjaGL();
//    void(*RysujScene)();
    
    
    
    ptrConf glconfig;
    int szerokosc = 1, wysokosc = 1;
    float planBliski = 5.0, planDaleki = 60.0;
    
        
};
using spEkranGL = shared_ptr<EkranGL>;
using upEkranGL = unique_ptr<EkranGL>;

template<typename T>
bool EkranGL::WykonajWkontekscieGL(void (T::*Func)(),T& obj_ref)
{
    auto gldrawable = get_gl_drawable();
    if(!gldrawable)return false;
	if (!gldrawable->gl_begin(get_gl_context()))
    return false;
    
    (obj_ref.*Func)();
    
    if (gldrawable->is_double_buffered())
    {
      gldrawable->swap_buffers();
//      cout<<"\nswap_buffers()";
    }
    else
    {
      glFlush();
//      cout<<"\nglFlush()";
    }
    gldrawable->gl_end();
    cout<<"\nWykonajWkontekscieGL koniec"<<endl;
	return true;
}

#endif // EkranGL_H
