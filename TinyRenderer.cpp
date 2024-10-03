// TinyRenderer.cpp : Defines the entry point for the application.
//

#include "TinyRenderer.h"
#include "tgaimage.h"

using namespace std;

const TGAColor white = { 255, 255, 255, 255 };
const TGAColor blue  = { 255, 0  , 0  , 255 }; // this is BRGA instead of RGBA like I expected - why?

// Thanks to https://www.geeksforgeeks.org/passing-by-pointer-vs-passing-by-reference-in-cpp/
// I'm guessing pass by ref is the generally safer option when accessing members of an instance in C++
// Probably should do pass by ref because we're not trying to modify internals of the TGAImage class directly? (does that make sense?)
void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) {
    for (float t = 0.; t < 1.; t += .01) {
        int x = x0 + (x1 - x0) * t;
        int y = y0 + (y1 - y0) * t;
        image.set(x, y, color);
    }
}

int main(int argc, char** argv) {
    TGAImage image(100, 100, TGAImage::RGB);
    line(41, 45, 59, 55, image, blue);
    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("output.tga");
    return 0;
}