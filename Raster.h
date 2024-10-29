#ifndef RASTER_H
#define RASTER_H
#include "Vector2.h"
#include "Vector4.h"
#include <cmath>
#include "Color.h"
#include <string>
#include "Triangle2D.h"
#include "Model.h"

class Raster {
private:
    int width;
    int height;
    Color* pixels;

void swap(float& a, float& b);

public:
    Raster();
    Raster(int pWidth, int pHeight, const Color& pFillColor);
    ~Raster();

    int getWidth() const;
    int getHeight() const;
    Color getColorPixel(int x, int y) const;
    void setColorPixel(int x, int y, const Color& pFillColor);
    void clear(const Color& pFillColor);
      void writeToPPM() const;
    void drawLine_DDA(float x1, float y1, float x2, float y2, const Color& fillColor);
    void drawLine_DDA_Interpolated(float x1, float y1, float x2, float y2, Color color1, Color color2);
    void drawTriangle_Barycentric(const Triangle3D& T);
    void drawTriangle2D_DotProduct(const Triangle2D& triangle);
    void drawModel(const Model& model);

};

#endif 