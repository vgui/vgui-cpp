#pragma once

#include "vgui.hpp"
#include <cairo/cairo.h>
#include <cairo/cairo-win32.h>


namespace vgui
{

class Canvas
{
public:

    Canvas() = default;

    Canvas(HDC hdc) : m_hdc(hdc)
    {
        m_surface = cairo_win32_surface_create(m_hdc);

        if(!m_surface)
            throw ExceptionInfo << "Can't create Win32 Cairo surface.";

        //cairo_create function does not return NULL.
        m_cairo = cairo_create(m_surface);

    }

    ~Canvas()
    {
        if(m_cairo)
        {
            cairo_destroy(m_cairo);
            m_cairo = nullptr;
        }

        if(m_surface)
        {
            cairo_surface_destroy(m_surface);
            m_surface = nullptr;
        }
    }

    Canvas& Fill(vgui::ColorD color)
    {

        cairo_set_source_rgba(m_cairo, color.r , color.g, color.b, 1.0);
        cairo_rectangle(m_cairo, rect.left, rect.top, rect.right, rect.bottom);
        cairo_fill(m_cairo);
        return *this;
    }

private:

    HDC m_hdc {nullptr};
    cairo_surface_t* m_surface {nullptr};
    cairo_t* m_cairo {nullptr};
};//class Canvas

}//namespace vgui
