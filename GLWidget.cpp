#include "glwidget.h"
#include <QTimer>
#include <math.h>
#include <QMouseEvent>

GLWidget::GLWidget()
				: file("point.txt"),
				cargo_z(0.0),
				RotateX_(0.0),
				RotateY_(0.0),
				RotateZ_(0.0),
				PostionLast_(0.0, 0.0)
{
				data_x_ = new QList<GLfloat>;
				data_y_ = new QList<GLfloat>;
				data_z_ = new QList<GLfloat>;
				data_valid_ = new QList<bool>;
				text_data_ = new QList<QString>;

				data_x_->clear();
				data_y_->clear();
				data_z_->clear();
				data_valid_->clear();
				text_data_->clear();
				
				// 뷰어 초기화
				OrthoValue[kLeft] = 27;
				OrthoValue[kRight] = 2;
				OrthoValue[kBottom] = 10;
				OrthoValue[kTop] = 28;
				OrthoValue[kZnear] = -2;
				OrthoValue[kZfar] = 3;

				TranslateValue[kValueX] = 45;
				TranslateValue[kValueY] = -485;
				TranslateValue[kValueZ] = -2220;

				// 포인트 파일 읽기(x, y)
				if(!file.open(QIODevice::ReadWrite))
								qDebug() << "not open";

				QTextStream in(&file);

				while(!in.atEnd()) {
								QString line = in.readLine();
								text_data_->push_back(line);
				}

				file.close();

				valid_range_[0] = 2650; // left
				valid_range_[1] = 2750;
				valid_range_[2] = 6650; // center
				valid_range_[3] = 6750;
				valid_range_[4] = -3450; // right
				valid_range_[5] = -3350;

				// 리스트에 각각의 좌표 저장
				int start = 0;
				int end = 274;
				int way = 1;

				for (int i = 0; i < 500; i++) { 
								if(i % 2 == 0)
								{
												PushbackElementP(0, 80, 0);
												PushbackElementP(80, 220, 2);
												PushbackElementP(220, 273, 4);
								}
								else
								{
												PushbackElementM(273, 220, 4);
												PushbackElementM(220, 80, 2);
												PushbackElementM(80, 0, 0);
								}

								cargo_z++;
				}

				text_data_->clear();
				delete text_data_;
}

void GLWidget::PushbackElementP(const int start, const int end, const int range_num)
{
				int min = valid_range_[range_num];
				int max = valid_range_[range_num + 1];

				for (int i = start; i < end; i++) { 
								QStringList fields = text_data_->at(i).split(",");
								data_x_->push_back((GLfloat)fields.at(0).toFloat());
								data_y_->push_back((GLfloat)fields.at(1).toFloat());
								data_z_->push_back((GLfloat)cargo_z);

								GLfloat value;

								if (range_num != 2)
												value = (GLfloat)fields.at(0).toFloat();
								else
												value = (GLfloat)fields.at(1).toFloat();

								if(value < min || value > max)
												data_valid_->push_back(false);
								else
												data_valid_->push_back(true);
				}
}

void GLWidget::PushbackElementM(const int start, const int end, const int range_num)
{
				int min = valid_range_[range_num];
				int max = valid_range_[range_num + 1];

				for (int i = start; i > end; i--) { 
								QStringList fields = text_data_->at(i).split(",");
								data_x_->push_back((GLfloat)fields.at(0).toFloat());
								data_y_->push_back((GLfloat)fields.at(1).toFloat());
								data_z_->push_back((GLfloat)cargo_z);

								GLfloat value;

								if (range_num != 2)
												value = (GLfloat)fields.at(0).toFloat();
								else
												value = (GLfloat)fields.at(1).toFloat();

								if(value < min || value > max)
												data_valid_->push_back(false);
								else
												data_valid_->push_back(true);
				}
}

void GLWidget::OrthoPlusLeft()    { OrthoValue[kLeft] += 3; updateGL(); }
void GLWidget::OrthoMinusLeft()   { OrthoValue[kLeft] -= 3; updateGL(); }
void GLWidget::OrthoPlusRight()   { OrthoValue[kRight] += 3; updateGL(); }
void GLWidget::OrthoMinusRight()  { OrthoValue[kRight] -= 3; updateGL(); }
void GLWidget::OrthoPlusBottom()  { OrthoValue[kBottom] += 3; updateGL(); }
void GLWidget::OrthoMinusBottom() { OrthoValue[kBottom] -= 3; updateGL(); }
void GLWidget::OrthoPlusTop()     { OrthoValue[kTop] += 3; updateGL(); }
void GLWidget::OrthoMinusTop()    { OrthoValue[kTop] -= 3; updateGL(); }
void GLWidget::OrthoPlusZNear()   { OrthoValue[kZnear] += 3; updateGL(); }
void GLWidget::OrthoMinusZNear()  { OrthoValue[kZnear] -= 3; updateGL(); }
void GLWidget::OrthoPlusZFar()    { OrthoValue[kZfar] += 3; updateGL(); }
void GLWidget::OrthoMinusZFar()   { OrthoValue[kZfar] -= 3; updateGL(); }

