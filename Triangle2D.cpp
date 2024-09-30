#include "Triangle2D.h"

Triangle2D::Triangle2D() : v1(), v2(), v3(), c1(), c2(), c3() {}

Triangle2D::Triangle2D(const Vector2& v1, const Vector2& v2, const Vector2& v3,
                       const Color& c1, const Color& c2, const Color& c3)
    : v1(v1), v2(v2), v3(v3), c1(c1), c2(c2), c3(c3) {}

void Triangle2D::calculateBarycentricCoordinates(const Vector2& P, float& lambda1, float& lambda2, float& lambda3) const {
    float detT = (v2.y - v3.y) * (v1.x - v3.x) + (v3.x - v2.x) * (v1.y - v3.y);

    lambda1 = ((v2.y - v3.y) * (P.x - v3.x) + (v3.x - v2.x) * (P.y - v3.y)) / detT;
    lambda2 = ((v3.y - v1.y) * (P.x - v3.x) + (v1.x - v3.x) * (P.y - v3.y)) / detT;
    lambda3 = 1.0f - lambda1 - lambda2;
}