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
	void addKeyframe( std::string name, Keyframe key );
	bool linkNameExist(std::string name);
	void connectVideo( std::string name, int frames );
	void saveFile( std::string fileName );
	Video* getPrimaryVideo() const;
	 Video* getSecondaryVideo() const;
	 std::vector<std::string> getKeys();
	 bool valid();
	 void clear();
	 bool isKeyFrameExist( std::string listName, int frame );
	 void updateKeyFrame( std::string linkName, Keyframe key );
	 std::vector<Area> getAllBlocks( int frameNumber );
	 bool ifSaveFileValid();
private:
	Video* primaryVideo, *secondaryVideo;
	std::map<std::string, HyperLink> hyperlinkMap;
};

