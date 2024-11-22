#include <iostream>
#include "Color.h"
#include "Raster.h"
#include "Triangle2D.h"
#include "Triangle3D.h"
#include "Vector2.h"
#include "Vector4.h"
#include "Model.h"

using namespace std;

int main() {
    // Initialize the Raster (framebuffer)
    int rasterWidth = 200;
    int rasterHeight = 200;
    Raster myRaster(rasterWidth, rasterHeight, White);

    // Load a Model
    Model teapot = Model();
    teapot.readFromOBJFile("./.objFiles/teapot.obj", Red);

    // 1. Test Translation, Rotation, and Scaling
    cout << "Applying transformations..." << endl;
    Matrix4 transform = Matrix4::translate3D(100, 100, 0) * // Translate to center
                        Matrix4::rotateZ3D(-45.0) *        // Rotate -45 degrees
                        Matrix4::scale3D(0.5, 0.5, 0.5);   // Scale down by half
    teapot.transform(transform);

    // 2. Test Backface Culling
    cout << "Performing backface culling..." << endl;
    Vector4 eye(0, 0, 100, 1);  // Camera position
    Vector4 lookAt(0, 0, 0, 1); // Look at the origin
    teapot.performBackfaceCulling(eye, lookAt);

    // 3. Test Perspective Projection
    cout << "Applying perspective projection..." << endl;
    Matrix4 perspectiveProj = Matrix4::perspective(90.0, rasterWidth / (float)rasterHeight, 1.0f, 1000.0f);
    teapot.transform(perspectiveProj);

    // 4. Test Viewport Transformation
    cout << "Applying viewport transformation..." << endl;
    Matrix4 viewport = Matrix4::viewport(0, 0, rasterWidth, rasterHeight);
    teapot.transform(viewport);

    // 5. Draw the Model
    cout << "Drawing the model..." << endl;
    myRaster.drawModel(teapot);

    // Write the raster to a PPM file
    cout << "Writing to FRAME_BUFFER.ppm..." << endl;
    myRaster.writeToPPM();

    // Test Depth Buffering
    cout << "Testing depth buffering with overlapping triangles..." << endl;
    Triangle3D triangle1(Vector4(50, 50, 10, 1), Vector4(150, 50, 10, 1), Vector4(100, 150, 10, 1),
                         Red, Green, Blue); // Closer triangle
    Triangle3D triangle2(Vector4(60, 60, 50, 1), Vector4(140, 60, 50, 1), Vector4(100, 140, 50, 1),
                         Cyan, Magenta, Yellow); // Farther triangle

    Model testModel;
    testModel.triangles.push_back(triangle1);
    testModel.triangles.push_back(triangle2);

    myRaster.clear(White, numeric_limits<float>::max()); // Clear raster and depth buffer
    myRaster.drawModel(testModel); // Should render triangle1 over triangle2
    myRaster.writeToPPM();

    cout << "Done!" << endl;

    return 0;
}
