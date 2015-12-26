#include "imageData.h"
#include "functions.h"
/* FUNCTIONS.C
 *
 * This file contains the functions for image manipulation that are described
 * below:
 *
 * calculateCosineFiler: calculates the cosine filter values
 *
 * convolveImage: applies a convolition between a filter and a image
 *
 * converToGrey: converts an image to greyscale
 *
 * colorThreshold: applies a threshold filter to an image
 *
 * Description of image convolution:
 *      Image convolution is a process when a filter matrix is applied to a
 *      image matrix. The values of the image channels are multiplied by the
 *      filter image and then summed. This sum is then truncated to defined
 *      limits and placed in the location of the image. Take the image and
 *      filter array below
 *
 *      +---+---+---+---+---+---+
 *      | 7 | 8 | 2 | 3 | 1 | 3 |
 *      +---+---+---+---+---+---+
 *      | 2 | 9 | 0 | 5 | 6 | 3 |
 *      +---+---+---+---+---+---+
 *      | 1 | 6 | 3 | 8 | 5 | 9 |
 *      +---+---+---+---+---+---+
 *      | 1 | 6 | 5 | 4 | 9 | 7 |
 *      +---+---+---+---+---+---+
 *      | 0 | 9 | 5 | 8 | 3 | 7 |
 *      +---+---+---+---+---+---+
 *      | 6 | 8 | 4 | 9 | 3 | 7 |
 *      +---+---+---+---+---+---+  <---- Image
 *
 *      +---+---+---+
 *      | 0 | 1 | 0 |
 *      +---+---+---+
 *      | 1 | 2 | 1 |
 *      +---+---+---+
 *      | 0 | 1 | 0 |
 *      +---+---+---+   <---- Filter
 *
 *      If we apply this filter to the pixel location (2,2):
 *
 *      +---+---+---+
 *      | 7 | 8 | 2 |
 *      +---+---+---+
 *      | 2 | 9 | 0 |
 *      +---+---+---+
 *      | 1 | 6 | 3 |
 *      +---+---+---+
 *
 *      We get this math for our resultant pixel:
 *
 *      0 + 8 + 0 + 2 + 18 + 0 + 0 + 6 + 0 = 34
 *
 *      This value is then clamped to our limits (in this case 10) and written
 *      to the corresponding pixel, so our image is now:
 *
 *      +---+----+---+---+---+---+
 *      | 7 |  8 | 2 | 3 | 1 | 3 |
 *      +---+----+---+---+---+---+
 *      | 2 | 10 | 0 | 5 | 6 | 3 |
 *      +---+----+---+---+---+---+
 *      | 1 |  6 | 3 | 8 | 5 | 9 |
 *      +---+----+---+---+---+---+
 *      | 1 |  6 | 5 | 4 | 9 | 7 |
 *      +---+----+---+---+---+---+
 *      | 0 |  9 | 5 | 8 | 3 | 7 |
 *      +---+----+---+---+---+---+
 *      | 6 |  8 | 4 | 9 | 3 | 7 |
 *      +---+----+---+---+---+---+
 *
 *      And so image convolution is performed.      
 */


/*
 * calculateCosineFilter - calculates the cosine filter values
 * INPUTS:  int radius- integer indicating the size of array.
 *          The filter has 2*radius+1 rows and 2*radius+1 columns
 * OUTPUTS: cosineFitler - pointer to the 1-D array of size
 *          (2*radius+1)*(2*radius+1). Appropriate space
 *          has already been allocated). This function must compute
 *          the appropriate values of this array as described
 *          in the wiki writeup
 * RETURN VALUE: none
 */