void GLWidget::TranslatefPlusX()  { TranslateValue[kValueX] += 20; updateGL(); }
void GLWidget::TranslatefMinusX() { TranslateValue[kValueX] -= 20; updateGL(); }
void GLWidget::TranslatefPlusY()  { TranslateValue[kValueY] += 20; updateGL(); }
void GLWidget::TranslatefMinusY() { TranslateValue[kValueY] -= 20; updateGL(); }
void GLWidget::TranslatefPlusZ()  { TranslateValue[kValueZ] += 60; updateGL(); }
void GLWidget::TranslatefMinusZ() { TranslateValue[kValueZ] -= 60; updateGL(); }

GLWidget::~GLWidget() //소멸자
{
				data_x_->clear();
				data_y_->clear();
				data_z_->clear();

				delete data_x_;
				delete data_y_;
				delete data_z_;
}

void GLWidget::initializeGL() { glEnable(GL_DEPTH_TEST); }

void GLWidget::resizeGL(int w, int h) //위젯 크기 변했을때
{
				GLfloat aspectRatio; //화면 비율

				if(h == 0)
								h = 1;

				glViewport(0, 0, 800, 800); //뷰포트 설정

				glMatrixMode(GL_PROJECTION); //행렬모드지정
				glLoadIdentity(); //좌표계 초기화

				aspectRatio = (GLfloat)w / (GLfloat)h; //화면비율 지정
				GLfloat WindowWidth = 0;
				GLfloat WindowHeight = 0;

				if(w <= h)
				{
								WindowWidth = 1;
								WindowHeight = 1 / aspectRatio;
								glFrustum(-1.0, 1.0, -WindowHeight, WindowHeight, 5.0,300.0);
				}
				else
				{
								WindowWidth = 1 * aspectRatio;
								WindowHeight = 1;
								glFrustum(-WindowWidth, WindowWidth, -1.0, 1.0, 5.0, 3000.0);
				}

				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
}

void GLWidget::paintGL() //실제 그리는 함수
{
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //화면을 지워준다.

				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				glTranslatef(TranslateValue[kValueX],
								TranslateValue[kValueY],
								TranslateValue[kValueZ]); //move along z-axis// 카메라 이동

				glRotatef(RotateY_,0.0,1.0,0.0); //rotate 30 degress around y-axis
				glRotatef(RotateX_,1.0,0.0,0.0); //rotate 15 degress around x-axis
				glViewport(0, 0, 800, 800);

				glOrtho(OrthoValue[kLeft],
								OrthoValue[kRight],
								OrthoValue[kBottom],
								OrthoValue[kTop],
								OrthoValue[kZnear],
								OrthoValue[kZfar]);

				glBegin(GL_LINE_STRIP);

				glColor3f(1.0, 1.0, 1.0);

				QList<float>::Iterator itor_y = data_y_->begin();
				QList<float>::Iterator itor_z = data_z_->begin();
				QList<bool>::Iterator itor_valid = data_valid_->begin();
				
				for (QList<GLfloat>::Iterator itor_x = data_x_->begin();
								itor_x != data_x_->end();) { 
												if(*itor_valid++ == false) { 
																glColor3f(1.0, 0.0, 0.0);
																glVertex3f(*itor_x++, *itor_y++, *itor_z++);
												}
												else { 
																glColor3f(1.0, 1.0, 1.0);
																glVertex3f(*itor_x++, *itor_y++, *itor_z++);
												}
				}
				
				glEnd();   // Done drawing the pyramid


// 				qDebug() << OrthoValue[kLeft] << ", " <<
// 								OrthoValue[kRight] << ", " <<
// 								OrthoValue[kBottom] << ", " <<
// 								OrthoValue[kTop] << ", " <<
// 								OrthoValue[kZnear] << ", " <<
// 								OrthoValue[kZfar];
// 
// 				qDebug() << TranslateValue[kValueX] << ", " <<
// 								TranslateValue[kValueY] << ", " <<
// 								TranslateValue[kValueZ];
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
				PostionLast_ = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
				int dx = event->x() - PostionLast_.x();
				int dy = event->y() - PostionLast_.y();

				if (event->buttons() & Qt::LeftButton) {
								RotationSetX(RotateX_ + 1 * dy);
								RotationSetY(RotateY_ + 1 * dx);
				} else if (event->buttons() & Qt::RightButton) {
								RotationSetX(RotateX_ + 1 * dy);
								RotationSetZ(RotateZ_ + 1 * dx);
				}

				PostionLast_ = event->pos();
}

static void qNormalizeAngle(int &angle)
{
				while (angle < 0)
								angle += 360 * 16;

				while (angle > 360 * 16)
								angle -= 360 * 16;
}

void GLWidget::RotationSetX(int angle)
{
				qNormalizeAngle(angle);

				if (angle != RotateX_) {
								RotateX_ = angle;
								updateGL();
				}
}

void GLWidget::RotationSetY(int angle)
{
				qNormalizeAngle(angle);

				if (angle != RotateY_) {
								RotateY_ = angle;
								updateGL();
				}
}

void GLWidget::RotationSetZ(int angle)
{
				qNormalizeAngle(angle);

				if (angle != RotateZ_) {
								RotateZ_ = angle;
								updateGL();
				}
}
