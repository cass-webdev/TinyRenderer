// TinyRenderer.cpp : Defines the entry point for the application.
//

#include "TinyRenderer.h"
#include "tgaimage.h"

using namespace std;

const TGAColor white = { 255, 255, 255, 255 };
const TGAColor blue  = { 255, 0  , 0  , 255 }; // this is BRGA instead of RGBA like I expected - why?
const TGAColor red   = { 0  , 255, 0  , 255 }; // this is BRGA instead of RGBA like I expected - why?

// Thanks to https://www.geeksforgeeks.org/passing-by-pointer-vs-passing-by-reference-in-cpp/ for some extra knowledge
// Second attempt - this is supposed to be erroneous as demonstrated, so try and figure out what's wrong.
/*
   Problems:
   1. What if x0 (start x) is greater than x1 (end x)?
     - Line will simply not render
     - This algorithm cannot handle coordinates that result in a straight vertical line.
     - Curiously, we can only render lines that fall within a ~178 deg angle facing right
   2. "int y" definition is affected by truncation

   Something to note:
   * The result of drawing a line segment should not depend on the order of points: the (a,b) line segment should be exactly the same as the (b,a) line segment.
*/
void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) {
    for (int x = x0; x <= x1; x++) {
        float t = (x - x0) / (float)(x1 - x0);
        int y = y0 * (1. - t) + y1 * t;
        image.set(x, y, color);
    }
}

int main(int argc, char** argv) {
    TGAImage image(100, 100, TGAImage::RGB);
    line(13, 20, 80, 40, image, white);
    line(20, 13, 40, 80, image, red);
    line(80, 40, 13, 20, image, blue);
    line(13, 80, 14, 13, image, white);
    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("output.tga");
    return 0;
}