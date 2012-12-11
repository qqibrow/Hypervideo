#pragma once
#include <string>
#include <QPixmap>
#include <QImage>
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
	Video(Video& other);
	~Video(void);
	void goToframeNo( int frames );
	std::string getVideoName() const;
	int getTotalFrames() const;
	QImage getQimage() ;
	int getCurrentFrame() const;
	void ReadImageFromPointer( char* start );
private:
	std::string videoName;
	int totalFrames;
	int curFrame;
	char* buff;
	char data[IMAGE_W*IMAGE_H*3];
	char RGBbuf[IMAGE_W*IMAGE_H*3];
};

