#include "widget.h"
#include "ui_widget.h"

extern Setting *setting;

Widget::Widget(QWidget *parent)
	: QWidget(parent),
	  ui(new Ui::Widget),
	  cursorSize(180),
	  cursorOriginSize(30)
{
	ui->setupUi(this);

	QScreen *screen = QGuiApplication::primaryScreen();
	pixmap = new QPixmap(screen->size());
	originalPixmap = screen->grabWindow(0);

	QColor color(setting->bgColorR, setting->bgColorG, setting->bgColorB, setting->bgColorA);
	pixmap->fill(color);

	this->setCursor(Qt::CrossCursor);
	//this->setAttribute(Qt::WA_TranslucentBackground);
	this->setAttribute(Qt::WA_Hover);
}

Widget::~Widget()
{
	delete ui;
}

bool Widget::event(QEvent *event)
{
	if (event->type() == QEvent::HoverMove)
	{
		QHoverEvent *e = (QHoverEvent *)event;

		QRect rectOrigin;
		rectOrigin.setX(e->pos().x() - cursorOriginSize / 2);
		rectOrigin.setY(e->pos().y() - cursorOriginSize / 2);
		rectOrigin.setWidth(cursorOriginSize);
		rectOrigin.setHeight(cursorOriginSize);

		QPixmap pix = originalPixmap.copy(rectOrigin);
		cursorRectPixmap = pix.scaled(cursorSize, cursorSize);
		QPainter painter(&cursorRectPixmap);
		QPen pen(QColor(0, 0, 0));
		pen.setWidth(3);
		painter.setPen(pen);
		painter.drawLine(cursorSize / 2, 0, cursorSize / 2, cursorSize);
		painter.drawLine(0, cursorSize / 2, cursorSize, cursorSize / 2);

		pen.setColor(QColor(255, 255, 255));
		pen.setWidth(1);

		painter.setPen(pen);
		painter.drawLine(cursorSize / 2, 0, cursorSize / 2, cursorSize);
		painter.drawLine(0, cursorSize / 2, cursorSize, cursorSize / 2);

		cursorPos = e->pos();
		this->update();
		return true;
	}

	return QWidget::event(event);
}

void Widget::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event)

	QPainter painter(this);
	painter.drawPixmap(QRect(0, 0, originalPixmap.width(), originalPixmap.height()), originalPixmap);
	painter.drawPixmap(QRect(0, 0, pixmap->width(), pixmap->height()), *pixmap);

	int curX = cursorPos.x() + cursorOriginSize;
	if (curX + cursorRectPixmap.width() > originalPixmap.width())
	{
		curX = cursorPos.x() - cursorOriginSize - cursorRectPixmap.width();
	}

	int curY = cursorPos.y() + cursorOriginSize;
	if (curY + cursorRectPixmap.height() > originalPixmap.height())
	{
		curY = cursorPos.y() - cursorOriginSize - cursorRectPixmap.height();
	}

	painter.drawPixmap(QRect(curX, curY, cursorRectPixmap.width(), cursorRectPixmap.height()), cursorRectPixmap);
}

void Widget::mousePressEvent(QMouseEvent *event)
{
	if (event->buttons() == Qt::LeftButton)
	{
		posStart = event->pos();
	}
	else if (event->buttons() == Qt::RightButton)
	{
		posStart.setX(0);
		posStart.setY(0);
		posEnd.setX(pixmap->width());
		posEnd.setY(pixmap->height());
		rectShot = twoPoints2Rect(posStart, posEnd);
		QPainter painter(pixmap);
		painter.setCompositionMode(QPainter::CompositionMode_Clear);
		painter.fillRect(rectShot, Qt::transparent);
		this->update();
	}
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
	if (event->buttons() == Qt::LeftButton)
	{
		posEnd = event->pos();

		QColor color(setting->bgColorR, setting->bgColorG, setting->bgColorB, setting->bgColorA);
		pixmap->fill(color);

		QPainter painter(pixmap);

		rectShot = twoPoints2Rect(posStart, posEnd);

		painter.setCompositionMode(QPainter::CompositionMode_Clear);
		painter.fillRect(rectShot, Qt::transparent);

		painter.setCompositionMode(QPainter::CompositionMode_DestinationOver);

		QPen pen(QColor(255, 255, 255));

		int border1x = 1;
		int border1y = 1;
		int border2x = 2;
		int border2y = 2;

		pen.setWidth(border1x);
		painter.setPen(pen);
		painter.drawRect(QRect(rectShot.x() - border1x, rectShot.y() - border1y, rectShot.width() + border1x * 2, rectShot.height() + border1y * 2));

		pen.setColor(QColor(0, 0, 0));
		pen.setWidth(border2x);
		painter.setPen(pen);
		painter.drawRect(QRect(rectShot.x() - border2x, rectShot.y() - border2y, rectShot.width() + border2x * 2, rectShot.height() + border2y * 2));
	}
	else if (event->buttons() == Qt::RightButton)
	{
		posStart.setX(0);
		posStart.setY(0);
		posEnd.setX(pixmap->width());
		posEnd.setY(pixmap->height());
		rectShot = twoPoints2Rect(posStart, posEnd);
		QPainter painter(pixmap);
		painter.setCompositionMode(QPainter::CompositionMode_Clear);
		painter.fillRect(rectShot, Qt::transparent);
	}
	this->update();
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
	Q_UNUSED(event)

	QScreen *screen = QGuiApplication::primaryScreen();
	if (screen && rectShot.width() != 0 && rectShot.height() != 0)
	{
		QPixmap pixmap = originalPixmap.copy(rectShot);
		QDateTime current_date_time = QDateTime::currentDateTime();
		QString current_date = current_date_time.toString("yyyy-MM-dd_hh-mm-ss-zzz");
		QString path;
		path.append(setting->filePath);
		path.append(setting->fileName);
		path.append("_");
		path.append(current_date);
		path.append(".png");
		editor.setPixmap(pixmap, path);
		pixmap.save(path);
	}

	if (setting->editAfterShot)
	{
		this->close();

		if (setting->editorIsMax)
		{
			editor.showMaximized();
			return;
		}
		editor.show();
		return;
	}
	QApplication::exit();
}

void Widget::keyPressEvent(QKeyEvent *event)
{
	event->accept();
}

void Widget::keyReleaseEvent(QKeyEvent *event)
{
	event->accept();

	if (event->key() == Qt::Key_Escape)
	{
		QApplication::exit();
	}
}

QRect Widget::twoPoints2Rect(QPoint p1, QPoint p2)
{
	int x1 = p1.x();
	int y1 = p1.y();
	int x2 = p2.x();
	int y2 = p2.y();

	int x3 = x1 < x2 ? x1 : x2;
	int y3 = y1 < y2 ? y1 : y2;
	int x4 = x1 > x2 ? x1 : x2;
	int y4 = y1 > y2 ? y1 : y2;

	QRect rect(x3, y3, x4 - x3, y4 - y3);
	return rect;
}