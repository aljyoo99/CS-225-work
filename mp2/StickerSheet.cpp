#include "cs225/HSLAPixel.h"
#include "StickerSheet.h"
#include "Image.h"

using namespace cs225;

StickerSheet::StickerSheet(const Image &picture, unsigned max)
{
	max_ = max;
	background = picture;
	xval = new int[max_];
	yval = new int[max_];
	imageCount = new int[max_];
	sheet = new Image*[max_];
	for (unsigned int i = 0; i < max_; i++) {
		imageCount[i] = 0;
		sheet[i] = nullptr;
	}
	stickerCount = 0;
}

StickerSheet::~StickerSheet()
{
	destroy();
}

StickerSheet::StickerSheet(const StickerSheet &other)
{
	copy(other);
}

const StickerSheet & StickerSheet::operator=(const StickerSheet &other)
{
	if (this == &other) {
		return *this;
	} else {
		destroy();
		copy(other);
		return *this;
	}
}

void StickerSheet::changeMaxStickers(unsigned max)
{
	if (max_ > max) {
		int* copyx = new int[max];
		int* copyy = new int[max];
		int* copyimageCount = new int[max];
		Image** copysheet = new Image*[max];
		for (unsigned int i = 0; i < max; i++) {
			copyx[i] = xval[i];
			copyy[i] = yval[i];
			copyimageCount[i] = imageCount[i];
			copysheet[i] = sheet[i];
		}
		for (unsigned int i = max; i < max_; i++) {
			delete sheet[i];
		}
		xval = new int[max];
		yval = new int[max];
		imageCount = new int[max];
		sheet = new Image*[max];
		for (unsigned int i = 0; i < max; i++) {
			xval[i] = copyx[i];
			yval[i] = copyy[i];
			imageCount[i] = copyimageCount[i];
			sheet[i] = copysheet[i];
		}
		delete[] copyx;
		delete[] copyy;
		delete[] imageCount;
		for (unsigned int i = 0; i < max; i++) {
			delete copysheet[i];
			copysheet[i] = nullptr;
		}
		delete[] copysheet;


	} else if (max_ < max) {
		int* copyx = new int[max_];
		int* copyy = new int[max_];
		int* copyimageCount = new int[max_];
		Image** copysheet = new Image*[max_];
		for (unsigned int i = 0; i < max_; i++) {
			copyx[i] = xval[i];
			copyy[i] = yval[i];
			copyimageCount[i] = imageCount[i];
			copysheet[i] = sheet[i];
		}
		xval = new int[max];
		yval = new int[max];
		imageCount = new int[max];
		sheet = new Image*[max];
		for (unsigned int i = 0; i < max_; i++) {
			xval[i] = copyx[i];
			yval[i] = copyy[i];
			imageCount[i] = copyimageCount[i];
			sheet[i] = copysheet[i];
		}
		delete[] copyx;
		delete[] copyy;
		delete[] imageCount;
		for (unsigned int i = 0; i < max_; i++) {
			delete copysheet[i];
			copysheet[i] = nullptr;
		}
		delete[] copysheet;
	}
}

int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y)
{
	if(stickerCount < max_) {
		for (unsigned int i = 0; i < max_; i++) {
			if (imageCount[i] == 0) {
				sheet[i] = new Image(sticker);
				xval[i] = x;
				yval[i] = y;
				stickerCount++;
				imageCount[i]++;
				return i;
			}
		}
	}
	return -1;
	
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y)
{
	if (index < max_ && imageCount[index] > 0) {
		xval[index] = x;
		yval[index] = y;
		return true;
	} else {
		return false;
	}
}

void StickerSheet::removeSticker (unsigned index)
{
	if (index < max_ && imageCount[index] > 0) {
		delete sheet[index];
		sheet[index] = nullptr;
		xval[index] = 0;
		yval[index] = 0;
		imageCount[index]--;
		stickerCount--;
	}
	
}

Image * StickerSheet::getSticker (unsigned index) const
{
	if (index < max_ && imageCount[index] > 0) {
		return sheet[index];
	} else {
		return NULL;
	}
}


Image StickerSheet::render() const
{
	unsigned int tempx;
	unsigned int tempy;
	unsigned int tempx2;
	unsigned int tempy2;
	for (unsigned int m = 0; m < max_; m++) {
		if (imageCount[m] > 0) {
			Image sticker = *sheet[m];
			tempx = xval[m] + sticker.width();
			tempy = yval[m] + sticker.height();
			if (background.width() < tempx) {
				tempx2 = tempx;
			}
			if (background.height() < tempy) {
				tempy2 = tempy;
			}
		}
	}
	Image *output = new Image(background);
	output->resize(tempx, tempy);
	for (unsigned int n = 0; n < max_; n++) {
		if (imageCount[n] > 0){
			Image sticker = *sheet[n];
			for (unsigned int i = xval[n]; i < xval[n] + sticker.width(); i++) {
				for (unsigned int j = yval[n]; j < yval[n] + sticker.height(); j++) {
					HSLAPixel &pixel = sticker.getPixel(i - xval[n], j - yval[n]);
					HSLAPixel &currP = background.getPixel(i, j);
						if (pixel.a != 0) {
							currP.h = pixel.h;
							currP.s = pixel.s;
							currP.l = pixel.l;
							currP.a = pixel.a;
						}
				}
			}	
		}
	}
	Image output2 = *output;
	delete output;
	output = NULL;

	return output2;
}


void StickerSheet::destroy()
{
	delete[] xval;
	delete[] yval;
	delete[] imageCount;
	for (unsigned int i = 0; i < max_; i++) {
		delete sheet[i];
		sheet[i] = nullptr;
	}
	delete[] sheet;
	xval = nullptr;
	yval = nullptr;
	imageCount = nullptr;
	sheet = nullptr;
}

void StickerSheet::copy(const StickerSheet &other)
{
	max_ = other.max_;
	background = other.background;
	for (unsigned int i = 0; i < max_; i++) {
		xval[i] = other.xval[i];
		yval[i] = other.yval[i];
		imageCount[i] = other.imageCount[i];
		if (other.sheet[i] != nullptr) {
			sheet[i] = other.sheet[i];
		} else {
			sheet[i] = nullptr;
		}
	}
	stickerCount = other.stickerCount;
}