void calculateCosineFilter(double *cosFilter,int radius)
{
    int x = -1 * radius;
    int y = -1 * radius;
    int currX = 0;
    int currY = 0;
    double total;
    //Image Width is : 2 * radius + 1
    //Image Height is: 2 * radius + 1
    //[ 1*4 +2], where 4 is the image width, 1 is the row index we want and 2 is
    //the column index we want
    for(currY = 0; currY < 2 * radius + 1; currY++) {
        for(currX = 0; currX < 2 * radius + 1; currX++) {
            //printf("Radius: %d, X: %d, Y: %d \n", radius, x, y);
            total = total + cos((M_PI*x)/(2*radius))+cos((M_PI*y)/(2*radius)); //add filter value to total
            cosFilter[currY*(2*radius+1)+currX] = cos((M_PI*x)/(2*radius))+cos((M_PI*y)/(2*radius)); //Calc filter
            x++;
        }
        y++;
        x = -1 * radius;
    }
    //Normalize the filer
    for(currY = 0; currY < 2 * radius + 1; currY++) {
        for(currX = 0; currX < 2 * radius + 1; currX++) {
            cosFilter[currY*(2*radius+1)+currX] = cosFilter[currY*(2*radius+1)+currX]/total;
        }
    }
}

/* convolveImage - performs a convolution between a filter and image
 * INPUTS: inRed - pointer to the input red channel (1-D array)
 *         inGreen - pointer to the input green channel (1-D array)
 *         inBlue - pointer to the input blue channel (1-D array)
 *         inAlpha - pointer to the input alpha channel (1-D array)
 *         filter - pointer to the convolution filter (1-D array)
 *         radius - radius of the convolution filter
 *         width - width of the input image
 *         height - height of the input image
 * OUTPUTS: outRed - pointer to the output red channel (1-D array)
 *          outGreen - pointer to the output green channel (1-D array)
 *          outBlue - pointer to the output blue channel (1-D array)
 *          outAlpha - pointer to the output alpha channel (1-D array)
 * RETURN VALUES: none
 * NOTE: Input image values are already loaded into the input arrays
 *       Filter is already initialized and contains desired values.
 *       Appropriate space has been allocated for output arrays.
 */
void convolveImage(uint8_t *inRed,uint8_t *inGreen,uint8_t *inBlue,
                uint8_t *inAlpha, uint8_t *outRed,uint8_t *outGreen,
                uint8_t *outBlue,uint8_t *outAlpha,const double *filter,
                int radius,int width,int height)
{
  int index = 0;
        for(int y = 0; y < height; y++){
                for(int x = 0; x < width; x++){
                        //initialize everything to 0
                        outRed[y*width+x] = 0;
                        outGreen[y*width+x] = 0;
                        outBlue[y*width+x] = 0;
                        outAlpha[y*width+x] = 0;
                        double rsum = 0, gsum = 0, bsum = 0;
                        for(int i = -1*radius; i < radius + 1; i++){
                                for(int j = -1*radius; j < radius + 1; j++){
                                        double fil = filter[(i+radius)*(2*radius + 1)+(j+radius)];
                                        double redval;
                                        //check bounds
                                        if(x+j < 0 || y+i < 0 || x+j >= width || y+i >=height)
                                                redval = 0;
                                        else
                                                redval = inRed[(y+i)*width + (x+j)];
                                        rsum += fil * redval;
 
                                        double greenval;
                                        if(x+j < 0 || y+i < 0 || x+j >= width || y+i >=height)
                                                greenval = 0;
                                        else
                                                greenval = inGreen[(y+i)*width + (x+j)];
                                        gsum += fil * greenval;
 
                                        double blueval;
                                        if(x+j < 0 || y+i < 0 || x+j >= width || y+i >=height)
                                                blueval = 0;
                                        else
                                                blueval = inBlue[(y+i)*width + (x+j)];
                                        bsum += fil * blueval;
 
 
                                }
                        }
                        //set the output values
                        outRed[y*width+x] = rsum;
                        outGreen[y*width+x] = gsum;
                        outBlue[y*width+x] = bsum;
 
                        outAlpha[index] = inAlpha[index];
                        index++;
                }
        }
}


