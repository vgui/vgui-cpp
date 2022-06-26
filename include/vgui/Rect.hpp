#pragma once


namespace vgui
{

template<typename T>
struct PointT
{
    T x {0};
    T y {0};
};

using PointI = PointT<int>;
using PointF = PointT<float>;
using PointD = PointT<double>;
using Point = PointI;

template<typename T>
struct SizeT
{
    T width {0};
    T height {0};
};

using SizeI = SizeT<int>;
using SizeF = SizeT<float>;
using SizeD = SizeT<double>;
using Size = SizeI;

template<typename T>
class RectT
{
public:

    T x {0};
    T y {0};
    T width {0};
    T height {0};
};

using RectI = RectT<int>;
using RectF = RectT<float>;
using RectD = RectT<double>;
using Rect = RectI;

}//namespace vgui
