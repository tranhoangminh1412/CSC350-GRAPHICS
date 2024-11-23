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

int main()
{
    // Initialize the Raster (framebuffer)
    Raster myRaster(WIDTH, HEIGHT, White);

    // Load Models
    Model teapot, bunny;
    teapot.readFromOBJFile("./teapot.obj", Red);
    bunny.readFromOBJFile("./bunny.obj", Blue);

    // Apply Model Transformations
    Matrix4 modelMatrixTeapot = Matrix4::translate3D(50, 50, -60) *
                                Matrix4::rotateZ3D(45.0) *
                                Matrix4::scale3D(0.5, 0.5, 0.5);

    Matrix4 modelMatrixBunny = Matrix4::translate3D(70, 30, -60) *
                               Matrix4::rotateZ3D(-20.0) *
                               Matrix4::scale3D(500, 500, 500);

    // Apply View Transformation (Camera)
    Matrix4 viewMatrix = Matrix4::lookAt(Vector4(50, 50, 30, 1),  // Camera position
                                         Vector4(50, 50, -40, 1), // Look at target
                                         Vector4(0, 1, 0, 0));    // Up direction

    // Apply Projection Transformation (Perspective)
    Matrix4 perspectiveMatrix = Matrix4::perspective(70.0,
                                                     myRaster.getWidth() / static_cast<float>(myRaster.getHeight()),
                                                     0.01,
                                                     1000.0);

    // Apply Viewport Transformation
    Matrix4 viewportMatrix = Matrix4::viewport(0, 0, myRaster.getWidth(), myRaster.getHeight());

    // Combine Transformations for each model
    teapot.transform(perspectiveMatrix * viewMatrix * modelMatrixTeapot);
    bunny.transform(perspectiveMatrix * viewMatrix * modelMatrixBunny);

    // Perform Homogenization
    teapot.homogenize();
    bunny.homogenize();

    // Apply Viewport Transformation to bring models into screen coordinates
    teapot.transform(viewportMatrix);
    bunny.transform(viewportMatrix);

    // Draw Models
    myRaster.drawModel(teapot);
    myRaster.drawModel(bunny);

    // Write Output to PPM
    myRaster.writeToPPM();

    cout << "Rendering completed. Check the generated FRAME_BUFFER.ppm file." << endl;

    return 0;
}
 

//  #include "Color.h"
// #include "Model.h"
// #include "Raster.h"
// #include "Triangle3D.h"
// #include "Vector4.h"
// #include "Matrix.h"

// #include <iostream>
// using namespace std;

// #define WIDTH 100
// #define HEIGHT 100

// int main() {
//     // Initialize the raster (framebuffer)
//     Raster myRaster(WIDTH, HEIGHT, White);

//     // Load the teapot model
//     Model teapot;
//     teapot.readFromOBJFile("./teapot.obj", Red);

//     // Define the model transformation matrix
//     Matrix4 modelMatrixTeapot = Matrix4::translate3D(50, 50, -30) * 
//                                 Matrix4::rotateZ3D(45.0) * 
//                                 Matrix4::scale3D(0.5, 0.5, 0.5);

//     // Define the camera
//     Vector4 eye(50, 50, 30, 1); // Camera position
//     Vector4 spot(50, 50, -30, 1); // Target position
//     teapot.performBackfaceCulling(eye, spot); // Perform backface culling

//     // Define the view matrix
//     Matrix4 viewMatrix = Matrix4::lookAt(eye, spot, Vector4(0, 1, 0, 0));

//     // Define the perspective projection matrix
//     Matrix4 perspectiveMatrix = Matrix4::perspective(70.0, 
//                                                      myRaster.getWidth() / static_cast<float>(myRaster.getHeight()), 
//                                                      0.01, 
//                                                      88.5);

//     // Define the viewport matrix
//     Matrix4 viewportMatrix = Matrix4::viewport(0, 0, myRaster.getWidth(), myRaster.getHeight());

//     // Apply transformations
//     teapot.transform(perspectiveMatrix * viewMatrix * modelMatrixTeapot);

//     // Homogenize and transform to viewport coordinates
//     teapot.homogenize();
//     teapot.transform(viewportMatrix);

//     // Render the model
//     myRaster.drawModel(teapot);

//     // Write the output to a PPM file
//     myRaster.writeToPPM();

//     cout << "Rendering completed! Check the generated FRAME_BUFFER.ppm file." << endl;

//     return 0;
// }
