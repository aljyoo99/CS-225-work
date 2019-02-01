#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"




/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 * 
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */

double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }	
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );    
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
	isEnd_ = false;
}

ImageTraversal::Iterator::Iterator(ImageTraversal *t, Point &start, PNG &png, double tolerance) {
  /** @todo [Part 1] */
	imgtrav_ = t;
	start_ = start;
	curr_ = start;
	png_ = png;
	tolerance_ = tolerance;
	isEnd_ = false;

	for (unsigned int i = 0; i < png_.width() * png_.height(); i++) {
		visited_.push_back(false);
	}

	visited_[start_.y * png_.width() + start_.x] = true;
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */

	unsigned x = curr_.x;
	unsigned y = curr_.y;

	Point right(x + 1, y);
	Point below(x, y + 1);
	Point left(x - 1, y);
	Point above(x, y - 1);
	if (isPointValid(right)) {
		imgtrav_->add(right);
	}
	if (isPointValid(below)) {
		imgtrav_->add(below);
	}
	if (isPointValid(left)) {
		imgtrav_->add(left);
	}
	if (isPointValid(above)) {
		imgtrav_->add(above);
	}
	Point tmp = imgtrav_->pop();
	while (visited_[tmp.y * png_.width() + tmp.x]) {
		if (imgtrav_->empty()) {
			setEnd(true);
			return *this;
		}
		tmp = imgtrav_->pop();
	}

	visited_[tmp.y * png_.width() + tmp.x] = true;	

	curr_ = tmp;
	
  return *this;
}


/**
 * Iterator accessor opreator.
 * 
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
	return curr_;
}

/**
 * Iterator inequality operator.
 * 

 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
	return isEnd_ != other.isEnd_;
}


bool ImageTraversal::Iterator::isPointValid(Point &point) {
	unsigned x = point.x;
	unsigned y = point.y;

	if (x >= png_.width() || y >= png_.height()) {
		return false;
	}

	bool vis = ImageTraversal::Iterator::visited_[y * png_.width() + x];
	if (vis) {
		return false;
	}

	HSLAPixel startPixel = png_.getPixel(start_.x, start_.y);
	HSLAPixel currPixel = png_.getPixel(point.x, point.y);
	double diff = calculateDelta(startPixel, currPixel);
	if (diff >= tolerance_) {
		return false;
	}

	return true;
}

void ImageTraversal::Iterator::setEnd(bool end) {
	isEnd_ = end;
}
