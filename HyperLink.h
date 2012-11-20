#pragma once
#include <string>
#include "Keyframe.h"
#include <ostream>
#include <vector>

class HyperLink
{
public:
	HyperLink(void);
	HyperLink(std::string name);
	~HyperLink(void);
	void addKeyFrame(Keyframe key);
	void connectToVideo( std::string name, int frames );
	friend std::ostream& operator<<(std::ostream& out, const HyperLink& keyframe);
private:
	std::vector<Keyframe> keyframes;
	std::string name;
	int id;
	std::string secondaryVideoName; // secondaryVideoName
	int secondaryFrameNumber; 


};

