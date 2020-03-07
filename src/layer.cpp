#include <math.h>
#include <QDebug>
#include "layer.h"

Layer::Layer(int type, int penWidth, QColor penColor)
	: type(type),
	  penWidth(penWidth),
	  penColor(penColor),
	  rect(rect),
	  posStart(-1, -1),
	  posEnd(-1, -1),
	  posPre(-1, -1)
{
}

Layer::~Layer()
{
}

void Layer::setPixmapSize(QSize size)
{
	pixmap = new QPixmap(size);
	painterPixmap = new QPainter(pixmap);
	pixmap->fill(QColor(0, 0, 0, 0));
}

void Layer::setRect(QRect rect)
{
	this->rect = rect;
}

void Layer::setPosStart(QPoint posStart)
{
	this->posStart = posStart;
}

void Layer::setPosEnd(QPoint posEnd)
{
	this->posEnd = posEnd;
}

void Layer::draw(QPainter *painter)
{
	switch (type)
	{
	case 0:
		drawRect(painter);
		break;
	case 1:
		drawEllipse(painter);
		break;
	case 2:
		drawLine(painter);
		break;
	case 3:
		drawArrow(painter);
		break;
	case 4:
		drawText(painter);
		break;
	case 5:
		drawHand(painter);
		break;
	default:
		break;
	}
}

void Layer::drawRect(QPainter *painter)
{
	QPen pen(penColor);
	pen.setWidth(penWidth);
	painter->setPen(pen);
	painter->drawRect(rect);
}

void Layer::drawEllipse(QPainter *painter)
{
	QPen pen(penColor);
	pen.setWidth(penWidth);
	painter->setPen(pen);
	painter->drawEllipse(rect);
}

void Layer::drawLine(QPainter *painter)
{
	QPen pen(penColor);
	pen.setWidth(penWidth);
	painter->setPen(pen);
	painter->drawLine(posStart, posEnd);
}

void Layer::drawArrow(QPainter *painter)
{
	QPen pen(penColor);
	pen.setWidth(penWidth);
	painter->setPen(pen);
	painter->drawLine(posStart, posEnd);

	float x1 = posStart.x();
	float y1 = posStart.y();
	float x2 = posEnd.x();
	float y2 = posEnd.y();

	float x = x2 - x1;
	float y = y2 - y1;

	float r = sqrtf(x * x + y * y);
	float cnt = 10;
	float stepX = x / r;
	float stepY = y / r;

	painter->setBrush(penColor);
	for (int i = 0; i < cnt; i++)
	{
		float cx = x2 - stepX * i * 4;
		float cy = y2 - stepY * i * 4;
		painter->drawEllipse(QPoint(cx, cy), i, i);
	}
	painter->setBrush(QColor(0, 0, 0, 0));
}

void Layer::drawText(QPainter *painter)
{
}

void Layer::drawHand(QPainter *painter)
{
	QPen pen(penColor);
	pen.setWidth(penWidth);
	painterPixmap->setPen(pen);
	if (posPre.x() < 0 || posPre.y() < 0)
	{
		this->posPre = posEnd;
	}
	painterPixmap->drawLine(posPre, posEnd);
	this->posPre = posEnd;

	painter->drawPixmap(rect, *pixmap, rect);
}