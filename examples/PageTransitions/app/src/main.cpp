#include "MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	QApplication::setFont(QFont("sans-serif", 14));

	w.show();

	return a.exec();
}
