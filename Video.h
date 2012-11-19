#pragma once
#include <string>
#include <QImage>
#include <QPixmap>
#include "VideoProcessor.h"
#define IMAGE_W 176
#define IMAGE_H 144



class Video
{
public:
	Video(void);
	Video(std::string videoName);
	~Video(void);
	void goToframeNo( int frames );
	int getFrames();
	QImage getQimage();

private:
	std::string videoName;
	VideoProcessor videoProcessor;
	int totalFrames;

};

