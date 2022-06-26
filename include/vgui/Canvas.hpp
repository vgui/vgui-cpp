#pragma once

#include <vgui/vgui.hpp>


namespace vgui
{

class Canvas
{
public:

    Canvas()
    {}

    ~Canvas()
    {}

    Canvas& Clear(vgui::Color color)
    {

        return *this;
    }

    Canvas& Display(HDC hdc)
    {

        return *this;
    }

    Canvas& Resize(size_t width, size_t height)
    {

        return *this;
    }

    vgui::Path& Path()
    {

        return m_path;
    }

    Canvas& SetPath(vgui::Path path)
    {

        return *this;
    }

private:

    vgui::Path m_path;
};//class Canvas

}//namespace vgui
