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

    // Default constructor
    Model();

    // Accessor for const objects (read-only)
    Triangle3D operator[](size_t i) const;

    // Accessor for non-const objects (read-write)
    Triangle3D &operator[](int i);

    // Returns the number of triangles in the model
    size_t numTriangles() const;

    // Applies a transformation matrix to each triangle in the model
    void transform(const Matrix4 &matrix);

    // Reads model data from an OBJ file and applies the given color to each triangle
    void readFromOBJFile(const std::string &filepath, const Color &color);
};

#endif // MODEL_H
