#ifndef VECTOR4_H
#define VECTOR4_H

using namespace std;

struct Vector4 {
    float x, y, z, w;

    Vector4();

    Vector4(float pX, float pY, float pZ, float pW);

    Vector4 operator*(float scalar) const;

    Vector4 operator+(const Vector4& other) const;

    Vector4 operator-(const Vector4& other) const;

    float magnitude() const;

    void normalize();

    float dot(const Vector4& other) const;

    Vector4 cross(const Vector4& other) const; // Cross product

};


#endif