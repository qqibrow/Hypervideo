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

ostream& operator<<(ostream& out, const Keyframe& keyframe)
{
	return out<<keyframe.keyFrameNo<<"	"
		<<keyframe.area.upleft.x<<"	 "
		<<keyframe.area.upleft.y
		<<"  "<<keyframe.area.bottomright.x
		<<"  "<<keyframe.area.bottomright.y<<endl;
}
