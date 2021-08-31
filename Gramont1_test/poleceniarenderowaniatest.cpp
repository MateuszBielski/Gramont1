#include <gtest/gtest.h>
#include "../src/Shared/grupowalne.h"
#include "../src/Shared/prostytrojkat.h"
#include "../src/Shared/donarysowaniajakopolecenia.h"
#include "../src/Process/renderowanie.h"
//#include "../src/Shared/rodzajakcji.cpp"

TEST(PoleceniaRenderowania,WstawieniePolecenDoZbioru)
{
    spDoNarysowania trojkat = make_shared<ProstyTrojkat>();
    Renderowanie rend;
    DoNarysowaniaJakoPolecenia polRys;
    polRys.PoleceniaWybierzIwstawWdobrejKolejnosci(trojkat);//rend
    auto polecenia =  polRys.Polecenia();
    
    ASSERT_EQ(3,polecenia.size());
    for(auto& pol : polecenia)
    {
        (rend.*pol)(trojkat);
    }
}
