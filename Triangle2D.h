#ifndef TRIANGLE2D_H
#define TRIANGLE2D_H

#include "Vector2.h"
#include "Vector4.h"
#include "Color.h"
#include "Triangle3D.h"

struct Triangle2D {
    Vector2 v1, v2, v3;
    Color c1, c2, c3;

    Triangle2D();
    Triangle2D(const Vector2& v1, const Vector2& v2, const Vector2& v3,
               const Color& c1, const Color& c2, const Color& c3);
    Triangle2D(const Triangle3D& tri3D);

    void calculateBarycentricCoordinates(const Vector2& P, float& lambda1, float& lambda2, float& lambda3) const;
};

#endif // TRIANGLE2D_H
