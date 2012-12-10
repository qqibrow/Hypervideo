#include "Color.h"
#define colorNum 20

#define COLOR_INTERVAL ((360 / colorNum ) - 1)
using namespace std;

vector<QColor> ColorFactory::getListofColors()
{
	vector<QColor> colorlist;
	QColor color;
	for( int i = 0; i < colorNum; i++)
	{
		color.setHsv(i*COLOR_INTERVAL, 255,255);
		colorlist.push_back(color);
	}
	return colorlist;
}
