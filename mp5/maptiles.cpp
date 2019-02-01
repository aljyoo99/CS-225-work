/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

/** The function mapTiles creates a mosaic which is basically a source image made up of numerous tile images. */
MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
	if (theTiles.size() == 0)
		return NULL;

	int row = theSource.getRows();
	int col = theSource.getColumns(); 
	MosaicCanvas* canvas = new MosaicCanvas(row,col);

	  
	vector<Point<3>> tiles;
	map<Point<3>, int> tilemap;
	//tiles.resize(theTiles.size());

	for(unsigned i = 0; i < theTiles.size(); i++) {
		LUVAPixel pix = theTiles[i].getAverageColor();
		Point<3> newpoint = convertToXYZ(pix);
		tiles.push_back(newpoint);
		tilemap[newpoint] = i;
	}
									
	KDTree<3> tree(tiles);

	for(int x = 0; x < row; x++) {
		for(int y = 0; y < col; y++) {
			LUVAPixel p = theSource.getRegionColor(x,y);
			Point<3> val = convertToXYZ(p);
			Point<3> nearest = tree.findNearestNeighbor(val);
			int idx = tilemap[nearest];
			//if (idx == 0)
				//idx = 1641;
			canvas->setTile(x, y, &theTiles[idx]);
			//if (tilemap[nearest] == NULL)
				//cout << nearest << endl;

		}
	}

	/**
	* @todo Implement this function!
	*/

	return canvas;
}

