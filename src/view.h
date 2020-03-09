#ifndef _VIEW_H
#define _VIEW_H

#include <QWidget>
#include <QMainWindow>
#include <QPaintEvent>
#include <QPainter>
#include <QMouseEvent>
#include <QIcon>
#include <QScrollBar>
#include <QColor>
#include <QList>
#include <QPixmap>
#include <QAction>
#include <QActionGroup>
#include <QPen>
#include <QPoint>
#include <QSpinBox>
#include <QWheelEvent>
#include <QFileDialog>
#include <QList>
#include <QDebug>

#include "setting.h"
#include "layer.h"
#include "undo_redo.h"

class View : public QWidget
{
	Q_OBJECT

public:
	View(QWidget *parent = nullptr);
	~View();

	void setPixmap(QPixmap pixmap);
	void savePixmap(QString filePath);

	bool isModified(void);

	void undo(void);
	void redo(void);

	bool canUndo(void);
	bool canRedo(void);

signals:
	void doSomething(void);

protected:
	void paintEvent(QPaintEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);

private:
	bool modified;
	QPixmap pixmap;
	QRect rectTemp;
	QPoint posStart;
	QPoint posEnd;
	Layer *layerTemp;
	QList<Layer *> layers;
	UndoRedo undoredo;
};
#endif // WIDGET_H
