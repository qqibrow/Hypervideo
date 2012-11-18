#include "FileController.h"

using namespace std;

FileController::FileController(void)
{
	file = NULL;
}

FileController::FileController( std::string fileName, std::string openType)
{
	getFile(fileName, openType);
}


FileController::~FileController(void)
{
	fclose(file);
}

void FileController::getFile( std::string fileName, std::string openType )
{
	FILE* infile = fopen(fileName.c_str(), openType.c_str());
	if(!infile)
	{
		string errorInfo = string("can not open file: ") + fileName;
		fprintf(stderr,errorInfo.c_str());
	}
	file =  infile;
}

int FileController::getFileLength()
{
	if(!file)
	{
		string errorInfo = "File is NULL\n";
		fprintf(stderr,errorInfo.c_str());
		return -1;
	}

	fseek(file,0,SEEK_END);
	int length = ftell(file);
	rewind (file);
	return length;
}

bool FileController::readWholeFileInBuffer(char* buff )
{
	//buff should be a NULL pointer
	if (!file || !buff)
	{
		fprintf(stderr,"the file is empty or the buff is empty\n");
		return false;
	}
	int fileLength = getFileLength();
// 	get the size and allocate memory
// 		int fileLength = getFileLength();
// 		//buff = (char*)malloc(sizeof(char)*fileLength);
// 		buff = new char[fileLength];
// 		if (!buff)
// 		{
// 			fprintf(stderr,"cannot allocate memory to buff\n");
// 			delete[] buff;
// 			return false;
// 		}

	//read file into memory
	int result = fread(buff, 1, fileLength, file);
	if (result != fileLength)
	{
		fprintf(stderr,"cannot load because of reading error\n");
		delete[] buff;
		return false;
	}

	return true;

}

bool FileController::writeBuffTnFile( char* buff, int fileLength )
{
	if (file == NULL)
	{
		fprintf(stderr,"file pointer is NULL\n");
		return false;
	}
	rewind(file);
	int write = fwrite(buff, 1, fileLength, file);
	if(write == 0)
		return false;

	return true;
}
