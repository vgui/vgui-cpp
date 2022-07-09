#pragma once

#include "vgui.hpp"
#include <windows.h>
#include <kcanvas/canvas.h>

namespace vgui::impl
{

template<typename T>
class Win32Window : public vgui::EventHandler
{
private:

    //CRTP friend trick that allow check derived class.
    friend T;
    //Now derived class can call private constructor
    //() = default;

public:


    virtual ~Win32Window()
    {
        Destroy();
    }

    vgui::Rect Rect()
    {
        RECT rect;
        ::GetClientRect(m_hwnd, &rect);
        return {rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top};
    }

    bool Visible()
    {
        return static_cast<bool>(::IsWindowVisible(m_hwnd));
    }

    T& SetRect(double x, double y, double width, double height, bool redraw = true)
    {
        ::MoveWindow(m_hwnd, x, y, width, height, redraw);
        //SetWindowPos(m_hwnd, HWND_TOP, x, y, width, height, SWP_NOZORDER);

        //        RectI rect = Rect();
        //        OnSize(0, 0, rect.width, rect.height);

        if(redraw)
            Redraw();

        return Derived();
    }

    T& SetVisible(bool show = true)
    {
        if(show)
            ::ShowWindow(m_hwnd, SW_SHOW);
        else
            ::ShowWindow(m_hwnd, SW_HIDE);

        ::UpdateWindow(m_hwnd);

        return Derived();
    }

    T& Redraw()
    {
        vgui::Rect rect = Rect();
        OnSize(0, 0, rect.width, rect.height);

        ::InvalidateRgn(m_hwnd, nullptr, TRUE);
        ::UpdateWindow(m_hwnd);
        return Derived();
    }

    /* vgui::Canvas& Canvas()
    {
        return m_canvas;
    }*/

protected:

    virtual void UpdateLayout()
    {}

    virtual void SetPath(vgui::Path& path)
    {}

    virtual void ClipSiblings()
    {}

    virtual void ClipChildren()
    {}

    void DrawRoundRect(double l,double t,double w,double h)
    {
        /*cairo_t* cr = (cairo_t*)context->cobj();
        // a custom shape that could be wrapped in a function
        double x         = l,        // parameters like cairo_rectangle
                y         = t,
                width         = w,
                height        = h,
                aspect        = 1.0,     // aspect ratio
                corner_radius = height / 10.0;   // and corner curvature radius

        double radius = corner_radius / aspect;
        double degrees = M_PI / 180.0;

        cairo_new_sub_path (cr);
        cairo_arc (cr, x + width - radius, y + radius, radius, -90 * degrees, 0 * degrees);
        cairo_arc (cr, x + width - radius, y + height - radius, radius, 0 * degrees, 90 * degrees);
        cairo_arc (cr, x + radius, y + height - radius, radius, 90 * degrees, 180 * degrees);
        cairo_arc (cr, x + radius, y + radius, radius, 180 * degrees, 270 * degrees);
        cairo_close_path (cr);

        double r = (rand()%100)/100.0;
        double g = (rand()%100)/100.0;
        double b = (rand()%100)/100.0;

        cairo_set_source_rgb (cr, r, g, b);
        cairo_fill_preserve  (cr);
        cairo_set_source_rgba (cr, 0.5, 0, 0, 0.5);
        cairo_set_line_width (cr, 10.0);
        cairo_stroke (cr);*/
    }

    virtual bool ProcessEvent(HWND handle, UINT msg, WPARAM wparam, LPARAM lparam, LRESULT& result)
    {
        if(handle == m_hwnd)
        {
            if(msg == WM_PAINT)
            {
                PAINTSTRUCT ps;
                HDC hdc = ::BeginPaint(m_hwnd, &ps);

                RECT r;
                ::GetClientRect(m_hwnd, &r);

                using namespace k_canvas;
                kRectInt krect(
                    r.left, r.top,
                    r.right, r.bottom);

                kContextCanvas canvas(hdc, &krect);


                srand(time(NULL));

                for(int i = 0; i<300;i++)
                {
                    double r = (rand()%100)/100.0;
                    double g = (rand()%100)/100.0;
                    double b = (rand()%100)/100.0;

                    double l = 0;//(rand()%100);
                    double t = 100;//(rand()%100);
                    double w = 400;//(rand()%100);
                    double h = 300;//(rand()%100);
                    //DrawRoundRect(context, l, t, w, h);

                    kBrush bg(k_canvas::kColor(r,g,b,0.5));
                    canvas.Rectangle(kRect(l,t,w,h), nullptr, &bg);


                }
                ::EndPaint(m_hwnd, &ps);
                result = 0;
                return true;
            }
            else if(msg == WM_ERASEBKGND)
            {
                result = 1;
                return true;
            }
            else if(msg == WM_SIZE)
            {
                int width = LOWORD(lparam);
                int height = HIWORD(lparam);

                //m_canvas.Resize(width, height);
                OnSize(0, 0, width, height);
                //UpdateLayout();
                //SetPath(m_canvas.Path());
                ClipSiblings();
                ClipChildren();

                result = 0;
                return true;
            }
            else if(msg == WM_CLOSE)
            {
                bool close = false;
                OnClose(close);

                if(close)
                    Destroy();

                result = 0;
                return true;
            }
        }

        OnIdle();
        return false;
    }

