#ifndef VideoProcessor_h__
#define VideoProcessor_h__

#include "Image.h"


class VideoProcessor
{
public:
	VideoProcessor();
	bool init(int w, int h, const char* filePath);
	bool getNextFrame();
	bool getToFrame(int value);
	int getWidth();
	int getHeight();
	char* getImageData();

	~VideoProcessor();
	int getFileLength();
private:
	int frames;
	int fileLength;
	char* buff;
	MyImage image;
};



#endif // VideoProcessor_h__
