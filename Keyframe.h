#pragma once
#include <ostream>

struct Point
{
	int x,y;
};

struct Area
{
	Point upleft, bottomright;
};


class Keyframe
{
public:
	Keyframe(void);
	Keyframe(Area a, int no);
	~Keyframe(void);
	friend std::ostream& operator<<(std::ostream& out, const Keyframe& keyframe);
private:
	int keyFrameNo;
	Area area;
};

