
#include <cmath> // For std::abs

#include <iostream>

using namespace std;

#ifndef COLOR_H
#define COLOR_H

struct Color {
    float red;
    float green;
    float blue;

    // Default constructor (sets color to black)
    Color();

    // Constructor that accepts red, green, blue values
    Color(float pRed, float pGreen, float pBlue);

    // Clamp method to ensure channel values are between 0.0 and 1.0
    void clamp();

    // Overloaded operators
    Color operator+(const Color& other) const;
    Color operator-(const Color& other) const;
    Color operator*(float scalar) const;

    // Preprocessor symbols for common colors
};
#define Red Color(1.0f, 0.0f, 0.0f)
#define Green Color(0.0f, 1.0f, 0.0f)
#define Blue Color(0.0f, 0.0f, 1.0f)
#define Black Color(0.0f, 0.0f, 0.0f)
#define White Color(1.0f, 1.0f, 1.0f)

#endif // COLOR_H

