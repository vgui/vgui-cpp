#include <string>
#include <vector>

using DOMString = std::string;


namespace vgui
{

enum CanvasWindingRule { nonzero, evenodd };

class CanvasGradient
{
public:

    void addColorStop(float offset, DOMString color);

};

class CanvasRenderingContext2D
{
public:

    void save();
    void restore();

    void scale(float sx, float sy);
    void rotate(float angle);
    void translate(float tx, float ty);
    void transform(float m11, float m12, float m21, float m22, float dx, float dy);
    void setTransform(float m11, float m12, float m21, float m22, float dx, float dy);


    CanvasGradient createLinearGradient(float x0, float y0, float x1, float y1);
    CanvasGradient createRadialGradient(float x0, float y0, float r0, float x1, float y1, float r1);


    void setLineDash(sequence<float> dash);
    sequence<float> getLineDash();

    void clearRect(float x, float y, float width, float height);
    void fillRect(float x, float y, float width, float height);

    void beginPath();
    void closePath();
    void moveTo(float x, float y);
    void lineTo(float x, float y);
    void quadraticCurveTo(float cpx, float cpy, float x, float y);
    void bezierCurveTo(float cp1x, float cp1y, float cp2x, float cp2y, float x, float y);
    void arcTo(float x1, float y1, float x2, float y2, float radius);
    void rect(float x, float y, float width, float height);
    void arc(float x, float y, float radius, float startAngle, float endAngle, [Default=Undefined] optional boolean anticlockwise);

                               void fill(optional CanvasWindingRule winding);
                               void stroke();
                               void clip(optional CanvasWindingRule winding);
                               boolean isPointInPath(float x, float y, optional CanvasWindingRule winding);
                               boolean isPointInStroke(float x, float y);


                               TextMetrics measureText(DOMString text);

                               // other

                               void setAlpha([Default=Undefined] optional float alpha);
                               void setCompositeOperation([Default=Undefined] optional DOMString compositeOperation);

                               void setLineWidth([Default=Undefined] optional float width);
                               void setLineCap([Default=Undefined] optional DOMString cap);
                               void setLineJoin([Default=Undefined] optional DOMString join);
                               void setMiterLimit([Default=Undefined] optional float limit);

                               void clearShadow();

                               void fillText(DOMString text, float x, float y, optional float maxWidth);
                               void strokeText(DOMString text, float x, float y, optional float maxWidth);

                               void setStrokeColor([StrictTypeChecking] DOMString color, optional float alpha);
                               void setStrokeColor(float grayLevel, optional float alpha);
                               void setStrokeColor(float r, float g, float b, float a);
                               void setStrokeColor(float c, float m, float y, float k, float a);

                               void setFillColor([StrictTypeChecking] DOMString color, optional float alpha);
                               void setFillColor(float grayLevel, optional float alpha);
                               void setFillColor(float r, float g, float b, float a);
                               void setFillColor(float c, float m, float y, float k, float a);

                               void strokeRect(float x, float y, float width, float height);

                               void drawImage(HTMLImageElement? image, float x, float y);
                               void drawImage(HTMLImageElement? image, float x, float y, float width, float height);
                               void drawImage(HTMLImageElement? image, float sx, float sy, float sw, float sh, float dx, float dy, float dw, float dh);
                               void drawImage(HTMLCanvasElement? canvas, float x, float y);
                               void drawImage(HTMLCanvasElement? canvas, float x, float y, float width, float height);
                               void drawImage(HTMLCanvasElement? canvas, float sx, float sy, float sw, float sh, float dx, float dy, float dw, float dh);

                               void drawImage(HTMLVideoElement? video, float x, float y);
                               void drawImage(HTMLVideoElement? video, float x, float y, float width, float height);
                               void drawImage(HTMLVideoElement? video, float sx, float sy, float sw, float sh, float dx, float dy, float dw, float dh);

                               void drawImageFromRect(HTMLImageElement image,
                               optional float sx, optional float sy, optional float sw, optional float sh,
                               optional float dx, optional float dy, optional float dw, optional float dh,
                               optional DOMString compositeOperation);

                               void setShadow(float width, float height, float blur, [StrictTypeChecking] optional DOMString color, optional float alpha);
                               void setShadow(float width, float height, float blur, float grayLevel, optional float alpha);
                               void setShadow(float width, float height, float blur, float r, float g, float b, float a);
                               void setShadow(float width, float height, float blur, float c, float m, float y, float k, float a);

                               void putImageData(ImageData? imagedata, float dx, float dy);
                               void putImageData(ImageData? imagedata, float dx, float dy, float dirtyX, float dirtyY, float dirtyWidth, float dirtyHeight);

                               void webkitPutImageDataHD(ImageData? imagedata, float dx, float dy);
                               void webkitPutImageDataHD(ImageData? imagedata, float dx, float dy, float dirtyX, float dirtyY, float dirtyWidth, float dirtyHeight);

                               CanvasPattern createPattern(HTMLCanvasElement? canvas, [TreatNullAs=NullString] DOMString repetitionType);
                               CanvasPattern createPattern(HTMLImageElement? image, [TreatNullAs=NullString] DOMString repetitionType);
                               ImageData createImageData(ImageData? imagedata);
                               ImageData createImageData(float sw, float sh);

                               // pixel manipulation
                               ImageData getImageData(float sx, float sy, float sw, float sh);

                               ImageData webkitGetImageDataHD(float sx, float sy, float sw, float sh);

                               private:

                               attribute float globalAlpha;
                               [TreatNullAs=NullString] attribute DOMString globalCompositeOperation;
                               attribute float lineWidth;
                               [TreatNullAs=NullString] attribute DOMString lineCap;
                               [TreatNullAs=NullString] attribute DOMString lineJoin;
                               attribute float miterLimit;

                               attribute float shadowOffsetX;
                               attribute float shadowOffsetY;
                               attribute float shadowBlur;
                               [TreatNullAs=NullString] attribute DOMString shadowColor;
                               attribute float lineDashOffset;

                               [Custom] attribute Array webkitLineDash;
                               attribute float webkitLineDashOffset;
                               attribute DOMPath currentPath;
                               [Custom] attribute custom strokeStyle;
                               [Custom] attribute custom fillStyle;
                               // text
                               attribute DOMString font;
                               attribute DOMString textAlign;
                               attribute DOMString textBaseline;

                               readonly attribute float webkitBackingStorePixelRatio;

                               attribute boolean webkitImageSmoothingEnabled;

};

}//namespace vgui
