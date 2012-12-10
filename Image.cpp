//*****************************************************************************
//
// Image.cpp : Defines the class operations on images
//
// Author - Parag Havaldar
// Code used by students as starter code to display and modify images
//
//*****************************************************************************

#include "Image.h"
#include <ctime>
#include <random>
#ifdef DEBUG
#include <vld.h>
#endif

// Constructor and Desctructors
MyImage::MyImage() 
{
	Data = NULL;
	Width = -1;
	Height = -1;
	ImagePath[0] = 0;
	tempbuffer = NULL;
	RGBbuf = NULL;
}

MyImage::~MyImage()
{
	if ( Data )
		delete Data;

	if(tempbuffer)
		delete[] tempbuffer;

	if(RGBbuf)
		delete[] RGBbuf;
}


// Copy constructor
MyImage::MyImage( MyImage *otherImage)
{
	Height = otherImage->Height;
	Width  = otherImage->Width;
	Data   = new char[Width*Height*3];
	strcpy(otherImage->ImagePath, ImagePath );

	for ( int i=0; i<(Height*Width*3); i++ )
	{
		Data[i]	= otherImage->Data[i];
	}


}

MyImage::MyImage( int w, int h, char* data /*= NULL*/ )
{
	this->Width = w;
	this->Height = h;
	RGBbuf = new char[3*w*h];
	this->Data = data;
	ImagePath[0] = 0;
	tempbuffer = NULL;
}



// = operator overload
MyImage & MyImage::operator= (const MyImage &otherImage)
{
	Height = otherImage.Height;
	Width  = otherImage.Width;
	Data   = new char[Width*Height*3];
	strcpy( (char *)otherImage.ImagePath, ImagePath );

	for ( int i=0; i<(Height*Width*3); i++ )
	{
		Data[i]	= otherImage.Data[i];
	}
	
	return *this;

}


// MyImage::ReadImage
// Function to read the image given a path
bool MyImage::ReadImage()
{

	// Verify ImagePath
	if (ImagePath[0] == 0 || Width < 0 || Height < 0 )
	{
		fprintf(stderr, "Image or Image properties not defined");
		fprintf(stderr, "Usage is `Image.exe Imagefile w h`");
		return false;
	}
	
	// Create a valid output file pointer
	FILE *IN_FILE;
	IN_FILE = fopen(ImagePath, "rb");
	if ( IN_FILE == NULL ) 
	{
		fprintf(stderr, "Error Opening File for Reading");
		return false;
	}

	// Create and populate RGB buffers
	int i;
	char *Rbuf = new char[Height*Width]; 
	char *Gbuf = new char[Height*Width]; 
	char *Bbuf = new char[Height*Width]; 

	for (i = 0; i < Width*Height; i ++)
	{
		Rbuf[i] = fgetc(IN_FILE);
	}
	for (i = 0; i < Width*Height; i ++)
	{
		Gbuf[i] = fgetc(IN_FILE);
	}
	for (i = 0; i < Width*Height; i ++)
	{
		Bbuf[i] = fgetc(IN_FILE);
	}
	
	// Allocate Data structure and copy
	Data = new char[Width*Height*3];
	for (i = 0; i < Height*Width; i++)
	{
		Data[3*i]	= Rbuf[i];
		Data[3*i+1]	= Gbuf[i];
		Data[3*i+2]	= Bbuf[i];
	}

	// Clean up and return
	delete Rbuf;
	delete Gbuf;
	delete Bbuf;
	fclose(IN_FILE);

	return true;

}


bool MyImage::ReadImage( FILE* file )
{
	if ( file == NULL ) 
	{
		fprintf(stderr, "Error Opening File for Reading");
		return false;
	}

	const int DIS = Width*Height;
	char* RGBbuf = new char[ 3 * DIS ];

	int c = fgetc(file);
	int i = 0;
	
	while( c != EOF && i < 3 * DIS)
	{
		RGBbuf[i++] = c;
		c = fgetc(file);
	}

// 	int i = -1;
// 	char x;
// 
// 	do{
// 		x = fgetc(file);		
// 		RGBbuf[++i] = x;
// 
// 	}while( x != EOF && i < 3*DIS);



// 	while (x = fgetc(file) != EOF && i < 3 * DIS)
// 	{
// 		RGBbuf[i] = x;
// 		i++;
// 	}

	if( i < 3*DIS)
	{
		delete[] RGBbuf;
		return false;
	}


	if(Data == NULL)
		Data = new char[DIS*3];
	else
		memset(Data, 0, 3*DIS*sizeof(char));

	
	for( i = 0; i < DIS; i++)
	{
		Data[3*i] = RGBbuf[i+ 2*DIS];
		Data[3*i + 1] = RGBbuf[i + DIS];
		Data[3*i + 2] = RGBbuf[i];
	}

	delete[] RGBbuf;

	//FilterParam filter(1);
	//this->averageFiltering(filter);

	return true;
}



