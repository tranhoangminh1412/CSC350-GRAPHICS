#include <iostream>
#include "Color.h"
#include "Raster.h"
#include "Triangle2D.h"
#include "Vector2.h"
#include "Vector4.h"
#include "Model.h"

using namespace std;

// int main()
// {
//     //     // Create a 20x20 raster with a white background
//     //    Raster raster(20, 20, White);

//     //     // Test various line types
//     //     raster.drawLine_DDA(0, 0, 19, 19, Red);  // Diagonal line
//     //     raster.drawLine_DDA(19, 0, 0, 19, Blue);  // Inverse diagonal line
//     //     raster.drawLine_DDA(10, 0, 10, 19, Blue);  // Vertical line
//     //     raster.drawLine_DDA(0, 10, 19, 10, Black);  // Horizontal line

//     //     // Test lines with reversed endpoints
//     //     raster.drawLine_DDA(15, 15, 5, 5, Color(1.0f, 0.5f, 0.0f));  // Should overlap with red line

//     //     // Test lines with out-of-bounds endpoints
//     //     raster.drawLine_DDA(-5, -5, 25, 25, Color(0.5f, 0.5f, 0.5f));  // Should draw partial line

//     //     // Write the result to a PPM file

//     //  Raster raster(100, 100, White);  // 100x100 black raster

//     //     Triangle2D myTriangle(
//     //         Vector2(2, 15),   // v1
//     //         Vector2(72, 10),   // v2
//     //         Vector2(45, 80),   // v3
//     //         Color(1, 0, 0),    // c1 (red)
//     //         Color(0, 1, 0),    // c2 (green)
//     //         Color(0, 0, 1)     // c3 (blue)
//     //     );

//     //     raster.drawTriangle_Barycentric(myTriangle);
//     //     raster.writeToPPM();  // Now this matches the method signature

//     //     std::cout << "PPM file 'FRAME_BUFFER.ppm' has been created." << std::endl;

//     //     return 0;

//     Model model;
//     Color defaultColor(1.0f, 0.0f, 0.0f); // Red color for all triangles

//     try
//     {
//         model.readFromOBJFile("./teapot.obj", defaultColor);
//     }
//     catch (const std::runtime_error &e)
//     {
//         std::cerr << "Error: " << e.what() << std::endl;
//         return -1;
//     }

//     // Process and render the model as needed
//     return 0;
// }

int main() {
    Model model;
    Color defaultColor(1.0f, 0.0f, 0.0f); // Red color for all triangles

    try {
        model.readFromOBJFile("./teapot.obj", defaultColor);
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }

    // If you want to render the model:
    Raster raster(100, 100, defaultColor); // Assuming White is defined
    raster.clear(defaultColor); // Clear with default color or background color

    // Draw the model if `drawModel` is implemented in Raster
    raster.drawModel(model);
    raster.writeToPPM();

    std::cout << "PPM file 'FRAME_BUFFER.ppm' has been created." << std::endl;

    return 0;
}