#include "qt_3d_test.h"

QT_3D_TEST::QT_3D_TEST(QMainWindow *parent)
		: QMainWindow(parent)
{
				ui.setupUi(this);
				setLayout(ui.verticalLayout);

				// 5.0 Style
				connect(ui.left_plus_, &QPushButton::clicked , this, &QT_3D_TEST::PlusLeft);
				connect(ui.right_plus_, &QPushButton::clicked , this, &QT_3D_TEST::PlusRight);
				connect(ui.bottom_plus_, &QPushButton::clicked , this, &QT_3D_TEST::PlusBottom);
				connect(ui.top_plus_, &QPushButton::clicked , this, &QT_3D_TEST::PlusTop);
				connect(ui.znear_plus_, &QPushButton::clicked , this, &QT_3D_TEST::PlusZNear);
				connect(ui.zfar_plus_, &QPushButton::clicked , this, &QT_3D_TEST::PlusZFar);
				connect(ui.left_minus_, &QPushButton::clicked , this, &QT_3D_TEST::MinusLeft);
				connect(ui.right_minus_, &QPushButton::clicked , this, &QT_3D_TEST::MinusRight);
				connect(ui.bottom_minus_, &QPushButton::clicked , this, &QT_3D_TEST::MinusBottom);
				connect(ui.top_minus_, &QPushButton::clicked , this, &QT_3D_TEST::MinusTop);
				connect(ui.znear_minus_, &QPushButton::clicked , this, &QT_3D_TEST::MinusZNear);
				connect(ui.zfar_minus_, &QPushButton::clicked , this, &QT_3D_TEST::MinusZFar);

				connect(ui.x_plus_, &QPushButton::clicked , this, &QT_3D_TEST::PlusX);
				connect(ui.y_plus_, &QPushButton::clicked , this, &QT_3D_TEST::PlusY);
				connect(ui.z_plus_, &QPushButton::clicked , this, &QT_3D_TEST::PlusZ);
				connect(ui.x_minus_, &QPushButton::clicked , this, &QT_3D_TEST::MinusX);
				connect(ui.y_minus_, &QPushButton::clicked , this, &QT_3D_TEST::MinusY);
				connect(ui.z_minus_, &QPushButton::clicked , this, &QT_3D_TEST::MinusZ);

				glw = new GLWidget();
				ui.verticalLayout->addWidget(glw);
}

QT_3D_TEST::~QT_3D_TEST()
{
				delete glw;
}
