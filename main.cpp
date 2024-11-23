#include "Color.h"
#include "Matrix.h"
#include "Model.h"
#include "Raster.h"
#include "Triangle2D.h"
#include "Triangle3D.h"
#include "Vector2.h"
#include "Vector4.h"

#include <iostream>
using namespace std;

#define WIDTH 100
#define HEIGHT 100


//UNCOMMENT FOR TESTING DEPTH BUFFER
// int main()
// {
//     // Initialize the Raster (framebuffer)
//     Raster myRaster(WIDTH, HEIGHT, White);

//     myRaster.clear(White, numeric_limits<float>::max());

//     // Load Models
//     Model teapot, bunny;
//     teapot.readFromOBJFile("./teapot.obj", Red);
//     bunny.readFromOBJFile("./bunny.obj", Blue);

//     // Apply Model Transformations
//     Matrix4 modelMatrixTeapot = Matrix4::translate3D(50, 50, -60) *
//                                 Matrix4::rotateZ3D(45.0) *
//                                 Matrix4::scale3D(0.5, 0.5, 0.5);

//     Matrix4 modelMatrixBunny = Matrix4::translate3D(70, 30, -60) *
//                                Matrix4::rotateZ3D(-20.0) *
//                                Matrix4::scale3D(500, 500, 500);

//     // Apply View Transformation (Camera)
//     Matrix4 viewMatrix = lookAt(Vector4(50, 50, 30, 1),  // Camera position
//                                          Vector4(50, 50, -40, 1), // Look at target
//                                          Vector4(0, 1, 0, 0));    // Up direction

//     // Apply Projection Transformation (Perspective)
//     Matrix4 perspectiveMatrix = perspective(70.0,
//                                                      myRaster.getWidth() / static_cast<float>(myRaster.getHeight()),
//                                                      0.01,
//                                                      1000.0);

//     // Apply Viewport Transformation
//     Matrix4 viewportMatrix = viewport(0, 0, myRaster.getWidth(), myRaster.getHeight());

//     // Combine Transformations for each model
//     teapot.transform(perspectiveMatrix * viewMatrix * modelMatrixTeapot);
//     bunny.transform(perspectiveMatrix * viewMatrix * modelMatrixBunny);

//     // Perform Homogenization
//     teapot.homogenize();
//     bunny.homogenize();

//     // Apply Viewport Transformation to bring models into screen coordinates
//     teapot.transform(viewportMatrix);
//     bunny.transform(viewportMatrix);

//     // Draw Models
//     myRaster.drawModel(teapot);
//     myRaster.drawModel(bunny);

//     // Write Output to PPM
//     myRaster.writeToPPM();

//     cout << "Rendering completed. Check the generated FRAME_BUFFER.ppm file." << endl;

//     return 0;
// }

// ------------------------------------------------------------------------------------------------
//UNCOMMENT FOR TESTING BACKFACE CULLING
int main() {
    // Initialize the raster (framebuffer)
    Raster myRaster(WIDTH, HEIGHT, White);

    // Load the teapot model
    Model teapot;
    teapot.readFromOBJFile("./teapot.obj", Red);

     Matrix4 modelMatrixTeapot = Matrix4::translate3D(50, 50, -30) * 
                                Matrix4::rotateZ3D(45.0) * 
                                Matrix4::scale3D(0.5, 0.5, 0.5);

    // Define the Camera (View Transformation)
    Vector4 eye(50, 50, 30, 1); // Camera position
    Vector4 spot(50, 50, -30, 1); // Target position
    Vector4 up(0, 1, 0, 0); // Up direction

    // Perform backface culling (if applicable in your pipeline)
    teapot.performBackfaceCulling(eye, spot);

    // Calculate the View Matrix
    Matrix4 viewMatrix = lookAt(eye, spot, up);

    // Define the Perspective Projection Matrix
    Matrix4 perspectiveMatrix = perspective(
        70.0, 
        myRaster.getWidth() / static_cast<float>(myRaster.getHeight()), 
        0.01, 
        88.5
    );

    // Define the Viewport Transformation Matrix
    Matrix4 viewportMatrix = viewport(0, 0, myRaster.getWidth(), myRaster.getHeight());

    // Combine all Transformations: Model -> View -> Projection
    teapot.transform(perspectiveMatrix * viewMatrix * modelMatrixTeapot);

    // Perform Homogenization (Divide by W for Perspective Projection)
    teapot.homogenize();

    // Transform to Screen Coordinates
    teapot.transform(viewportMatrix);

    // Draw the Teapot Model
    myRaster.drawModel(teapot);

    // Write Output to PPM File
    myRaster.writeToPPM();

    // Notify Completion
    cout << "Rendering completed. Check the generated FRAME_BUFFER.ppm file." << endl;

    return 0;
}

