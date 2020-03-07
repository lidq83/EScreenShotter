#include "setting.h"

Setting::Setting(void)
{
	filePath = QString("~/Picures/");
	fileName = QString("EScreenShotter");

	bgColorR = 64;
	bgColorG = 64;
	bgColorB = 128;
	bgColorA = 128;

	editAfterShot = true;

	editorRect.setLeft(0);
	editorRect.setTop(0);
	editorRect.setWidth(1200);
	editorRect.setHeight(800);

	editorIsMax = true;

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

	editAfterShot = setting->value("editAfterShot", editAfterShot).toBool();
	editorIsMax = setting->value("editorIsMax", editorIsMax).toBool();

	editorRect = setting->value("editorRect", editorRect).toRect();
}

void Setting::save(void)
{
	setting->setValue("filePath", filePath);
	setting->setValue("fileName", fileName);

	setting->setValue("bgColorR", bgColorR);
	setting->setValue("bgColorG", bgColorG);
	setting->setValue("bgColorB", bgColorB);
	setting->setValue("bgColorA", bgColorA);

	setting->setValue("editAfterShot", editAfterShot);
	setting->setValue("editorIsMax", editorIsMax);

	setting->setValue("editorRect", editorRect);
}
