#pragma once

#include <vgui/Window.hpp>

namespace vgui
{

class MainWindow : public Window<Widget>
{
public:

    MainWindow(const char* title, int x, int y, int width, int height, bool visible = true) :
        Window(title, x, y, width, height, visible)
    {
        Create(title, x, y, width, height, visible);
    }

protected:

    void OnClose(bool& close) override
    {
        close = true;
    }

    void OnSize(double x, double y, double width, double height) override
    {
        Window::OnSize(x, y, width, height);

    }

private:

};//class MainWindow

}//namespace vgui
