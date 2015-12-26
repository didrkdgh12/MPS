#ifndef SCENE_H
#define SCENE_H

#include "image.h"

class Scene : public PNG {
    public:
            // Values

            /** Max number of images in the scene */
            int max;

            /** The maximum width of the full scene */
            int max_width;

            /** The maximum height of the full scene */
            int max_height;

            /** An array of Image pointers currently in the scene */
            Image ** images;

            /** An array of x coordinates for the scene  */
            int * xCoord;

            /** An array of y corrdinates for the scene  */
            int * yCoord;

            /**
             * Creates a scene object with a "max" number of images
             * @param max Maximum number of layers in the scene
             */
            Scene(int init_max);

            ~Scene();

            /**
             * Copy constructor of the Scene
             * @param source Scene refrence to copy from
             */
            Scene(const Scene & source);

            /**
             * Assigment operator for a scene
             * @param source Scene to copy from
             * @return a constant Scene refrence
             */
            const Scene & operator=(const Scene & source);

            /**
             * Modifies the array of image pointers without changing their
             * indicies
             * @param newmax The new maximum number of images in the scene
             */
            void changemaxlayers(int newmax);

            /**
             * Adds an image to the spcified location, index, and coord.
             * @param FileName Filename of the image to be loaded
             * @param index Location in the scene where image is placed
             * @param x X-Coord for the image
             * @param y Y-Coord for the image
             */
            void addpicture(const char* FileName, int index, int x, int y);

            /**
             * Moves an image from one layer to another,
             * @param index Layer to move
             * @param newindex Destination layer
             */
            void changelayer(int index, int newindex);

            /**
             * Changes the x and y coords of an image in a layer
             * @param index Index of image to be modified
             * @param xcoord New X location of the image
             * @param ycoord New Y location of the image
             */
            void translate(int index, int xcoord, int ycoord);

            /**
             * Deletes the image at the given location
             * @param index Location of image to delete
             */
            void deletepicture(int index);

            /**
             * Gets the image at the specified location
             * @param index Location of image to get
             * @return Pointer of the image
             */
            Image * getpicture(int index) const;

            /**
             * Creates a Image from the current scene
             * @return Image of the created scene
             */
            Image drawscene() const;
    private:

            /**
             * Destructor/assignment operator clear helper function
             */
            void clear();

            /**
             * Copy Constructor/assigment operator copy helper function
             */
            void copy(const Scene & source);

};
#endif
