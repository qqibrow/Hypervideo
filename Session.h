#pragma once
#include "Video.h"
#include <map>
#include <string>
#include "HyperLink.h"
#include <vector>

class Session
{
public:
	Session(void);
	void addHyperLink(std::string name, Keyframe keyframe);
	~Session(void);
	void setPrimaryVideo( Video* primaryVideo );
	void setSecondaryVideo( Video* secondaryVideo );
	void primaryVideoGoto( int frames );
	void secondaryVideoGoto(int frames);
	void videoGoto(Video* video, int frames);
	void addKeyframe( std::string name, Keyframe key );
	bool linkNameExist(std::string name);
	void connectVideo( std::string name, int frames );
	void saveFile( std::string fileName );
	int getPrimaryVideoLength();
	int getVideoLength( Video* video );
	int getSecondaryVideoLength();
	Video* getPrimaryVideo();
	 Video* getSecondaryVideo() const;
	 std::vector<std::string> getKeys();
private:
	Video* primaryVideo, *secondaryVideo;
	std::map<std::string, HyperLink> hyperlinkMap;
};

