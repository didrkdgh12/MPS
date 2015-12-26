#ifndef IMAGE_H
#define IMAGE_H

#include "png.h"

class Image : public PNG {
        public:
                /**
                 * Takes a PNG Pointer.
                 * Flips the PNG down the vertical center.
                 * @param image Pointer of the PNG to be flipped
                 * @return void
                 */
                void flipleft();
                
                /**
                 * Takes the three color channels.
                 * Uses these to adjust the brightness by specified value.
                 * Accounts for overflow (<0 is 0, >255 is 255)
                 * @param r Integer for red channel adjustment
                 * @param g Integer for green channel adjustment
                 * @param b Integer for blue channel adjustment
                 * @param image PNG pointer of image to be adjusted
                 * @return void
                 */
                void adjustbrightness(int r, int g, int b);
                
                /**
                 * Takes a PNG Pointer.
                 * Inverts the colors of the image.
                 * Does 255-currentPixelChannelValue
                 * @param image Pointer of the PNG to be inverted
                 * @return void
                 */
                void invertcolors();

};
#endif
