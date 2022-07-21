#pragma once

/*
#include "Color.hpp"
#include "Rect.hpp"
#include "Path.hpp"
#include "Canvas.hpp"
*/

#include "Exception.hpp"
#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9math.h>
#include <d3dx9tex.h>
#include <wrl.h>

namespace wrl = Microsoft::WRL;

namespace vgui
{

class D3D9Canvas
{
public:

    wrl::ComPtr<IDirect3DDevice9> Device()
    {
        return m_device;
    }

    void Create(HWND hwnd, int width, int height)
    {
        if(!s_d3d)
        {
            if(::CoInitialize(NULL) < 0)
                throw ExceptionInfo << "COM initializing error.";

            s_d3d = ::Direct3DCreate9(D3D_SDK_VERSION);

            if(!s_d3d)
                throw ExceptionInfo << "Direct3D9: Initialization error.";
        }

        if(!::IsWindow(hwnd))
            throw ExceptionInfo << "Direct3D9: invalid window handle.";
        else
            m_hwnd = hwnd;

        D3DPRESENT_PARAMETERS params = {0};
        params.Windowed = TRUE;
        params.SwapEffect = D3DSWAPEFFECT_DISCARD;
        params.BackBufferFormat = D3DFMT_X8R8G8B8;
        params.BackBufferCount = 1;
        params.hDeviceWindow = m_hwnd;
        params.BackBufferWidth = width;
        params.BackBufferHeight = height;
        params.MultiSampleType = D3DMULTISAMPLE_16_SAMPLES;

        if(s_d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
                                      m_hwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &params, &m_device) < 0)
            throw ExceptionInfo << "Direct3D9: can't create device.";

        if(m_device->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, TRUE) < 0)
            throw ExceptionInfo << "Direct3D9: can't set antialiasing.";

    }

    void Reset(int width, int height)
    {
        //IF CLIENT AREA WIDTH OR HEIGHT EQUAL TO ZERO THAN IDirect3dDevice9::Reset
        //WILL CAUSE RUNTIME ERROR
        if(width == 0) width = 1;
        if(height == 0) height = 1;

        D3DPRESENT_PARAMETERS params {0};
        params.Windowed = TRUE;
        params.SwapEffect = D3DSWAPEFFECT_DISCARD;
        params.BackBufferFormat = D3DFMT_X8R8G8B8;
        params.BackBufferCount = 1;
        params.hDeviceWindow = m_hwnd;
        params.BackBufferWidth = width;
        params.BackBufferHeight = height;
        params.MultiSampleType = D3DMULTISAMPLE_16_SAMPLES;

        if(m_device->Reset(&params) < 0)
            throw ExceptionInfo << "Direct3D9: can't reset device.";

        if(m_device->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, TRUE) < 0)
            throw ExceptionInfo << "Direct3D9: can't set antialiasing.";
    }

    void Destroy()
    {
        if(m_surface) m_surface.Reset();
        if(m_device) m_device.Reset();
        m_hwnd = nullptr;
        //::CoUninitialize();
    }

    HWND Window()
    {
        return m_hwnd;
    }

    void Clear(byte r, byte g, byte b)
    {
        if(m_device->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_XRGB(r, g, b), 1.0f, 0) < 0)
            throw ExceptionInfo << "Direct3D9: can't clear device.";;
    }

    void Begin()
    {
        if(m_device->BeginScene() == D3D_OK)
        {
            if(m_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE) < 0)
                throw ExceptionInfo << "Direct3D9: can't set render state.";

            if(m_device->SetRenderState(D3DRS_LIGHTING, FALSE) < 0)
                throw ExceptionInfo << "Direct3D9: can't set render state.";

            if(m_device->SetRenderState(D3DRS_AMBIENT,RGB(255,255,255)) < 0)
                throw ExceptionInfo << "Direct3D9: can't set render state.";

            if(m_device->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE) < 0)
                throw ExceptionInfo << "Direct3D9: can't set render state.";
        }
    }

    void End()
    {
        if(m_device->EndScene() < 0)
            throw ExceptionInfo << "Direct3D9: can't end scene.";

        if(m_device->Present(nullptr,nullptr, nullptr, nullptr) < 0)
            throw ExceptionInfo << "Direct3D9: can't present.";
    }

