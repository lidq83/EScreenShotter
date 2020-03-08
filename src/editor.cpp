#include "editor.h"
#include "ui_editor.h"

extern Setting *setting;

Editor::Editor(QWidget *parent)
	: QMainWindow(parent),
	  ui(new Ui::Editor),
	  toolsGroup(this),
	  colorsGroup(this),
	  currTool(nullptr),
	  currColor(nullptr)
{
	ui->setupUi(this);
	this->setGeometry(setting->editorRect);

	initToolBar();
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

void Editor::initToolBar(void)
{
	QSpinBox *spin = new QSpinBox(this);
	spin->setMaximum(100);
	spin->setMinimum(1);
	spin->setValue(setting->penWidth);
	ui->toolBarTools->addWidget(spin);

	initDrawColor(ui->actionColorBlack, QColor(0, 0, 0));
	initDrawColor(ui->actionColorWhite, QColor(255, 255, 255));
	initDrawColor(ui->actionColorGray, QColor(128, 128, 128));
	initDrawColor(ui->actionColorRed, QColor(255, 0, 0));
	initDrawColor(ui->actionColorGreen, QColor(0, 255, 0));
	initDrawColor(ui->actionColorBlue, QColor(0, 0, 255));

	toolsGroup.addAction(ui->actionRect);
	toolsGroup.addAction(ui->actionEllipse);
	toolsGroup.addAction(ui->actionLine);
	toolsGroup.addAction(ui->actionArrow);
	toolsGroup.addAction(ui->actionText);
	toolsGroup.addAction(ui->actionDraw);

	colorsGroup.addAction(ui->actionColorBlack);
	colorsGroup.addAction(ui->actionColorWhite);
	colorsGroup.addAction(ui->actionColorGray);
	colorsGroup.addAction(ui->actionColorRed);
	colorsGroup.addAction(ui->actionColorGreen);
	colorsGroup.addAction(ui->actionColorBlue);
	colorsGroup.addAction(ui->actionColorCustom);

	connect(&toolsGroup, SIGNAL(triggered(QAction *)), this, SLOT(slotToolChanged(QAction *)));
	connect(&colorsGroup, SIGNAL(triggered(QAction *)), this, SLOT(slotColorChanged(QAction *)));

	ui->actionRect->setChecked(true);
	ui->actionColorRed->setChecked(true);

	slotToolChanged(ui->actionRect);
	slotColorChanged(ui->actionColorRed);
}

void Editor::initDrawColor(QAction *action, QColor color)
{
	QPixmap pixmap(128, 128);
	pixmap.fill(QColor(0, 0, 0, 0));
	QPainter painter(&pixmap);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setBrush(color);
	int spacing = 16;
	painter.drawEllipse(spacing, spacing, pixmap.width() - spacing * 2, pixmap.height() - spacing * 2);

	QIcon icon(pixmap);
	action->setIcon(icon);
}

void Editor::slotToolChanged(QAction *action)
{
	currTool = action;

	if (action == ui->actionRect)
	{
		toolType = 0;
	}
	else if (action == ui->actionEllipse)
	{
		toolType = 1;
	}
	else if (action == ui->actionLine)
	{
		toolType = 2;
	}
	else if (action == ui->actionArrow)
	{
		toolType = 3;
	}
	else if (action == ui->actionText)
	{
		toolType = 4;
	}
	else if (action == ui->actionDraw)
	{
		toolType = 5;
	}
	else
	{
		toolType = 0;
	}

	setting->toolType = toolType;
}

void Editor::slotColorChanged(QAction *action)
{
	currColor = action;

	if (action == ui->actionColorRed)
	{
		colorType = 0;
	}
	else if (action == ui->actionColorGreen)
	{
		colorType = 1;
	}
	else if (action == ui->actionColorBlue)
	{
		colorType = 2;
	}
	else if (action == ui->actionColorGray)
	{
		colorType = 3;
	}
	else if (action == ui->actionColorWhite)
	{
		colorType = 4;
	}
	else if (action == ui->actionColorBlack)
	{
		colorType = 5;
	}
	else if (action == ui->actionColorCustom)
	{
		colorType = 6;
	}
	else
	{
		colorType = 0;
	}

	switch (colorType)
	{
	case 0:
		setting->penColorR = 255;
		setting->penColorG = 0;
		setting->penColorB = 0;
		setting->penColorA = 255;
		break;

	case 1:
		setting->penColorR = 0;
		setting->penColorG = 255;
		setting->penColorB = 0;
		setting->penColorA = 255;

		break;

	case 2:
		setting->penColorR = 0;
		setting->penColorG = 0;
		setting->penColorB = 255;
		setting->penColorA = 255;

		break;

	case 3:
		setting->penColorR = 128;
		setting->penColorG = 128;
		setting->penColorB = 128;
		setting->penColorA = 255;

		break;

	case 4:
		setting->penColorR = 255;
		setting->penColorG = 255;
		setting->penColorB = 255;
		setting->penColorA = 255;

		break;

	case 5:
		setting->penColorR = 0;
		setting->penColorG = 0;
		setting->penColorB = 0;
		setting->penColorA = 255;

		break;

	case 6:
		//custom color
		break;

	default:
		break;
	}

	setting->save();
}

void Editor::setPixmap(QPixmap pixmap, QString filePath)
{
	if (pixmap.width() <= 0 || pixmap.height() <= 0)
	{
		return;
	}
	this->filePath = filePath;
	ui->view->setPixmap(pixmap);
}

void Editor::slotActionSave(void)
{
	ui->view->savePixmap(this->filePath);
}