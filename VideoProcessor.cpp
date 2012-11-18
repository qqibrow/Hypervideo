#include "VideoProcessor.h"


#include "FileController.h"

#include <string>

using namespace std;

VideoProcessor::~VideoProcessor()
{
	delete[] buff;
}

bool VideoProcessor::getNextFrame()
{

	int h = image.getHeight();
	int w =  image.getWidth();

	// move the pointer to current image start position

	int offset = h * w * 3 * frames;
	if( offset == fileLength)
	{
		frames = 0;
		offset = 0;
	}
	char* currentStartPosition = buff + offset;
	++frames;

	return image.ReadImageFromPointer(currentStartPosition);
	
}

int VideoProcessor::getWidth()
{
	return image.getWidth();
}

int VideoProcessor::getHeight()
{
	return image.getHeight();
}

char* VideoProcessor::getImageData()
{
	return image.getImageData();
}

bool VideoProcessor::init( int w, int h, char* filePath )
{
	image.setWidth(w);
	image.setHeight(h);
	image.setImagePath(filePath);
	frames = 0;

	// read the file into buff
	FileController sss(filePath, "rb");
	buff = new char[fileLength = sss.getFileLength()];


	if(sss.readWholeFileInBuffer(buff))
		return true;
	else
	{
		return false;
	}
}

VideoProcessor::VideoProcessor()
{

}

