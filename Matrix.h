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

    Matrix4();

    Matrix4(float ix, float jx, float kx, float ox,
            float iy, float jy, float ky, float oy,
            float iz, float jz, float kz, float oz,
            float iw, float jw, float kw, float ow);
        

    Vector4 operator*(const Vector4 &vec) const;

    Matrix4 operator*(const Matrix4 &other) const;

    static Matrix4 translate3D(float tX, float tY, float tZ);

    static Matrix4 scale3D(float sX, float sY, float sZ);

    static Matrix4 rotateX3D(float degrees);


    static Matrix4 rotateY3D(float degrees);

    static Matrix4 rotateZ3D(float degrees);

    static Matrix4 rotate3D(float xDegrees, float yDegrees, float zDegrees);
};

#endif