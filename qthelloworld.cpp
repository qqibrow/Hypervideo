#include "qthelloworld.h"
 #include <QImage>
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
#include <QPainter>
#include "..\src\gui\kernel\qevent.h"
#include <assert.h>
using namespace std;

qtHelloWorld::qtHelloWorld(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	// set CSS
	ui.primaryVideoView->setStyleSheet("border: 2px solid black");

	connect(ui.addPrimaryVideoButton, SIGNAL(clicked()), this, SLOT(addPrimaryVideoClicked()));
	connect(ui.addSecondaryVideoButton, SIGNAL(clicked()), this, SLOT(addSecondVideoClicked()));
	connect(ui.primaryVideoSlider, SIGNAL(sliderReleased()),this,SLOT(primaryVideoSliderClicked()));
	connect(ui.secondaryVideoSlider, SIGNAL(sliderReleased()),this,SLOT(secondaryVideoSliderClicked()));
	connect(ui.createLinkButton, SIGNAL(clicked()), this, SLOT(addLinkClicked()));
	connect(ui.connectVideoButton, SIGNAL(clicked()), this, SLOT(connecVideoClicked()));
	connect(ui.saveFileButton, SIGNAL(clicked()), this, SLOT(saveFileClicked()));
	//videoProcessor.init(176,144,"Incursion_176x144.rgb");

}

qtHelloWorld::~qtHelloWorld()
{
	
}

void qtHelloWorld::pushButtonClicked()
{
// 	videoProcessor.getNextFrame();
// 	QImage image((uchar*)videoProcessor.getImageData(), 176, 144, QImage::Format_RGB888);
// 	ui.label->setPixmap(QPixmap::fromImage(image));
//	ui.label->setText("hello world");
		
}

void qtHelloWorld::addPrimaryVideoClicked()
{
	QString videoName = QFileDialog::getOpenFileName(this, tr("Open File"),
		"/",tr("Video (*.rgb)"));
	
	if(videoName != "")
	{
		std::string utf8_text = videoName.toUtf8().constData();
		session.setPrimaryVideo(new Video(utf8_text));
		ui.primaryVideoSlider->setRange(1,session.getPrimaryVideo()->getTotalFrames());
		//ui.primaryVideoView->get
		//ui.primaryVideoView->setFixedWidth()
		ui.primaryVideoView->setPixmap(QPixmap::fromImage(this->session.getPrimaryVideo()->getQimage()));
	}
	
}

void qtHelloWorld::addSecondVideoClicked()
{

	QString videoName = QFileDialog::getOpenFileName(this, tr("Open File"),
		"/",tr("Images (*.rgb)"));
	if(videoName != "")
	{
		std::string utf8_text = videoName.toUtf8().constData();
		session.setSecondaryVideo(new Video(utf8_text));
		ui.secondaryVideoSlider->setRange(1,session.getSecondaryVideo()->getTotalFrames());
		ui.secondaryVideoView->setPixmap(QPixmap::fromImage(session.getSecondaryVideo()->getQimage()));
	}

	
}

void qtHelloWorld::primaryVideoSliderClicked()
{
	int value = this->ui.primaryVideoSlider->value();
	session.getPrimaryVideo()->goToframeNo(value);
	ui.primaryVideoView->setPixmap(QPixmap::fromImage(this->session.getPrimaryVideo()->getQimage()));
}

void qtHelloWorld::secondaryVideoSliderClicked()
{
	int value = this->ui.secondaryVideoSlider->value();
	session.getSecondaryVideo()->goToframeNo(value);
	ui.secondaryVideoView->setPixmap(QPixmap::fromImage(this->session.getSecondaryVideo()->getQimage()));
	
}


void qtHelloWorld::finishDrawingRectangle()
{
	if(CurKeyFrameRect.isNull())
		return;

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
	string name = getSelectedItemText();
	if(name == "")
	{
		QMessageBox::information(NULL, "Title","please select a hyperlink first", QMessageBox::Yes, QMessageBox::Yes);
		return;
	}
	int frames = ui.secondaryVideoSlider->value();

	if(!session.valid())
		QMessageBox::information(NULL, "Title","please add both videos first", QMessageBox::Yes, QMessageBox::Yes);
	else session.connectVideo(name, frames);
}

void qtHelloWorld::saveFileClicked()
{

	string fileName = this->session.getPrimaryVideo()->getVideoName() + ".meta";
	session.saveFile(fileName);
}

