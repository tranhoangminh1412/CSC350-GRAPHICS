#include "Raster.h"
#include <fstream>
#include <cmath>
#include <algorithm>
#include <iostream>
#include "Triangle2D.h"
using namespace std;
Raster::Raster() : width(0), height(0), pixels(nullptr) {}

Raster::Raster(int pWidth, int pHeight, const Color& pFillColor) 
    : width(pWidth), height(pHeight), pixels(new Color[pWidth * pHeight]) {
    clear(pFillColor);
}

Raster::~Raster() {
    delete[] pixels;
}

int Raster::getWidth() const { return width; }
int Raster::getHeight() const { return height; }

Color Raster::getColorPixel(int x, int y) const {
    return pixels[y * width + x];
}

void Raster::setColorPixel(int x, int y, const Color& pFillColor) {
    pixels[y * width + x] = pFillColor;
}

void Raster::clear(const Color& pFillColor) {
    for (int i = 0; i < width * height; ++i) {
        pixels[i] = pFillColor;
    }
}

void Raster::writeToPPM() const {
    ofstream outFile("FRAME_BUFFER.ppm");
    if (!outFile) {
        cerr << "Error opening file for writing: FRAME_BUFFER.ppm" << endl;
        return;
    }
    outFile << "P3\n" << width << " " << height << "\n255\n";
    for (int y = height - 1; y >= 0; --y) {
        for (int x = 0; x < width; ++x) {
            Color pixelColor = getColorPixel(x, y);
            outFile << static_cast<int>(pixelColor.red * 255) << " "
                    << static_cast<int>(pixelColor.green * 255) << " "
                    << static_cast<int>(pixelColor.blue * 255) << " ";
        }
        outFile << "\n";
    }
}

void Raster::swap(float& a, float& b) {
    float temp = a;
    a = b;
    b = temp;
}

void Raster::drawLine_DDA_Interpolated(float x1, float y1, float x2, float y2, Color color1, Color color2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    float steps = max(abs(dx), abs(dy));

    float xIncrement = dx / steps;
    float yIncrement = dy / steps;

    Vector2 colorIncrement(
        (color2.red - color1.red) / steps,
        (color2.green - color1.green) / steps
    );

    float x = x1;
    float y = y1;
    Vector2 currentColor(color1.red, color1.green);

    for (int i = 0; i <= steps; ++i) {
        int roundedX = round(x);
        int roundedY = round(y);
        
        if (roundedX >= 0 && roundedX < width && roundedY >= 0 && roundedY < height) {
            Color interpolatedColor(currentColor.x, currentColor.y, color1.blue);
            setColorPixel(roundedX, roundedY, interpolatedColor);
        }

        x += xIncrement;
        y += yIncrement;
        currentColor = currentColor + colorIncrement;
    }
}


void Raster::drawLine_DDA(float x1, float y1, float x2, float y2, const Color& fillColor) {
    float dx = x2 - x1;
    float dy = y2 - y1;

    if (abs(dx) > abs(dy)) {
        // Line is more horizontal than vertical
        if (x2 < x1) {
            swap(x1, x2);
            swap(y1, y2);
        }
        float m = dy / dx;
        float y = y1;
        for (float x = x1; x <= x2; x += 1.0f) {
            setColorPixel(round(x), round(y), fillColor);
            y += m;
        }
    } else {
        // Line is more vertical than horizontal
        if (y2 < y1) {
            swap(x1, x2);
            swap(y1, y2);
        }
        float m = dx / dy;
        float x = x1;
        for (float y = y1; y <= y2; y += 1.0f) {
            setColorPixel(round(x), round(y), fillColor);
            x += m;
        }
    }
}
 

void Raster::drawTriangle2D_DotProduct(const Triangle2D& triangle) {
    // Calculate bounding box
     int minX = max(0, static_cast<int>(min(min(triangle.v1.x, triangle.v2.x), triangle.v3.x)));
    int minY = max(0, static_cast<int>(min(min(triangle.v1.y, triangle.v2.y), triangle.v3.y)));
    int maxX = min(width - 1, static_cast<int>(max(max(triangle.v1.x, triangle.v2.x), triangle.v3.x)));
    int maxY = min(height - 1, static_cast<int>(max(max(triangle.v1.y, triangle.v2.y), triangle.v3.y)));

    // Calculate edge vectors
    Vector2 edge1 = triangle.v2 - triangle.v1;
    Vector2 edge2 = triangle.v3 - triangle.v2;
    Vector2 edge3 = triangle.v1 - triangle.v3;

    // Calculate perpendicular vectors
    Vector2 perp1 = edge1.perpendicular();
    Vector2 perp2 = edge2.perpendicular();
    Vector2 perp3 = edge3.perpendicular();

    // Iterate over the bounding box
    for (int y = minY; y <= maxY; ++y) {
        for (int x = minX; x <= maxX; ++x) {
            Vector2 p(x + 0.5f, y + 0.5f);  // Center of the pixel

            Vector2 v1 = p - triangle.v1;
            Vector2 v2 = p - triangle.v2;
            Vector2 v3 = p - triangle.v3;

            // Check if the point is inside the triangle
            if (v1.dot(perp1) <= 0 && v2.dot(perp2) <= 0 && v3.dot(perp3) <= 0) {
                setColorPixel(x, y, triangle.c1);  // You can change this to interpolate colors if desired
            }
        }
    }
}
void Raster::drawTriangle_Barycentric(const Triangle3D& T) {
    // Calculate bounding box
    int minX = max(0, static_cast<int>(min(min(T.v1.x, T.v2.x), T.v3.x)));
    int minY = max(0, static_cast<int>(min(min(T.v1.y, T.v2.y), T.v3.y)));
    int maxX = min(width - 1, static_cast<int>(max(max(T.v1.x, T.v2.x), T.v3.x)));
    int maxY = min(height - 1, static_cast<int>(max(max(T.v1.y, T.v2.y), T.v3.y)));

    // Iterate over the bounding box
    for (int y = minY; y <= maxY; ++y) {
        for (int x = minX; x <= maxX; ++x) {
            Vector2 P(x + 0.5f, y + 0.5f);  // Center of the pixel

            float lambda1, lambda2, lambda3;
            T.calculateBarycentricCoordinates(P, lambda1, lambda2, lambda3);

            // Check if the point is inside the triangle
            if (lambda1 >= 0 && lambda2 >= 0 && lambda3 >= 0) {
                // Interpolate color
                Color interpolatedColor(
                    lambda1 * T.c1.red + lambda2 * T.c2.red + lambda3 * T.c3.red,
                    lambda1 * T.c1.green + lambda2 * T.c2.green + lambda3 * T.c3.green,
                    lambda1 * T.c1.blue + lambda2 * T.c2.blue + lambda3 * T.c3.blue
                );

                setColorPixel(x, y, interpolatedColor);
            }
        }
    }
}

void Raster::drawModel(const Model& model) {
    for (size_t i = 0; i < model.numTriangles(); ++i) {
        drawTriangle_Barycentric(model[i]);
    }
}