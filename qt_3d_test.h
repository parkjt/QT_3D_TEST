#ifndef QT_3D_TEST_H
#define QT_3D_TEST_H

#include <QtWidgets/QMainWindow>

#include "ui_qt_3d_test.h"
#include "glwidget.h"

namespace Ui {
				class Widget;
}

class QT_3D_TEST : public QMainWindow
{
				Q_OBJECT

public:
				explicit QT_3D_TEST(QMainWindow *parent = 0);
				~QT_3D_TEST();

private:
				Ui::QT_3D_TESTClass ui;
				GLWidget* glw;

private slots:
				void PlusLeft()    { glw->OrthoPlusLeft(); }
				void PlusRight()   { glw->OrthoPlusRight(); }
				void PlusBottom()  { glw->OrthoPlusBottom(); }
				void PlusTop()     { glw->OrthoPlusTop(); }
				void PlusZNear()   { glw->OrthoPlusZNear(); }
				void PlusZFar()    { glw->OrthoPlusZFar(); }
				void MinusLeft()   { glw->OrthoMinusLeft(); }
				void MinusRight()  { glw->OrthoMinusRight(); }
				void MinusBottom() { glw->OrthoMinusBottom(); }
				void MinusTop()    { glw->OrthoMinusTop(); }
				void MinusZNear()  { glw->OrthoMinusZNear(); }
				void MinusZFar()   { glw->OrthoMinusZFar(); }

private slots:
				void PlusX()  { glw->TranslatefPlusX(); }
				void PlusY()  { glw->TranslatefPlusY(); }
				void PlusZ()  { glw->TranslatefPlusZ(); }
				void MinusX() { glw->TranslatefMinusX(); }
				void MinusY() { glw->TranslatefMinusY(); }
				void MinusZ() { glw->TranslatefMinusZ(); }
};

#endif
