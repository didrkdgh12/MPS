// **************************************************************
// *
// *  quadtree.cpp
// *
// *  Quadtree class
// *
// *  CS 225 Spring 2008
// *
// **************************************************************

#include "quadtree.h"
#include <iostream>
#include <math.h>

using namespace std;

//Default constructor for the Quadtree
Quadtree::Quadtree() {
    root = NULL;
    dim = 0;
}

//Constructor for the Quadtree that takes in a source image and resolution to
//crop
Quadtree::Quadtree(PNG const & source, int resolution) {
    root = NULL; //Incase resolution is 0
    dim = resolution;
    buildTree(source, resolution);
}

//Destructor for the Quadtree
Quadtree::~Quadtree() {
    deleteTree(root);
    root = NULL;
}

//Quadtree copy constructor
Quadtree::Quadtree(Quadtree const & other) {
    dim = other.dim;
    root = copyHelper(other.root);
}

//Quadtree equals assignment operator overload
Quadtree const & Quadtree::operator=(Quadtree const & other) {
    deleteTree(root);
    root = copyHelper(other.root);
    dim = other.dim;
    return *this;
}

//Quadtree constructor helper function that builds the tree
void Quadtree::buildTree(PNG const & source, int resolution) {
    deleteTree(root);
    dim = resolution;
    root = bobTheBuilder(source, resolution, 0, 0);
}

RGBAPixel Quadtree::getPixel(int x, int y) const {
    if( (x<dim) && (x>=0) && (y<dim) && (y>= 0) && (root != NULL)) {
        return getHelper(root, x, y, dim);
    }
    return RGBAPixel();
}
//Returs the underlying PNG image represented by the Quadtree
PNG Quadtree::decompress() const{
    if(root == NULL || dim == 0){
        return PNG();
    } else {
        PNG ret(dim, dim);
        for(int i = 0; i < dim; i++) {
            for(int j = 0; j < dim; j++) {
                *ret(i,j) = getPixel(i,j);
            }
        }
        return ret;
    }
}

//Rotates the Quadtree 90 degrees clockwise
void Quadtree::clockwiseRotate() {
    clockwiseRotateHelper(root);
}

void Quadtree::prune(int tolerance){
    lopper(root, tolerance);
}

int Quadtree::pruneSize(int tolerance) const {
    return cutterCounter(root, tolerance, 0);
}

int Quadtree::idealPrune(int numLeaves) const {
    if(root == NULL) {
        return 0;
    }
    int min = 0;
    int max = 999999999;
    int average = (min+max)/2;
    return perfectPruner(average, min, max, numLeaves);
}
//buildTree helper function that recursively builds the Quadtree from a source
//image a resolution
Quadtree::QuadtreeNode* Quadtree::bobTheBuilder(const PNG & source, int res, int xCoord, int yCoord) {
    if(res == 1) {
        QuadtreeNode * rN = new QuadtreeNode;
        rN->nwChild = NULL;
        rN->neChild = NULL;
        rN->swChild = NULL;
        rN->seChild = NULL;
        rN->element = *source(xCoord, yCoord);
        return rN;
    }
    QuadtreeNode * r = new QuadtreeNode;
    r->nwChild = bobTheBuilder(source, res/2, xCoord, yCoord);
    r->neChild = bobTheBuilder(source, res/2, xCoord+(res/2), yCoord);
    r->swChild = bobTheBuilder(source, res/2, xCoord, yCoord+(res/2));
    r->seChild = bobTheBuilder(source, res/2, xCoord+(res/2), yCoord+(res/2));

    int red = (r->nwChild->element.red + r->neChild->element.red + r->swChild->element.red + r->seChild->element.red)/4;
    int green = (r->nwChild->element.green + r->neChild->element.green + r->swChild->element.green + r->seChild->element.green)/4;
    int blue = (r->nwChild->element.blue + r->neChild->element.blue + r->swChild->element.blue + r->seChild->element.blue)/4;

    r->element.red = red;
    r->element.green = green;
    r->element.blue = blue;

    return r;
}

//Helper function for the Quadtree deconstructor
void Quadtree::deleteTree(QuadtreeNode* root) {
    if(root != NULL) {
        deleteTree(root->nwChild);
        deleteTree(root->swChild);
        deleteTree(root->neChild);
        deleteTree(root->seChild);
        delete(root);
        root = NULL;
    }
    return;
}

//Helper function for the Quadtree copy constructor
Quadtree::QuadtreeNode * Quadtree::copyHelper(const Quadtree::QuadtreeNode * root) const {
    if(root != NULL) {
        QuadtreeNode * r = new QuadtreeNode;
        r->element = root->element;
        r->neChild= copyHelper(root->neChild);
        r->nwChild= copyHelper(root->nwChild);
        r->seChild= copyHelper(root->seChild);
        r->swChild= copyHelper(root->swChild);
        return r;
    }
    return NULL;
}

