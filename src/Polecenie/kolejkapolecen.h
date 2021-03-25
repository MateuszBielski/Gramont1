#ifndef KolejkaPolecen_H
#define KolejkaPolecen_H
#include <memory>


using namespace std;
//using namespace Gtk;

template<typename Wlasciciel>
class KolejkaPolecen
{
    using spWlasciciel = shared_ptr<Wlasciciel>;
    spWlasciciel wlasciciel = nullptr;
    
public:
    KolejkaPolecen(spWlasciciel w):wlasciciel(w){};
    spWlasciciel getWlasciciel(){return wlasciciel;};
   
    protected:

    private:
        
};

//using upKolejkaPolecen = unique_ptr<KolejkaPolecen>;

#endif // KolejkaPolecen_H
