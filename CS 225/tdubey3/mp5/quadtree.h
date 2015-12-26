// **************************************************************
// *
// *  quadtree.h
// *
// *  Quadtree class
// *
// *  CS 225 Spring 2008
// *
// **************************************************************

#ifndef QUADTREE_H
#define QUADTREE_H

#include "png.h"

class Quadtree
{
    public:

    /*
     * Default constructor for a Quadtree.
     * Initalizes a Quadtree with no QuadtreeNode objects and the root set as
     * null.
     */
    Quadtree();

    /*
     * Constructor for a Quadtree representing the upperleft d by d blck of the
     * source image.
     * Effectively corps the source image into a d by d square. Where d is a
     * power of 2.
     *
     * @param source PNG the source image which to crop from
     * @param resolution Integer value of the d by d square to crop
     */
    Quadtree(PNG const & source, int resolution);

    /*
     * Destructor for a Quadtree
     */
    ~Quadtree();

    /*
     * Copy constructor for the Quadtree
     * @param other Quadtree to copy
     */
    Quadtree(Quadtree const & other);

    /*
     * Equals assignment operator for the Quadtree
     * @param other Quadtree to copy from
     */
    Quadtree const & operator=(Quadtree const & other);

    /*
     * Deletes the contents of this Quadtree and turns it into a Quadtree
     * representing the upper-left d by d block of the source
     * @param source The source image to base this Quadtree on
     * @resolution The width and height of the sides of the image to be
     * represented
     */
    void buildTree(PNG const & source, int resolution);

    /*
     * Gets the RGBAPixel assoicated with a certain x, y location
     */
    RGBAPixel getPixel(int x, int y) const;
    /*
     * Returns the underlying PNG image represented by the Quadtree
     */
    PNG decompress() const;

    /*
     * Rotates the Quadtree 90 degrees clockwise
     */
    void clockwiseRotate();

    /*
     * Compresses the image in this quadtree by removing subtrees below a
     * specific tolerance
     * @param tolerance Value at which to trim the tree
     */
    void prune(int tolerance);

    /*
     * Counts the number of leaves that would be cut if prune was run
     * @param tolerance Value at which to trim the tree
     */
    int pruneSize(int tolerance) const;

    /*
     * Finds the ideal tolerance to cut a certain number of leaves
     * @param numLeaves The Number of leaves to cut
     */
    int idealPrune(int numLeaves) const;
    private:

    // A simple class representing a single node of a Quadtree.
    // You may want to add to this class; in particular, it could probably
    // use a constructor or two...
    class QuadtreeNode
    {
        public:
        QuadtreeNode* nwChild;  // pointer to northwest child
        QuadtreeNode* neChild;  // pointer to northeast child
        QuadtreeNode* swChild;  // pointer to southwest child
        QuadtreeNode* seChild;  // pointer to southeast child

        RGBAPixel element;  // the pixel stored as this node's "data"
    };

    QuadtreeNode* root;    // pointer to root of quadtree
    int dim;               // stores the resolution of the tree

    /*
     * Helper function for buildTree. Runs recursively to construct the tree
     * from an image
     * @param source PNG to build tree from
     * @param res int describing the resolution level the tree is at
     * @param xCoord int holding the current x position
     * @param yCoord int holding the current y position
     */
    Quadtree::QuadtreeNode* bobTheBuilder(const PNG & source, int res, int xCoord, int yCoord);

    /*
     * Helper function for Quadtree destructor. Recursively destroys trees
     * @param root Root node of tree to be deleted
     */
    void deleteTree(QuadtreeNode* root);

    /*
     * Helper function for the Quadtree copier. Recursively copies trees
     * @param root Root node of tree to be copied
     */
    Quadtree::QuadtreeNode * copyHelper(const Quadtree::QuadtreeNode * root) const;

    RGBAPixel getHelper(Quadtree::QuadtreeNode * src, int x, int y, int reso) const;
    /*
     * Helper function for the Quadtree decompressor. Recursivly
     * decompressresses trees
     * @param rootSrc QuadtreeNode to decompress
     * @param source PNG image to write decompression to
     * @param xCoord current x position being processed
     * @param yCoord current y position being processed
     * @param res Resolution of the image
     */
//    void decompressor(const Quadtree::QuadtreeNode* rootSrc, PNG & source, int xCoord, int yCoord, int reso) const;

    /*
     * Helper function for the Quadtree rotator. Recursively rotates the quadtree
     * @param rootSrc Node to rotate at
     */
    void clockwiseRotateHelper(Quadtree::QuadtreeNode* rootSrc);

    /*
     * Helper function for the Quadtree pruner.
     * @param src Node to prune
     * @param tolerance Value that is acceptable
     */
    void lopper(Quadtree::QuadtreeNode* src, int tolerance);
    
    /*
     * Helper function to see if a Quadtree is elegible to be pruned
     * @param src Node to evaluate to
     * @param srcChild Node to search at
     * @param tolerance Value to prune at
     */
    bool trimmer(Quadtree::QuadtreeNode* src, Quadtree::QuadtreeNode* srcChild, int tolerance) const;
    
    /**
     * Helper function to count the number of leaves cut during a prune
     * @param src Node to count at
     * @param tolerance Value to prune at
     * @currentCount Current value of leaves cut
     */
    int cutterCounter(Quadtree::QuadtreeNode* src, int tolerance, int currentCount) const;

    /**
     * Helper function to find the perfect tolerance for a specific number of leaves
     * @param average The value of the tolerance
     * @param min The minimum value of the tolerance in the search
     * @param max The max value of the tolerance in the search
     * @param currentCount The number of leaves to cut
     */
    int perfectPruner(int average, int min, int max, int currentCount) const;
    /**** Functions added for testing/grading                ****/
    /**** Do not remove this line or copy its contents here! ****/
    #include "quadtree_given.h"
};

#endif
