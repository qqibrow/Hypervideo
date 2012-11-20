#include "HyperLink.h"

using namespace std;

struct comp {
	bool operator() (Keyframe& i,Keyframe& j) { return (i.getKeyFrameNo()<j.getKeyFrameNo());}
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

HyperLink::HyperLink( std::string name ):name(name)
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
