#ifndef MATRIX_H
#define MATRIX_H

#include "Vector2.h"
#include "Vector4.h"
#include <cmath>

using namespace std;

struct Matrix4
{
    float ix, jx, kx, ox;
    float iy, jy, ky, oy;
    float iz, jz, kz, oz;
    float iw, jw, kw, ow;

    // Default constructor (identity matrix)
    Matrix4();

    // Parameterized constructor
    Matrix4(float ix, float jx, float kx, float ox,
            float iy, float jy, float ky, float oy,
            float iz, float jz, float kz, float oz,
            float iw, float jw, float kw, float ow);
        

    // Matrix-Vector multiplication
    Vector4 operator*(const Vector4 &vec) const;

    // Matrix-Matrix multiplication
    Matrix4 operator*(const Matrix4 &other) const;

    Matrix4 translate3D(float tX, float tY, float tZ);

    Matrix4 scale3D(float sX, float sY, float sZ);

    Matrix4 rotateX3D(float degrees);


    // Rotate around the Y-axis by an angle (in degrees)
    Matrix4 rotateY3D(float degrees);

    // Rotate around the Z-axis by an angle (in degrees)
    Matrix4 rotateZ3D(float degrees);

    // Composite rotation around X, Y, and Z
    Matrix4 rotate3D(float xDegrees, float yDegrees, float zDegrees);
};

#endif