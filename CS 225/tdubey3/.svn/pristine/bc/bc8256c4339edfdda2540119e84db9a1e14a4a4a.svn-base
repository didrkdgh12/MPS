#include "image.h"

void Image::flipleft() {
    RGBAPixel tempHolder;
    for(int x = 0; x < (width()/2); x++) {
        for(int y = 0; y < height(); y++) {
             tempHolder = *(*this)(x,y);
             *(*this)(x,y) = *(*this)(width()-x-1,y);
             *(*this)(width()-x-1, y) = tempHolder;
        }
    }
}

void Image::adjustbrightness(int r, int g, int b){
    RGBAPixel tempHolder;
    for(int x = 0; x < width(); x++) {
            for(int y = 0; y < height(); y++) {
                tempHolder = *(*this)(x,y);
                
                //Check for red over/underflow
                if(tempHolder.red + r > 255) {
                    tempHolder.red = 255;
                } else if (tempHolder.red + r < 0) {
                    tempHolder.red = 0;
                } else {
                    tempHolder.red = tempHolder.red + r;
                }
                
                //Check for green over/underflow
                if(tempHolder.green + g > 255) {
                    tempHolder.green = 255;
                } else if (tempHolder.green + g < 0) {
                    tempHolder.green = 0;
                } else {
                    tempHolder.green = tempHolder.green + g;
                }
                
                //Check for blue over/underflow
                if(tempHolder.blue + b > 255) {
                    tempHolder.blue = 255;
                } else if (tempHolder.blue + b < 0) {
                    tempHolder.blue = 0;
                } else {
                    tempHolder.blue = tempHolder.blue + b;
                }
                
                //Write to image
                *(*this)(x,y) = tempHolder;
            }
    }
}

void Image::invertcolors(){
    RGBAPixel tempHolder;

    for(int x = 0; x < width(); x++) {
        for(int y = 0; y < height(); y++) {
            tempHolder = *(*this)(x,y);
            tempHolder.red = 255 - tempHolder.red;
            tempHolder.green = 255 - tempHolder.green;
            tempHolder.blue = 255 - tempHolder.blue;
            *(*this)(x,y) = tempHolder;
        }
    }
}