    virtual void Create(const char* title, int x, int y, int width, int height, bool visible = true)
    {
        if(m_hwnd)
            throw ExceptionInfo << "Wind32 window already created.";

        std::wstring classname = L"Window";
        //Add to classname address of object
        classname += std::to_wstring(reinterpret_cast<int64_t>(this));

        HINSTANCE hinstance = (HINSTANCE)::GetModuleHandle(nullptr);

        WNDCLASSEXW wndclassex = {0};
        wndclassex.cbSize = sizeof(WNDCLASSEXW);
        wndclassex.lpfnWndProc = Win32Window::StaticProcessEvent;
        wndclassex.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
        wndclassex.hInstance = hinstance;
        wndclassex.lpszClassName = classname.c_str();
        wndclassex.hCursor = LoadCursor(nullptr, IDC_ARROW);

        if(!::RegisterClassExW(&wndclassex))
            throw ExceptionInfo << L"Can't register Win32 window class.";

        DWORD windowstyle = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
        //if(visible) windowstyle |= WS_VISIBLE;

        std::wstring wtitle = vgui::Utf8ToWstring(title);
        m_hwnd = ::CreateWindowExW(0, classname.c_str(), wtitle.c_str(), windowstyle,
                                   x, y, width, height, nullptr, nullptr, hinstance, this);

        if(!m_hwnd)
            throw ExceptionInfo << "Can't create Win32 window.";

        HDC hdc = ::GetDC(m_hwnd);
        m_created = true;

        if(visible)
        {
            ::ShowWindow(m_hwnd, SW_SHOW);
            ::UpdateWindow(m_hwnd);
        }
    }

    virtual void Destroy()
    {
        if(m_hwnd && ::IsWindow(m_hwnd))
        {
            //            if(m_hdc)
            //            {
            //                ::ReleaseDC(m_hwnd, m_hdc);
            //                m_hdc = nullptr;
            //            }

            ::DestroyWindow(m_hwnd);
            m_hwnd = nullptr;
        }

        m_created = false;
    }

private:

    HWND m_hwnd{nullptr};
    //HDC m_hdc {nullptr};

    vgui::ColorD m_color{0.0, 1.0, 1.0, 1.0};
    bool m_created = false;

    T& Derived() { return static_cast<T&>(*this); }

    HWND Handle()
    {
        return m_hwnd;
    }

    static LRESULT CALLBACK StaticProcessEvent(HWND handle, UINT msg, WPARAM wparam, LPARAM lparam)
    {
        if(msg == WM_NCCREATE)
        {
            LONG_PTR win_ptr = LONG_PTR(LPCREATESTRUCT(lparam)->lpCreateParams);

            if(win_ptr)
                SetWindowLongPtr(handle, GWLP_USERDATA, win_ptr);
            else
                throw ExceptionInfo << "Win32Window nullptr in CreateWindow function.";

            return 1;
        }
        else if(msg == WM_DESTROY)
        {
            PostQuitMessage(0);
            return 0;
        }

        Win32Window* window = (Win32Window*)::GetWindowLongPtr(handle, GWLP_USERDATA);
        LRESULT result = 0;

        //If window NO CREATED make default message processing.
        if(window &&  window->m_created && window->ProcessEvent(handle, msg, wparam, lparam, result))
            return result;
        else
            //Do not call DefWindowProc from Win32Window::ProcessEvent,  this will cause an OS error.
            return ::DefWindowProcW(handle, msg, wparam, lparam);
    }

    int ProcessEvents()
    {
        MSG msg;
        BOOL ret = FALSE;

        while((ret = GetMessage( &msg, nullptr, 0, 0 )) != 0)
        {
            if(ret == -1)
                throw ExceptionInfo << "Win32 event loop error.";
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }

        return msg.wParam;
    }

};

}//namespace vgui::impl

