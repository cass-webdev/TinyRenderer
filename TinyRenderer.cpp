// TinyRenderer.cpp : Defines the entry point for the application.
//

#include "TinyRenderer.h"
#include "tgaimage.h"

using namespace std;

const TGAColor white = { 255, 255, 255, 255 };
const TGAColor blue = { 255, 0, 0, 255 }; // this is BRGA instead of RGBA like I expected - why?

int main(int argc, char** argv) {
    TGAImage image(100, 100, TGAImage::RGB);
    image.set(51, 41, blue);
    image.set(52, 41, blue);
    image.set(53, 41, blue);
    image.set(54, 41, blue);
    image.set(55, 41, blue);
    image.set(53, 39, blue);
    image.set(53, 40, blue);
    image.set(53, 41, blue);
    image.set(53, 42, blue);
    image.set(53, 43, blue);
    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("output.tga");
    return 0;
}