/* convertToGray - convert the input image to grayscale
 * INPUTS: inRed - pointer to the input red channel (1-D array)
 *         inGreen - pointer to the input green channel (1-D array)
 *         inBlue - pointer to the input blue channel (1-D array)
 *         inAlpha - pointer to the input alpha channel (1-D array)
 *         gMonoMult - pointer to array with constants to be multipiled with
 *                     RBG channels to convert image to grayscale (3 element array)
 *         width - width of the input image
 *         height - height of the input image
 * OUTPUTS: outRed - pointer to the output red channel (1-D array)
 *          outGreen - pointer to the output green channel (1-D array)
 *          outBlue - pointer to the output blue channel (1-D array)
 *          outAlpha - pointer to the output alpha channel (1-D array)
 * RETURN VALUES: none
 * NOTE: Input image values are already loaded into the input arrays
 *       gMonoMult contains the desired grayscale weights.
 *       Appropriate space has been allocated for output arrays.
 */
void convertToGray(uint8_t *inRed,uint8_t *inGreen,uint8_t *inBlue,
                uint8_t *inAlpha,uint8_t *outRed,uint8_t *outGreen,
                uint8_t *outBlue,uint8_t *outAlpha,
                const double *gMonoMult,int width,int height)
{
    int i;
    for(i=0; i < width*height; i++) {
        double total = inRed[i] * gMonoMult[0] + inGreen[i] * gMonoMult[1] + inBlue[i] * gMonoMult[2]; //calc the values

        //Apply values
        outRed[i] = (uint8_t)total;
        outBlue[i] = (uint8_t)total;
        outGreen[i] = (uint8_t)total;
        outAlpha[i] = inAlpha[i];
    }
}

/* invertImage - inverts the colors of the image
 * INPUTS: inRed - pointer to the input red channel (1-D array)
 *         inGreen - pointer to the input green channel (1-D array)
 *         inBlue - pointer to the input blue channel (1-D array)
 *         inAlpha - pointer to the input alpha channel (1-D array)
 *         width - width of the input image
 *         height - height of the input image
 * OUTPUTS: outRed - pointer to the output red channel (1-D array)
 *          outGreen - pointer to the output green channel (1-D array)
 *          outBlue - pointer to the output blue channel (1-D array)
 *          outAlpha - pointer to the output alpha channel (1-D array)
 * RETURN VALUES: none
 * NOTE: Input image values are already loaded into the input arrays
 *       Appropriate space has been allocated for output arrays.
 */
void invertImage(uint8_t *inRed,uint8_t *inGreen,uint8_t *inBlue,
                uint8_t *inAlpha,uint8_t *outRed,uint8_t *outGreen,
                uint8_t *outBlue,uint8_t *outAlpha,int width,int height)
{
    int i;
    //Calc and apply values, I can't really say much it's self expanatory
    for(i=0; i<width*height; i++) {
        outRed[i] = 255 - inRed[i];
        outBlue[i] = 255 - inBlue[i];
        outGreen[i] = 255 - inGreen[i];
        outAlpha[i] = inAlpha[i];
    }
}

/* color threshold - for each pixel of input image, compares value to red, green, and blue threshold. If the values exceed all three thresholds, set the output image to the input image values. Otherwise, set them to zero. Alpha should remain unchanged.
 * INPUTS: inRed - pointer to the input red channel (1-D array)
 *         inGreen - pointer to the input green channel (1-D array)
 *         inBlue - pointer to the input blue channel (1-D array)
 *         inAlpha - pointer to the input alpha channel (1-D array)
 *         width - width of the input image
 *         height - height of the input image
 * OUTPUTS: outRed - pointer to the output red channel (1-D array)
 *          outGreen - pointer to the output green channel (1-D array)
 *          outBlue - pointer to the output blue channel (1-D array)
 *          outAlpha - pointer to the output alpha channel (1-D array)
 * RETURN VALUES: none
 * NOTE: Input image values are already loaded into the input arrays
 *       Appropriate space has been allocated for output arrays.
 */