RGBAPixel Quadtree::getHelper(Quadtree::QuadtreeNode* src, int x, int y, int reso) const {
    if(src->nwChild == NULL) {
        return src->element;
    }
    if((x < reso/2) && (y<reso/2)) {
        return getHelper(src->nwChild, x, y, reso/2);
    }
    else if((x >= reso/2) && (y<reso/2)) {
        return getHelper(src->neChild, x-reso/2, y, reso/2);
    }
    else if((x < reso/2) && (y>=reso/2)) {
        return getHelper(src->swChild, x, y-reso/2, reso/2);
    }
    else  {
        return getHelper(src->seChild, x-reso/2, y-reso/2, reso/2);
    }
}

//Helper function for the Quadtree decompressor
//void Quadtree::decompressor(const Quadtree::QuadtreeNode* rootSrc, PNG & source, int xCoord, int yCoord, int reso) const {
//   if(rootSrc->nwChild == NULL ) {
//        for(int i = xCoord; i < xCoord+reso; i++) {
//            for(int j = yCoord; j < yCoord+reso; j++) {
//                *source(i,j) = rootSrc->element;
//            }
//        }
//        return;
//    }
//    decompressor(rootSrc->nwChild, source, xCoord, yCoord, reso/2);
//    decompressor(rootSrc->neChild, source, xCoord+(reso/2), yCoord, reso/2);
//    decompressor(rootSrc->swChild, source, xCoord, yCoord+(reso/2), reso/2);
//    decompressor(rootSrc->seChild, source, xCoord+(reso/2), yCoord+(reso/2), reso/2);
//}

//Helper function for the Quadtree rotator
void Quadtree::clockwiseRotateHelper(Quadtree::QuadtreeNode* rootSrc) {
    if(rootSrc != NULL) {
        QuadtreeNode * r = rootSrc->nwChild;
        rootSrc->nwChild = rootSrc->swChild;
        rootSrc->swChild = rootSrc->seChild;
        rootSrc->seChild = rootSrc->neChild;
        rootSrc->neChild = r;
        clockwiseRotateHelper(rootSrc->neChild);
        clockwiseRotateHelper(rootSrc->nwChild);
        clockwiseRotateHelper(rootSrc->seChild);
        clockwiseRotateHelper(rootSrc->swChild);
    }
    return;
}

//Helper function for the Quadtree pruner
void Quadtree::lopper(Quadtree::QuadtreeNode* src, int tolerance) {
    if(src != NULL) {
        if(trimmer(src, src, tolerance)) {
            deleteTree(src->nwChild);
            deleteTree(src->neChild);
            deleteTree(src->swChild);
            deleteTree(src->seChild);
            src->nwChild = NULL;
            src->neChild = NULL;
            src->swChild = NULL;
            src->seChild = NULL;
            return;
        }
        lopper(src->nwChild, tolerance);
        lopper(src->neChild, tolerance);
        lopper(src->seChild, tolerance);
        lopper(src->swChild, tolerance);
        return;
    }
    return;
}

bool Quadtree::trimmer(Quadtree::QuadtreeNode* src, Quadtree::QuadtreeNode* srcChild, int tolerance) const{
    if(src == NULL || srcChild == NULL) {
        return true;
    }
    if(srcChild->nwChild != NULL) {
        return trimmer(src, srcChild->nwChild, tolerance) && trimmer(src, srcChild->neChild, tolerance) && trimmer(src, srcChild->seChild, tolerance) && trimmer(src, srcChild->swChild, tolerance);
    }
    int red = pow(src->element.red - srcChild->element.red, 2);
    int blue = pow(src->element.blue - srcChild->element.blue, 2);
    int green = pow(src->element.green - srcChild->element.green, 2);
    return ((red + blue + green) <= tolerance);
}

int Quadtree::cutterCounter(Quadtree::QuadtreeNode* src, int tolerance, int currentCount) const {
    if(src == NULL) {
        return 0;
    }
    if((src->nwChild == NULL) || trimmer(src, src, tolerance)) {
        return 1;
    }
    return cutterCounter(src->nwChild, tolerance, 0) + cutterCounter(src->neChild, tolerance, 0) + cutterCounter(src->seChild, tolerance, 0) + cutterCounter(src->swChild, tolerance, 0);
}

int Quadtree::perfectPruner(int average, int min, int max, int currentCount) const {
    if(max <= min) {
        return min;
    }
    average = (min+max)/2;

    int count = pruneSize(average);

    if(count <= currentCount) {
        max = average;
    } else {
        min = average + 1;
    }

    return perfectPruner(average, min, max, currentCount);
}
