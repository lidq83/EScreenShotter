#include "dialog_text.h"

extern Setting *setting;

DialogText::DialogText(QDialog *parent)
	: QDialog(parent),
	  ui(new Ui::DialogText)
{
	ui->setupUi(this);

	ui->fontComboBox->setCurrentFont(QFont(setting->textFont));
	ui->spinBoxSize->setValue(setting->textSize);
	ui->chkItalic->setChecked(setting->textItalic);
	ui->chkBold->setChecked(setting->textBold);
}

DialogText::~DialogText()
{
	delete ui;
}

int DialogText::show()
{
	return QDialog::exec();
}

QString DialogText::getText(void)
{
	return ui->textEdit->toPlainText();
}

void DialogText::slotDialogCancel(void)
{
	this->done(0);
}

void DialogText::slotDialogOk(void)
{
	setting->textFont = ui->fontComboBox->currentFont().family();
	setting->textSize = ui->spinBoxSize->value();
	setting->textItalic = ui->chkItalic->isChecked();
	setting->textBold = ui->chkBold->isChecked();

	this->done(1);
}
