#pragma once
#include <string>
#include "Keyframe.h"
#include <ostream>
#include <vector>

class HyperLink
{
public:
	HyperLink(void);
	~HyperLink(void);
	std::ostream& operator<<(std::ostream& out);
private:
	std::vector<Keyframe> keyframes;
	std::string name;
	int id;
	std::string secondaryVideoName; // secondaryVideoName
	int secondaryFrameNumber; 


};

