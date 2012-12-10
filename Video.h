#pragma once
#include <string>
#include <QImage>
#include <QPixmap>
#include "VideoProcessor.h"
#ifdef DEBUG
#include <vld.h>
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
	void timeup();
	QImage getQimage() ;
	int getCurrentFrame() const;
	void setFrame(int frame);

private:
	std::string videoName;
	VideoProcessor videoProcessor;
	int totalFrames;
	int curFrame;
};

