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
	if(!primaryVideo) delete primaryVideo;
	if(!secondaryVideo) delete secondaryVideo;
}

void Session::setPrimaryVideo( Video* primaryVideo )
{
	this->primaryVideo = primaryVideo;
}

void Session::setSecondaryVideo( Video* secondaryVideo )
{
	this->secondaryVideo = secondaryVideo;
}

void Session::addKeyframe( string name, Keyframe key )
{
	// find the hyperlink with name:name in the map
	map<string,HyperLink>::iterator it = hyperlinkMap.find(name);

	// it should find a result
	assert(it != hyperlinkMap.end());

	// find duplicate
	it->second.addKeyFrame(key);

}

// find the hyperlink according to the name, and then set its secondaryVideoName and connectedFrameNo
void Session::connectVideo( string name, int frames )
{
	//throw std::exception("The method or operation is not implemented.");
	map<string,HyperLink>::iterator it = hyperlinkMap.find(name);
	assert(it != hyperlinkMap.end());
	it->second.connectToVideo(this->getSecondaryVideo()->getVideoName(), frames);
}

void Session::saveFile( string fileName )
{	
	fileName = "a.txt";
	ofstream fout(fileName);
	for(map<string,HyperLink>::iterator it = hyperlinkMap.begin(); it != hyperlinkMap.end(); it++)
		fout<<it->second<<endl;
}

void Session::addHyperLink( std::string name, Keyframe keyframe )
{	
		HyperLink temp(name);
		temp.addKeyFrame(keyframe);
		hyperlinkMap.insert(pair<string, HyperLink>(name, temp));
}

Video* Session::getPrimaryVideo() const
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

 bool Session::valid()
 {
	return this->primaryVideo != NULL && this->secondaryVideo != NULL;
 }

 bool Session::isKeyFrameExist( string linkName, int frame )
 {
	 map<string,HyperLink>::iterator it = hyperlinkMap.find(linkName);
	 assert(it != hyperlinkMap.end());
	 return it->second.isFrameExist(frame);

 }

 void Session::updateKeyFrame( string linkName, Keyframe key )
 {
	 map<string,HyperLink>::iterator it = hyperlinkMap.find(linkName);
	 assert(it != hyperlinkMap.end());
	 return it->second.updateKeyFrame(key);
 }

 std::vector<Area> Session::getAllBlocks( int frameNumber )
 {
	std::vector<Area> areas;
	for(map<string,HyperLink>::const_iterator it = hyperlinkMap.begin(); it != hyperlinkMap.end(); it++)
	{
		areas.push_back(it->second.getAreaOfFrame(frameNumber));
	}
	assert(areas.size() == hyperlinkMap.size());
	return areas;
 }
