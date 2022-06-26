#pragma once

#include <vgui/vgui.hpp>


namespace vgui
{

class Widget : public vgui::Relatives<Widget>, public vgui::EventHandler
{
public:

    friend class vgui::Window<Widget>;
    using WindowType = vgui::Window<Widget>;

    Widget() = default;

    //    Widget(Widget* parent, size_t index = MaxIndex) : base_type(parent, index)
    //    {
    //    }

    virtual ~Widget()
    {}

    bool Visible()
    {
        if(m_parentvisible && m_visible)
            return true;
        else
            return false;
    }

    void SetVisible(bool visible)
    {
        if(!Parent())
        {
            m_parentvisible = Window()->Visible(); m_visible = visible;
        }
        else
        {
            bool parentvisible = Parent()->Visible();

            m_visible = visible;

            for(size_t i = 0 ; i < Childs(); ++i)
                Child(i).SetParentVisible(parentvisible && m_visible);
        }
    }

    double X()
    {
        return m_x;
    }

    double Y()
    {
        return m_y;
    }

    double Width()
    {
        return m_width;
    }

    double Height()
    {
        return m_height;
    }

    RectD Rect() const
    {
        return {m_x, m_y, m_width, m_height};
    }

    Widget& SetRect(const RectD& rect)
    {
        return SetRect(rect.x, rect.y, rect.width, rect.height);
    }

    Widget& SetRect(double x, double y, double width, double height)
    {
        OnSizeChanging(x, y, width, height);

        if(Parent())
        {
            auto [left_offset, top_offset, right_offset, bottom_offset] = ViewportOffset();

            {//Formatting block. QtCreator-4.14.0 not recognize structure bindings.
                m_dx = Parent()->m_dx + left_offset + x;
                m_dy = Parent()->m_dy + top_offset + y;
            }
        }
        else
        {
            m_dx = x;
            m_dy = y;
        }

        m_x = x;
        m_y = y;
        m_width = width;
        m_height = height;

        OnSize(m_x, m_y, m_width, m_height);

        return *this;
    }

    RectD Viewport()
    {
        return {m_dx, m_dy, m_width, m_height};
    }

    virtual std::tuple<double, double, double, double> ViewportOffset()
    {
        return {0.0, 0.0, 0.0, 0.0};//{BorderWidth(), BorderWidth(), BorderWidth(), BorderWidth()};
    }

    WindowType* Window() const
    {
        return m_window;
    }

    vgui::Canvas& Canvas()
    {
        return m_window->Canvas();
    }

    Widget& Redraw()
    {
        OnDraw(Canvas());
        return *this;
    }

    Widget& SetText(std::string text)
    {
        m_text = text;
        return *this;
    }

    std::string Text()
    {
        return m_text;
    }

protected:

    void OnParentChanging(Widget* newparent, size_t& newchildindex) override
    {
        if(newparent)
            m_window = newparent->m_window;
    }

    void OnDraw(vgui::Canvas& canvas) override
    {
        if(Visible())
        {
//            g.Render(m_inclipper, Color());
//            g.Render(m_stroker, BorderColor());

            for(size_t i = 0; i < Childs(); ++i)
                Child(i).OnDraw(canvas);
        }
    }

    void OnSize(double x, double y, double width, double height) override
    {}

    virtual void UpdateLayout()
    {
        for(size_t i = 0; i < Childs(); ++i)
            Child(i).UpdateLayout();
    }

    virtual void SetPath(vgui::Path& path)
    {
        //auto [dx, dy, width, height] = Viewport(); auto [left, top, right, bottom] = ViewportOffset();


      /*  {//Formatting block. QtCreator-4.14.0 not recognize structure bindings.
            path.Reset();
            path.RoundedRect(dx, dy, dx + width, dy + height, Theme()->RoundedRectCornerRadius);
            Graphics().Render(path, m_outclipper);

            path.Reset();
            path.RoundedRect(dx + left, dy + top, dx + width - right, dy + height - bottom, Theme()->RoundedRectCornerRadius);
            Graphics().Render(path, m_inclipper);

            auto [storage, sl1, sl2, sl3] = Graphics().RendererCache();
            agg::sbool_combine_shapes_aa(agg::sbool_a_minus_b, m_outclipper, m_inclipper, sl1, sl2, sl3, m_stroker);
        }*/

        for(size_t i = 0; i < Childs(); ++i)
        {
            Child(i).SetPath(path);
            std::cout << "Child - " << Text() << " - " << Child(i).Text() << std::endl;
        }
    }

    void ClipSiblings()
    {
        //auto [dest, sl1, sl2, sl3] = Graphics().RendererCache();

        for(size_t i = ChildIndex() + 1; i < Siblings(); ++i)
        {
         /*   agg::sbool_combine_shapes_aa(agg::sbool_a_minus_b, m_outclipper, Sibling(i).m_outclipper, sl1, sl2, sl3, dest);
            m_outclipper.swap(dest);

            agg::sbool_combine_shapes_aa(agg::sbool_a_minus_b, m_stroker, Sibling(i).m_outclipper, sl1, sl2, sl3, dest);
            m_stroker.swap(dest);

            agg::sbool_combine_shapes_aa(agg::sbool_a_minus_b, m_inclipper, Sibling(i).m_outclipper, sl1, sl2, sl3, dest);
            m_inclipper.swap(dest);
            */
        }

        for(size_t i = 0; i < Childs(); ++i)
            Child(i).ClipSiblings();
    }

    void ClipChildren()
    {
        //auto [dest, sl1, sl2, sl3] = Graphics().RendererCache();

        for(size_t i = 0; i < Childs(); ++i)
        {
          /*  agg::sbool_combine_shapes_aa(agg::sbool_and, Child(i).m_outclipper, m_outclipper, sl1, sl2, sl3, dest);
            Child(i).m_outclipper.swap(dest);

            agg::sbool_combine_shapes_aa(agg::sbool_and, Child(i).m_inclipper, m_outclipper, sl1, sl2, sl3, dest);
            Child(i).m_inclipper.swap(dest);

            agg::sbool_combine_shapes_aa(agg::sbool_and, Child(i).m_stroker, m_outclipper, sl1, sl2, sl3, dest);
            Child(i).m_stroker.swap(dest);

            agg::sbool_combine_shapes_aa(agg::sbool_a_minus_b, m_outclipper, Child(i).m_outclipper, sl1, sl2, sl3, dest);
            m_outclipper.swap(dest);
            */
        }

        for(size_t i = 0; i < Childs(); ++i)
            Child(i).ClipChildren();
    }

private:

    void SetParentVisible(bool visible)
    {
        m_parentvisible = visible;

        for(size_t i = 0; i < Childs(); ++i)
            Child(i).SetParentVisible(visible);
    }

    WindowType* m_window {nullptr};

    bool m_visible = true;
    bool m_parentvisible = true;
    double m_dx {0};
    double m_dy {0};
    double m_x {0};
    double m_y {0};
    double m_width {0};
    double m_height {0};

    std::string m_text = "Widget";

};//class Widget

}//namespace vgui

