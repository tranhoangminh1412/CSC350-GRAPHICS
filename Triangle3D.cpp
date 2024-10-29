#include "Vector2.h"
#include "Vector4.h"
#include "Color.h"
#include "Matrix.h"
#include "Triangle3D.h"
#include <iostream>

using namespace std;

// Default constructor
Triangle3D :: Triangle3D() : v1(0, 0, 0, 1), v2(0, 0, 0, 1), v3(0, 0, 0, 1),
               c1(White), c2(White), c3(White) {}

// Parameterized constructor
Triangle3D :: Triangle3D(const Vector4 &pV1, const Vector4 &pV2, const Vector4 &pV3,
           const Color &pC1, const Color &pC2, const Color &pC3)
    : v1(pV1), v2(pV2), v3(pV3), c1(pC1), c2(pC2), c3(pC3) {}

// Transform method
void Triangle3D :: transform(const Matrix4 &matrix)
{
    v1 = matrix * v1;
    v2 = matrix * v2;
    v3 = matrix * v3;
}

void Triangle3D::calculateBarycentricCoordinates(const Vector2 &P, float &lambda1, float &lambda2, float &lambda3) const
{
    float detT = (v2.y - v3.y) * (v1.x - v3.x) + (v3.x - v2.x) * (v1.y - v3.y);

    lambda1 = ((v2.y - v3.y) * (P.x - v3.x) + (v3.x - v2.x) * (P.y - v3.y)) / detT;
    lambda2 = ((v3.y - v1.y) * (P.x - v3.x) + (v1.x - v3.x) * (P.y - v3.y)) / detT;
    lambda3 = 1.0f - lambda1 - lambda2; 
}