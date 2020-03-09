#ifndef EDITOR_H
#define EDITOR_H

#include <QWidget>
#include <QMainWindow>
#include <QPaintEvent>
#include <QCloseEvent>
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
#include <QMessageBox>
#include <QWheelEvent>
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

	void setPixmap(QPixmap pixmap, QString filePath);

protected slots:
	void slotToolChanged(QAction *action);
	void slotColorChanged(QAction *action);
	void slotPenWidthChanged(int width);
	void slotActionOpen(void);
	void slotActionSave(void);
	void slotActionSaveAs(void);
	void slotActionUndo(void);
	void slotActionRedo(void);
	void slotDoSomething(void);

protected:
	void closeEvent(QCloseEvent *event);

private:
	void initToolBar(void);
	void initDrawColor(QAction *action, QColor color);

private:
	Ui::Editor *ui;
	QActionGroup toolsGroup;
	QActionGroup colorsGroup;

	QAction *currTool;
	QAction *currColor;

	QString filePath;

	int toolType;
	int colorType;
};
#endif // WIDGET_H
