#include <gtest/gtest.h>
#include <GL/gl.h>
#include <thread>
#include <future>
//#include <gtkglmm.h>

#include "../src/Polecenie/kolejkapolecen.h"
#include "../src/Process/obslugasygnalow.h"
#include "../src/Polecenie/obrot.h"
#include "../src/Polecenie/przerysuj.h"
#include "../src/Polecenie/ustawdonarysowania.h"
//#include "../src/Process/zarzadzaniemodelami.h"
#include "zarzadzaniemodelamimock.h"
#include "obslugapolecenmock.h"
#include "renderowaniemock.h"
#include "testrenderklas.h"



//https://github.com/anthonywilliams/ccia_code_samples/blob/main/listings/listing_6.2.cpp - threadsafe_queue
//https://github.com/anthonywilliams/ccia_code_samples/blob/main/listings/listing_11.1.cpp testowanie jak wyżej

TEST(PolecenieTest,DodanieIzabraniePoleceniaWjednymCzasie)
{
    KolejkaPolecen q;

    std::promise<void> go,push_ready,pop_ready;
    std::shared_future<void> ready(go.get_future());

    std::future<void> push_done;
    std::future<upPolecenie> pop_done;
    
    

    try
    {
        push_done=std::async(std::launch::async,
                             [&q,ready,&push_ready]()
                             {
                                 upPolecenie polecenie42= make_unique<PoleceniePuste>(42);
                                 push_ready.set_value();
                                 ready.wait();
                                 q.push(move(polecenie42));
                             }
            );
        pop_done=std::async(std::launch::async,
                            [&q,ready,&pop_ready]()
                            {
                                pop_ready.set_value();
                                ready.wait();
                                return q.wait_and_pop();
                            }
            );
        push_ready.get_future().wait();
        pop_ready.get_future().wait();
        go.set_value();

        push_done.get();
        Polecenie* pol= pop_done.get().get();
        PoleceniePuste* result = static_cast<PoleceniePuste*>(pol);
        ASSERT_EQ(42,result->id);
        ASSERT_TRUE(q.empty());
    }
    catch(...)
    {
        go.set_value();
        throw;
    }
}
TEST(PolecenieTest,DodanieIzabraniePoleceniaWjednymCzasieKonwersjaTypu)
{
    KolejkaPolecen q;

    std::promise<void> go,push_ready,pop_ready;
    std::shared_future<void> ready(go.get_future());

    std::future<void> push_done;
    std::future<PoleceniePuste> pop_done;
    
    

    try
    {
        push_done=std::async(std::launch::async,
                             [&q,ready,&push_ready]()
                             {
                                 upPolecenie polecenie42= make_unique<PoleceniePuste>(42);
                                 push_ready.set_value();
                                 ready.wait();
                                 q.push(move(polecenie42));
                             }
            );
        pop_done=std::async(std::launch::async,
                            [&q,ready,&pop_ready]()
                            {
                                pop_ready.set_value();
                                ready.wait();
                                return q.wait_and_pop<PoleceniePuste>();
                            }
            );
        push_ready.get_future().wait();
        pop_ready.get_future().wait();
        go.set_value();

        push_done.get();
//        Polecenie* pol= pop_done.get().get();
        PoleceniePuste result = pop_done.get();
        ASSERT_EQ(42,result.id);
        ASSERT_TRUE(q.empty());
    }
    catch(...)
    {
        go.set_value();
        throw;
    }
}

TEST(PolecenieTest,PolecenieKoniecZatrzymujeRun)
{
    ObslugaPolecenMock obslPolecen;
    
    auto kolejka = obslPolecen.getKolejkaPolecen();
    thread t(&ObslugaPolecen::Run,&obslPolecen);
    kolejka->push(make_unique<PolecenieKoniec>());
    t.join();
    ASSERT_EQ(1,obslPolecen.licznikRun);
}

TEST(PolecenieTest,WykonanieKilkuPolecen)
{
    ObslugaPolecenMock obslPolecen;
    
    auto kolejka = obslPolecen.getKolejkaPolecen();
    thread t(&ObslugaPolecen::Run,&obslPolecen);
    for(short i = 0; i < 4 ; i++)kolejka->push(make_unique<PoleceniePuste>(i));
    kolejka->push(make_unique<PolecenieKoniec>());
    t.join();
    ASSERT_EQ(5,obslPolecen.licznikRun);
}
TEST(PolecenieTest,PrzerysujUzywaRenderowanieFunPrzerysuj)
{
    RenderowanieMock renderowanie;
    Przerysuj przerysuj(make_shared<DoNarysowania>());
    przerysuj.WykonajW(renderowanie);
    ASSERT_TRUE(renderowanie.przerysujDostaloDoNarysowania);
}

TEST(PolecenieTest,UstawDoNarysowania)
{
    Renderowanie rend;
    
    spDoNarysowania rys(make_shared<DoNarysowania>());
    auto kolejka = rend.getKolejkaPolecen();
    kolejka->push(make_unique<UstawDoNarysowania>(rys));
    kolejka->push(make_unique<PolecenieKoniec>());
    rend.Run();
    
    TestRenderKlas testRend;
    ASSERT_TRUE(testRend.CzyMaTenSamDoNarysowania(rend,rys));
}