#ifndef EkranGLMock_H
#define EkranGLMock_H
#include <gtkmm.h>
#include <gtkglmm.h>
#include <memory>
#include "../src/Shared/ekrangl.h"
using namespace std;


class EkranGLMock : public EkranGL
{
public:
    EkranGLMock() = default;
    EkranGLMock(int _w, int _h):w(_w),h(_h){};
    virtual ~EkranGLMock();
    int get_width(){return w;};
    int get_height(){return h;};
    int w = 2,h = 2;
	
protected:

private:
        
};
using spEkranGLMock = shared_ptr<EkranGLMock>;
using upEkranGLMock = unique_ptr<EkranGLMock>;
#endif // EkranGLMock_H
