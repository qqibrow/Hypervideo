#pragma once
#include <string>


class Video
{
public:
	Video(void);
	~Video(void);
	static Video* loadVideo( std::string videoName );
	void primaryVideoGoto( int frames );
};

