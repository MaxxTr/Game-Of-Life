#include "../Headers/gameoflife.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	GameOfLife w;
	w.show();
	return a.exec();
}
