#include "mymainwindow.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	myMainWindow mainWin;
	mainWin.show();

	return a.exec();
}
