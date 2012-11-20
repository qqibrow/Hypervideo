
#pragma once
#ifndef FileController_h__
#define FileController_h__



#include <string>

class FileController
{
public:
	FileController(void);
	~FileController(void);
	FileController(std::string fileName, std::string openType);
	void getFile(std::string fileName, std::string openType);
	int getFileLength();

	//read
	bool readWholeFileInBuffer(char* buff);
	

	// write image
	bool writeBuffTnFile(char* buff, int fileLength);
private:
	FILE* file;
};

#endif // FileController_h__