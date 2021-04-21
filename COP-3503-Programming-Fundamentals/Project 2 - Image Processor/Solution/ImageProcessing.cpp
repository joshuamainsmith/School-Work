#include "ImageProcessing.h"

Image::Image()
{
	ptrImage = nullptr;
}

Image::~Image()
{
	delete[] ptrImage;
}

void Image::operator=(Header &obj)
{
	this->idLen = obj.idLength;
	this->colorMapTy = obj.colorMapType;
	this->dataTyCode = obj.dataTypeCode;
	this->colorMapOr = obj.colorMapOrigin;
	this->colorMapLen = obj.colorMapLength;
	this->colorMapDe = obj.colorMapDepth;
	this->xOr = obj.xOrigin;
	this->yOr = obj.yOrigin;
	this->h = obj.height;
	this->w = obj.width;
	this->bitsPerPix = obj.bitsPerPixel;
	this->ImageDesc = obj.imageDescriptor;
}

void Image::operator=(Image &obj)
{
	this->idLen = obj.idLen;
	this->colorMapTy = obj.colorMapTy;
	this->dataTyCode = obj.dataTyCode;
	this->colorMapOr = obj.colorMapOr;
	this->colorMapLen = obj.colorMapLen;
	this->colorMapDe = obj.colorMapDe;
	this->xOr = obj.xOr;
	this->yOr = obj.yOr;
	this->h = obj.h;
	this->w = obj.w;
	this->bitsPerPix = obj.bitsPerPix;
	this->ImageDesc = obj.ImageDesc;
}