void colorThreshold(uint8_t *inRed,uint8_t *inGreen,uint8_t *inBlue,
                uint8_t *inAlpha,uint8_t *outRed,uint8_t *outGreen,
                uint8_t *outBlue,uint8_t *outAlpha,int width,int height,int redThreshold,int blueThreshold,int greenThreshold)
{
    int i;
    for(i=0; i < width*height; i++) {

        //If the values are above threshold, clamp
        if((inRed[i] > redThreshold) && (inBlue[i] > blueThreshold) && (inGreen[i] > greenThreshold)){
            outRed[i] = inRed[i];
            outGreen[i] = inGreen[i];
            outBlue[i] = inBlue[i];
            outAlpha[i] = inAlpha[i];
        } else {
            //otherwise reset it
            outRed[i] = 0;
            outGreen[i] = 0;
            outBlue[i] = 0;
            outAlpha[i] = 255;
        }
    }
}


/* Challenge problem 2
 * Detect target image in input image. Code should see if the target image is part of the
 * input image. Outputs the center pixel of the target in the input image.
 * INPUTS: inRed - pointer to the input red channel (1-D array)
 *         inGreen - pointer to the input green channel (1-D array)
 *         inBlue - pointer to the input blue channel (1-D array)
 *         inAlpha - pointer to the input alpha channel (1-D array)
 *         targetRed - pointer to the target red channel (1-D array)
 *         targetGreen - pointer to the target green channel (1-D array)
 *         targetBlue - pointer to the target blue channel (1-D array)
 *         targetAlpha - pointer to the target alpha channel (1-D array)
 *         width - width of the input image
 *         height - height of the input image
 *         targetWidth - width of the target image
 *         targetHeight - height of the target image
 * OUTPUTS: outPixelCol - column index of detected target (-1 if no target found)
 *          outPixelRow - row index of detected target (-1 if no target found)
 * RETURN VALUES: none
 * NOTE: Input and target image values are already loaded into the input arrays
 *       outPixelCol and outPixelRow are passed by reference. Set the value at these pointers
 *       to the location of the target image in the larger image (-1, -1 if not found)
 */
void detectImage(uint8_t *inRed,uint8_t *inGreen,uint8_t *inBlue,
                uint8_t *inAlpha,int* outPixelCol, int* outPixelRow, uint8_t *targetRed, uint8_t *targetBlue, uint8_t *targetGreen, uint8_t *targetAlpha,int width,int height,int targetWidth, int targetHeight){
        //Your Code here
}


/* Challenge Problem 1
 * transformImage - Computes an affline transformation of the input image
 * This can be used to compute rotations, rescale, and skew the image.
 * The two-dimensional array transform defines the transform to be done.
 * The values of the output image at x', y' are assigned by finding the closest (x,y) pair in
 * the original image by inverting the transform
 * INPUTS: inRed - pointer to the input red channel (1-D array)
 *         inGreen - pointer to the input green channel (1-D array)
 *         inBlue - pointer to the input blue channel (1-D array)
 *         inAlpha - pointer to the input alpha channel (1-D array)
 *	   transform - two-dimensional array containing transform coefficients (2-D array)
 *         width - width of the input and output image
 *         height - height of the input and output image
 * OUTPUTS: outRed - pointer to the output red channel (1-D array)
 *          outGreen - pointer to the output green channel (1-D array)
 *          outBlue - pointer to the output blue channel (1-D array)
 *          outAlpha - pointer to the output alpha channel (1-D array)
 * RETURN VALUES: none
 * NOTE: Input values are already loaded into the input arrays
 *       Appropriate space is already allocated for output image
 */
void transformImage(uint8_t *inRed,uint8_t *inGreen,uint8_t *inBlue,uint8_t *inAlpha,
                uint8_t *outRed,uint8_t *outGreen,uint8_t *outBlue,
                uint8_t *outAlpha,const double transform[2][2],int width,int height)
{
        //Your Code here

}
