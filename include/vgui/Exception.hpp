#pragma once

#include <string>
#include <string_view>
#include <cstring>

#ifndef VGUI_EXCEPTION_BUFFER_SIZE
    #define VGUI_EXCEPTION_BUFFER_SIZE 128
#endif


/**
    This macro uses for sending information into vgui::Eexception class objects.
    It sends name of current file, current line of code and name of function.
    Class have shift left operator and can recieve additional textual and digital information about exception.
    For example:
    void Foo()
    {
        int my_information = 123;
        ...
        throw ExceptionInfo << "One" << my_information << "Two" << "Three";
        ...
    }
*/
#define ExceptionInfo vgui::Exception("", __FILE__, __LINE__, __func__)


namespace vgui
{
class Exception : public std::exception
{
public:

    Exception(std::string_view text = "", std::string_view file = "", int line = 0, std::string_view func = "")
    {
        std::strncpy(m_text, text.begin(), VGUI_EXCEPTION_BUFFER_SIZE - 1);
        std::strncpy(m_file, file.begin(), VGUI_EXCEPTION_BUFFER_SIZE - 1);
        std::strncpy(m_func, func.begin(), VGUI_EXCEPTION_BUFFER_SIZE - 1);

        if(line != 0)
        {
            std::snprintf(s_buffer, VGUI_EXCEPTION_BUFFER_SIZE - 1, "%d", line);
            std::strncpy(m_line, s_buffer, VGUI_EXCEPTION_BUFFER_SIZE - 1);
        }
    }

    Exception(const Exception&) = default;

protected:

    virtual std::string_view Format() const
    {
        s_buffer[0] = '\0';

        if(std::strlen(m_text))
        {
            std::strncpy(s_buffer, m_text, VGUI_EXCEPTION_BUFFER_SIZE - 2);
            std::strcat(s_buffer, "\n");
        }

        if(std::strlen(m_file))
        {
            std::strcat(s_buffer, "\tin file: ");
            std::strncat(s_buffer, m_file, VGUI_EXCEPTION_BUFFER_SIZE - 2);
            std::strcat(s_buffer, "\n");
        }

        if(std::strlen(m_line))
        {
            std::strcat(s_buffer, "\tat line: ");
            std::strncat(s_buffer, m_line, VGUI_EXCEPTION_BUFFER_SIZE - 2);
            std::strcat(s_buffer, "\n");
        }

        if(std::strlen(m_func))
        {
            std::strcat(s_buffer, "\tin function: ");
            std::strncat(s_buffer, m_func, VGUI_EXCEPTION_BUFFER_SIZE - 2);
            std::strcat(s_buffer, "\n");
        }

        return std::string_view(s_buffer);
    }

public:

    const std::string_view What() const
    {
        return Format();
    }

    const char* what() const noexcept override
    {
        return Format().begin();
    }

    void Print() const
    {
        std::string_view str = Format();

        if(str.length())
            std::printf(str.begin());
    }

    Exception& operator << (const char* str)
    {
        std::strncat(m_text, str, VGUI_EXCEPTION_BUFFER_SIZE - std::strlen(m_text) - 1);
        return *this;        
    }

    Exception& operator << (char ch)
    {
        char str[2];
        str[0] = ch;
        str[1] = '\0';

        std::strncat(m_text, str, VGUI_EXCEPTION_BUFFER_SIZE - std::strlen(m_text) - 2 - 1);

        return *this;
    }

    template<typename T>
    Exception& operator << (T val)
    {
        static char str[VGUI_EXCEPTION_BUFFER_SIZE];
        str[0] = '\0';
        std::snprintf(str, VGUI_EXCEPTION_BUFFER_SIZE-1, "%d", val);

        std::strncat(m_text, str,
                     VGUI_EXCEPTION_BUFFER_SIZE
                     - std::strlen(m_text) - std::strlen(str) - 1);

        return *this;
    }

    std::string_view Text() const
    {
        return std::string_view(m_text);
    }

    std::string_view File() const
    {
        return std::string_view(m_file);
    }

    std::string_view Line() const
    {
        return std::string_view(m_line);
    }

    std::string_view Func() const
    {
        return std::string_view(m_func);
    }

protected:

    char m_text[VGUI_EXCEPTION_BUFFER_SIZE] = {""};
    char m_file[VGUI_EXCEPTION_BUFFER_SIZE] = {"\tin file: "};
    char m_line[VGUI_EXCEPTION_BUFFER_SIZE] = {"\tat line: "};
    char m_func[VGUI_EXCEPTION_BUFFER_SIZE] = {"\tin function: "};
    static inline char s_buffer[VGUI_EXCEPTION_BUFFER_SIZE * 5] = {""};
};//class Exception

}//namespace vgui

