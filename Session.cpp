#include "Session.h"
#include <fstream>

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
	throw std::exception("The method or operation is not implemented.");
	// get the hyperlink from the name in the map, and then add key to that hyperlink
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

}
