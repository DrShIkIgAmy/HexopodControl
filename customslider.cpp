#include "customslider.h"
#include <QPainter>
#include <QMouseEvent>
#include <qdebug.h>
#include <QRadialGradient>

CustomSlider::CustomSlider(QWidget *parent) : QWidget(parent)
{

}

void CustomSlider::paintEvent(QPaintEvent *event)
{
  onSizeChanged();
  QPainter painter(this);
  drawGroove(&painter);
}

qreal CustomSlider::_calculateValue(qreal Angle)
{
  qreal transformedStartAngle = initialAngle*360/PI_num;
  qreal transformedStopAngle = stopAngle*360/PI_num;
  return Angle/(transformedStopAngle-transformedStartAngle);
}

void CustomSlider::onSizeChanged()
{
  if(this->width()!=Size_||this->height()!=Size_)
  {
    Size_ = this->height();
    this->setMaximumWidth(Size_);
    this->setMinimumWidth(Size_);
  }
}

void CustomSlider::drawGroove(QPainter *painterInst)
{
  qreal margin_ = Size_*(1-boundingBoxScale)/2;
  QRectF bounds(margin_,margin_,Size_*boundingBoxScale,Size_*boundingBoxScale);

  QRadialGradient gradient(Size_/2,Size_/2,Size_);

  QColor startColor(grooveColorStart);
  QColor endColor(grooveColorEnd);

  qreal startGroove = Size_*boundingBoxScale/2 - grooveWidth/2;
  qreal endGroove = startGroove+grooveWidth;

  qreal relStart = startGroove/Size_;
  qreal relEnd = endGroove/Size_;

  startColor.setAlpha(0);
  gradient.setColorAt(relStart,startColor);
  startColor.setAlpha(255);
  gradient.setColorAt(relStart+0.01,startColor);

  endColor.setAlpha(255);
  gradient.setColorAt((relStart-relEnd)/2+relStart,endColor);
  endColor.setAlpha(50);
  gradient.setColorAt(relEnd-0.02,endColor);
  gradient.setColorAt(relEnd-0.01,QColor("#00ffffff"));

  painterInst->setPen(QPen(gradient,grooveWidth));
  painterInst->drawArc(bounds,initialAngle*16,(-initialAngle+stopAngle)*16);
}

