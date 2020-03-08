#include "view.h"
#include "ui_editor.h"

extern Setting *setting;

View::View(QWidget *parent)
	: QWidget(parent),
	  layerTemp(nullptr),
	  modified(false)
{
}

View::~View()
{
}

void View::setPixmap(QPixmap pixmap)
{
	if (pixmap.width() <= 0 || pixmap.height() <= 0)
	{
		return;
	}

	for (int i = 0; i < layers.size(); i++)
	{
		delete layers.at(i);
	}
	layers.clear();

	this->pixmap = pixmap;

	this->setMinimumWidth(pixmap.width());
	this->setMinimumHeight(pixmap.height());
	this->setMaximumWidth(pixmap.width());
	this->setMaximumHeight(pixmap.height());
	this->resize(QSize(pixmap.width(), pixmap.height()));
}

void View::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event)

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	QRect rect;
	rect.setX(0);
	rect.setY(0);
	rect.setWidth(pixmap.width());
	rect.setHeight(pixmap.height());
	painter.drawPixmap(rect, pixmap);

	for (int i = 0; i < layers.size(); i++)
	{
		layers.at(i)->draw(&painter);
	}

	if (layerTemp != nullptr)
	{
		layerTemp->draw(&painter);
	}
}

void View::mousePressEvent(QMouseEvent *event)
{
	modified = true;
	QColor color(setting->penColorR, setting->penColorG, setting->penColorB, setting->penColorA);
	layerTemp = new Layer(setting->toolType, setting->penWidth, color);
	posStart = event->pos();
	posEnd = event->pos();
	layerTemp->setPixmapSize(pixmap.size());
	layerTemp->setPosStart(posStart);
	layerTemp->setPosEnd(posEnd);
	if (setting->toolType == 5)
	{
		this->update();
	}
}

void View::mouseMoveEvent(QMouseEvent *event)
{
	posEnd = event->pos();

	int x = posEnd.x() < posStart.x() ? posEnd.x() : posStart.x();
	int y = posEnd.y() < posStart.y() ? posEnd.y() : posStart.y();
	int x1 = posEnd.x() > posStart.x() ? posEnd.x() : posStart.x();
	int y1 = posEnd.y() > posStart.y() ? posEnd.y() : posStart.y();

	rectTemp.setX(x);
	rectTemp.setY(y);
	rectTemp.setWidth(abs(x1 - x));
	rectTemp.setHeight(abs(y1 - y));

	layerTemp->setRect(rectTemp);
	layerTemp->setPosStart(posStart);
	layerTemp->setPosEnd(posEnd);

	this->update();
}

void View::mouseReleaseEvent(QMouseEvent *event)
{
	Q_UNUSED(event)
	if (layerTemp != nullptr)
	{
		layers.append(layerTemp);
		layerTemp = nullptr;
	}
}

void View::savePixmap(QString filePath)
{
	QPixmap pixmapSave(pixmap.width(), pixmap.height());
	pixmapSave.fill(QColor(0, 0, 0, 0));
	QPainter painter(&pixmapSave);

	painter.setRenderHint(QPainter::Antialiasing);

	QRect rect;
	rect.setX(0);
	rect.setY(0);
	rect.setWidth(pixmap.width());
	rect.setHeight(pixmap.height());
	painter.drawPixmap(rect, pixmap);

	for (int i = 0; i < layers.size(); i++)
	{
		layers.at(i)->draw(&painter);
	}

	if (layerTemp != nullptr)
	{
		layerTemp->draw(&painter);
	}

	pixmapSave.save(filePath);
	
	modified = false;
}

bool View::isModified(void)
{
	return this->modified;
}