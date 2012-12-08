#include "HyperLink.h"
#include <QtGlobal>
#include <algorithm>

using namespace std;

struct comp {
	bool operator() (const Keyframe& i,const Keyframe& j) { return (i.getKeyFrameNo()<j.getKeyFrameNo());}
} compKeyFrame;

 std::ostream& operator<<( std::ostream& out, const HyperLink& hyperlink )
{
	out<<hyperlink.id<<"	"
		<<hyperlink.name<<"	    "
		<<hyperlink.keyframes.size()<<endl
		<<hyperlink.secondaryVideoName<<"	"
		<<hyperlink.secondaryFrameNumber<<endl;

	for( int i = 0; i < hyperlink.keyframes.size(); i++)
	{
		out<<hyperlink.keyframes[i];
	}
	return out;
}

HyperLink::HyperLink(void)
{
}

HyperLink::HyperLink( std::string name ):name(name),id(qrand()%0xefffffff)
{

}


HyperLink::~HyperLink(void)
{
}

void HyperLink::addKeyFrame( Keyframe key )
{
	this->keyframes.push_back(key);
	sort(keyframes.begin(), keyframes.end(), compKeyFrame);
}

void HyperLink::connectToVideo( string name, int frames )
{
	this->secondaryVideoName = name;
	this->secondaryFrameNumber = frames;
}

bool HyperLink::isFrameExist( int frame ) const
{
	return binary_search(keyframes.begin(), keyframes.end(), Keyframe(Area(),frame), compKeyFrame);
}


void HyperLink::updateKeyFrame( Keyframe key )
{
	for(vector<Keyframe>::iterator it = keyframes.begin(); it != keyframes.end();it++)
	{
		if(it->getKeyFrameNo() == key.getKeyFrameNo())
		{
			it->setArea(key.getArea());
		}
	}
}

Area HyperLink::getAreaOfFrame( int frameNo ) const
{
	for(vector<Keyframe>::const_iterator it = keyframes.begin(); it != keyframes.end();it++)
	{
		if(it->getKeyFrameNo() == frameNo)
		{
			return it->getArea();
		}
	}
	return Area();
}

QRect HyperLink::interpolateFrame( int frameNo ) const
{



	return QRect();
}

std::istream& operator>>( std::istream& in, HyperLink& link )
{
	int numOfkeyFrames;
	in>>link.id>>link.name>>numOfkeyFrames>>link.secondaryVideoName>>link.secondaryFrameNumber;
	Keyframe key;
	for(int i = 0; i < numOfkeyFrames; i++)
	{
		in>>key;
		link.keyframes.push_back(key);
	}
	return in;	
}
