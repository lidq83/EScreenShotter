#ifndef __SRC_DIALOG_TEXT_H
#define __SRC_DIALOG_TEXT_H

#include <QDialog>
#include <QDebug>
#include <ui_dialog_text.h>
#include "setting.h"

namespace Ui
{
class DialogText;
}

class DialogText : public QDialog
{
	Q_OBJECT

public:
	explicit DialogText(QDialog *parent = 0);
	virtual ~DialogText(void);
	int show(void);
	QString getText(void);

protected slots:
	void slotDialogOk(void);
	void slotDialogCancel(void);

private:
	Ui::DialogText *ui;
};

#endif // __SRC_MAINWINDOW_NEWDOCDIALOG_H
