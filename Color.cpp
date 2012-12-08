#include "Color.h"
#define colorNum 20

using namespace std;

vector<QColor> ColorFactory::getListofColors()
{
	vector<QColor> colorlist;
	int QtColours[]= { 3,2,7,13,8,14,9, 15, 10, 16, 11, 17, 12, 18, 5, 4, 6, 19, 0, 1 };
	for( int i = 0; i < colorNum; i++)
	{
		colorlist.push_back(QColor(QtColours[i],0,QtColours[i]));
	}
	return colorlist;
}
