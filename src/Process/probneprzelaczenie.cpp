#include "probneprzelaczenie.h"

bool ProbnePrzelaczenie::wybrany = false;

ProbnePrzelaczenie::ProbnePrzelaczenie(ZarzadzanieModelami * const zarzadzanie, GdkEventKey* event)
{
    if(event->keyval != GDK_KEY_s)return;
    if(wybrany)
    {
        auto rysWybrany = zarzadzanie->WyszukajModel(236);
        zarzadzanie->DoTransformacji(rysWybrany);
        cout<<"wybrany"<<endl;
//        zarzadzanie.
    }
    else
    {
        auto calosc = zarzadzanie->WyszukajModel(235);
        zarzadzanie->DoTransformacji(calosc);
        cout<<"całość"<<endl;
    }
        
    wybrany = !wybrany;
}
