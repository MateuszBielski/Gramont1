#include "probneprzelaczenie.h"

bool ProbnePrzelaczenie::wybrany = false;

ProbnePrzelaczenie::ProbnePrzelaczenie(ZarzadzanieModelami * const zarzadzanie)
{
    
    spDoNarysowania coWybrano = nullptr;
    if(wybrany)
    {
        coWybrano  = zarzadzanie->WyszukajModel(235);
//        zarzadzanie->DoTransformacji(rysWybrany);
        cout<<"wybrany"<<endl;
//        zarzadzanie.
    }
    else
    {
        coWybrano = zarzadzanie->WyszukajModel(234);
        cout<<"całość"<<endl;
    }
        
    if(!coWybrano)
        cout<<"zarzadzanie->WyszukajModel zwróciła nullptr"<<endl;
    zarzadzanie->DoTransformacji(coWybrano);
    wybrany = !wybrany;
}
