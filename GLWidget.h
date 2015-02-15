#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QList>

class GLWidget : public QGLWidget
{
				static const int OrthoIdxMax = 6;
				static const int TranslateIdxMax = 3;

				enum OrhoIndex { 
								kLeft = 0,
								kRight,
								kBottom,
								kTop,
								kZnear,
								kZfar
				};

				enum TranslateIndex {
								kValueX = 0,
								kValueY,
								kValueZ,
				};

				Q_OBJECT

public:
				GLWidget();
				~GLWidget();
				
private slots:
				void RotationSetX(int angle); //X축으로 회전하기
				void RotationSetY(int angle); //Y축으로 회전하기
				void RotationSetZ(int angle); //Z축으로 회전하기

private: // Override
				void initializeGL(); //Opengl 초기화
				void resizeGL(int w, int h); //위젯 크기 변했을때 발생하는 함수
				void paintGL(); //실제 그래픽을 그린다.

				void mousePressEvent(QMouseEvent *event); //마우스클릭 이벤트
				void mouseMoveEvent(QMouseEvent *event); //마우스이동이벤트

private:
				void PushbackElementP(const int start, const int end, const int range_num);
				void PushbackElementM(const int start, const int end, const int range_num);

 			QFile file; // point.txt 파일 읽기
				QList<QString> *text_data_;
				int valid_range_[6];

				QList<GLfloat> *data_x_; // 3D 좌표들
				QList<GLfloat> *data_y_;
				QList<GLfloat> *data_z_;
				QList<bool> *data_valid_;

				GLdouble OrthoValue[OrthoIdxMax]; // 뷰어 관련
				GLfloat TranslateValue[TranslateIdxMax];
				double cargo_z;

				GLfloat RotateX_; // 회전을 위한 변수
				GLfloat RotateY_;
				GLfloat RotateZ_;

				QPoint PostionLast_; //마우스 이동을 위한 변수

public:
				void OrthoPlusLeft();
				void OrthoPlusRight();
				void OrthoPlusBottom();
				void OrthoPlusTop();
				void OrthoPlusZNear();
				void OrthoPlusZFar();
				void OrthoMinusLeft();
				void OrthoMinusRight();
				void OrthoMinusBottom();
				void OrthoMinusTop();
				void OrthoMinusZNear();
				void OrthoMinusZFar();

				void TranslatefPlusX();
				void TranslatefPlusY();
				void TranslatefPlusZ();
				void TranslatefMinusX();
				void TranslatefMinusY();
				void TranslatefMinusZ();
};

#endif 