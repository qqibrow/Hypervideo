#pragma once
#include <string>
#include "Keyframe.h"
#include <ostream>
#include <vector>
#include <Qrect>


//************************************

// Description: HyperLink consists a set of keyFrames and is responsible to maintain these keyframes. 
// Usually, one set of KeyFrames is the motion of one object in the video. 
//************************************
class HyperLink
{
public:
	HyperLink(void);
	HyperLink(std::string name);
	~HyperLink(void);
	void addKeyFrame(Keyframe key);

	//************************************
	// Method:    connectToVideo
	// FullName:  HyperLink::connectToVideo
	// Access:    public 
	// Returns:   @void
	// Parameter: std::string name // the name of the video it links
	// Parameter: int frames    // the frame of the link start
	// Description:  save the linked video name and frame
	//************************************
	void connectToVideo( std::string name, int frames );
			//************************************
	// Method:    operator<<
	// Access:    public 
	// Returns:   std::ostream&
	// Parameter: std::ostream & out
	// Parameter: const HyperLink & link
	// Description: serialize the HyperLink so that it can output to file
	//************************************
	friend std::ostream& operator<<(std::ostream& out, const HyperLink& link);
			//************************************
	// Method:    operator>>
	// Access:    public 
	// Returns:   std::istream&
	// Parameter: std::istream & in
	// Parameter:  HyperLink & link
	// Description: serialize the HyperLink so that it can be imported from file
	//************************************
	friend std::istream& operator>>(std::istream& in,  HyperLink& link);

	//************************************
	// Method:    isFrameExist
	// FullName:  HyperLink::isFrameExist
	// Access:    public 
	// Returns:   @bool
	// Qualifier: const
	// Parameter: int frame
	// Description: check whether there is a frame on this frame No.
	//************************************
	bool isFrameExist( int frame ) const;
	//************************************
	// Method:    updateKeyFrame
	// FullName:  HyperLink::updateKeyFrame
	// Access:    public 
	// Returns:   @void
	// Qualifier:
	// Parameter: Keyframe key	
	// Description: update the keyFrame with the same frame No.
	//************************************
	void updateKeyFrame( Keyframe key );
	// get  the Area of this Frame given this frame No.
	Area getAreaOfFrame(int frameNo) const;
	
	//************************************
	// Method:    interpolateFrame
	// FullName:  HyperLink::interpolateFrame
	// Access:    public 
	// Returns:   @QT_NAMESPACE::QRect
	// Qualifier: const
	// Parameter: int frameNo
	// Description: interpolate the area based on its neighbor frames
	//************************************
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