// ------------------------------------------------------------------------------------------------
//UNCOMMENT FOR TESTING FORESHORTENING
// void printMatrix(const Matrix4& matrix, const string& name) {
//     cout << "Matrix: " << name << endl;
//     cout << matrix.ix << " " << matrix.jx << " " << matrix.kx << " " << matrix.ox << endl;
//     cout << matrix.iy << " " << matrix.jy << " " << matrix.ky << " " << matrix.oy << endl;
//     cout << matrix.iz << " " << matrix.jz << " " << matrix.kz << " " << matrix.oz << endl;
//     cout << matrix.iw << " " << matrix.jw << " " << matrix.kw << " " << matrix.ow << endl;
//     cout << endl;
// }

// int main() {
//     // Initialize the Raster (framebuffer)
//     Raster myRaster(WIDTH, HEIGHT, White);

//     // Load the Teapot Model
//     Model teapot;
//     teapot.readFromOBJFile("./teapot.obj", Red);

//     // Model Transformation for Teapot
//     // (1) Scale it to half its size
//     // (2) Rotate it 45 degrees around the Z-axis
//     // (3) Translate the teapot into world coordinates
//     Matrix4 modelMatrixTeapot = Matrix4::translate3D(50, 50, -90) *
//                                 Matrix4::rotateZ3D(45.0) *
//                                 Matrix4::scale3D(0.5, 0.5, 0.5);

//     // View Transformation
//     // (eye) Place the camera at (x=50, y=50, z=30)
//     // (spot) Look at the spot (x=50, y=50, z=-40)
//     // (up) Define the "up" direction in world space as (x=0, y=1, z=0)
//     Matrix4 viewMatrix = lookAt(
//         Vector4(50, 50, 30, 1),  // Eye position
//         Vector4(50, 50, -40, 1), // Look-at target
//         Vector4(0, 1, 0, 0)      // Up direction
//     );

//     // Perspective Transformation
//     // Field of view: 90 degrees, aspect ratio: width/height,
//     // Near: 0.01, Far: 1000
//     Matrix4 perspectiveMatrix = perspective(
//         90.0,
//         myRaster.getWidth() / static_cast<float>(myRaster.getHeight()),
//         0.01,
//         1000.0
//     );

//     // Viewport Transformation
//     // Screen coordinates: start at (0,0), with width and height of the raster
//     Matrix4 viewportMatrix = viewport(
//         0, 0,
//         myRaster.getWidth(),
//         myRaster.getHeight()
//     );

//     // printMatrix(perspectiveMatrix, "perspective");
//     // printMatrix(viewMatrix, "viewMatrix");
//     // printMatrix(modelMatrixTeapot, "modelMatrixTeapot");

//     // Apply Transformations
//     // Apply Model -> View -> Perspective transformations (right-to-left matrix multiplication)
//     teapot.transform(perspectiveMatrix * viewMatrix * modelMatrixTeapot);

//     // Perform Homogenization
//     teapot.homogenize();

//     // Transform into Screen Coordinates
//     teapot.transform(viewportMatrix);

//     // Draw the Teapot
//     myRaster.drawModel(teapot);

//     // Save to PPM File
//     myRaster.writeToPPM();

//     cout << "Foreshortening test completed. Check the FRAME_BUFFER.ppm file." << endl;

//     return 0;
// }
