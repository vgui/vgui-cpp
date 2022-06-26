#pragma once


namespace vgui
{


#include <cmath>

/**
  If return type of 'operator' std::is_integral,
  and argement type of 'operator' std::is_floating_point,
  then std::round is the result.
  Otherwise used 'operator' without rounding.
*/
#define VGUI_ROUND_OPERATOR(Name, op) \
    template<typename R, typename A> \
    R Name(R arg1, A arg2) \
{ if constexpr(std::is_integral<R>::value == true && \
    std::is_floating_point<A>::value == true) \
    return static_cast<R>(std::round(arg1 op arg2)); \
    else return static_cast<R>(arg1 op arg2); }


VGUI_ROUND_OPERATOR(RoundAdd, +)
VGUI_ROUND_OPERATOR(RoundSub, -)
VGUI_ROUND_OPERATOR(RoundMult, *)
VGUI_ROUND_OPERATOR(RoundDiv, /)


#ifdef _WIN32

#include <string>
#include <cstring>
#include <windows.h>
#include <tchar.h>

using tstring  = std::basic_string<TCHAR>;
using tstringstream  = std::basic_stringstream<TCHAR>;

static std::wstring Utf8ToWstring(const char* str)
{
    size_t length = std::strlen(str);

    if(length != 0)
    {
        int num_chars = ::MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, str, length, NULL, 0);
        std::wstring wstrTo;
        if(num_chars)
        {
            wstrTo.resize(num_chars);
            if(::MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, str, length, &wstrTo[0], num_chars))
            {
                return wstrTo;
            }
        }
    }

    return std::wstring();
}

#endif//_WIN32

}//namespace vgui

