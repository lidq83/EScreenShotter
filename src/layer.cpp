#include "layer.h"

extern Setting *setting;

Layer::Layer(int type, int penWidth, QColor penColor)
	: type(type),
	  penWidth(penWidth),
	  penColor(penColor),
	  rect(rect),
	  posStart(-1, -1),
	  posEnd(-1, -1),
	  posPre(-1, -1),
	  x_min(999999),
	  y_min(999999),
	  x_max(-999999),
	  y_max(-999999)
{
}

Layer::~Layer()
{
}

void Layer::setPixmapSize(QSize size)
{
	pixmap = new QPixmap(size);
	pixmap->fill(QColor(0, 0, 0, 0));
	painterPixmap = new QPainter(pixmap);
}

void Layer::setRect(QRect rect)
{
	this->rect = rect;
}

void Layer::setPosStart(QPoint posStart)
{
	this->posStart = posStart;

	int x = posStart.x();
	int y = posStart.y();

	x_min = x_min > x ? x : x_min;
	y_min = y_min > y ? y : y_min;

	x_max = x_max < x ? x : x_max;
	y_max = y_max < y ? y : y_max;
}

void Layer::setPosEnd(QPoint posEnd)
{
	this->posEnd = posEnd;

	int x = posEnd.x();
	int y = posEnd.y();

	x_min = x_min > x ? x : x_min;
	y_min = y_min > y ? y : y_min;

	x_max = x_max < x ? x : x_max;
	y_max = y_max < y ? y : y_max;
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
	float x0 = r;
	float y0 = 0;
	float angle = -getRotateAngle(x, y, x0, y0) * M_PI / 180.0;

	float linelen = setting->arrowLength;
	float x4 = -linelen;
	float y4 = -linelen / 2;
	float x5 = -linelen;
	float y5 = +linelen / 2;

	float x6 = x4 * cosf(angle) - y4 * sinf(angle);
	float y6 = x4 * sinf(angle) + y4 * cosf(angle);
	float x7 = x5 * cosf(angle) - y5 * sinf(angle);
	float y7 = x5 * sinf(angle) + y5 * cosf(angle);

	x6 += x2;
	y6 += y2;
	x7 += x2;
	y7 += y2;

	painter->drawLine(x2, y2, x6, y6);
	painter->drawLine(x2, y2, x7, y7);
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

	QRect rectDraw(x_min - penWidth, y_min - penWidth, x_max - x_min + penWidth * 2, y_max - y_min + penWidth * 2);
	painter->drawPixmap(rectDraw, *pixmap, rectDraw);
}

float Layer::getRotateAngle(float x1, float y1, float x2, float y2)
{
	const float epsilon = 1.0e-6;
	const float nyPI = acos(-1.0);
	float dist = 0;
	float dot = 0;
	float degree = 0;
	float angle = 0;

	dist = sqrt(x1 * x1 + y1 * y1);
	x1 /= dist;
	y1 /= dist;
	dist = sqrt(x2 * x2 + y2 * y2);
	x2 /= dist;
	y2 /= dist;
	dot = x1 * x2 + y1 * y2;
	if (fabs(dot - 1.0) <= epsilon)
	{
		angle = 0.0;
	}
	else if (fabs(dot + 1.0) <= epsilon)
	{
		angle = nyPI;
	}
	else
	{
		float cross = 0.0;
		angle = acos(dot);
		cross = x1 * y2 - x2 * y1;
		if (cross < 0)
		{
			angle = 2 * nyPI - angle;
		}
	}
	degree = angle * 180.0 / nyPI;
	return degree;
}