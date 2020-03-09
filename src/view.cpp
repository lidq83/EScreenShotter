#include "view.h"
#include "ui_editor.h"

extern Setting *setting;

View::View(QWidget *parent)
	: QWidget(parent),
	  layerTemp(nullptr),
	  modified(false)
{
}

View::~View()
{
}

void View::setPixmap(QPixmap pixmap)
{
	if (pixmap.width() <= 0 || pixmap.height() <= 0)
	{
		return;
	}

	for (int i = 0; i < layers.size(); i++)
	{
		delete layers.at(i);
	}
	layers.clear();

	this->pixmap = pixmap;

	this->setMinimumWidth(pixmap.width());
	this->setMinimumHeight(pixmap.height());
	this->setMaximumWidth(pixmap.width());
	this->setMaximumHeight(pixmap.height());
	this->resize(QSize(pixmap.width(), pixmap.height()));
}

void View::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event)

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	QRect rect;
	rect.setX(0);
	rect.setY(0);
	rect.setWidth(pixmap.width());
	rect.setHeight(pixmap.height());
	painter.drawPixmap(rect, pixmap);

	for (int i = 0; i < layers.size(); i++)
	{
		layers.at(i)->draw(&painter);
	}

	if (layerTemp != nullptr)
	{
		layerTemp->draw(&painter);
	}
}

void View::mousePressEvent(QMouseEvent *event)
{
	if (setting->toolType == 5)
	{
		return;
	}

	modified = true;
	QColor color(setting->penColorR, setting->penColorG, setting->penColorB, setting->penColorA);
	layerTemp = new Layer(setting->toolType, setting->penWidth, color);
	posStart = event->pos();
	posEnd = event->pos();
	layerTemp->setPixmapSize(pixmap.size());
	layerTemp->setPosStart(posStart);
	layerTemp->setPosEnd(posEnd);
	if (setting->toolType == 4)
	{
		this->update();
	}
}

void View::mouseMoveEvent(QMouseEvent *event)
{
	if (setting->toolType == 5)
	{
		return;
	}

	posEnd = event->pos();

	int x = posEnd.x() < posStart.x() ? posEnd.x() : posStart.x();
	int y = posEnd.y() < posStart.y() ? posEnd.y() : posStart.y();
	int x1 = posEnd.x() > posStart.x() ? posEnd.x() : posStart.x();
	int y1 = posEnd.y() > posStart.y() ? posEnd.y() : posStart.y();

	rectTemp.setX(x);
	rectTemp.setY(y);
	rectTemp.setWidth(abs(x1 - x));
	rectTemp.setHeight(abs(y1 - y));

	layerTemp->setRect(rectTemp);
	layerTemp->setPosStart(posStart);
	layerTemp->setPosEnd(posEnd);

	this->update();
}

void View::mouseReleaseEvent(QMouseEvent *event)
{
	if (setting->toolType == 5)
	{
		this->setAttribute(Qt::WA_Hover, false);
	}

	if (layerTemp != nullptr)
	{
		layers.append(layerTemp);
		layerTemp = nullptr;

		undoredo.doSomething(&layers);
		emit doSomething();
	}
}

bool View::event(QEvent *event)
{
	if (event->type() == QEvent::HoverEnter)
	{
		QHoverEvent *e = (QHoverEvent *)event;
		layerTemp->setPosStart(e->pos());
		this->update();
		return true;
	}
	else if (event->type() == QEvent::HoverMove)
	{
		QHoverEvent *e = (QHoverEvent *)event;
		layerTemp->setPosStart(e->pos());
		this->update();
		return true;
	}

	return QWidget::event(event);
}

void View::setText(QString text)
{
	QColor color(setting->penColorR, setting->penColorG, setting->penColorB, setting->penColorA);

	QFont font;
	font.setFamily(setting->textFont);
	font.setPointSize(setting->textSize);
	font.setItalic(setting->textItalic);
	font.setBold(setting->textBold);
	QFontMetrics fontMetrics(font);

	int textWidth = 0;
	int textHeight = 0;
	int textLineHeight = 0;

	QStringList lines = text.split("\n");
	for (int i = 0; i < lines.size(); i++)
	{
		QString text = lines.at(i);
		int w = fontMetrics.width(text);
		int h = fontMetrics.height();

		textWidth = textWidth < w ? w : textWidth;
		textLineHeight = textLineHeight < h ? h : textLineHeight;
	}
	textHeight = textLineHeight * lines.size();

	QPixmap textPixmap(textWidth, textHeight);
	textPixmap.fill(Qt::transparent);

	QTextOption option(Qt::AlignLeft | Qt::AlignTop);
	QPainter painterText(&textPixmap);
	painterText.setRenderHint(QPainter::Antialiasing);
	QPen pen(color);
	painterText.setPen(pen);
	painterText.setFont(font);

	for (int i = 0; i < lines.size(); i++)
	{
		QString text = lines.at(i);
		painterText.drawText(QRect(0, textLineHeight * i, textWidth * 2, textLineHeight), text, option);
	}

	setting->toolType = 5;
	layerTemp = new Layer(setting->toolType, setting->penWidth, color);
	layerTemp->setTextPixmap(textPixmap);
	layerTemp->setPixmapSize(pixmap.size());
	layerTemp->setPosStart(posStart);
	layerTemp->setPosEnd(posEnd);
	this->setAttribute(Qt::WA_Hover, true);

	if (setting->toolType == 5)
	{
		this->update();
	}
}

void View::savePixmap(QString filePath)
{
	QPixmap pixmapSave(pixmap.width(), pixmap.height());
	pixmapSave.fill(QColor(0, 0, 0, 0));
	QPainter painter(&pixmapSave);

	painter.setRenderHint(QPainter::Antialiasing);

	QRect rect;
	rect.setX(0);
	rect.setY(0);
	rect.setWidth(pixmap.width());
	rect.setHeight(pixmap.height());
	painter.drawPixmap(rect, pixmap);

	for (int i = 0; i < layers.size(); i++)
	{
		layers.at(i)->draw(&painter);
	}

	if (layerTemp != nullptr)
	{
		layerTemp->draw(&painter);
	}

	pixmapSave.save(filePath);

	modified = false;
}

bool View::isModified(void)
{
	return this->modified;
}

void View::undo(void)
{
	undoredo.undo();
	this->update();
}
void View::redo(void)
{
	undoredo.redo();
	this->update();
}

bool View::canUndo(void)
{
	return undoredo.canUndo();
}

bool View::canRedo(void)
{
	return undoredo.canRedo();
}