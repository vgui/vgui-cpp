#pragma once

/*
#include "Color.hpp"
#include "Rect.hpp"
#include "Path.hpp"
#include "Canvas.hpp"
*/

#include <d3d9.h>
#include <d3d9x.h>


namespace vgui
{

class D3D9Context
{
public:

private:
IDirect3D9* m_d3d;
IDirect3D9Device* m_device;

};//class D3D9Context

}//namespace vgui

