#include "HyperLink.h"
#include <QtGlobal>
#include <algorithm>
#include <assert.h>
#ifdef DEBUG
#include <vld.h>
#endif
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

HyperLink::HyperLink( std::string name ):name(name),id(qrand()%0xefffffff),secondaryVideoName("")
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
	if(keyframes.size() == 1) return QRect();

	int upkeyframe,downkeyframe;
	int i;
	for(i = 0; i < keyframes.size() && keyframes[i].getKeyFrameNo() < frameNo; i++);

	if(i == 0 || i == keyframes.size())
		return  QRect();
	else if(i-1 >= 0)
	{
		int interpolateNo = keyframes[i].getKeyFrameNo()-keyframes[i-1].getKeyFrameNo();
		int topleft_x = keyframes[i-1].getArea().topleft.x() + (frameNo - keyframes[i-1].getKeyFrameNo()) * (keyframes[i].getArea().topleft.x() - keyframes[i-1].getArea().topleft.x()) / interpolateNo;
		int topleft_y = keyframes[i-1].getArea().topleft.y() + (frameNo - keyframes[i-1].getKeyFrameNo()) * (keyframes[i].getArea().topleft.y() - keyframes[i-1].getArea().topleft.y()) / interpolateNo;
		int bottomright_x = keyframes[i-1].getArea().bottomright.x() + (frameNo - keyframes[i-1].getKeyFrameNo()) * (keyframes[i].getArea().bottomright.x() - keyframes[i-1].getArea().bottomright.x()) / interpolateNo;
		int bottomright_y = keyframes[i-1].getArea().bottomright.y() + (frameNo - keyframes[i-1].getKeyFrameNo()) * (keyframes[i].getArea().bottomright.y() - keyframes[i-1].getArea().bottomright.y()) / interpolateNo;

		QRect rect;
		rect.setTopLeft(QPoint(topleft_x, topleft_y));
		rect.setBottomRight(QPoint(bottomright_x, bottomright_y));
		return rect;
	}
	else{
		assert(false && "this cannot happen");
		return QRect();
	}
}

int HyperLink::getSecondaryVideoStartFrame() const
{
	return this->secondaryFrameNumber;
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