void Image::tasks(Image &image1, Image &image2, Image &image3, Image &newImage, unsigned int task, string tracker)
{
	bool RoundTwo = true;
	string fileName = "output/part" + to_string(task);

	if (task == 8)
	{
		fileName = fileName + tracker;
	}

	if ((image1.h == image2.h) && (image1.w == image2.w))
	{
		newImage = image1;
	}
	
	if (newImage.ptrImage == nullptr)
	{
		newImage.ptrImage = new unsigned char**[newImage.w];

	}
	for (int i = 0; i < newImage.w; i++)
	{
		newImage.ptrImage[i] = new unsigned char*[newImage.h];

		for (int j = 0; j < newImage.h; j++)
		{
			newImage.ptrImage[i][j] = new unsigned char[3];

			for (int k = 0; k < 3; k++)
			{
				/*			Task 1, 3 and 4			*/
				/*			Multiplication			*/
				if (task == 1 || task == 3 || task == 4)
				{
					newImage.ptrImage[i][j][k] = (((float)(image1.ptrImage[i][j][k]) / MAX * (float)(image2.ptrImage[i][j][k]) / MAX) * MAX) + 0.5;
				}

				/*				Task 2				*/
				/*				Subtraction			*/
				else if (task == 2)
				{
					if (((int)(image2.ptrImage[i][j][k]) - (int)(image1.ptrImage[i][j][k])) >= 0)
					{
						newImage.ptrImage[i][j][k] = (int)(image2.ptrImage[i][j][k]) - (int)(image1.ptrImage[i][j][k]);
					}
					else
					{
						newImage.ptrImage[i][j][k] = MIN;
					}
				}

				/*				Task 5				*/
				/*				Overlay				*/
				else if (task == 5)
				{
					if (((float)(image2.ptrImage[i][j][k]) / MAX) <= 0.5)
					{
						newImage.ptrImage[i][j][k] = (2 * ((float)(image1.ptrImage[i][j][k]) / MAX * (float)(image2.ptrImage[i][j][k]) / MAX) * MAX) + 0.5;
					}
					else
					{
						newImage.ptrImage[i][j][k] = ((1 - 2 * ((1 - ((float)(image1.ptrImage[i][j][k]) / MAX)) * (1 - ((float)(image2.ptrImage[i][j][k])) / MAX))) * MAX) + 0.5;
					}

				}

				/*				Task 6				*/
				/*				Add Green			*/
				else if (task == 6)
				{
					if (k == 1)
					{
						if ((int)(image1.ptrImage[i][j][k]) + 200 <= MAX)
						{
							newImage.ptrImage[i][j][k] = (int)(image1.ptrImage[i][j][k]) + 200;
						}

						else
						{
							newImage.ptrImage[i][j][k] = MAX;
						}
					}
					else
					{
						newImage.ptrImage[i][j][k] = (int)(image1.ptrImage[i][j][k]);
					}
				}

				

				/*			Task 7			*/
				/*			Scale Red by 4, Blue by 0			*/
				else if (task == 7)
				{
					if (k == 2)
					{
						if ((int)(image1.ptrImage[i][j][k]) * 4 <= MAX)
						{
							newImage.ptrImage[i][j][k] = (int)(image1.ptrImage[i][j][k]) * 4;
						}

						else
						{
							newImage.ptrImage[i][j][k] = MAX;
						}
					}

					else if (k == 0)
					{
						newImage.ptrImage[i][j][k] = (int)(image1.ptrImage[i][j][k]) * 0;
					}
					else
					{
						newImage.ptrImage[i][j][k] = (int)(image1.ptrImage[i][j][k]);
					}
				}

				/*  Task 8  */
				else if (task == 8)
				{
					if (tracker == "_r")
					{
						int tmp = k + 2;
						newImage.ptrImage[i][j][k] = (int)(image1.ptrImage[i][j][tmp]);
						k++;
						newImage.ptrImage[i][j][k] = (int)(image1.ptrImage[i][j][tmp]);
						k++;
						newImage.ptrImage[i][j][k] = (int)(image1.ptrImage[i][j][tmp]);
					}

					else if (tracker == "_g")
					{
						int tmp = k + 1;
						newImage.ptrImage[i][j][k] = (int)(image1.ptrImage[i][j][tmp]);
						k++;
						newImage.ptrImage[i][j][k] = (int)(image1.ptrImage[i][j][tmp]);
						k++;
						newImage.ptrImage[i][j][k] = (int)(image1.ptrImage[i][j][tmp]);
					}

					else // (tracker == "_b")
					{
						int tmp = k;
						newImage.ptrImage[i][j][k] = (int)(image1.ptrImage[i][j][tmp]);
						k++;
						newImage.ptrImage[i][j][k] = (int)(image1.ptrImage[i][j][tmp]);
						k++;
						newImage.ptrImage[i][j][k] = (int)(image1.ptrImage[i][j][tmp]);
					}
				}

				/*  Task 9  */
				else if (task == 9)
				{
					if (k == 2)
					{
						newImage.ptrImage[i][j][k] = (int)(image1.ptrImage[i][j][k]);
					}
					else if (k == 1)
					{
						newImage.ptrImage[i][j][k] = (int)(image2.ptrImage[i][j][k]);
					}
					else if (k == 0)
					{
						newImage.ptrImage[i][j][k] = (int)(image3.ptrImage[i][j][k]);
					}
				}

				/* Task 10  */
				else if (task == 10)
				{
					newImage.ptrImage[i][j][k] = (int)(image1.ptrImage[image1.w - i - 1][image1.h - j - 1][k]);
				}
			}

		}
	}

	/*			 Round Two			    */
	if (task == 3 || task == 4)
	{
		Image newerImage;

		if (task == 3)
		{
			newerImage.loadHeader("input/text.tga", newerImage);
		}

		else if (task == 4)
		{
			newerImage.loadHeader("input/pattern2.tga", newerImage);
		}

		for (int i = 0; i < newerImage.w; i++)
		{
			for (int j = 0; j < newerImage.h; j++)
			{
				for (int k = 0; k < 3; k++)
				{
					/*			Screen			*/
					/*			Task 3			*/
					if (task == 3)
					{
						newImage.ptrImage[i][j][k] = ((1 - ((1 - ((float)(newerImage.ptrImage[i][j][k]) / MAX)) * (1 - ((float)(newImage.ptrImage[i][j][k])) / MAX))) * MAX) + 0.5;
					}

					/*			Subtraction			*/
					/*			Task 4			*/
					else if (task == 4)
					{
						if (((int)(newImage.ptrImage[i][j][k]) - (int)(newerImage.ptrImage[i][j][k])) >= 0)
						{
							newImage.ptrImage[i][j][k] = (int)(newImage.ptrImage[i][j][k]) - (int)(newerImage.ptrImage[i][j][k]);
						}
						else
						{
							newImage.ptrImage[i][j][k] = MIN;
						}
					}
				}
			}
		}
	}

	fileName = fileName + ".tga";

	writeHeader(fileName, newImage);

	

}

