#include "qthelloworld.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	qtHelloWorld w;
	w.show();
	return a.exec();
}
