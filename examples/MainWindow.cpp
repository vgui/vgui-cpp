#include <vgui/vgui.hpp>
#include "MainWindow.hpp"


int main()
{    
    try
    {
        vgui::MainWindow window("Main Window", 400, 200, 300, 300);
//        vgui::Window window2("Window1", 100, 100, 800, 600, false);
//        vgui::Window window3("Window3", 400, 400, 800, 600, false);
//        window2.SetVisible(true);
//        window3.SetVisible(true);

        return window.Run();
    }
    catch(const vgui::Exception& e)
    {
        e.Print();
    }
    catch(const std::exception& e)
    {
        std::cout << "std::exception was caught." << std::endl;
        std::cout << e.what() << std::endl;
    }
    catch(...)
    {
        std::cout << "Unknown Error in vgui application !" << std::endl;
    }

    return 0;
}
