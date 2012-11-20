#include "HyperLink.h"

using namespace std;

struct comp {
	bool operator() (Keyframe& i,Keyframe& j) { return (i.getKeyFrameNo()<j.getKeyFrameNo());}
} compKeyFrame;

HyperLink::HyperLink(void)
{
}

HyperLink::HyperLink( std::string name ):name(name)
{

}


HyperLink::~HyperLink(void)
{
}

ostream& HyperLink::operator<<( ostream& out )
{
	out<<this->id<<"	"
		<<this->name<<"	    "
		<<keyframes.size()<<endl
		<<secondaryVideoName<<"	"
		<<secondaryFrameNumber<<endl;

	for( int i = 0; i < keyframes.size(); i++)
	{
			
	}
// 	for(vector<Keyframe>::iterator it = keyframes.begin(); it != keyframes.end(); it++)
// 	{
// 		out<<*it;
// 	}

	return out;
}

void HyperLink::addKeyFrame( Keyframe key )
{
	this->keyframes.push_back(key);
	sort(keyframes.begin(), keyframes.end(), compKeyFrame);
}
