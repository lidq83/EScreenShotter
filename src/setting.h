#ifndef __SETTING_H
#define __SETTING_H

#include <QRect>
#include <QString>
#include <QColor>
#include <QSettings>
#include <QCoreApplication>

class Setting
{
public:
	Setting(void);
	virtual ~Setting(void);

	void load(void);
	void save(void);

	QString filePath;
	QString fileName;
	int bgColorR;
	int bgColorG;
	int bgColorB;
	int bgColorA;

	int penColorR;
	int penColorG;
	int penColorB;
	int penColorA;

	int toolType;

	bool editAfterShot;
	QRect editorRect;
	bool editorIsMax;
	int penWidth;
	int arrowLength;

private:
	QSettings *setting;
};

#endif