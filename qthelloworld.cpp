#include "qthelloworld.h"
 #include <QImage>
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
#include <QPainter>
#include <QEvent>
#include <QMouseEvent>
#include <assert.h>
#include "Color.h"

#ifdef DEBUG
#include <vld.h>
#endif


#define LEAK_TEST
using namespace std;

qtHelloWorld::qtHelloWorld(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags),firstTime(true)
{
	ui.setupUi(this);
	colors = ColorFactory::getListofColors();
	ui.primaryVideoView->setStyleSheet("border: 2px solid black");
	ui.secondaryVideoView->setStyleSheet("border: 2px solid black");
	connect(ui.addPrimaryVideoButton, SIGNAL(clicked()), this, SLOT(addPrimaryVideoClicked()));
	connect(ui.addSecondaryVideoButton, SIGNAL(clicked()), this, SLOT(addSecondVideoClicked()));
	connect(ui.primaryVideoSlider, SIGNAL(sliderReleased()),this,SLOT(primaryVideoSliderClicked()));
	connect(ui.secondaryVideoSlider, SIGNAL(sliderReleased()),this,SLOT(secondaryVideoSliderClicked()));
	connect(ui.createLinkButton, SIGNAL(clicked()), this, SLOT(addLinkClicked()));
	connect(ui.connectVideoButton, SIGNAL(clicked()), this, SLOT(connecVideoClicked()));
	connect(ui.saveFileButton, SIGNAL(clicked()), this, SLOT(saveFileClicked()));
}

qtHelloWorld::~qtHelloWorld()
{
	
}

