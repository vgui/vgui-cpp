#pragma once

#include <windows.h>
#include <GL/glew.h>
#include "Exception.hpp"


namespace vgui
{

class WGLContext
{
public:

    WGLContext() = default;

    virtual ~WGLContext()
    {
        Destroy();
    }

    void Create(HWND handle)
    {
        ::PIXELFORMATDESCRIPTOR pfd {0};
        pfd.nSize = sizeof(::PIXELFORMATDESCRIPTOR);
        pfd.nVersion = 1;
        pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
        pfd.iPixelType = PFD_TYPE_RGBA;
        pfd.cColorBits = 32;
        //pfd.cDepthBits = 16;
        //pfd.cStencilBits = 8;
        pfd.iLayerType = PFD_MAIN_PLANE;

        //HDC desktop compatible
        HDC hdc = ::GetDC(NULL);
        int pixelformat = ::ChoosePixelFormat(hdc, &pfd);
        if(!pixelformat)
            throw ExceptionInfo << "Can't choose OpenGL pixelformat.";

        if(!::SetPixelFormat(hdc, pixelformat, &pfd))
            throw ExceptionInfo << "Can't set OpenGL pixelformat.";

        m_glrc = ::wglCreateContext(hdc);
        if(!m_glrc)
            throw ExceptionInfo << "Can't create OpenGL 2.0 context.";

        ::wglMakeCurrent(hdc, m_glrc);

        if(::glewInit() != GLEW_OK )
            throw ExceptionInfo << "Can't initialize GLEW.";

        glEnable(GL_ALPHA_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glShadeModel(GL_SMOOTH);
        //        glEnable(GL_DEPTH_TEST);
        //        glEnable(GL_COLOR_MATERIAL);
        //        glEnable(GL_LIGHTING);
        //        glEnable(GL_LIGHT0);

        m_vertex[0] = 0.0; m_vertex[1] = 0.0; m_vertex[2] =-1.0;
        m_vertex[3] =0.5; m_vertex[4] =0.0; m_vertex[5] =-1.0;
        m_vertex[6] = 0.0; m_vertex[7] =0.5; m_vertex[8]= -1.0;

        m_color[0] = 1.0; m_color[1] = 0.0; m_color[2] = 0.0;
        m_color[3] = 0.0; m_color[4] = 1.0; m_color[5] = 0.0;
        m_color[6] = 0.0; m_color[7] = 0.0; m_color[8] = 1.0;

        // Second simple object
        float* vert2 = new float[9];	// vertex array

        vert2[0] =-0.2; vert2[1] = 0.5; vert2[2] =-1.0;
        vert2[3] = 0.3; vert2[4] =-0.5; vert2[5] =-1.0;
        vert2[6] = 0.8; vert2[7] = 0.5; vert2[8]= -1.0;

        // Two VAOs allocation
        glGenVertexArrays(2, &m_vaoID[0]);

        // First VAO setup
        glBindVertexArray(m_vaoID[0]);

        glGenBuffers(2, m_vboID);

        glBindBuffer(GL_ARRAY_BUFFER, m_vboID[0]);
        glBufferData(GL_ARRAY_BUFFER, 9*sizeof(GLfloat), m_vertex, GL_STATIC_DRAW);
        glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, m_vboID[1]);
        glBufferData(GL_ARRAY_BUFFER, 9*sizeof(GLfloat), m_color, GL_STATIC_DRAW);
        glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(1);

        // Second VAO setup
        glBindVertexArray(m_vaoID[1]);

        glGenBuffers(1, &m_vboID[2]);

        glBindBuffer(GL_ARRAY_BUFFER, m_vboID[2]);
        glBufferData(GL_ARRAY_BUFFER, 9*sizeof(GLfloat), vert2, GL_STATIC_DRAW);
        glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);

        glBindVertexArray(0);

        ::wglMakeCurrent(nullptr, nullptr);
    }

    void Destroy()
    {
        if(m_glrc)
        {
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            glDeleteBuffers(3, m_vboID);

            glBindVertexArray(0);
            glDeleteVertexArrays(2, m_vaoID);

            ::wglMakeCurrent(nullptr, nullptr);
            ::wglDeleteContext(m_glrc);
            m_glrc = nullptr;
        }
    }

    void Reshape(int width, int height)
    {
    }

    void BeginFrame(HDC hdc)
    {
        ::wglMakeCurrent(hdc, m_glrc);
    }

    void Render()
    {
    }

    void EndFrame(HDC hdc)
    {
        ::SwapBuffers(hdc);
        ::wglMakeCurrent(nullptr, nullptr);
    }

    void Clear(float R, float G, float B, float A)
    {
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

private:

    HGLRC m_glrc {nullptr};
    GLuint m_vaoID[2];			// two vertex array objects, one for each drawn object
    GLuint m_vboID[3];			// three VBOs
    float m_vertex[9] = {0.0f};
    float m_color[9] = {0.0f};

};//class WGLContext


}//namespace vgui

