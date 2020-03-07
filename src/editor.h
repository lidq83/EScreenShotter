#ifndef EDITOR_H
#define EDITOR_H

#include <QWidget>
#include <QMainWindow>
#include <QPaintEvent>
#include <QPainter>
#include <QMouseEvent>
#include <QIcon>
#include <QColor>
#include <QList>
#include <QPixmap>
#include <QAction>
#include <QActionGroup>
#include <QPen>
#include <QSpinBox>
#include <QFileDialog>
#include <QList>
#include <QDebug>

#include "setting.h"
#include "layer.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class Editor;
}
QT_END_NAMESPACE

class Editor : public QMainWindow
{
	Q_OBJECT

public:
	Editor(QWidget *parent = nullptr);
	~Editor();

	void setPixmap(QPixmap pixmap, QString filePath = 0);

protected slots:
	void slotToolChanged(QAction *action);
	void slotColorChanged(QAction *action);
	void slotActionSave(void);

protected:
	void paintEvent(QPaintEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);

private:
	void initToolBar(void);
	void initDrawColor(QAction *action, QColor color);
	QColor getToolColor(void);

private:
	Ui::Editor *ui;
	QActionGroup toolsGroup;
	QActionGroup colorsGroup;
	QString filePath;

	QAction *currTool;
	QAction *currColor;

	int toolType;
	int colorType;

	QPixmap pixmap;
	QRect rectTemp;
	QPoint posStart;
	QPoint posEnd;
	Layer *layerTemp;

	QList<Layer *> layers;
};
#endif // WIDGET_H
