#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QScreen>
#include <QApplication>
#include <QDesktopWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QMouseEvent>
#include <QPen>
#include <QDateTime>
#include <QDesktopWidget>
#include <QDebug>

#include "setting.h"
#include "editor.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
	Q_OBJECT

public:
	Widget(QWidget *parent = nullptr);
	~Widget();

protected:
	void paintEvent(QPaintEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);

private:
	Ui::Widget *ui;
	QPixmap originalPixmap;
	QPixmap *pixmap;
	QPoint posStart;
	QPoint posEnd;
	QRect rectShot;
	Editor editor;
};
#endif // WIDGET_H
