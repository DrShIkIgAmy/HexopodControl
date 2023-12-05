#include "joystick.h"
#include <QPainter>
#include <QMouseEvent>
#include <qdebug.h>



JoyStick::JoyStick(QWidget *parent) : QWidget(parent)
{
  redrawTimer = new QTimer();
  redrawTimer->setInterval(timInterval);
  connect(redrawTimer,SIGNAL(timeout()),this,SLOT(onDrawTimerTicked()));
  redrawTimer->start();

}

void JoyStick::onResized()
{
  if(this->height()!=Heigth_)
  {
    Heigth_ = this->height();
    this->setMaximumWidth(Heigth_);
    this->setMinimumWidth(Heigth_);

    padSize = Heigth_*padSizeScale;
    thumbSize = this->height()*thumbSizeScale;
    shift = padSize/2;
    _padBounds = QRectF(margin/2,margin/2,padSize-margin,padSize-margin);

    isRedrawNeeded = true;
  }
}

void JoyStick::paintEvent(QPaintEvent *event)
{
  auto centrePoint = fromPolar(currentRo,currentAngle);
  qreal centreX = centrePoint.x()+shift-thumbSize/2;
  qreal centreY = centrePoint.y()+shift-thumbSize/2;
  QPainter painter(this);
  QRectF thumbBounds = QRectF(centreX,centreY,thumbSize,thumbSize);
  painter.fillRect(_padBounds, getPadGradient(isTargedCaptured));
  painter.fillRect(thumbBounds, getThumbGradient(isTargedCaptured,QPointF(centreX+thumbSize/2,centreY+thumbSize/2)));
}

QRadialGradient JoyStick::getThumbGradient(bool isActive, QPointF focus_)
{
  if(!isActive)
  {
    QColor _thumbColor_2(thumbColorActiveString);
    QColor _thumbColor(thumbColorInactiveString);
    QRadialGradient thumbGradient(focus_,thumbSize/2);
    thumbGradient.setColorAt(0,_thumbColor_2);
    _thumbColor.setAlpha(255);
    thumbGradient.setColorAt(0.76,_thumbColor);
    _thumbColor.setAlpha(160);
    thumbGradient.setColorAt(0.9,_thumbColor);
    _thumbColor.setAlpha(0);
    thumbGradient.setColorAt(1,_thumbColor);
    return thumbGradient;
  }
  else
  {
    QColor _thumbColor(thumbColorActiveString);
    QColor _thumbColor_2(thumbColorInactiveString);
    QRadialGradient thumbGradient(focus_,thumbSize/2);
    thumbGradient.setColorAt(0,_thumbColor_2);
    _thumbColor.setAlpha(255);
    thumbGradient.setColorAt(0.76,_thumbColor);
    _thumbColor.setAlpha(160);
    thumbGradient.setColorAt(0.9,_thumbColor);
    _thumbColor.setAlpha(0);
    thumbGradient.setColorAt(1,_thumbColor);
    return thumbGradient;
  }
}

QRadialGradient JoyStick::getPadGradient(bool isActive)
{
  if(isActive)
  {
    QColor _backgroundColor(padColorActiveString);
    QRadialGradient padGradient(QPointF((padSize)/2,(padSize)/2),(padSize-margin)/2);

    _backgroundColor.setAlpha(255);
    padGradient.setColorAt(0,_backgroundColor);

    _backgroundColor.setAlpha(200);
    padGradient.setColorAt(0.4,_backgroundColor);

    _backgroundColor.setAlpha(0);
    padGradient.setColorAt(1,_backgroundColor);
    return padGradient;
  }
  else
  {
    QColor _backgroundColor(padColorInactiveString);
    QRadialGradient padGradient(QPointF((padSize)/2,(padSize)/2),(padSize-margin)/2);

    _backgroundColor.setAlpha(0);
    padGradient.setColorAt(0,_backgroundColor);

    _backgroundColor.setAlpha(255);
    padGradient.setColorAt(0.8,_backgroundColor);

    _backgroundColor.setAlpha(0);
    padGradient.setColorAt(1,_backgroundColor);
    return padGradient;
  }
}

QPointF JoyStick::fromPolar(qreal ro, qreal alpha)
{
  return QPointF(ro*cos(alpha),ro*sin(alpha));
}

QPointF JoyStick::toPolar(qreal x, qreal y)
{
  qreal ro = sqrt(pow(x,2)+pow(y,2));
  qreal alpha = 0;
  if(x==0&&y<0)
    alpha = -3.14159265359/2;
  else if(x==0&&y>=0)
    alpha = 3.14159265359/2;
  else
    alpha = atan2(y,x);
  return QPointF(ro,alpha);

}

void JoyStick::processSignal()
{
  auto point = fromPolar(currentRo,currentAngle);
  double tg = 0;
  double angle = 0;
  angle = atan2(abs(point.x()),abs(point.y()));
  point.setX(point.x()*-1);
  point.setY(point.y()*-1);
  if(point.x()<0)
  {
    if(point.y()<0)
    {
      angle = 3.14159265359+angle;
    }
    else
    {
      angle = 2*3.14159265359-angle;
    }
  }
  else
  {
    if(point.y()<0)
    {
      angle = 3.14159265359-angle;
    }
    else
    {
      angle = angle;
    }
  }
  double transformedR0 = (currentRo/(padSize/2-deadZone))*100;
  emit thumbMoved(transformedR0,2*3.14159265359-angle);

}

//***********************************//
//********* MOUSE EVENTS ************//
//***********************************//

void JoyStick::mousePressEvent(QMouseEvent *event)
{
  isMousePressed = true;
  auto pos = event->localPos();
  auto polarPos = toPolar(pos.x()-shift,pos.y()-shift);
  if(polarPos.x()<=thumbSize/2)
    isTargedCaptured = true;
}

void JoyStick::mouseReleaseEvent(QMouseEvent *event)
{
  isMousePressed = false;
  isTargedCaptured = false;
  currentRo = 0;
  currentAngle = 0;
  processSignal();
  isRedrawNeeded = true;
}

void JoyStick::mouseMoveEvent(QMouseEvent *event)
{
  if(isTargedCaptured)
  {
    auto pos = event->localPos();
    auto point = toPolar(pos.x()-shift,pos.y()-shift);
    if(point.x()<=padSize/2-deadZone)
    {
      currentRo = point.x();
      currentAngle = point.y();
    }
    else
    {
      currentRo = padSize/2-deadZone;
      currentAngle = point.y();
    }
    processSignal();
    isRedrawNeeded = true;
  }
}

void JoyStick::onDrawTimerTicked()
{
  onResized();
  if(isRedrawNeeded)
  {
    repaint();
    isRedrawNeeded = false;
  }
}

//***********************************//
//******** MICE EVENTS END **********//
//***********************************//

