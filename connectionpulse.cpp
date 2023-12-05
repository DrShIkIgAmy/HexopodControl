#include "connectionpulse.h"
#include <QPainter>


ConnectionPulse::ConnectionPulse(QWidget *parent) : QWidget(parent)
{
  sampleHead = 1;
  sampleTail = sampleHead-sampleLength;
  tim = new QTimer();
  tim->setInterval(timerInterval);
  connect(tim,SIGNAL(timeout()),this,SLOT(onTimerTicked()));
  tim->start();
}

void ConnectionPulse::widgetInfoCalculation()
{
  if(Heigth_!=height()||Width_!=width())
  {
    qreal prevWidth = Width_;
    qreal prevSampleLength = sampleLength;
    qreal prevSampleInc = sampleIncrement;
    Heigth_=height();
    Width_=width();
    scalePulseForm(Width_,Heigth_);
    defineCoeffs();
    pointHalo = Heigth_*pointHaloScale;
    sampleIncrement *= (sampleLength/prevSampleLength);
    sampleLength = Width_*sampleLengthScale;
    defineSpeed();


    qreal HeadProgress = sampleHead/prevWidth;
    qreal TailProgress = sampleTail/prevWidth;
    sampleHead = Width_*HeadProgress;
    sampleTail = Width_*TailProgress;
  }
}

void ConnectionPulse::paintEvent(QPaintEvent *event)
{
  widgetInfoCalculation();
  QPainter painter(this);
  drawGrid(&painter);
  drawLines(&painter);
  drawCircule(&painter);
  drawWidget(&painter);

}

void ConnectionPulse::drawWidget(QPainter *painterInst)
{
  QColor _BorderColor(borderColor);
  QColor _backgroundColor(widgetBackgroundColor);

  QRectF rectangle(borderLineWidth/2,borderLineWidth/2,this->width()-borderLineWidth,this->height()-borderLineWidth);
  QBrush borderBrush(_BorderColor);
  QPen pen(borderBrush,borderLineWidth);
  painterInst->setPen(pen);
  painterInst->drawRect(rectangle);

  QRadialGradient gradient(QPointF(Width_/2,Heigth_/2),Width_/2);
  _backgroundColor.setAlpha(0);
  gradient.setColorAt(0,_backgroundColor);
  _backgroundColor.setAlpha(255);
  gradient.setColorAt(1,_backgroundColor);

  QRectF gradRect(0,0,this->width(),this->height());
  painterInst->fillRect(gradRect, gradient);
}

void ConnectionPulse::drawLines(QPainter *painterInst)
{
  QColor _pulseLineColor(pulseLineColor);
  QPen pulseLinePen(_pulseLineColor,pulseLineWidth);


  painterInst->setPen(pulseLinePen);
  int tmpTail = sampleTail<borderLineWidth?borderLineWidth:sampleTail;
  int tmpHead = sampleHead>=Width_-borderLineWidth?Width_-borderLineWidth:sampleHead;
  tmpHead = tmpHead<=borderLineWidth?borderLineWidth+1:tmpHead;

  auto lines = getLines(tmpTail,tmpHead);
  foreach (auto line, lines)
  {
    painterInst->drawLine(line);
  }
}

void ConnectionPulse::drawGrid(QPainter *painterInst)
{
  QColor gridColor(gridLinesColor);
  QPen gridPen(gridColor,gridLineWidth);
  painterInst->setPen(gridPen);
  auto grid = getGrid();
  foreach (auto line, grid)
  {
    painterInst->drawLine(line);
  }
}

void ConnectionPulse::drawCircule(QPainter *painterInst)
{
  qreal Y__ = -1;
  foreach (auto line, pulseForm)
  {
    if(line.lower<=sampleHead&&line.upper>=sampleHead)
    {
      Y__ = line.k*sampleHead+line.c;
      break;
    }
  }

  QColor circleColor(pulseCircleColor);

  QRadialGradient gradient(QPointF(sampleHead,Y__),pointHalo);

  circleColor.setAlpha(255);
  gradient.setColorAt(0,circleColor);
  circleColor.setAlpha(200);
  gradient.setColorAt(0.2,circleColor);
  circleColor.setAlpha(50);
  gradient.setColorAt(0.5,circleColor);
  circleColor.setAlpha(0);
  gradient.setColorAt(1,circleColor);

  QRectF gradRect(sampleHead-pointHalo,Y__-pointHalo,pointHalo*2,pointHalo*2);
  painterInst->fillRect(gradRect, gradient);
}

