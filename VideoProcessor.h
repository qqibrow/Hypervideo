#ifndef VideoProcessor_h__
#define VideoProcessor_h__

#include "Image.h"


class VideoProcessor
{
public:
	VideoProcessor();
	virtual bool init(int w, int h, const char* filePath);
	virtual bool getNextFrame();
	virtual bool getToFrame(int value);
	int getWidth();
	int getHeight();
	virtual char* getImageData();

	virtual ~VideoProcessor();
	int getFileLength();
protected:
	int frames;
	int fileLength;
	char* buff;
	MyImage image;
};



#endif // VideoProcessor_h__
