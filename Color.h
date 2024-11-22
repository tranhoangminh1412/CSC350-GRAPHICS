
#include <cmath> // For abs

#include <iostream>

using namespace std;

#ifndef COLOR_H
#define COLOR_H

struct Color {
    float red;
    float green;
    float blue;

    Color();

    Color(float pRed, float pGreen, float pBlue);

    void clamp();

    Color operator+(const Color& other) const;
    Color operator-(const Color& other) const;
    Color operator*(float scalar) const;

};
#define Red Color(1.0f, 0.0f, 0.0f)
#define Green Color(0.0f, 1.0f, 0.0f)
#define Blue Color(0.0f, 0.0f, 1.0f)
#define Black Color(0.0f, 0.0f, 0.0f)
#define White Color(1.0f, 1.0f, 1.0f)
#define Cyan Color(0.0f, 1.0f, 1.0f)      // Green + Blue
#define Magenta Color(1.0f, 0.0f, 1.0f)  // Red + Blue
#define Yellow Color(1.0f, 1.0f, 0.0f)   // Red + Green

#endif // COLOR_H