// MyImage functions defined here
bool MyImage::WriteImage()
{
	// Verify ImagePath
	// Verify ImagePath
	if (ImagePath[0] == 0 || Width < 0 || Height < 0 )
	{
		fprintf(stderr, "Image or Image properties not defined");
		return false;
	}
	
	// Create a valid output file pointer
	FILE *OUT_FILE;
	OUT_FILE = fopen(ImagePath, "wb");
	if ( OUT_FILE == NULL ) 
	{
		fprintf(stderr, "Error Opening File for Writing");
		return false;
	}

	// Create and populate RGB buffers
	int i;
	char *Rbuf = new char[Height*Width]; 
	char *Gbuf = new char[Height*Width]; 
	char *Bbuf = new char[Height*Width]; 

	for (i = 0; i < Height*Width; i++)
	{
		Bbuf[i] = Data[3*i];
		Gbuf[i] = Data[3*i+1];
		Rbuf[i] = Data[3*i+2];
	}

	
	// Write data to file
	for (i = 0; i < Width*Height; i ++)
	{
		fputc(Rbuf[i], OUT_FILE);
	}
	for (i = 0; i < Width*Height; i ++)
	{
		fputc(Gbuf[i], OUT_FILE);
	}
	for (i = 0; i < Width*Height; i ++)
	{
		fputc(Bbuf[i], OUT_FILE);
	}
	
	// Clean up and return
	delete Rbuf;
	delete Gbuf;
	delete Bbuf;
	fclose(OUT_FILE);

	return true;

}

bool MyImage::WriteImage( FILE* file )
{

	if ( file == NULL ) 
	{
		fprintf(stderr, "Error Opening File for Writing");
		return false;
	}

	if( Data == NULL)
	{
		fprintf(stderr, "Error no data exist");
		return false;
	}

	// Create and populate RGB buffers
	int i;
	char *Rbuf = new char[Height*Width]; 
	char *Gbuf = new char[Height*Width]; 
	char *Bbuf = new char[Height*Width]; 

	for (i = 0; i < Height*Width; i++)
	{
		Bbuf[i] = Data[3*i];
		Gbuf[i] = Data[3*i+1];
		Rbuf[i] = Data[3*i+2];
	}


	// Write data to file
	for (i = 0; i < Width*Height; i ++)
	{
		fputc(Rbuf[i], file);
	}
	for (i = 0; i < Width*Height; i ++)
	{
		fputc(Gbuf[i], file);
	}
	for (i = 0; i < Width*Height; i ++)
	{
		fputc(Bbuf[i], file);
	}

	// Clean up and return
	delete Rbuf;
	delete Gbuf;
	delete Bbuf;
//	fclose(OUT_FILE);

	return true;
}




// Here is where you would place your code to modify an image
// eg Filtering, Transformation, Cropping, etc.
bool MyImage::Modify()
{

	// TO DO by student
	static int x = 1;

	x = x + 10;

	for ( int i=0; i<Width*Height; i++ )
	{
		Data[3*i] = x%255;
		Data[3*i+1] = x%255;

	}

	return false;
}

