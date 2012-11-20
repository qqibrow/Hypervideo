#include "Keyframe.h"

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

int Keyframe::getKeyFrameNo()
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
