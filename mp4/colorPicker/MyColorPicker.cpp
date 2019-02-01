#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
MyColorPicker::MyColorPicker(double change) {
	sat_ = 1;
	change_ = change;
}

HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
	/* @todo [Part 3] */
	HSLAPixel pixel(190, sat_, 0.5);
	sat_ -= change_;
	if (sat_ <= 0) {
		sat_ = 1;
	}
	return pixel;
}
