#pragma once
#include <iostream>
#include <QtCore>
struct Point
{
	Point():x(-1),y(-1){};
	Point(int mx,int my):x(mx),y(my){};
	Point(QPoint p):x(p.x()),y(p.y()){};
	int x,y;
};

struct Area
{
	Area(){};
	Area(QPoint tl, QPoint br): topleft(tl), bottomright(br){};
	Area(QRect rect):topleft(rect.topLeft()),bottomright(rect.bottomRight()){};
	QPoint topleft, bottomright;
};


class Keyframe
{
public:
	Keyframe(void);
	Keyframe(Area a, int no);
	~Keyframe(void);
	friend std::ostream& operator<<(std::ostream& out, const Keyframe& keyframe);
	friend std::istream& operator>>(std::istream& in, Keyframe& keyframe);
	int getKeyFrameNo() const;
	Area getArea() const { return area; }
	void setArea(Area val) { area = val; }
private:
	int keyFrameNo;
	Area area;
	
};

