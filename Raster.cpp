#include "Raster.h"
#include <fstream>
#include <cmath>
#include <algorithm>
#include <iostream>
#include "Triangle2D.h"
#include "Triangle3D.h"

using namespace std;

Raster::Raster() : width(0), height(0), pixels(nullptr), depthPixels(nullptr) {}

Raster::Raster(int pWidth, int pHeight, const Color& pFillColor) 
    : width(pWidth), height(pHeight), 
      pixels(new Color[pWidth * pHeight]), 
      depthPixels(new float[pWidth * pHeight]) {
    clear(pFillColor, numeric_limits<float>::max());
}

Raster::~Raster() {
    delete[] pixels;
    delete[] depthPixels;
}

int Raster::getWidth() const { return width; }
int Raster::getHeight() const { return height; }

Color Raster::getColorPixel(int x, int y) const {
    return pixels[y * width + x];
}

void Raster::setColorPixel(int x, int y, const Color& pFillColor) {
    pixels[y * width + x] = pFillColor;
}

float Raster::getDepthPixel(int x, int y) const {
    return depthPixels[y * width + x];
}

void Raster::setDepthPixel(int x, int y, float depth) {
    depthPixels[y * width + x] = depth;
}

void Raster::clear(const Color& pFillColor, float depthValue) {
    for (int i = 0; i < width * height; ++i) {
        pixels[i] = pFillColor;
        depthPixels[i] = depthValue;
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

void Raster::drawTriangle_Barycentric(const Triangle3D& triangle) {

    // Calculate bounding box
    int minX = max(0, static_cast<int>(min({triangle.v1.x, triangle.v2.x, triangle.v3.x})));
    int minY = max(0, static_cast<int>(min({triangle.v1.y, triangle.v2.y, triangle.v3.y})));
    int maxX = min(width - 1, static_cast<int>(max({triangle.v1.x, triangle.v2.x, triangle.v3.x})));
    int maxY = min(height - 1, static_cast<int>(max({triangle.v1.y, triangle.v2.y, triangle.v3.y})));

    // Iterate over the bounding box
    for (int y = minY; y <= maxY; ++y) {
        for (int x = minX; x <= maxX; ++x) {
            Vector2 P(x + 0.5f, y + 0.5f);  // Center of the pixel

            float lambda1, lambda2, lambda3;
            triangle.calculateBarycentricCoordinates(P, lambda1, lambda2, lambda3);

            // Check if the point is inside the triangle
            if (lambda1 >= 0 && lambda2 >= 0 && lambda3 >= 0) {
                // Interpolate depth
                float interpolatedDepth =
                    lambda1 * triangle.v1.z +
                    lambda2 * triangle.v2.z +
                    lambda3 * triangle.v3.z;

                if (interpolatedDepth < getDepthPixel(x, y)) {
                    // Update depth buffer and color buffer
                    setDepthPixel(x, y, interpolatedDepth);

                    // Interpolate color
                    Color interpolatedColor(
                        lambda1 * triangle.c1.red + lambda2 * triangle.c2.red + lambda3 * triangle.c3.red,
                        lambda1 * triangle.c1.green + lambda2 * triangle.c2.green + lambda3 * triangle.c3.green,
                        lambda1 * triangle.c1.blue + lambda2 * triangle.c2.blue + lambda3 * triangle.c3.blue
                    );
                    setColorPixel(x, y, interpolatedColor);
                }
            }
        }
    }
}

void Raster::drawModel(const Model& model) {
    for (const auto& triangle : model.triangles) {
        if (triangle.shouldDraw) {
            drawTriangle_Barycentric(triangle);
        }
    }
}
