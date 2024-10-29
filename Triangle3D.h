#ifndef TRIANGLE3D_H
#define TRIANGLE3D_H

#include "Vector4.h"
#include "Color.h"
#include "Matrix.h"

using namespace std;

struct Triangle3D {
    Vector4 v1, v2, v3;
    Color c1, c2, c3;

    Triangle3D();

    Triangle3D(const Vector4& pV1, const Vector4& pV2, const Vector4& pV3,
               const Color& pC1, const Color& pC2, const Color& pC3);

    void transform(const Matrix4& matrix);

    void calculateBarycentricCoordinates(const Vector2& P, float& lambda1, float& lambda2, float& lambda3) const;
};

#endif // TRIANGLE3D_H