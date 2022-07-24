#pragma once

#include <vgui/vgui.hpp>

namespace vgui
{

class MainWindow : public Window<Widget>
{
public:

    MainWindow(const char* title, int x, int y, int width, int height, bool visible = true)
    {
        Create(title, x, y, width, height);
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