void Image::writeHeader(string fileName, Image &image)
{
	ofstream file(fileName, ios::out | ios::binary);

	file.write(&image.idLen, sizeof(image.idLen));
	file.write(&image.colorMapTy, sizeof(image.colorMapTy));
	file.write(&image.dataTyCode, sizeof(image.dataTyCode));
	file.write((char *)&image.colorMapOr, sizeof(image.colorMapOr));
	file.write((char *)&image.colorMapLen, sizeof(image.colorMapLen));
	file.write(&image.colorMapDe, sizeof(image.colorMapDe));
	file.write((char *)&image.xOr, sizeof(image.xOr));
	file.write((char *)&image.yOr, sizeof(image.yOr));
	file.write((char *)&image.w, sizeof(image.w));
	file.write((char *)&image.h, sizeof(image.h));
	file.write(&image.bitsPerPix, sizeof(image.bitsPerPix));
	file.write(&image.ImageDesc, sizeof(image.ImageDesc));

	writeImage(fileName, image);

	file.close();
}

void Image::writeImage(string fileName, Image &image)
{
	ofstream file(fileName, ios::out | ios::binary);
	file.seekp(18, ios::beg);

	for (int i = 0; i < image.w; i++)
	{
		for (int j = 0; j < image.h; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				ByteMe = image.ptrImage[i][j][k];
				file.write((char *)&ByteMe, sizeof(ByteMe));
			}
		}
	}

	file.close();

}


void Image::loadHeader(string fileName, Image &image)
{
	ifstream file(fileName, ios::in | ios::binary);

	Header headerObject;
	file.read(&headerObject.idLength, sizeof(headerObject.idLength));
	file.read(&headerObject.colorMapType, sizeof(headerObject.colorMapType));
	file.read(&headerObject.dataTypeCode, sizeof(headerObject.dataTypeCode));
	file.read((char *)&headerObject.colorMapOrigin, sizeof(headerObject.colorMapOrigin));
	file.read((char *)&headerObject.colorMapLength, sizeof(headerObject.colorMapLength));
	file.read(&headerObject.colorMapDepth, sizeof(headerObject.colorMapDepth));
	file.read((char *)&headerObject.xOrigin, sizeof(headerObject.xOrigin));
	file.read((char *)&headerObject.yOrigin, sizeof(headerObject.yOrigin));
	file.read((char *)&headerObject.width, sizeof(headerObject.width));
	file.read((char *)&headerObject.height, sizeof(headerObject.height));
	file.read(&headerObject.bitsPerPixel, sizeof(headerObject.bitsPerPixel));
	file.read(&headerObject.imageDescriptor, sizeof(headerObject.imageDescriptor));

	image = headerObject;

	if (ptrImage == nullptr)
	{
		Image::loadFirstImage(fileName, image);
	}
	else
	{
		Image::loadImage(fileName, image);

	}

	file.close();
}

void Image::loadFirstImage(string fileName, Image &image)
{
	ifstream file(fileName, ios::in | ios::binary);
	file.seekg(18, ios::beg);

	ptrImage = new unsigned char**[image.w];
	for (int i = 0; i < image.w; i++)
	{
		ptrImage[i] = new unsigned char*[image.h];

		for (int j = 0; j < image.h; j++)
		{
			ptrImage[i][j] = new unsigned char[3];

			for (int k = 0; k < 3; k++)
			{
				file.read((char *)&ByteMe, sizeof(ByteMe));
				ptrImage[i][j][k] = ByteMe;
			}

		}
	}	

	file.close();
}



void Image::loadImage(string fileName, Image &image)
{
	ifstream file(fileName, ios::in | ios::binary);
	file.seekg(18, ios::beg);

	for (int i = 0; i < image.w; i++)
	{
		for (int j = 0; j < image.h; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				file.read((char *)&ByteMe, sizeof(ByteMe));
				if (!ptrImage[i][j][k])
				{
					ptrImage = new unsigned char**[image.w];
					ptrImage[i] = new unsigned char*[image.h];
					ptrImage[i][j] = new unsigned char[3];
				}
				ptrImage[i][j][k] = ByteMe;
			}
		}
	}

	file.close();
}