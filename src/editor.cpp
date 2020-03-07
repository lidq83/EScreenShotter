#include "editor.h"
#include "ui_editor.h"

extern Setting *setting;

Editor::Editor(QWidget *parent)
	: QWidget(parent),
	  ui(new Ui::Editor)
{
	ui->setupUi(this);
	this->setGeometry(setting->editorRect);
}

Editor::~Editor()
{
	setting->editorIsMax = true;
	if (!this->isMaximized())
	{
		setting->editorRect = this->geometry();
		setting->editorIsMax = false;
	}
	setting->save();

	delete ui;
}

void Editor::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event)

	QPainter painter(this);
}

void Editor::mousePressEvent(QMouseEvent *event)
{
	Q_UNUSED(event)
}

void Editor::mouseMoveEvent(QMouseEvent *event)
{
	Q_UNUSED(event)
}

void Editor::mouseReleaseEvent(QMouseEvent *event)
{
	Q_UNUSED(event)
}
