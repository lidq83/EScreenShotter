#include "widget.h"
#include "setting.h"
#include <unistd.h>
#include <QApplication>

Setting *setting = nullptr;

int main(int argc, char *argv[])
{
	if (argc == 3 && strcmp(argv[1], "-d") == 0)
	{
		int delay = 0;
		sscanf(argv[2], "%d", &delay);
		sleep(delay);
	}

	QApplication a(argc, argv);
	Setting s;
	s.load();
	s.save();
	setting = &s;
	Widget w;
	w.showFullScreen();
	return a.exec();
}
