#pragma once

#include "vgui.hpp"


namespace vgui
{

//We use CRTP to avoid using *.cpp files
template<typename T>
class Window : public Win32Window<Window<T>>
{
public:

    using WidgetType = T;
    using ThisType = Window<WidgetType>;
    using BaseType = Win32Window<ThisType>;

    void Create(const char* title, int x, int y, int width, int height, bool visible = true) override
    {
        BaseType::Create(title, x, y, width, height, visible);
        m_widget.m_window = this;
        AddToEventLoop(this);
    }

    void Destroy() override
    {
        BaseType::Destroy();
        RemoveFromEventLoop(this);
    }

    WidgetType& Widget()
    {
        return m_widget;
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

    void OnBeginPaint() override
    {
        this->Canvas().Begin();
    }

    void OnPaint() override
    {
        this->Canvas().Clear(255, 0, 0);
        //m_widget.OnDraw(canvas);
    }

    void OnEndPaint() override
    {
        this->Canvas().End();
    }

    void OnSize(double x, double y, double width, double height) override
    {
        //this->Canvas().Reset(width, height);
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
