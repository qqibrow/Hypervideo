#include "Keyframe.h"
#ifdef DEBUG
#include <vld.h>
#endif
using namespace std;

Keyframe::Keyframe(void)
{
}

Keyframe::Keyframe( Area a, int no ):area(a),keyFrameNo(no)
{

}


Keyframe::~Keyframe(void)
{
}

int Keyframe::getKeyFrameNo() const
{
	return this->keyFrameNo;
}

ostream& operator<<(ostream& out, const Keyframe& keyframe)
{
	return out<<keyframe.keyFrameNo<<"	"
		<<keyframe.area.topleft.x()<<"	 "
		<<keyframe.area.topleft.y()
		<<"  "<<keyframe.area.bottomright.x()
		<<"  "<<keyframe.area.bottomright.y()<<endl;
}

std::istream& operator>>( std::istream& in, Keyframe& keyframe )
{
	in>>keyframe.keyFrameNo;
	int tlx,tly,brx,bry;
	in>>tlx>>tly>>brx>>bry;
	keyframe.setArea(Area(QPoint(tlx, tly), QPoint(brx, bry)));
	return in;
}