private:

    HWND m_hwnd{nullptr};
    wrl::ComPtr<IDirect3DDevice9> m_device;
    wrl::ComPtr<IDirect3DSurface9> m_surface;
    static inline wrl::ComPtr<IDirect3D9> s_d3d {nullptr};

};//class D3D9Canvas
/*
class DX9Window : public Window
{
public:

    DX9Window(const char* title, int x, int y, int width, int height) :
        Window()
    {
        if(FAILED(::CoInitialize(NULL)))
            throw std::runtime_error("COM initializing error.");

        Create(title, x, y, width, height);
    }

    virtual ~DX9Window()
    {
        ::CoUninitialize();
    }

protected:

    void Create(const char* title, int x, int y, int width, int height) override
    {
        Window::Create(title, x, y, width, height);

        m_canvas.CreateDevice(Handle(), 0, 0);
    }


    void OnPaint() override
    {
        m_d3dmutex.lock();

        int width = ViewportWidth();
        int height = ViewportHeight();

        m_canvas.BeginDraw();
        m_canvas.Clear(255, 255, 255);

        {
            static float angle{0};
            angle += 0.1f;

            D3DXMATRIX rotation;
            //            D3DXMatrixRotationZ(&rotation, angle);
            //            if(FAILED(m_device->SetTransform(D3DTS_WORLD, &rotation)))
            //               throw std::runtime_error("Direct3D9: can't create vertex buffer.");

            ComPtr<IDirect3DDevice9> device = m_canvas.Device();
            device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
            device->SetRenderState(D3DRS_LIGHTING, FALSE);
            device->SetRenderState(D3DRS_AMBIENT,RGB(255,255,255));
            device->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);

            D3DVERTEX vertices[3];

            vertices[0].x = -1.0;
            vertices[0].y = -1.0;
            vertices[0].z = 0.0;
            vertices[0].color = D3DCOLOR_XRGB(255, 0, 0);

            vertices[1].x = 0.0;
            vertices[1].y = 1.0;
            vertices[1].z = 0.0;
            vertices[1].color = D3DCOLOR_XRGB(0, 255, 0);

            vertices[2].x =  1.0;
            vertices[2].y = -1.0;
            vertices[2].z = 0.0;
            vertices[2].color = D3DCOLOR_XRGB(0, 0, 255);

            ComPtr<IDirect3DVertexBuffer9> vertex_buffer;
            void *video_memory = nullptr;

            if(FAILED(device->CreateVertexBuffer(3*sizeof(D3DVERTEX), 0,
                                                   D3DFVF_XYZ|D3DFVF_DIFFUSE, D3DPOOL_DEFAULT, &vertex_buffer, NULL)))
                throw std::runtime_error("Direct3D9: can't create vertex buffer.");

            if(FAILED(vertex_buffer->Lock(0, 3*sizeof(D3DVERTEX), &video_memory, 0)))
                throw std::runtime_error("Direct3D9: can't lock vertex object.");

            memcpy(video_memory, vertices, 3*sizeof(D3DVERTEX));

            if(FAILED(vertex_buffer->Unlock()))
                throw std::runtime_error("Direct3D9: can't unlock vertex object.");

            if(FAILED(device->SetStreamSource(0, vertex_buffer.Get(), 0, sizeof(D3DVERTEX))))
                throw std::runtime_error("Direct3D9: can't set stream source.");

            if(FAILED(device->SetFVF(D3DFVF_XYZ|D3DFVF_DIFFUSE)))
                throw std::runtime_error("Direct3D9: can't set format.");

            if(FAILED(device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1)))
                throw std::runtime_error("Direct3D9: can't draw primitives.");

            if(FAILED(device->EndScene()))
                throw std::runtime_error("Direct3D9: can't end scene.");

            if(FAILED(device->Present(NULL,NULL, NULL, NULL)))
                throw std::runtime_error("Direct3D9: can't present.");

            vertex_buffer.Reset();
        }

        m_d3dmutex.unlock();
    }

    void OnResize(int width, int height) override
    {
        m_d3dmutex.lock();
        m_canvas.ResetDevice(width, height);
        m_d3dmutex.unlock();
    }

private:

    HWND m_hwnd = nullptr;
    wrl::ComPtr<IDirect3DDevice9> m_device;
    wrl::ComPtr<IDirect3DSurface9> m_surface;
    static inline wrl::ComPtr<IDirect3D9> s_d3d = nullptr;

};//class D3D9Canvas
*/
}//namespace vgui