void ConnectionPulse::defineCoeffs()
{
  for(int i=0;i<pulseForm.length();i++)
  {
    pulseForm[i].k = (pulseForm[i].head.y()-pulseForm[i].tail.y())/(pulseForm[i].head.x()-pulseForm[i].tail.x());
    pulseForm[i].c =  pulseForm[i].tail.y()-pulseForm[i].k*pulseForm[i].tail.x();
  }
}

void ConnectionPulse::scalePulseForm(qreal _w, qreal _h)
{
  qreal _x_coeff = _w/ _pulse_form_width;
  qreal _y_coeff = _h/ _pulse_form_height;
  _pulse_form_width = _w;
  _pulse_form_height = _h;
  for(int i=0;i<pulseForm.length();i++)
  {
    pulseForm[i].lower = pulseForm[i].lower*_x_coeff;
    pulseForm[i].upper = pulseForm[i].upper*_x_coeff;

    pulseForm[i].tail = QPointF(pulseForm[i].tail.x()*_x_coeff,pulseForm[i].tail.y()*_y_coeff);
    pulseForm[i].head = QPointF(pulseForm[i].head.x()*_x_coeff,pulseForm[i].head.y()*_y_coeff);
  }

}

void ConnectionPulse::defineSpeed()
{
  qreal fullLength = Width_ - borderLineWidth;
  qreal shotsCount = (Duration*1000)/timerInterval;
  sampleIncrement = fullLength/shotsCount;
}

QList<QLineF> ConnectionPulse::getLines(qreal X_tail, qreal X_head)
{
  QList<QLineF> listArr;
  foreach (auto line, pulseForm)
  {
    if(X_tail<=line.lower&&X_head>line.upper)
    {
      listArr.push_back(QLineF(line.tail,line.head));
    }
    if(X_tail<=line.lower&&X_head<=line.upper)
    {
      qreal _y = line.k*X_head+line.c;
      listArr.push_back(QLineF(line.tail,QPointF(X_head,_y)));
      break;
    }

    if(X_tail>line.lower && X_tail<line.upper && X_head>line.upper)
    {
      qreal _y = line.k*X_tail+line.c;
      listArr.push_back(QLineF(QPointF(X_tail,_y),line.head));
    }

    if(X_tail>line.lower&&X_head<line.upper)
    {
      qreal _y_tail = line.k*X_tail+line.c;
      qreal _y_head = line.k*X_head+line.c;
      listArr.push_back(QLineF(QPointF(X_tail,_y_tail),QPointF(X_head,_y_head)));
      break;
    }
  }
  return listArr;
}

QList<QLineF> ConnectionPulse::getGrid()
{
  QList<QLineF> lines;
  qreal xStep = this->width()/ScaleX;
  qreal fixedY = this->height()-borderLineWidth;
  qreal xLimit = this->width();
  for(int i=1;i<ScaleX;i++)
  {
    if(i*xStep>xLimit)
      break;
    lines.push_back(QLine(i*xStep,borderLineWidth,i*xStep,fixedY));
  }

  qreal yStep = this->height()/ScaleY;
  qreal fixedX = this->width()-borderLineWidth;
  qreal yLimit = this->height();
  for(int i=1;i<ScaleY;i++)
  {
    if(i*yStep>yLimit)
      break;
    lines.push_back(QLine(borderLineWidth,i*yStep,fixedX-borderLineWidth,i*yStep));
  }

  return lines;
}

void ConnectionPulse::onTimerTicked()
{
  if(sampleHead>=Width_)
  {
    if(sampleTail<Width_)
    {
      sampleHead = Width_;
      sampleTail+=sampleIncrement;
    }
    else
    {
      sampleHead = 1;
      sampleTail = sampleHead-sampleLength;
    }
  }
  else
  {
    sampleTail+=sampleIncrement;
    sampleHead+=sampleIncrement;
  }
  this->update();
  this->repaint();
}

