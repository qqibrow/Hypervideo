#include "HyperLink.h"

using namespace std;

HyperLink::HyperLink(void)
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