bool MyImage::averageFiltering( FilterParam params )
{
	int a, b, i, j;
	double sumR, sumG, sumB;

	int radius = params.radius;


	if(tempbuffer == NULL)
		tempbuffer = new char[ Width*Height*3];

	memset(tempbuffer,0, sizeof(char)*Width*Height*3);

	for( a = radius; a < Height-radius; a++ )
		for( b = radius; b < Width-radius; b++ )
		{	
			sumR = sumG = sumB = 0;
			for( i = 0; i < 2*radius+1; i++ )
				for( j = 0; j < 2*radius+1; j++ )
				{
					sumR += (unsigned char)Data[ 3*((a-radius+i)*Width + b-radius+j) ];
					sumG += (unsigned char)Data[ 3*((a-radius+i)*Width + b-radius+j) + 1 ];
					sumB += (unsigned char)Data[ 3*((a-radius+i)*Width + b-radius+j) + 2 ];
				}

				int base = (2*radius+1)*(2*radius+1);
				tempbuffer[ 3*(a*Width+b) ] = sumR/base;
				tempbuffer[ 3*(a*Width+b) +1 ] = sumG/base;
				tempbuffer[ 3*(a*Width+b) +2 ] = sumB/base;

		}

		for( a = radius; a < Height-radius; a++ )
			for( b = radius; b < Width-radius; b++ )
			{
				Data[3*(a*Width+b)] = tempbuffer[3*(a*Width+b)];
				Data[3*(a*Width+b) + 1 ] = tempbuffer[3*(a*Width+b) + 1 ];
				Data[3*(a*Width+b) + 2 ] = tempbuffer[3*(a*Width+b) + 2 ];
			}




	return true;
}
// 
// #define filterWidth 3 
// #define filterHeight 3 
// 
// //declare image buffers 

bool MyImage::imageFilter()
{

// 	double filter[filterWidth][filterHeight] =  
// 	{ 
// 		1, 1, 1, 
// 		1, 1, 1, 
// 		1, 1, 1 
// 	}; 
// 
// 	image = Data;
// 	if(tempbuffer == NULL)
// 		tempbuffer = new char[ Width*Height*3];
// 
// 
// 	//apply the filter 
// 	for(int x = 0; x < Width; x++) 
// 		for(int y = 0; y < Height; y++) 
// 		{ 
// 			double red = 0.0, green = 0.0, blue = 0.0; 
// 
// 			//multiply every value of the filter with corresponding image pixel 
// 			for(int filterX = 0; filterX < filterWidth; filterX++) 
// 				for(int filterY = 0; filterY < filterHeight; filterY++) 
// 				{ 
// 					int imageX = (x - filterWidth / 2 + filterX + w) % w; 
// 					int imageY = (y - filterHeight / 2 + filterY + h) % h; 
// 					red += image[imageX][imageY].r * filter[filterX][filterY]; 
// 					green += image[imageX][imageY].g * filter[filterX][filterY]; 
// 					blue += image[imageX][imageY].b * filter[filterX][filterY]; 
// 				} 
// 
// 				//truncate values smaller than zero and larger than 255 
// 				result[x][y].r = min(max(int(factor * red + bias), 0), 255); 
// 				result[x][y].g = min(max(int(factor * green + bias), 0), 255); 
// 				result[x][y].b = min(max(int(factor * blue + bias), 0), 255);
// 		}  

	return true;
}



//************************************
// Method:    ReadImageFromPointer
// FullName:  MyImage::ReadImageFromPointer
// Access:    public 
// Returns:   @bool
// Qualifier:
// Parameter: char * start, a complete RRR...GGG...BBB... format data pointer
// CreateTime: 12/7/2012 
// Description: load a image to local variable Data, and change it format to RGBRGBRGB...
// Modified History: 
//************************************
bool MyImage::ReadImageFromPointer( char* start )
{
	
	const int DIS = Width*Height;

	if(!RGBbuf)
		RGBbuf = new char[DIS*3];

	memcpy(RGBbuf, start, DIS*3);

	if(Data == NULL)
		Data = new char[DIS*3];
	else
		memset(Data, 0, 3*DIS*sizeof(char));


	for( int i = 0; i < DIS; i++)
	{
		Data[3*i] = RGBbuf[i];
		Data[3*i + 1] = RGBbuf[i + DIS];
		Data[3*i + 2] = RGBbuf[i+2*DIS];
	}

	//delete[] RGBbuf;
	return true;
}

bool MyImage::WriteImageToPointer( char* start )
{
	if( Data == NULL)
	{
		fprintf(stderr, "Error no data exist");
		return false;
	}

	// Create and populate RGB buffers
	int i;
	char *Rbuf = new char[Height*Width]; 
	char *Gbuf = new char[Height*Width]; 
	char *Bbuf = new char[Height*Width]; 

	for (i = 0; i < Height*Width; i++)
	{
		Bbuf[i] = Data[3*i];
		Gbuf[i] = Data[3*i+1];
		Rbuf[i] = Data[3*i+2];
	}

	memcpy(start, Rbuf, Width*Height);
	memcpy(start +  Width*Height, Gbuf, Width*Height);
	memcpy(start + 2* Width*Height, Bbuf, Width*Height);

	// Clean up and return
	delete Rbuf;
	delete Gbuf;
	delete Bbuf;

	return true;
}

