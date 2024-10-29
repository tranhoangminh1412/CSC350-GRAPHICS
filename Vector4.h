#ifndef VECTOR4_H
#define VECTOR4_H

using namespace std;

// In Vector.h
struct Vector4 {
    float x, y, z, w;

    // Default constructor
    Vector4();

    // Constructor with parameters
    Vector4(float pX, float pY, float pZ, float pW);

    // Operator overloads for scaling, addition, and subtraction
    Vector4 operator*(float scalar) const;

    Vector4 operator+(const Vector4& other) const;

    Vector4 operator-(const Vector4& other) const;

    // Calculate the magnitude (ignore w)
    float magnitude() const;

    // Normalize the vector (ignore w)
    void normalize();

    // Dot product calculation (include w)
    float dot(const Vector4& other) const;
};


#endif