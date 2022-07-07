#pragma once

#include "vgui.hpp"


namespace vgui
{

//We use CRTP to avoid using *.cpp files
template<typename T>
class Window : public impl::Win32Window<Window<T>>
{
public:

    using WidgetType = T;
    using ThisType = vgui::Window<WidgetType>;
    using BaseType = impl::Win32Window<ThisType>;

    Window(const char* title, int x, int y, int width, int height, bool visible = true) :
        BaseType()
    {
        m_widget.m_window = this;
    }

    WidgetType& Widget()
    {
        return m_widget;
    }

    void Create(const char* title, int x, int y, int width, int height, bool visible) override
    {
        BaseType::Create(title, x, y, width, height, visible);
        AddToEventLoop(this);
    }

    void Destroy() override
    {
        RemoveFromEventLoop(this);
        BaseType::Destroy();
    }

    static int Run()
    {
        while(s_windows.size())
        {
            for(auto window : s_windows)
                window->ProcessEvents();

           /* for(auto window : s_windows)
                window->OnIdle();*/
        }

        return 777;
    }

protected:

    void OnDraw() override
    {
        //m_widget.OnDraw(canvas);
    }

    void OnSize(double x, double y, double width, double height) override
    {
        m_widget.SetRect(0, 0, width, height);
    }

    void UpdateLayout() override
    {

    }

    void SetPath(vgui::Path& path) override
    {
        m_widget.SetPath(path);
    }

    void ClipSiblings() override
    {
        m_widget.ClipSiblings();
    }

    void ClipChildren() override
    {
        m_widget.ClipChildren();
    }

private:

    static void AddToEventLoop(ThisType* window)
    {
        auto i = std::find(s_windows.begin(), s_windows.end(), window);

        if( i== s_windows.end())
            s_windows.push_back(window);
    }

    static void RemoveFromEventLoop(ThisType* window)
    {
        auto i = std::find(s_windows.begin(), s_windows.end(), window);

        if( i!= s_windows.end())
            s_windows.erase(i);
    }

    WidgetType m_widget;

    static inline std::vector<ThisType*> s_windows;
};//class Window


}//namespace vgui
