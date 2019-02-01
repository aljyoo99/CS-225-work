#include <cmath>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "Image.h"
using namespace cs225;
using namespace std;

void Image::lighten() {
	for (unsigned x = 0; x < this->width(); x++) {
		for (unsigned y = 0; y < this->height(); y++) {
			HSLAPixel & pixel = this->getPixel(x, y);
			if (pixel.l + 0.1 > 1) {
				pixel.l = 1;
			} else {
				pixel.l = pixel.l + 0.1;
			}
		}
	}
}
void Image::lighten(double amount) {
	for (unsigned x = 0; x < this->width(); x++) {
		for (unsigned y = 0; y < this->height(); y++) {
			HSLAPixel & pixel = this->getPixel(x, y);
			if (pixel.l + amount > 1) {
				pixel.l = 1;
			} else if (pixel.l + amount < 0) {
				pixel.l = 0;
			} else {
				pixel.l = pixel.l + amount;
			}
		}
	}
}
void Image::darken() {
	for (unsigned x = 0; x < this->width(); x++) {
		for (unsigned y = 0; y < this->height(); y++) {
			HSLAPixel & pixel = this->getPixel(x, y);
			if (pixel.l - 0.1 < 0) {
				pixel.l = 0;
			} else {
				pixel.l = pixel.l - 0.1;
			}
		}
	}
}
void Image::darken(double amount) {
	for (unsigned x = 0; x < this->width(); x++) {
		for (unsigned y = 0; y < this->height(); y++) {
			HSLAPixel & pixel = this->getPixel(x, y);
			if (pixel.l - amount > 1) {
				pixel.l = 1;
			} else if (pixel.l - amount < 0) {
				pixel.l = 0;
			} else {
				pixel.l = pixel.l - amount;
			}
		}
	}
}



void Image::saturate() {
	for (unsigned x = 0; x < this->width(); x++) {
		for (unsigned y = 0; y < this->height(); y++) {
			HSLAPixel & pixel = this->getPixel(x, y);
			if (pixel.s + 0.1 > 1) {
				pixel.s = 1;
			} else {
				pixel.s = pixel.s + 0.1;
			}
		}
	}
}
void Image::saturate(double amount) {
	for (unsigned x = 0; x < this->width(); x++) {
		for (unsigned y = 0; y < this->height(); y++) {
			HSLAPixel & pixel = this->getPixel(x, y);
			if (pixel.s + amount > 1) {
				pixel.s = 1;
			} else if (pixel.s + amount < 0) {
				pixel.s = 0;
			} else {
				pixel.s = pixel.s + amount;
			}
		}
	}
}
void Image::desaturate() {
	for (unsigned x = 0; x < this->width(); x++) {
		for (unsigned y = 0; y < this->height(); y++) {
			HSLAPixel & pixel = this->getPixel(x, y);
			if (pixel.s - 0.1 < 0) {
				pixel.s = 0;
			} else {
				pixel.s = pixel.s - 0.1;
			}
		}
	}
}
void Image::desaturate(double amount) {
	for (unsigned x = 0; x < this->width(); x++) {
		for (unsigned y = 0; y < this->height(); y++) {
			HSLAPixel & pixel = this->getPixel(x, y);
			if (pixel.s - amount > 1) {
				pixel.s = 1;
			} else if (pixel.s - amount < 0) {
				pixel.s = 0;
			} else {
				pixel.s = pixel.s - amount;
			}
		}
	}
}



void Image::grayscale() {
	for (unsigned x = 0; x < this->width(); x++) {
		for (unsigned y = 0; y < this->height(); y++) {
			HSLAPixel & pixel = this->getPixel(x, y);
			pixel.s = 0;
		}
	}
}
void Image::rotateColor(double degrees) {
	for (unsigned x = 0; x < this->width(); x++) {
		for (unsigned y = 0; y < this->height(); y++) {
			HSLAPixel & pixel = this->getPixel(x, y);
			int q = (pixel.h + degrees)/360;
			if (q > 0) {
				pixel.h = pixel.h + degrees - 360 * q;
			} else if (q < 0) {
				pixel.h = pixel.h + degrees - 360 * q;
				pixel.h = 360 + pixel.h;
			} else {
				if (pixel.h + degrees < 0) {
					pixel.h = 360 + pixel.h + degrees;
				} else {
					pixel.h = pixel.h + degrees;
				}
			}
		}
	}
}
void Image::illinify() {
	for (unsigned int x = 0; x < this->width(); x++) {
		for (unsigned int y = 0; y < this->height(); y++) {
			int a;
			int b;
			int iorange = 11;
			int iblue = 216;
			double mid = 77.5;			
			HSLAPixel & pixel = this->getPixel(x, y);
			if (pixel.h <= iblue) {
				a = abs(pixel.h - iorange);
				b = abs(pixel.h - iblue);
				if (a > b) {
					pixel.h = iblue;
				} else {
					pixel.h = iorange;
				}
			} else {
				if (pixel.h <= iblue + mid) {
					pixel.h = iblue;
				} else {
					pixel.h = iorange;
				}
			}
			
		}
	}
}


void Image::scale(double factor) {
	Image* old = new Image();
	*old = *this;	
	this->resize(this->width()*factor, this->height()*factor);

	

	for (unsigned int x = 0; x < this->width(); x++) {
		for (unsigned int y = 0; y < this->height(); y++) {
			HSLAPixel & oldpixel = old->getPixel((int)(x/factor), (int)(y/factor));
			HSLAPixel & pixel = this->getPixel(x, y);
			pixel.h = oldpixel.h;
			pixel.s = oldpixel.s;
			pixel.l = oldpixel.l;
			pixel.a = oldpixel.a;
		}
	}
}
void Image::scale(unsigned w, unsigned h) {
	Image* old = new Image();
	*old = *this;	
	this->resize(w, h);

	double xfactor = w / (double)(old->width());
	double yfactor = h / (double)(old->height());

	for (unsigned int x = 0; x < this->width(); x++) {
		for (unsigned int y = 0; y < this->height(); y++) {
			HSLAPixel & oldpixel = old->getPixel((int)(x/xfactor), (int)(y/yfactor));
			HSLAPixel & pixel = this->getPixel(x, y);
			pixel.h = oldpixel.h;
			pixel.s = oldpixel.s;
			pixel.l = oldpixel.l;
			pixel.a = oldpixel.a;
		}
	}	
}
