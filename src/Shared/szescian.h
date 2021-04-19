#ifndef Szescian_H
#define Szescian_H
//#include <memory>
#include "donarysowania.h"

using namespace std;
//using namespace Gtk;


class Szescian : public DoNarysowania
{
public:
    Szescian();
    virtual ~Szescian();
	
protected:

private:
   unsigned short m_indeksyNaroznikow[16];
        
};
//using spSzescian = shared_ptr<Szescian>;
//using upSzescian = unique_ptr<Szescian>;
#endif // Szescian_H
