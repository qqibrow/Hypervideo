#include "qthelloworld.h"
#include <QMessageBox>

using namespace std;

qtHelloWorld::qtHelloWorld(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	connect(ui.addButton, SIGNAL(clicked()), this, SLOT(pushButtonClicked()));
}

qtHelloWorld::~qtHelloWorld()
{

}

void qtHelloWorld::pushButtonClicked()
{
	 QMessageBox::information(this,"Button clicked!\n", "Warning");
}

void qtHelloWorld::addPrimaryVideoClicked()
{
	string videoName;
	Video* primaryVideo = Video::loadVideo(videoName);
	session.setPrimaryVideo(primaryVideo);
}

void qtHelloWorld::addSecondVideoClicked()
{
	string videoName;
	Video* secondaryVideo = Video::loadVideo(videoName);
	session.setSecondaryVideo(secondaryVideo);
}

void qtHelloWorld::primaryVideoSliderClicked()
{
	int frames;
	session.primaryVideoGoto(frames);
}

void qtHelloWorld::secondaryVideoSliderClicked()
{
	int frames;
	session.secondaryVideoGoto(frames);
}


void qtHelloWorld::finishDrawingRectangle()
{
	Area area; // check whether it's valid
	int frame;
	Keyframe key(area, frame);

	if( /* already selected a option in the list*/false)
	{
		string name; // get from the list
		session.addKeyframe(name, key); // pay attetion to sort the keyframes
	}
	else
	{
		// create a new hyperlink
		string hyperlikeName; // get from a popup window
		session.addHyperLink(hyperlikeName, key);
	}
}

void qtHelloWorld::connecVideoClicked()
{
	string name; // get from option in the list
	int frames; // get from secondaryVideo slider
	session.connectVideo(name, frames);
}

void qtHelloWorld::saveFileClicked()
{
	string fileName;
	session.saveFile(fileName);
}

void qtHelloWorld::updateView()
{

}

