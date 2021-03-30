#ifndef ZarzadzanieModelamiMock_H
#define ZarzadzanieModelamiMock_H
//#include <gtkmm.h>
//#include <gtkglmm.h>
//#include <iostream>
//#include <memory>
#include "../src/Process/zarzadzaniemodelami.h"

using namespace std;
//using namespace Gtk;


class ZarzadzanieModelamiMock : public ZarzadzanieModelami
{
  
    public:
    ZarzadzanieModelamiMock();
    virtual ~ZarzadzanieModelamiMock();
    virtual spTransformowalne DoTransformacji() override;
	
protected:

private:
        
};
//using spZarzadzanieModelamiMock = shared_ptr<ZarzadzanieModelamiMock>;
//using upZarzadzanieModelamiMock = unique_ptr<ZarzadzanieModelamiMock>;
#endif // ZarzadzanieModelamiMock_H
