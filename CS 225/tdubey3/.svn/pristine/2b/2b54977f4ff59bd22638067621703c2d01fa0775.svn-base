#include "scene.h"
#include <iostream>

using namespace std;

/**
 * Main scene constructor
 * Creates a scene with init_max-1 layers
 */
Scene::Scene(int init_max) {

    max = init_max;
    images = new Image*[max];
    for(int i = 0; i < max; i++) {
        images[i] = NULL;
    }
    xCoord = new int[max];
    for(int i = 0; i < max; i++) {
        xCoord[i] = (int)NULL;
    }
    yCoord = new int[max];
    for(int i = 0; i < max; i++) {
        yCoord[i] = (int)NULL;
    }
}

/**
 * Scene copy constructor
 */
Scene::Scene(const Scene & source) {
    copy(source);
}

/**
 * Scene assignment operator
 */
const Scene & Scene::operator=(const Scene & source) {
    if (this != &source) {
        clear();
        copy(source);
    }
    return *this;
}

Scene::~Scene() {
    clear();
}

/**
 * Changes the number of layers in a scene
 */
void Scene::changemaxlayers(int newmax) {
    /** Check for non-null outside of newmax  */
    if(newmax < max) {
        for(int i = newmax-1; i < max; i++) {
            if(images[i] != NULL) {
                cout << "invalid newmax" << endl;
                return;
            }
        }

        Image ** temp = new Image*[newmax];
        for(int i = 0; i < newmax; i++) {
            temp[i] = images[i];
        }

        int * xTemp = new int[newmax];
        for(int i = 0; i < newmax; i++) {
            xTemp[i] = xCoord[i];
        }

        int * yTemp = new int[newmax];
        for(int i = 0; i < newmax; i++) {
            yTemp[i] = yCoord[i];
        }
        max = newmax;
        delete [] images;
        delete [] xCoord;
        delete [] yCoord;
        images = temp;
        xCoord = xTemp;
        yCoord = yTemp;
        return;
    }
    /** Check if newmax and max are the same  */
    if(newmax == max) {
        return;
    }

    Image ** temp = new Image*[newmax];
    for(int i = 0; i < max; i++) {
        temp[i] = images[i];
    }
    for(int i = max; i < newmax; i++) {
        temp[i] = NULL;
    }

    int * xTemp = new int[newmax];
    for(int i = 0; i < max; i++) {
        xTemp[i] = xCoord[i];
    }
    for(int i = max; i < newmax; i++) {
        xTemp[i] = (int) NULL;
    }

    int * yTemp = new int[newmax];
    for(int i = 0; i < max; i++) {
        yTemp[i] = yCoord[i];
    }
    for(int i = max; i < newmax; i++) {
        yTemp[i] = (int)NULL;
    }
    max = newmax;
    delete [] images;
    delete [] xCoord;
    delete [] yCoord;
    images = temp;
    xCoord = xTemp;
    yCoord = yTemp;
}

/**
 * Adds a image to the specified index and x,y location
 */
void Scene::addpicture(const char* FileName, int index, int x, int y) {
    if(index > max-1 || index < 0) {
        cout << "index out of bounds" << endl;
        return;
    }
    Image * addImage = new Image();
    addImage->readFromFile(FileName);
    images[index] = addImage;
    xCoord[index] = x;
    yCoord[index] = y;
}

/**
 * Changes the index of an image, makes the source NULL
 */
void Scene::changelayer(int index, int newindex) {
    if(index > max-1 || index < 0) {
        cout << "invalid index" << endl;
        return;
    }
    if(newindex > max-1 || newindex < 0) {
        cout << "invalid index" << endl;
        return;
    }
    if(index == newindex) {
        return;
    }
    if(images[newindex] != NULL) {
        delete images[newindex];
    }
    images[newindex] = images[index];
    images[index] = NULL;
    xCoord[newindex] = xCoord[index];
    yCoord[newindex] = yCoord[index];
    xCoord[index] =(int) NULL;
    yCoord[index] = (int)NULL;
}

/**
 * Changes the position of the image at the given index
 */

void Scene::translate(int index, int xcoord, int ycoord) {
    if(index > max-1 || index < 0) {
        cout << "invalid index" << endl;
        return;
    }
    if(images[index] == NULL) {
        cout << "invalid index" << endl;
        return;
    }
    xCoord[index] = xcoord;
    yCoord[index] = ycoord;
}

/**
 * Deletes image at specified location
 */
void Scene::deletepicture(int index) {
    if(index > max-1 || index < 0) {
        cout << "invalid index" << endl;
        return;
    }
    if(images[index] == NULL) {
        cout << "invalid index" << endl;
        return;
    }
    delete images[index];
    images[index] = NULL;
}

/**
 * Returns the pointer of the image at the given index
 */
Image * Scene::getpicture(int index) const {
    if(index > max-1 || index < 0) {
        cout << "invalid index" << endl;
        return NULL;
    }
    if(images[index] == NULL) {
        cout << "invalid index" << endl;
        return NULL;
    }
    return images[index];
}

/**
 * Returns an image with all the images in the scene
 */
Image Scene::drawscene() const{
    int maxW = 1;
    for(int i = 0; i < max; i++) {
        if(images[i] != NULL) {
            if((int)(images[i]->width() + xCoord[i]) > maxW) {
                maxW = images[i]->width() + xCoord[i];
            }
        }
    }

    int maxH = 1;
    for(int i = 0; i < max; i++) {
        if(images[i] != NULL) {
            if((int)(images[i]->height() + yCoord[i]) > maxH) {
                maxH = images[i]->height() + yCoord[i];
            }
        }
    }

    Image finalImage;
    finalImage.resize(maxW, maxH);
    for(int i = 0; i < max; i++) {
        if(images[i] != NULL) {
            for(int x = 0; x < (int)(images[i]->width()); x++){
                for(int y = 0; y < (int)(images[i]->height()); y++){
                    *finalImage(x+xCoord[i],y+yCoord[i]) = *images[i]->operator()(x,y);
                }
            }
        }
    }
    return finalImage;
}

/**
 * Destructor/assignment operator clear helper function
 */
void Scene::clear() {
    if( images != NULL) {
        for(int i = 0; i<max; i++) {
            delete images[i];
        }
        delete [] images;
    }
    if( xCoord != NULL) {
        delete [] xCoord;
    }
    if( yCoord != NULL) {
        delete [] yCoord;
    }
    images = NULL;
    xCoord = NULL;
    yCoord = NULL;
}

void Scene::copy(const Scene & source){

            max = source.max;
            xCoord = new int[max];
            yCoord = new int[max];
            images = new Image*[max]();
            for(int i = 0; i < max; i++){
                if(source.images[i]!=NULL){ 
                    images[i] = new Image(*(source.images[i]));
                    xCoord[i] = source.xCoord[i];
                    yCoord[i] = source.yCoord[i];
                }
            }
}
