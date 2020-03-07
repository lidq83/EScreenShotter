#ifndef _LAYER_H
#define _LAYER_H

#include <QObject>
#include <QRect>
#include <QColor>
#include <QPainter>

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
	void drawText(QPainter *painter);
	void drawHand(QPainter *painter);

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
};

#endif