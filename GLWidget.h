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
				void RotationSetX(int angle); //X������ ȸ���ϱ�
				void RotationSetY(int angle); //Y������ ȸ���ϱ�
				void RotationSetZ(int angle); //Z������ ȸ���ϱ�

private: // Override
				void initializeGL(); //Opengl �ʱ�ȭ
				void resizeGL(int w, int h); //���� ũ�� �������� �߻��ϴ� �Լ�
				void paintGL(); //���� �׷����� �׸���.

				void mousePressEvent(QMouseEvent *event); //���콺Ŭ�� �̺�Ʈ
				void mouseMoveEvent(QMouseEvent *event); //���콺�̵��̺�Ʈ

private:
				void PushbackElementP(const int start, const int end, const int range_num);
				void PushbackElementM(const int start, const int end, const int range_num);

 			QFile file; // point.txt ���� �б�
				QList<QString> *text_data_;
				int valid_range_[6];

				QList<GLfloat> *data_x_; // 3D ��ǥ��
				QList<GLfloat> *data_y_;
				QList<GLfloat> *data_z_;
				QList<bool> *data_valid_;

				GLdouble OrthoValue[OrthoIdxMax]; // ��� ����
				GLfloat TranslateValue[TranslateIdxMax];
				double cargo_z;

				GLfloat RotateX_; // ȸ���� ���� ����
				GLfloat RotateY_;
				GLfloat RotateZ_;

				QPoint PostionLast_; //���콺 �̵��� ���� ����

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