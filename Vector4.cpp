#include <cmath>
#include "vector4.h"

// Default constructor: initializes all components to zero
Vector4::Vector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}

// Constructor with parameters
Vector4::Vector4(float pX, float pY, float pZ, float pW) : x(pX), y(pY), z(pZ), w(pW) {}

// Scaling operator (scales each component by a scalar)
Vector4 Vector4::operator*(float scalar) const {
    return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
}

// Addition operator (adds corresponding components of two vectors)
Vector4 Vector4::operator+(const Vector4& other) const {
    return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
}

// Subtraction operator (subtracts corresponding components of two vectors)
Vector4 Vector4::operator-(const Vector4& other) const {
    return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
}

// Calculate the magnitude of the vector (ignoring the w component)
float Vector4::magnitude() const {
    return std::sqrt(x * x + y * y + z * z);
}

// Normalize the vector (ignoring the w component)
void Vector4::normalize() {
    float mag = magnitude();
    if (mag != 0) {
        x /= mag;
        y /= mag;
        z /= mag;
    }
}

// Dot product calculation (including the w component)
float Vector4::dot(const Vector4& other) const {
    return x * other.x + y * other.y + z * other.z + w * other.w;
}
