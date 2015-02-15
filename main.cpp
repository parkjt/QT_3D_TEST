#include "qt_3d_test.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
				QApplication a(argc, argv);
				QT_3D_TEST w;
				w.show();
				return a.exec();
}
