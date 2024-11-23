#include "Model.h"
#include "Vector2.h"
#include "Vector4.h"
#include "Triangle3D.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>

Model::Model() {}

Triangle3D Model::operator[](size_t i) const {
    return triangles[i];
}

Triangle3D& Model::operator[](int i) {
    return triangles[i];
}

size_t Model::numTriangles() const {
    return triangles.size();
}

void Model::transform(const Matrix4& modelMatrix) {
    for (auto& triangle : triangles) {
        if (!triangle.shouldDraw) continue;

        // Transform each vertex
        triangle.v1 = modelMatrix * triangle.v1;
        triangle.v2 = modelMatrix * triangle.v2;
        triangle.v3 = modelMatrix * triangle.v3;
    }
}

void Model::homogenize() {
    for (auto& triangle : triangles) {
        // Normalize each vertex
        if (triangle.v1.w != 0.0f) {
            triangle.v1.x /= triangle.v1.w;
            triangle.v1.y /= triangle.v1.w;
            triangle.v1.z /= triangle.v1.w;
            triangle.v1.w = 1.0f;
        }
        if (triangle.v2.w != 0.0f) {
            triangle.v2.x /= triangle.v2.w;
            triangle.v2.y /= triangle.v2.w;
            triangle.v2.z /= triangle.v2.w;
            triangle.v2.w = 1.0f;
        }
        if (triangle.v3.w != 0.0f) {
            triangle.v3.x /= triangle.v3.w;
            triangle.v3.y /= triangle.v3.w;
            triangle.v3.z /= triangle.v3.w;
            triangle.v3.w = 1.0f;
        }
    }
}

void Model::performBackfaceCulling(const Vector4& eye, const Vector4& spot) {
    // Calculate the camera's look vector
    Vector4 look = Vector4(spot.x - eye.x, spot.y - eye.y, spot.z - eye.z, 0.0f);

    for (auto& triangle : triangles) {
        // Calculate the surface normal
        Vector4 edge1 = triangle.v2 - triangle.v1;
        Vector4 edge2 = triangle.v3 - triangle.v1;
        Vector4 normal = edge1.cross(edge2);

        // Check if the normal faces the same direction as the look vector
        float dotProduct = normal.dot(look);
        triangle.shouldDraw = (dotProduct > 0.0f); // Set shouldDraw to false for back-facing triangles
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
