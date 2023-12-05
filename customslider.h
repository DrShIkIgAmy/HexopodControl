#ifndef CUSTOMSLIDER_H
#define CUSTOMSLIDER_H

#include <QWidget>

class CustomSlider : public QWidget
{
private:
  const double PI_num = 3.14159265359;
  Q_OBJECT
private:
  qreal Size_ = -1;
  qreal pos = -1;
  int initialAngle = 155;
  int stopAngle = 260;
public:
  explicit CustomSlider(QWidget *parent = 0);
protected:
    void paintEvent(QPaintEvent *event);
public:
    qreal grooveWidth = 15;
    qreal boundingBoxScale = 0.8;
    qreal handleScale = 0.01;

    QString grooveColorStart = "#00d200";
    QString grooveColorEnd = "#00ff00";
private:
    qreal _calculateValue(qreal Angle);
    qreal _calculateAngle(qreal X,qreal Y);
    void onSizeChanged();
    void drawGroove(QPainter* painterInst);
    void drawHandle(QPainter* painterInst);
signals:

public slots:
};

#endif // CUSTOMSLIDER_H
