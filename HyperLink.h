#pragma once
#include <string>
#include "Keyframe.h"
#include <ostream>
#include <vector>
#include <Qrect>


class HyperLink
{
public:
	HyperLink(void);
	HyperLink(std::string name);
	~HyperLink(void);
	void addKeyFrame(Keyframe key);
	void connectToVideo( std::string name, int frames );
	friend std::ostream& operator<<(std::ostream& out, const HyperLink& link);
	friend std::istream& operator>>(std::istream& in,  HyperLink& link);
	bool isFrameExist( int frame ) const;
	void updateKeyFrame( Keyframe key );
	Area getAreaOfFrame(int frameNo) const;
	QRect interpolateFrame(int frameNo) const;
	std::string getSecondaryVideoName() const {return secondaryVideoName;};
int getSecondaryVideoStartFrame() const;
private:
	std::vector<Keyframe> keyframes;
	std::string name;
	int id;
	std::string secondaryVideoName; // secondaryVideoName
	int secondaryFrameNumber; 


};

