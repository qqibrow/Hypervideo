#include "Video.h"
#include <assert.h>

using namespace std;

Video::Video(void)
{
}

Video::Video( std::string videoName )
{
	this->videoName = videoName;
	assert(videoProcessor.init(IMAGE_W,IMAGE_H,videoName.c_str()));
	this->totalFrames = videoProcessor.getFileLength() /(IMAGE_H*IMAGE_W*3);
	setFrame(0);
}


Video::~Video(void)
{

}

void Video::goToframeNo( int frame )
{
	assert( frame >= 0 && frame <= totalFrames);
	this->videoProcessor.getToFrame(frame);
	setFrame(frame);
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

bool Video::isEnd()
{
	return curFrame  == totalFrames;
}

void Video::timeup()
{
	setFrame(curFrame+1);
	this->videoProcessor.getToFrame(curFrame+1);
	assert(curFrame <= totalFrames);
}

int Video::getCurrentFrame() const
{
	return curFrame;
}

void Video::setFrame( int frame )
{
	curFrame = frame;
}
