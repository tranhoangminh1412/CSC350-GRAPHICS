#include "Model.h"
#include "Vector2.h"
#include "Vector4.h"
#include "Triangle3D.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>

// Default constructor is handled by = default in Model.h

Model::Model() {};

// Accessor for const objects (read-only)
Triangle3D Model::operator[](size_t i) const {
    return triangles[i];
}

// Accessor for non-const objects (read-write)
Triangle3D& Model::operator[](int i) {
    return triangles[i];
}

// Returns the number of triangles in the model
size_t Model::numTriangles() const {
    return triangles.size();
}

// Applies a transformation matrix to each triangle in the model
void Model::transform(const Matrix4& matrix) {
    for (auto& triangle : triangles) {
        triangle.transform(matrix);
    }
}

// Reads model data from an OBJ file and applies the given color to each triangle
void Model::readFromOBJFile(const std::string& filepath, const Color& color) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open OBJ file: " + filepath);
    }

    std::vector<Vector4> vertices; // Store parsed vertices

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string prefix;
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

            // Create a triangle with the specified color and add it to the model
            triangles.emplace_back(vertex1, vertex2, vertex3, color, color, color);
        }
    }

    file.close();
}
