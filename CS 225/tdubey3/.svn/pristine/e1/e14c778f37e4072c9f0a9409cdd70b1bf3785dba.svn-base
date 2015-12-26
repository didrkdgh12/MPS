/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */
	 			
#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

MosaicCanvas * mapTiles(SourceImage const & theSource, vector<TileImage> const & theTiles)
{
    /**
     * @todo Implement this function!
     */
    int row = theSource.getRows();
    int col = theSource.getColumns();

    MosaicCanvas *image = new MosaicCanvas(row, col);

    vector<Point<3>> rgb;
    vector<TileImage>::iterator it;

    map<Point<3>, TileImage> imgMap;

    for(size_t i = 0; i < theTiles.size(); i++) {
    	RGBAPixel holder = theTiles[i].getAverageColor();
    	Point<3> temp(holder.red, holder.blue, holder.green);
    	imgMap[temp] = theTiles[i];
    	rgb.push_back(temp);
    }

    KDTree<3> tree(rgb);
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++) {
            RGBAPixel holder = theSource.getRegionColor(i,j);
            Point<3> qsearch(holder.red, holder.blue, holder.green);
            Point<3> out = tree.findNearestNeighbor(qsearch);

            TileImage outImg = imgMap[out];
            image->setTile(i, j, outImg);
        }
    }

	return image;
}
