#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QScreen>
#include <QApplication>
#include <QDesktopWidget>
#include <QPaintEvent>
#include <QKeyEvent>
#include <QPainter>
#include <QEvent>
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
	bool event(QEvent *event);
	void paintEvent(QPaintEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);

private:
	Ui::Widget *ui;
	QPixmap originalPixmap;
	QPixmap cursorRectPixmap;
	QPixmap *pixmap;
	QPoint cursorPos;
	QPoint posStart;
	QPoint posEnd;
	QRect rectShot;
	Editor editor;
	int cursorSize;
	int cursorOriginSize;
};
#endif // WIDGET_H
