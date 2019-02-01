#include "cs225/PNG.h"
using cs225::PNG;

#include "cs225/HSLAPixel.h"
using cs225::HSLAPixel;

#include <string>

PNG* setupOutput(unsigned w, unsigned h) {
	PNG* image = new PNG(w, h);
	return image;
}

void rotate(std::string inputFile, std::string outputFile) {
	PNG original;
	original.readFromFile(inputFile);

	unsigned width = original.width();
	unsigned height = original.height();
	PNG output = *(setupOutput(width, height));

	for (unsigned x = 0; x < width; x++) {
		for (unsigned y = 0; y < height; y++) {
			// Calculate the pixel difference
			HSLAPixel &pixel = original.getPixel(x, y);
			HSLAPixel &outPixel = output.getPixel(width - 1 - x, height - 1 - y);
			outPixel = pixel;
		}
	}
	output.writeToFile(outputFile);

}

PNG myArt(unsigned int width, unsigned int height) {
	PNG png(width, height);
	for (unsigned x = 0; x < width/3; x++) {
		for (unsigned y = 0; y < height; y++) {
			// Calculate the pixel difference
			HSLAPixel &pixel = png.getPixel(x, y);
			pixel.h = 161.171;
			pixel.s = 1;
			pixel.l = 0.2208;
			pixel.a = 1;
		}
	}

	for (unsigned x = 2*width/3; x < width; x++) {
		for (unsigned y = 0; y < height; y++) {
			// Calculate the pixel difference
			HSLAPixel &pixel = png.getPixel(x, y);
			pixel.h = 350.962;
			pixel.s = 0.8333;
			pixel.l = 0.4208;
			pixel.a = 1;
		}
	}	

	return png;
}
