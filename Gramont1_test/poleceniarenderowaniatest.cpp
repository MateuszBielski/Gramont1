#include <gtest/gtest.h>
#include "../src/Shared/grupowalne.h"
#include "../src/Shared/prostytrojkat.h"
#include "../src/Shared/donarysowaniajakopolecenia.h"
#include "../src/Process/renderowanie.h"
//#include "../src/Shared/rodzajakcji.cpp"

TEST(PoleceniaRenderowania,WstawieniePolecenDoZbioru)
{
    spDoNarysowania trojkat = make_shared<ProstyTrojkat>();
    DoNarysowaniaJakoPolecenia<spDoNarysowania,Renderowanie> polRys;
    polRys.PoleceniaWybierzIwstawWdobrejKolejnosci(trojkat);
    auto polecenia =  polRys.Polecenia();
    
    ASSERT_EQ(3,polecenia.size());
    
    Renderowanie rend;
    for(auto& pol : polecenia)
    {
        (rend.*pol)(trojkat);
    }
}
