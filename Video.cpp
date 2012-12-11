#include "Video.h"
#include "FileController.h"
#include <assert.h>

#ifdef DEBUG
#include <vld.h>
#endif
using namespace std;

Video::Video(void)
{
	buff = NULL;
}

Video::Video( std::string videoName )
{
	buff = new char[IMAGE_W*IMAGE_H*3*720];
	this->videoName = videoName;
	FileController fileloader(videoName, "rb");
	int fileLength = fileloader.getFileLength();
	this->totalFrames = fileLength /(IMAGE_H*IMAGE_W*3);

	assert(fileloader.readWholeFileInBuffer(buff));

	curFrame = 0;
}

Video::Video( Video& other )
{
	this->videoName = other.videoName;
	this->totalFrames = other.totalFrames;
	this->buff = new char[IMAGE_W*IMAGE_H*3*720];
	memcpy(buff, other.buff, IMAGE_W*IMAGE_H*3*720);
	this->curFrame = other.curFrame;

}


Video::~Video(void)
{
	if (buff)
	{
		delete[] buff;
		buff = NULL;
	}
}

void Video::goToframeNo( int frame )
{
	if(frame >= totalFrames)
		curFrame = totalFrames - 1;
	else curFrame = frame;
}

int Video::getTotalFrames() const
{
	return this->totalFrames;
}

QImage Video::getQimage() 
{
	int offset = IMAGE_W*IMAGE_H*3*curFrame;
	ReadImageFromPointer(buff + offset);
	return QImage((uchar*)data,IMAGE_W, IMAGE_H, QImage::Format_RGB888 );
}

std::string Video::getVideoName() const
{
	return this->videoName;
}

int Video::getCurrentFrame() const
{
	return curFrame;
}


void Video::ReadImageFromPointer( char* start )
{

	const int DIS = IMAGE_W*IMAGE_H;
	memcpy(RGBbuf, start, DIS*3);

	for( int i = 0; i < DIS; i++)
	{
		data[3*i] = RGBbuf[i];
		data[3*i + 1] = RGBbuf[i + DIS];
		data[3*i + 2] = RGBbuf[i+2*DIS];
	}
}