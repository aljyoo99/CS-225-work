/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include "Image.h"

using namespace cs225;

class StickerSheet{
	public:
		StickerSheet(const Image &picture, unsigned max);
		~StickerSheet();
		StickerSheet(const StickerSheet &other);
		const StickerSheet & operator=(const StickerSheet &other);
		void changeMaxStickers(unsigned max);
		int addSticker(Image &sticker, unsigned x, unsigned y);
		bool translate(unsigned index, unsigned x, unsigned y);
		void removeSticker (unsigned index);
		Image * getSticker (unsigned index) const;
		Image render() const;
	private:
		unsigned int max_;
		Image background;
		int* xval;
		int* yval;
		int* imageCount;
		Image** sheet;
		unsigned int stickerCount;
		void destroy();
		void copy(const StickerSheet &other);

};