void qtHelloWorld::updateView()
{

}

void qtHelloWorld::mousePressEvent( QMouseEvent * event )
{
	QPoint p = event->pos() - ui.primaryVideoView->pos();
	//string info = "the current point position is " + std::to_string((long double)p.x()) + " , " + std::to_string((long double)p.y());
	if(insidePrimaryWidget(p))
		last = p;
	else
	{
		last.setX(0);
		last.setY(0);
	}
		//QMessageBox::information(NULL, "Title", QString(info.c_str()), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

//	this->ui->primaryVideoView->rect();
}

void qtHelloWorld::mouseMoveEvent( QMouseEvent * event )
{
	if (!last.isNull())
	{

		QPoint cur = event->pos() - ui.primaryVideoView->pos();
		ui.primaryVideoView->clear();
		QRect rec(last, cur);
		QImage backImage = session.getPrimaryVideo()->getQimage().copy();
		QPainter* painter = new QPainter(&backImage); 
		painter->setPen(Qt::blue);
		painter->drawRect(rec);
		ui.primaryVideoView->setPixmap(QPixmap::fromImage(backImage));
		delete painter;
	}
}

void qtHelloWorld::mouseReleaseEvent( QMouseEvent * event )
{
	
	if (!last.isNull())
	{
		QPoint cur = event->pos() - ui.primaryVideoView->pos();
		ui.primaryVideoView->clear();
		QRect rec(last, cur);
		QImage backImage = session.getPrimaryVideo()->getQimage().copy();
		QPainter* painter = new QPainter(&backImage);
		painter->setPen(Qt::red);
		painter->drawRect(rec);
		ui.primaryVideoView->setPixmap(QPixmap::fromImage(backImage));
		delete painter;
		CurKeyFrameRect = rec;

		QList<QListWidgetItem *> list = ui.listWidget->selectedItems();
		assert(list.size() < 2);
		if(!list.empty())
		{
			string listName = list[0]->text().toUtf8().constData();
			addKeyFrameToSession(listName);

			QMessageBox::information(NULL, "Title",QString("added a keyframe to a hyperlink:") + list[0]->text(), QMessageBox::Yes, QMessageBox::Yes);
		}
	}
}

bool qtHelloWorld::insidePrimaryWidget(QPoint& p)
{
	QRect rect = ui.primaryVideoView->rect();
	return rect.contains(p);
}

void qtHelloWorld::addLinkClicked()
{
	if (CurKeyFrameRect.isNull())
	{
		QMessageBox::information(NULL, "Title","please draw a rectangle first", QMessageBox::Yes, QMessageBox::Yes);
	}
	else
	{
		bool ok;
		QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
			tr("Link Name:"), QLineEdit::Normal,
			QDir::home().dirName(), &ok);

		string linkName;
		if (!ok || text.isEmpty())
		{
			QMessageBox::information(NULL, "Title","please input hyperlink name", QMessageBox::Yes, QMessageBox::Yes);
			return;
		}
		linkName = text.toUtf8().constData();
		if(session.linkNameExist(linkName))
		{
			QMessageBox::information(NULL, "Title","name exist,please choose another name", QMessageBox::Yes, QMessageBox::Yes);
			return;
		}

		Area area(CurKeyFrameRect);
		int frame = ui.primaryVideoSlider->value();

		Keyframe key(area, frame);
		session.addHyperLink(linkName,key);

		//update items in the list
		vector<string> list = session.getKeys();
		ui.listWidget->clear();
		for( int i = 0; i < list.size(); i++)
		{
// 			QListWidgetItem *newItem = new QListWidgetItem;
// 			newItem->setText(list[i]);
// 			ui.listWidget->insertItem(i, newItem);
			ui.listWidget->addItem(list[i].c_str());
		}

	}
}

void qtHelloWorld::addKeyFrameToSession( string linkName )
{
	Area area(CurKeyFrameRect);
	int frame = ui.primaryVideoSlider->value();

	Keyframe key(area, frame);
	session.addKeyframe(linkName,key);
}

std::string qtHelloWorld::getSelectedItemText()
{
	QList<QListWidgetItem *> list = ui.listWidget->selectedItems();
	assert(list.size() < 2);
	if(!list.empty())
		return list[0]->text().toUtf8().constData();
	else
		return "";
}

