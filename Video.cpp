#include "Video.h"
#include <assert.h>

using namespace std;

Video::Video(void)
{
}

Video::Video( std::string videoName )
{
	this->videoName = videoName;
	videoProcessor.init(IMAGE_W,IMAGE_H,videoName.c_str());
	this->totalFrames = videoProcessor.getFileLength() /(IMAGE_H*IMAGE_W*3);
}


Video::~Video(void)
{

}

void Video::goToframeNo( int frames )
{
	assert( frames >= 0 && frames <= totalFrames);
	this->videoProcessor.getToFrame(frames);
}

int Video::getTotalFrames() const
{
	return this->totalFrames;
}

QImage Video::getQimage() 
{
	return QImage((uchar*)videoProcessor.getImageData(), IMAGE_W, IMAGE_H, QImage::Format_RGB888);
}

std::string Video::getVideoName() const
{
	return this->videoName;
}
