#include "widget.h"
#include "ui_widget.h"

extern Setting *setting;

Widget::Widget(QWidget *parent)
	: QWidget(parent), ui(new Ui::Widget)
{
	ui->setupUi(this);

	QScreen *screen = QGuiApplication::primaryScreen();
	pixmap = new QPixmap(screen->size());
	originalPixmap = screen->grabWindow(0);

	QColor color(setting->bgColorR, setting->bgColorG, setting->bgColorB, setting->bgColorA);
	pixmap->fill(color);

	this->setCursor(Qt::CrossCursor);
	//this->setAttribute(Qt::WA_TranslucentBackground);
}

Widget::~Widget()
{
	delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event)

	QPainter painter(this);
	painter.drawPixmap(QRect(0, 0, originalPixmap.width(), originalPixmap.height()), originalPixmap);
	painter.drawPixmap(QRect(0, 0, pixmap->width(), pixmap->height()), *pixmap);
}

void Widget::mousePressEvent(QMouseEvent *event)
{
	posStart = event->pos();
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
	posEnd = event->pos();

	QColor color(setting->bgColorR, setting->bgColorG, setting->bgColorB, setting->bgColorA);
	pixmap->fill(color);

	QPainter painter(pixmap);

	rectShot = QRect(posStart.x(), posStart.y(), posEnd.x() - posStart.x(), posEnd.y() - posStart.y());
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

	if (rectShot.width() < 0)
	{
		border1x = -border1x;
		border2x = -border2x;
	}
	if (rectShot.height() < 0)
	{
		border1y = -border1y;
		border2y = -border2y;
	}

	painter.drawRect(QRect(rectShot.x() - border1x, posStart.y() - border1y, rectShot.width() + border1x * 2, rectShot.height() + border1y * 2));

	pen.setColor(QColor(0, 0, 0));
	pen.setWidth(border2x);
	painter.setPen(pen);
	painter.drawRect(QRect(rectShot.x() - border2x, posStart.y() - border2y, rectShot.width() + border2x * 2, rectShot.height() + border2y * 2));

	this->update();
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
	Q_UNUSED(event)

	QScreen *screen = QGuiApplication::primaryScreen();
	if (screen && rectShot.width() != 0 && rectShot.height() != 0)
	{
		QRect rect = rectShot;
		if (rectShot.width() < 0)
		{
			rect.setX(rectShot.x() + rectShot.width());
			rect.setWidth(-rectShot.width());
		}
		if (rectShot.height() < 0)
		{
			rect.setY(rectShot.y() + rectShot.height());
			rect.setWidth(-rectShot.height());
		}

		QPixmap pixmap = originalPixmap.copy(rect);
		QDateTime current_date_time = QDateTime::currentDateTime();
		QString current_date = current_date_time.toString("yyyy-MM-dd_hh-mm-ss-zzz");
		QString path;
		path.append(setting->filePath);
		path.append(setting->fileName);
		path.append("_");
		path.append(current_date);
		path.append(".png");
		pixmap.save(path);
		editor.setPixmap(pixmap, path);
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
