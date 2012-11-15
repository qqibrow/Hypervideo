#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>
#include "ui_adddialog.h"

class AddDialog : public QDialog, public Ui::AddDialog
{
	Q_OBJECT

public:
	AddDialog(QWidget *parent = 0);
	~AddDialog();
};

#endif // ADDDIALOG_H