void qtHelloWorld::addPrimaryVideoClicked()
{
	int ret = 0;
	if(!firstTime)
	{
		//construct a Qmessagebox

#ifdef LEAK_TEST
		QMessageBox msgBox;
		msgBox.setText("You are trying to start a new section, make sure you already saved");
		msgBox.setInformativeText("Do you want to continue?");
		msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
		msgBox.setDefaultButton(QMessageBox::No);
		ret = msgBox.exec();
#endif
	

		switch (ret) {
		case QMessageBox::Yes:
			reload();
			break;
		case QMessageBox::No:
			return;
			break;
		default:
			// should never be reached
			throw exception("should never be reached");
			break;
		}
	
	}

	//reload only if the videoName != "" && ret == yes

	
#ifdef LEAK_TEST
 	QString videoName = QFileDialog::getOpenFileName(this, tr("Open File"),
 		"/",tr("Video (*.rgb)"));
#endif

#ifndef LEAK_TEST
	static int xxx = 5;
	QString videoName = QString("vdo%1.rgb").arg(xxx++);
	std::string utf8_text = videoName.toUtf8().constData();
	session.setPrimaryVideo(new Video(utf8_text));
	ui.primaryVideoSlider->setRange(1,session.getPrimaryVideo()->getTotalFrames());
	//ui.primaryVideoView->get
	//ui.primaryVideoView->setFixedWidth()
	ui.primaryVideoView->setPixmap(QPixmap::fromImage(this->session.getPrimaryVideo()->getQimage()));
	firstTime = false;
	showQmessageBox("import primary video successfully");
	this->ui.primaryVideoSlider->setValue(40);
	primaryVideoSliderClicked();
#endif
	
	
	if(videoName != "" && (firstTime || ret == QMessageBox::Yes))
	{
		std::string utf8_text = videoName.toUtf8().constData();
		session.setPrimaryVideo(new Video(utf8_text));
		ui.primaryVideoSlider->setRange(1,session.getPrimaryVideo()->getTotalFrames());
		//ui.primaryVideoView->get
		//ui.primaryVideoView->setFixedWidth()
		ui.primaryVideoView->setPixmap(QPixmap::fromImage(this->session.getPrimaryVideo()->getQimage()));
		firstTime = false;
		showQmessageBox("import primary video successfully");
		this->ui.primaryVideoSlider->setValue(40);
		primaryVideoSliderClicked();
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

	showQmessageBox("import secondary video successfully");
}

void qtHelloWorld::primaryVideoSliderClicked()
{
	if(this->session.getPrimaryVideo() == NULL)
	{
		showQmessageBox("Sorry, you haven't set primary video yet");
		this->ui.primaryVideoSlider->setValue(0);
		return;
	}
	int value = this->ui.primaryVideoSlider->value();
	session.getPrimaryVideo()->goToframeNo(value);

	//set the background 
	curImg = drawAllHyperlinkBlocks(value);
	ui.primaryVideoView->setPixmap(QPixmap::fromImage(curImg));
}

void qtHelloWorld::secondaryVideoSliderClicked()
{
	if(this->session.getSecondaryVideo() == NULL)
	{
		showQmessageBox("Sorry, you haven't set secondary video yet");
		this->ui.secondaryVideoSlider->setValue(0);
		return;
	}
	int value = this->ui.secondaryVideoSlider->value();
	session.getSecondaryVideo()->goToframeNo(value);
	ui.secondaryVideoView->setPixmap(QPixmap::fromImage(this->session.getSecondaryVideo()->getQimage()));
	
}


void qtHelloWorld::finishDrawingRectangle()
{
}

void qtHelloWorld::connecVideoClicked()
{
	string name = getSelectedItemText();
	if(name == "")
	{
		showQmessageBox("please select a hyperlink first");
		return;
	}
	int frames = ui.secondaryVideoSlider->value();

	if(!session.valid())
	{
		showQmessageBox("please add both videos first");
		return;
	}	
	else 
		session.connectVideo(name, frames);

	string info = "connect hyperlink " + name + " to current secondary video successfully";
	showQmessageBox(info.c_str());
}

void qtHelloWorld::saveFileClicked()
{
	//show check every hyperlink should all have secondary video 

	if (!(this->session.valid() && this->session.ifSaveFileValid()))
	{
		showQmessageBox("sorry, you must set primary video and all the secondary videos for the hyperlink first");
		return;
	}


	string fileName = this->session.getPrimaryVideo()->getVideoName() + ".meta";
	session.saveFile(fileName);
	string info = "save file " + fileName + " to the same directory of primaryVideo successfully";
	showQmessageBox(info.c_str());
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
//	curImg = this->session.getPrimaryVideo()->getQimage();	

	//QMessageBox::information(NULL, "Title", QString(info.c_str()), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

//	this->ui->primaryVideoView->rect();
}

void qtHelloWorld::mouseMoveEvent( QMouseEvent * event )
{
	if (!last.isNull())
	{
		QPoint cur = event->pos() - ui.primaryVideoView->pos();
		QRect rec(last, cur);
		QImage backImage = curImg.copy();
		drawRectOnImage(backImage, rec, Qt::blue);
		ui.primaryVideoView->setPixmap(QPixmap::fromImage(backImage));
	}
}

void qtHelloWorld::mouseReleaseEvent( QMouseEvent * event )
{
	
	if (!last.isNull())
	{
		//set the new Rectangle
		QPoint cur = event->pos() - ui.primaryVideoView->pos();
		ui.primaryVideoView->clear();

		QRect rec;
		if(last.x() > cur.x() && last.y() > cur.y())
		{
			rec.setTopLeft(cur);
			rec.setBottomRight(last);
		}
		else
		{
			rec.setBottomRight(cur);
			rec.setTopLeft(last);
		}

	//	QRect rec(last, cur);

		CurKeyFrameRect = rec;

		QList<QListWidgetItem *> list = ui.listWidget->selectedItems();
		assert(list.size() < 2);

		QImage bg = curImg.copy();
		if(list.empty())
			drawRectOnImage(bg, rec, Qt::red);
		else
		{
			bool changed = false;
			string listName = list[0]->text().toUtf8().constData();
			int frame = ui.primaryVideoSlider->value();
			Area area(CurKeyFrameRect);
			Keyframe key(area, frame);

			if(session.isKeyFrameExist(listName, frame))
			{
				switch(QMessageBox::question(NULL, "Title","keyframe exist. do you want to change that one?", 
					QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes)
				)
				{
				case QMessageBox::Yes:
					session.updateKeyFrame(listName,key);
					changed = true;
					break;
				default:
					break;
				}			
			}
			else
			{
				session.addKeyframe(listName,key);
				changed = true;
				QMessageBox::information(NULL, "Title",QString("added a keyframe to a hyperlink:") + list[0]->text(), QMessageBox::Yes, QMessageBox::Yes);
			}
			if(changed)
				bg = curImg = drawAllHyperlinkBlocks(this->ui.primaryVideoSlider->value());			
		}
		ui.primaryVideoView->setPixmap(QPixmap::fromImage(bg));
	}
}

bool qtHelloWorld::insidePrimaryWidget(QPoint& p)
{
	QRect rect = ui.primaryVideoView->rect();
	return rect.contains(p);
}

void qtHelloWorld::addLinkClicked()
{
	if(this->session.getPrimaryVideo() == NULL)
	{
		showQmessageBox("You haven't set a primary video yet");
		return;
	}

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
		if(!ok)
			return;

		if (text.isEmpty())
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

QImage qtHelloWorld::drawAllHyperlinkBlocks( int frameNumber )
{
	vector<Area> areas = session.getAllBlocks(frameNumber);
	QImage backImage = session.getPrimaryVideo()->getQimage().copy();

	for(int i = 0; i < areas.size(); i++)
	{
		if(!(areas[i].topleft.isNull() && areas[i].bottomright.isNull()))
		{
			QRect rec(areas[i].topleft, areas[i].bottomright);
			drawRectOnImage(backImage, rec, colors[i]);
		}
	}
	return backImage;
}

void qtHelloWorld::drawRectOnImage( QImage& image, QRect& rec, QColor color )
{
	QPainter* painter = new QPainter(&image); 
	painter->setPen(color);
	painter->drawRect(rec);
	delete painter;
}

void qtHelloWorld::showQmessageBox( const QString info )
{
#ifdef LEAK_TEST
	QMessageBox::information(NULL, "Title",info, QMessageBox::Yes, QMessageBox::Yes);
#endif
	
}

void qtHelloWorld::reload()
{
	//throw std::exception("The method or operation is not implemented.");
	this->session.clear();
	ui.listWidget->clear();
}

