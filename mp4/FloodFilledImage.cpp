#include "cs225/PNG.h"
#include <list>
#include <iostream>

#include "colorPicker/ColorPicker.h"
#include "imageTraversal/ImageTraversal.h"

#include "Point.h"
#include "Animation.h"
#include "FloodFilledImage.h"

using namespace cs225;

/**
 * Constructs a new instance of a FloodFilledImage with a image `png`.
 * 
 * @param png The starting image of a FloodFilledImage
 */
FloodFilledImage::FloodFilledImage(const PNG & png) {
  /** @todo [Part 2] */
	png_ = png;
}

/**
 * Adds a flood fill operation to the FloodFillImage.  This function must store the operation,
 * which will be used by `animate`.
 * 
 * @param traversal ImageTraversal used for this FloodFill operation.
 * @param colorPicker ColorPicker used for this FloodFill operation.
 */
void FloodFilledImage::addFloodFill(ImageTraversal & traversal, ColorPicker & colorPicker) {
  /** @todo [Part 2] */
	ImageTraversal *trav = &traversal;
	ColorPicker *color = &colorPicker;

	trav_.push_back(trav);
	cop_.push_back(color);
}

/**
 * Creates an Animation of frames from the FloodFill operations added to this object.
 * 
 * Each FloodFill operation added by `addFloodFill` is executed based on the order
 * the operation was added.  This is done by:
 * 1. Visiting pixels within the image based on the order provided by the ImageTraversal iterator and
 * 2. Updating each pixel to a new color based on the ColorPicker
 * 
 * While applying the FloodFill to the image, an Animation is created by saving the image
 * after every `frameInterval` pixels are filled.  To ensure a smooth Animation, the first
 * frame is always the starting image and the final frame is always the finished image.
 * 
 * (For example, if `frameInterval` is `4` the frames are:
 *   - The initial frame
 *   - Then after the 4th pixel has been filled
 *   - Then after the 8th pixel has been filled
 *   - ...
 *   - The final frame, after all pixels have been filed)
 */ 
Animation FloodFilledImage::animate(unsigned frameInterval) const {
  Animation animation;
  /** @todo [Part 2] */

	unsigned count = 0;
	animation.addFrame(png_);
	for (unsigned i = 0; i < trav_.size(); i++) {
		ImageTraversal::Iterator start = trav_[i]->begin();
		ImageTraversal::Iterator finish = trav_[i]->end();

		for (ImageTraversal::Iterator itr = start; itr != finish; ++itr) {

			if (count == frameInterval) {
				animation.addFrame(png_);
				count = 0;
			}
			Point point = *itr;
			HSLAPixel &pngpixel = png_.getPixel(point.x, point.y);
			HSLAPixel cppixel = cop_[i]->getColor(point.x, point.y);
			pngpixel.h = cppixel.h;
			pngpixel.s = cppixel.s;
			pngpixel.l = cppixel.l;
			pngpixel.a = cppixel.a;
			count++;
		}
	}
	animation.addFrame(png_);

	return animation;
}
