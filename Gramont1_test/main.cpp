#include <gtest/gtest.h>
//#include "../../gtk_GL_interfaces_tdd/funkcje/FunkcjePomocnicze.h"
#include <gtkmm.h>
#include <gtkglmm.h>


using namespace std;
using namespace Gtk;

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
//    StartGTK_GL(argc, argv);
    Gtk::Main app(argc,argv);
    GL::init(argc, argv);
    return RUN_ALL_TESTS();
    
}



