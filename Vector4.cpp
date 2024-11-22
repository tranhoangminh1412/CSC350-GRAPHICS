#include <cmath>
#include "vector4.h"

Vector4::Vector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}

Vector4::Vector4(float pX, float pY, float pZ, float pW) : x(pX), y(pY), z(pZ), w(pW) {}

Vector4 Vector4::operator*(float scalar) const {
    return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
}

Vector4 Vector4::operator+(const Vector4& other) const {
    return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
}

Vector4 Vector4::operator-(const Vector4& other) const {
    return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
}

float Vector4::magnitude() const {
    return sqrt(x * x + y * y + z * z);
}

void Vector4::normalize() {
    float mag = magnitude();
    if (mag != 0) {
        x /= mag;
        y /= mag;
        z /= mag;
    }
}

float Vector4::dot(const Vector4& other) const {
    return x * other.x + y * other.y + z * other.z + w * other.w;
}

Vector4 Vector4::cross(const Vector4& other) const {
    return Vector4(
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x,
        0.0f // Resulting vector is not a point, w = 0
    );
}