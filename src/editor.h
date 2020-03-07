#ifndef EDITOR_H
#define EDITOR_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QMouseEvent>
#include <QPen>
#include <QDebug>

#include "setting.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Editor; }
QT_END_NAMESPACE

class Editor : public QWidget
{
	Q_OBJECT

public:
	Editor(QWidget *parent = nullptr);
	~Editor();

protected:
	void paintEvent(QPaintEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);

private:
	Ui::Editor *ui;
};
#endif // WIDGET_H
