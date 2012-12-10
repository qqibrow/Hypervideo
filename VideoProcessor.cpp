#include "VideoProcessor.h"
#include "FileController.h"
#ifdef DEBUG
#include <vld.h>
#endif
#include <string>
#include <assert.h>

using namespace std;

VideoProcessor::~VideoProcessor()
{
	if(buff) delete[] buff;
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

bool VideoProcessor::init( int w, int h, const char* filePath )
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

int VideoProcessor::getFileLength()
{
	return this->fileLength;
}

bool VideoProcessor::getToFrame( int value )
{
	this->frames = value;
	int h = image.getHeight();
	int w =  image.getWidth();

	// move the pointer to current image start position

	int offset = h * w * 3 * frames;
	if( offset == fileLength)
	{
	//	assert(false && "this means the video get the the last frame");
		frames = 0;
		offset = 0;
	}
	char* currentStartPosition = buff + offset;
	return image.ReadImageFromPointer(currentStartPosition);
}

