/*
 * Name: MP1 - Image Manipulation 1
 *
 * Purpose: Rotate a PNG image 180 degrees.
 *
 * Input: PNG file named "in.png" in working directory
 *
 * Output: PNG file named "out.png" in working directory
 */

#include "png.h"

int main() {
    PNG imgOrig = PNG("in.png");
    PNG imgRot = PNG(imgOrig.width(), imgOrig.height());
    for( int i = 0; i < imgOrig.height(); i++) {
        for(int j = 0; j < imgOrig.width(); j++) {
            RGBAPixel *copyPixel;
            copyPixel = imgOrig(j,i);
            *imgRot((imgRot.width()-1) - j, (imgRot.height()-1) - i) = *copyPixel;
        }
    }
    imgRot.writeToFile("out.png");

    return 0;
}
