#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#define MAX 255
#define MIN 0

using namespace std;

class Image
{
public:
	char idLen, colorMapTy, 
		dataTyCode, colorMapDe, 
		bitsPerPix, ImageDesc;
	short w, h, colorMapOr, colorMapLen, xOr, yOr;
	unsigned char ***ptrImage;
	unsigned char ByteMe;
	struct Header
	{
		char idLength;
		char colorMapType;
		char dataTypeCode;
		short colorMapOrigin;
		short colorMapLength;
		char colorMapDepth;
		short xOrigin;
		short yOrigin;
		short width;
		short height;
		char bitsPerPixel;
		char imageDescriptor;
	};
	
	Image();
	~Image();

	void operator=(Header &obj);
	void operator=(Image &obj);

	void tasks(Image &image1, Image &image2, Image &image3, Image &newImage, unsigned int taskNum, string tracker);

	void writeHeader(string fileName, Image &image);
	void writeImage(string fileName, Image &image);

	void loadHeader(string fileName, Image &image);
	void loadImage(string fileName, Image &image);
	void loadFirstImage(string fileName, Image &image);

};