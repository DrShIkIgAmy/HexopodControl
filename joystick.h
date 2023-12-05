#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <QWidget>
#include <QTimer>
#include <QImage>

class JoyStick : public QWidget
{
  Q_OBJECT
private:
  qreal padSize = 0;
  qreal thumbSize = 0;
  qreal currentRo = 0;
  qreal currentAngle = 0;
  qreal localX = 0;
  qreal localY = 0;
  qreal shift = 0;
  bool isMousePressed = false;
  bool isTargedCaptured = false;

  bool isRedrawNeeded = true;


  qreal Width_ = -1;
  qreal Heigth_ = -1;

  QRectF _padBounds;

  QTimer* redrawTimer = NULL;
  int timInterval = 15;
public:
  explicit JoyStick(QWidget *parent = 0);
private:
  void onResized();
  qreal distance(QPointF point_1,QPointF point_2);
  QPointF fromPolar(qreal ro,qreal alpha);
  QPointF toPolar(qreal x,qreal y);
  void processSignal();

  QRadialGradient getThumbGradient(bool isActive,QPointF focus_);
  QRadialGradient getPadGradient(bool isActive);
protected:
  void paintEvent(QPaintEvent *event);
  void mousePressEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
public:
    /*//////////////////////////*/
    /*//////////////////////////*/
    //.///--> Properties <--///.//
    /*//////////////////////////*/
    /*//////////////////////////*/
  qreal margin = 30;
  qreal deadZone = 50;
  qreal padSizeScale = 1;
  qreal thumbSizeScale = 0.25;

  QString padColorInactiveString = "#cc0000";
  QString padColorActiveString = "#00ff00";
  QString thumbColorInactiveString = "#00d200";
  QString thumbColorActiveString = "#cc0000";
  QString padBorderColorString = "#00d200";
  QString thumbBorderColorString = "#00d200";
signals:
  void thumbMoved(double power,double angle);
private slots:
public slots:
  void onDrawTimerTicked();
};

#endif // JOYSTICK_H
