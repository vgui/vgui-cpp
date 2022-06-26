#pragma once

#include <vgui/Rect.hpp>
#include <vgui/Color.hpp>
#include <vgui/Canvas.hpp>

namespace vgui
{

class EventHandler
{
protected:

    virtual void OnIdle(){}
    virtual void OnSizeChanging(double& /*x*/, double& /*y*/, double& /*width*/, double& /*height*/) {}
    virtual void OnSize(double /*x*/, double /*y*/, double /*width*/, double /*height*/) {}
    virtual void OnDraw(vgui::Canvas& /*canvas*/){}

    virtual void OnLostFocus(){}
    virtual void OnFocus(){}
    virtual void OnTextEnter(){}
    virtual void OnKeyPress(){}
    virtual void OnKeyRelease(){}
    virtual void OnMouseWheelMove(){}
    virtual void OnMouseWheelScroll(){}
    virtual void OnMouseButtonPress(){}
    virtual void OnMouseButtonRelease(){}
    virtual void OnMouseMove(){}
    virtual void OnMouseEnter(){}
    virtual void OnMouseLeft(){}
    virtual void OnJoystickButtonPress(){}
    virtual void OnJoystickButtonRelease(){}
    virtual void OnJoystickMove(){}
    virtual void OnJoystickConnect(){}
    virtual void OnJoystickDisconnect(){}
    virtual void OnTouchBegin(){}
    virtual void OnTouchMove(){}
    virtual void OnTouchEnd(){}
    virtual void OnSensorChange(){}
    virtual void OnClose(bool& close){ close = true; }

};//class EventHandler

}//namespace vgui

