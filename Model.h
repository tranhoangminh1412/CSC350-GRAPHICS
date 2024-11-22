#ifndef MODEL_H
#define MODEL_H

#include "Triangle3D.h"
#include "Color.h"
#include "Matrix.h"
#include <vector>
#include <string>

using namespace std;

class Model
{
public:
    vector<Triangle3D> triangles;

    Model();

    Triangle3D operator[](size_t i) const;

    Triangle3D &operator[](int i);

    size_t numTriangles() const;

    void transform(const Matrix4 &matrix);

    void homogenize();
    void performBackfaceCulling(const Vector4& eye, const Vector4& spot);

    void readFromOBJFile(const string &filepath, const Color &color);
};

#endif // MODEL_H
