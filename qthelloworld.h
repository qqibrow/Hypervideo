#ifndef QTHELLOWORLD_H
#define QTHELLOWORLD_H

#include <QtGui/QMainWindow>
#include "ui_qthelloworld.h"
#include "Video.h"
#include "Keyframe.h"
#include "HyperLink.h"
#include "Session.h"
#include <string>

class qtHelloWorld : public QMainWindow
{
	Q_OBJECT

public:
	qtHelloWorld(QWidget *parent = 0, Qt::WFlags flags = 0);
	~qtHelloWorld();
	
	protected slots:
		void pushButtonClicked();
		void addPrimaryVideoClicked();
		void addSecondVideoClicked();
		void primaryVideoSliderClicked();
		void secondaryVideoSliderClicked();
		void finishDrawingRectangle();
		void connecVideoClicked();
		void saveFileClicked();
		void updateView();
private:
	Ui::qtHelloWorldClass ui;
	Session session;
};

#endif // QTHELLOWORLD_H
