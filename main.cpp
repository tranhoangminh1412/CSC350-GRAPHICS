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
    Raster myRaster(100,100,White);
    Model teapot = Model();
    teapot.readFromOBJFile("./teapot.obj", Red);

    Matrix4 m = Matrix4::translate3D(50,50,0) * Matrix4::rotateZ3D(-45.0) * Matrix4::scale3D(0.5,0.5,0.5);
    teapot.transform(m);

    myRaster.drawModel(teapot);
    myRaster.writeToPPM();

    return 0;
}