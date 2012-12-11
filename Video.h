#pragma once
#include <string>
#include <QImage>
#include <QPixmap>
#include <vector>
#include "VideoProcessor.h"
#ifdef DEBUG
#include <vld.h>
#include <QList>
#endif
#define IMAGE_W 352
#define IMAGE_H 288



class Video
{
public:
	Video(void);
	Video(std::string videoName);
	~Video(void);
	void goToframeNo( int frames );
	std::string getVideoName() const;
	int getTotalFrames() const;
	bool isEnd();
	QImage getQimage() ;
	int getCurrentFrame() const;
	void setFrame(int frame);
	void ReadImageFromPointer( char* start );
private:
	std::string videoName;
	//VideoProcessor videoProcessor;
	int totalFrames;
	std::vector<QImage> imageVector;
	int curFrame;
	char buff[IMAGE_W*IMAGE_H*3*720];
	char data[IMAGE_W*IMAGE_H*3];
	char RGBbuf[IMAGE_W*IMAGE_H*3];
};

