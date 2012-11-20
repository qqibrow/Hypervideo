#include "Session.h"
#include <fstream>
#include <assert.h>
#include <string>
using namespace std;

Session::Session(void):primaryVideo(NULL),secondaryVideo(NULL)
{
}


Session::~Session(void)
{
}

void Session::setPrimaryVideo( Video* primaryVideo )
{
	this->primaryVideo = primaryVideo;
}

void Session::setSecondaryVideo( Video* secondaryVideo )
{
	//throw std::exception("The method or operation is not implemented.");
	this->secondaryVideo = secondaryVideo;
}

void Session::primaryVideoGoto( int frames )
{
	this->videoGoto(primaryVideo, frames);
}

void Session::secondaryVideoGoto( int frames )
{
	this->videoGoto(secondaryVideo,frames);
}

void Session::addKeyframe( string name, Keyframe key )
{
	// find the hyperlink with name:name in the map
	map<string,HyperLink>::iterator it;
	it = hyperlinkMap.find(name);
	if( it == hyperlinkMap.end()) // doesn't find 
	{
		HyperLink temp(name);
		temp.addKeyFrame(key);
		hyperlinkMap.insert(pair<string, HyperLink>(name, temp));
	}
	else
		it->second.addKeyFrame(key);
}

void Session::connectVideo( string name, int frames )
{
	throw std::exception("The method or operation is not implemented.");
}

void Session::saveFile( string fileName )
{
	//throw std::exception("The method or operation is not implemented.");
	ofstream fout(fileName);
	// map shuchu
	
}

void Session::addHyperLink( std::string name, Keyframe keyframe )
{

}

void Session::videoGoto( Video* video, int frames )
{
	video->goToframeNo(frames);
}

int Session::getPrimaryVideoLength()
{
	return getVideoLength(this->primaryVideo);
}

int Session::getVideoLength( Video* video )
{
	return video->getFrames();
}

int Session::getSecondaryVideoLength()
{
	return getVideoLength(this->secondaryVideo);
}

Video* Session::getPrimaryVideo()
{
	assert(primaryVideo != NULL);
	return primaryVideo;
}

 Video* Session::getSecondaryVideo() const
{
	assert(secondaryVideo != NULL);
	return secondaryVideo;
}

 bool Session::linkNameExist( std::string name )
 {
	 if(hyperlinkMap.empty())
		 return false;

	 map<string,HyperLink>::iterator it = hyperlinkMap.find(name);
	 return it != hyperlinkMap.end();
 }

 vector<string> Session::getKeys()
 {
	vector<string> strs;
	if( hyperlinkMap.empty())
		return strs;
	for(map<string, HyperLink>::iterator it = hyperlinkMap.begin(); it != hyperlinkMap.end(); it++)
	{
		strs.push_back(it->first);
	}
	return strs;
 }
