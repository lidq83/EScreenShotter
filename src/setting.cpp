#include "setting.h"

Setting::Setting(void)
{
	filePath = QString("/home/lidq/Pictures/");
	fileName = QString("EScreenShotter");

	bgColorR = 64;
	bgColorG = 64;
	bgColorB = 128;
	bgColorA = 128;

	penColorR = 255;
	penColorG = 0;
	penColorB = 0;
	penColorA = 255;

	toolType = 0;

	editAfterShot = true;

	editorRect.setLeft(0);
	editorRect.setTop(0);
	editorRect.setWidth(1200);
	editorRect.setHeight(800);

	editorIsMax = true;

	penWidth = 6;
	arrowLength = 23;

	textFont = QString("SimSun");
	textSize = 16;
	textItalic = false;
	textBold = false;

	QString path(QCoreApplication::applicationDirPath());
	path.append("/setting.cfg");
	setting = new QSettings(path, QSettings::IniFormat, 0);
}

Setting::~Setting(void)
{
	delete setting;
}

void Setting::load(void)
{
	filePath = setting->value("filePath", filePath).toString();
	fileName = setting->value("fileName", fileName).toString();

	bgColorR = setting->value("bgColorR", bgColorR).toInt();
	bgColorG = setting->value("bgColorG", bgColorG).toInt();
	bgColorB = setting->value("bgColorB", bgColorB).toInt();
	bgColorA = setting->value("bgColorA", bgColorA).toInt();

	penColorR = setting->value("penColorR", penColorR).toInt();
	penColorG = setting->value("penColorG", penColorG).toInt();
	penColorB = setting->value("penColorB", penColorB).toInt();
	penColorA = setting->value("penColorA", penColorA).toInt();

	toolType = setting->value("toolType", toolType).toInt();

	editAfterShot = setting->value("editAfterShot", editAfterShot).toBool();
	editorIsMax = setting->value("editorIsMax", editorIsMax).toBool();

	editorRect = setting->value("editorRect", editorRect).toRect();

	penWidth = setting->value("penWidth", penWidth).toInt();
	arrowLength = setting->value("arrowLength", arrowLength).toInt();

	textFont = setting->value("textFont", textFont).toString();
	textSize = setting->value("textSize", textSize).toInt();
	textItalic = setting->value("textItalic", textItalic).toBool();
	textBold = setting->value("textBold", textBold).toBool();
}

void Setting::save(void)
{
	setting->setValue("filePath", filePath);
	setting->setValue("fileName", fileName);

	setting->setValue("bgColorR", bgColorR);
	setting->setValue("bgColorG", bgColorG);
	setting->setValue("bgColorB", bgColorB);
	setting->setValue("bgColorA", bgColorA);

	setting->setValue("penColorR", penColorR);
	setting->setValue("penColorG", penColorG);
	setting->setValue("penColorB", penColorB);
	setting->setValue("penColorA", penColorA);

	setting->setValue("toolType", toolType);

	setting->setValue("editAfterShot", editAfterShot);
	setting->setValue("editorIsMax", editorIsMax);

	setting->setValue("editorRect", editorRect);

	setting->setValue("penWidth", penWidth);
	setting->setValue("arrowLength", arrowLength);

	setting->setValue("textFont", textFont);
	setting->setValue("textSize", textSize);
	setting->setValue("textItalic", textItalic);
	setting->setValue("textBold", textBold);
}
