#include "Triangle2D.h"
#include <iostream>

using namespace std;

Triangle2D::Triangle2D() : v1(), v2(), v3(), c1(), c2(), c3() {}

Triangle2D::Triangle2D(const Vector2 &v1, const Vector2 &v2, const Vector2 &v3,
                       const Color &c1, const Color &c2, const Color &c3)
    : v1(v1), v2(v2), v3(v3), c1(c1), c2(c2), c3(c3) {}

Triangle2D::Triangle2D(const Triangle3D &tri3D)
    : v1(tri3D.v1.x, tri3D.v1.y), v2(tri3D.v2.x, tri3D.v2.y), v3(tri3D.v3.x, tri3D.v3.y),
      c1(tri3D.c1), c2(tri3D.c2), c3(tri3D.c3) {}

void Triangle2D::calculateBarycentricCoordinates(const Vector2 &P, float &lambda1, float &lambda2, float &lambda3) const
{
    float detT = (v2.y - v3.y) * (v1.x - v3.x) + (v3.x - v2.x) * (v1.y - v3.y);

    lambda1 = ((v2.y - v3.y) * (P.x - v3.x) + (v3.x - v2.x) * (P.y - v3.y)) / detT;
    lambda2 = ((v3.y - v1.y) * (P.x - v3.x) + (v1.x - v3.x) * (P.y - v3.y)) / detT;
    lambda3 = 1.0f - lambda1 - lambda2;
}

Triangle2D::Triangle2D(const Triangle3D &tri3D)
    : v1(tri3D.v1.x, tri3D.v1.y), v2(tri3D.v2.x, tri3D.v2.y), v3(tri3D.v3.x, tri3D.v3.y),
      c1(tri3D.c1), c2(tri3D.c2), c3(tri3D.c3) {}
