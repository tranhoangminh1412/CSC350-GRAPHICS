#include <iostream>
#include "Vector2.h"
#include "Vector4.h"
#include "Matrix.h"
#include <cmath>
#define M_PI 3.14159265358979323846
#define _USE_MATH_DEFINES

using namespace std;

Matrix4::Matrix4() : ix(1), jx(0), kx(0), ox(0),
                     iy(0), jy(1), ky(0), oy(0),
                     iz(0), jz(0), kz(1), oz(0),
                     iw(0), jw(0), kw(0), ow(1) {}

Matrix4::Matrix4(float ix, float jx, float kx, float ox,
                 float iy, float jy, float ky, float oy,
                 float iz, float jz, float kz, float oz,
                 float iw, float jw, float kw, float ow)
    : ix(ix), jx(jx), kx(kx), ox(ox),
      iy(iy), jy(jy), ky(ky), oy(oy),
      iz(iz), jz(jz), kz(kz), oz(oz),
      iw(iw), jw(jw), kw(kw), ow(ow) {}

Vector4 Matrix4::operator*(const Vector4 &vec) const
{
    return Vector4(
        ix * vec.x + jx * vec.y + kx * vec.z + ox * vec.w,
        iy * vec.x + jy * vec.y + ky * vec.z + oy * vec.w,
        iz * vec.x + jz * vec.y + kz * vec.z + oz * vec.w,
        iw * vec.x + jw * vec.y + kw * vec.z + ow * vec.w);
}

Matrix4 Matrix4::operator*(const Matrix4 &other) const
{
    return Matrix4(
        ix * other.ix + jx * other.iy + kx * other.iz + ox * other.iw,
        ix * other.jx + jx * other.jy + kx * other.jz + ox * other.jw,
        ix * other.kx + jx * other.ky + kx * other.kz + ox * other.kw,
        ix * other.ox + jx * other.oy + kx * other.oz + ox * other.ow,

        iy * other.ix + jy * other.iy + ky * other.iz + oy * other.iw,
        iy * other.jx + jy * other.jy + ky * other.jz + oy * other.jw,
        iy * other.kx + jy * other.ky + ky * other.kz + oy * other.kw,
        iy * other.ox + jy * other.oy + ky * other.oz + oy * other.ow,

        iz * other.ix + jz * other.iy + kz * other.iz + oz * other.iw,
        iz * other.jx + jz * other.jy + kz * other.jz + oz * other.jw,
        iz * other.kx + jz * other.ky + kz * other.kz + oz * other.kw,
        iz * other.ox + jz * other.oy + kz * other.oz + oz * other.ow,

        iw * other.ix + jw * other.iy + kw * other.iz + ow * other.iw,
        iw * other.jx + jw * other.jy + kw * other.jz + ow * other.jw,
        iw * other.kx + jw * other.ky + kw * other.kz + ow * other.kw,
        iw * other.ox + jw * other.oy + kw * other.oz + ow * other.ow);
}
Matrix4 Matrix4::translate3D(float tX, float tY, float tZ)
{
    return Matrix4(1, 0, 0, tX,
                   0, 1, 0, tY,
                   0, 0, 1, tZ,
                   0, 0, 0, 1);
}

Matrix4 Matrix4::scale3D(float sX, float sY, float sZ)
{
    return Matrix4(sX, 0, 0, 0,
                   0, sY, 0, 0,
                   0, 0, sZ, 0,
                   0, 0, 0, 1);
}

Matrix4 Matrix4::rotateX3D(float degrees)
{
    float radians = degrees * M_PI / 180.0f;
    float cosAngle = cos(radians);
    float sinAngle = sin(radians);
    return Matrix4(
        1, 0, 0, 0,
        0, cosAngle, sinAngle, 0,
        0, -sinAngle, cosAngle, 0,
        0, 0, 0, 1);
}

Matrix4 Matrix4::rotateY3D(float degrees)
{
    float radians = degrees * M_PI / 180.0f;
    float cosAngle = cos(radians);
    float sinAngle = sin(radians);
    return Matrix4(
        cosAngle, 0, -sinAngle, 0,  // Y-axis rotation
        0, 1, 0, 0,
        sinAngle, 0, cosAngle, 0,  // Flip sign on sine for proper rotation
        0, 0, 0, 1);
}

Matrix4 Matrix4::rotateZ3D(float degrees)
{
    float radians = degrees * M_PI / 180.0f;
    float cosAngle = cos(radians);
    float sinAngle = sin(radians);
    return Matrix4(
        cosAngle, sinAngle, 0, 0,  // Z-axis rotation
        -sinAngle, cosAngle, 0, 0, // Flip sine to preserve right-hand system
        0, 0, 1, 0,
        0, 0, 0, 1);
}


Matrix4 Matrix4::rotate3D(float xDegrees, float yDegrees, float zDegrees)
{
    Matrix4 rotX = rotateX3D(xDegrees);
    Matrix4 rotY = rotateY3D(yDegrees);
    Matrix4 rotZ = rotateZ3D(zDegrees);

    // Combine the rotations in the correct order: Z * Y * X
    return rotZ * rotY * rotX;
}

Matrix4 Matrix4::identity()
{
    return Matrix4();
}

Matrix4 lookAt(const Vector4 &eye, const Vector4 &spot, const Vector4 &up)
{
    Vector4 forward = Vector4(spot.x - eye.x, spot.y - eye.y, spot.z - eye.z, 0.0f);
    forward.normalize();

    Vector4 right = forward.cross(up);
    right.normalize();

    Vector4 cameraUp = right.cross(forward);
    cameraUp.normalize();

    return Matrix4(
        right.x, right.y, right.z, -right.dot(eye),
        cameraUp.x, cameraUp.y, cameraUp.z, -cameraUp.dot(eye),
        -forward.x, -forward.y, -forward.z, forward.dot(eye),
        0, 0, 0, 1);
}

Matrix4 perspective(float fovY, float aspect, float nearZ, float farZ)
{
    float radians = fovY * M_PI / 180.0;
    float tanHalfFovY = tan(radians / 2.0);

    return Matrix4(
        1.0f / (aspect * tanHalfFovY), 0, 0, 0,
        0, 1.0f / tanHalfFovY, 0, 0,
        0, 0, -(farZ + nearZ) / (farZ - nearZ), -(2.0f * farZ * nearZ) / (farZ - nearZ),
        0, 0, -1, 0);
}

Matrix4 viewport(float x, float y, float width, float height)
{
    return Matrix4(
        width / 2.0f, 0, 0, x + width / 2.0f,
        0, height / 2.0f, 0, y + height / 2.0f,
        0, 0, 0.5f, 0.5f,
        0, 0, 0, 1);
}

Matrix4 orthographic(float minX, float maxX, float minY, float maxY, float minZ, float maxZ)
{
    return Matrix4(
        2.0f / (maxX - minX), 0, 0, -(maxX + minX) / (maxX - minX),
        0, 2.0f / (maxY - minY), 0, -(maxY + minY) / (maxY - minY),
        0, 0, -2.0f / (maxZ - minZ), -(maxZ + minZ) / (maxZ - minZ),
        0, 0, 0, 1);
}