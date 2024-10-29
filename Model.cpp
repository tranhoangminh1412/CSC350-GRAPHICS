#include "Model.h"
#include "Vector2.h"
#include "Vector4.h"
#include "Triangle3D.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>


Model::Model() {};

Triangle3D Model::operator[](size_t i) const {
    return triangles[i];
}

Triangle3D& Model::operator[](int i) {
    return triangles[i];
}

size_t Model::numTriangles() const {
    return triangles.size();
}

void Model::transform(const Matrix4& matrix) {
    for (auto& triangle : triangles) {
        triangle.transform(matrix);
    }
}

void Model::readFromOBJFile(const string& filepath, const Color& color) {
    ifstream file(filepath);
    if (!file.is_open()) {
        throw runtime_error("Could not open OBJ file: " + filepath);
    }

    vector<Vector4> vertices; 

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string prefix;
        iss >> prefix;

        // Process vertex lines
        if (prefix == "v") {
            float x, y, z;
            iss >> x >> y >> z;
            vertices.emplace_back(x, y, z, 1.0f); // Add vertex with w=1.0 for homogeneous coordinates
        }
        // Process face lines
        else if (prefix == "f") {
            int v1, v2, v3;
            iss >> v1 >> v2 >> v3;

            // Convert OBJ's 1-based indexing to 0-based indexing
            Vector4 vertex1 = vertices[v1 - 1];
            Vector4 vertex2 = vertices[v2 - 1];
            Vector4 vertex3 = vertices[v3 - 1];

            triangles.emplace_back(vertex1, vertex2, vertex3, color, color, color);
        }
    }

    file.close();
}
