#ifndef _LAYER_H
#define _LAYER_H

#include <QObject>
#include <QRect>
#include <QColor>
#include <QPainter>
#include <math.h>
#include <QDebug>
#include "setting.h"

class Layer
{

public:
	Layer(int type, int penWidth, QColor penColor);
	~Layer();

	void setPixmapSize(QSize size);
	void setRect(QRect rect);
	void setPosStart(QPoint posStart);
	void setPosEnd(QPoint posEnd);

	void draw(QPainter *painter);

private:
	void drawRect(QPainter *painter);
	void drawEllipse(QPainter *painter);
	void drawLine(QPainter *painter);
	void drawArrow(QPainter *painter);
	void drawHand(QPainter *painter);
	float getRotateAngle(float x1, float y1, float x2, float y2);

private:
	int type;
	int penWidth;
	QColor penColor;
	QRect rect;
	QPoint posStart;
	QPoint posEnd;
	QPoint posPre;
	QPixmap *pixmap;
	QPainter *painterPixmap;

	int x_min;
	int y_min;
	int x_max;
	int y_max;
};

#endif