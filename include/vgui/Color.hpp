#pragma once


namespace vgui
{

template<typename T>
struct ColorT
{
    T r;
    T g;
    T b;
    T a;
};

using ColorI = ColorT<int>;
using ColorF = ColorT<float>;
using ColorD = ColorT<double>;
using Color = ColorI;

}//namespace vgui
