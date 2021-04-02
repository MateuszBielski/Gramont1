#include <gtest/gtest.h>
#include <GL/gl.h>
#include <thread>
#include <future>
//#include <gtkglmm.h>

#include "../src/Polecenie/kolejkapolecen.h"
#include "../src/Process/obslugasygnalow.h"
#include "../src/Polecenie/obrot.h"
//#include "../src/Process/zarzadzaniemodelami.h"
#include "zarzadzaniemodelamimock.h"



//https://github.com/anthonywilliams/ccia_code_samples/blob/main/listings/listing_6.2.cpp - threadsafe_queue
//https://github.com/anthonywilliams/ccia_code_samples/blob/main/listings/listing_11.1.cpp testowanie jak wyżej

TEST(KolejkaPolecen,DodanieIzabraniePoleceniaWjednymCzasie)
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
TEST(KolejkaPolecen,DodanieIzabraniePoleceniaWjednymCzasieKonwersjaTypu)
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
