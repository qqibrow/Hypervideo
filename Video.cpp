#include "Video.h"
#include "FileController.h"
#include "Image.h"
#include <assert.h>
#ifdef DEBUG
#include <vld.h>
#endif
using namespace std;

Video::Video(void)
{
}

Video::Video( std::string videoName )
{
	this->videoName = videoName;
// 	VideoProcessor videoProcessor;
// 	assert(videoProcessor.init(IMAGE_W,IMAGE_H,videoName.c_str()));
// 	this->totalFrames = videoProcessor.getFileLength() /(IMAGE_H*IMAGE_W*3);
// 
// 		for( int i = 0; i < totalFrames; i++)
// 	{
// 		
// 		videoProcessor.getToFrame(i);
// 		imageVector.push_back(QImage((uchar*)videoProcessor.getImageData(), IMAGE_W, IMAGE_H, QImage::Format_RGB888));
// 	}



	FileController fileloader(videoName, "rb");
	int fileLength = fileloader.getFileLength();
//	buff = new char[fileLength = fileloader.getFileLength()];
	this->totalFrames = fileLength /(IMAGE_H*IMAGE_W*3);

	assert(fileloader.readWholeFileInBuffer(buff));
// 	
// 	MyImage image;
// 	image.setHeight(IMAGE_H);
// 	image.setWidth(IMAGE_W);
// 
// 	for( int i = 0; i < totalFrames; i++)
// 	{
// 		int offset = IMAGE_W*IMAGE_H*3*i;
// 		assert(image.ReadImageFromPointer(buff + offset));
// 		QImage image((uchar*)image.getImageData(),IMAGE_W, IMAGE_H, QImage::Format_RGB888 );
// 		imageVector.push_back(image);
// 	}
//	image.set

//	delete[] buff;
	curFrame = 0;
	setFrame(curFrame);
}


Video::~Video(void)
{

}

void Video::goToframeNo( int frame )
{
	assert( frame >= 0 && frame <= totalFrames);
	//this->videoProcessor.getToFrame(frame);
	setFrame(frame);
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

	//return QImage((uchar*)videoProcessor.getImageData(), IMAGE_W, IMAGE_H, QImage::Format_RGB888);
//	return imageVector[curFrame];
}

std::string Video::getVideoName() const
{
	return this->videoName;
}

bool Video::isEnd()
{
	return curFrame  == totalFrames-1;
}

int Video::getCurrentFrame() const
{
	return curFrame;
}

void Video::setFrame( int frame )
{
	curFrame = frame;
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