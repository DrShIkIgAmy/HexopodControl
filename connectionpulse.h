#ifndef CONNECTIONPULSE_H
#define CONNECTIONPULSE_H

#include <QObject>
#include <QWidget>
#include <QList>
#include <QTimer>
#include "pulseform.h"



class ConnectionPulse : public QWidget
{
  Q_OBJECT
private:


public:
  explicit ConnectionPulse(QWidget *parent = 0);
private:
  QList<FormLines> pulseForm = PulseForm::InitializePulseForm();
  qreal Heigth_ = -1;
  qreal Width_ = -1;

  qreal sampleIncrement = 12;
  qreal sampleTail = -1;
  qreal sampleHead = borderLineWidth;

  int timerInterval = 20;
  QTimer* tim = NULL;


  qreal sampleLength = 0.5;
  qreal pointHalo = 0.1;
protected:
    void paintEvent(QPaintEvent *event);
signals:
private:
    void defineCoeffs();
    void scalePulseForm(qreal _w,qreal _h);
    void defineSpeed();
    void drawWidget(QPainter* painterInst);
    void drawLines(QPainter* painterInst);
    void drawGrid(QPainter* painterInst);
    void drawCircule(QPainter* painterInst);
    void widgetInfoCalculation();
    QList<QLineF> getLines(qreal X_tail,qreal X_head);
    QList<QLineF> getGrid();
private slots:
    void onTimerTicked();
public:
    /*//////////////////////////*/
    /*//////////////////////////*/
    //.///--> Properties <--///.//
    /*//////////////////////////*/
    /*//////////////////////////*/
    qreal gridLineWidth = 0.5;
    qreal borderLineWidth = 3;
    qreal pulseLineWidth = 3;
    qreal sampleLengthScale = 0.5;
    qreal pointRad = 7;
    qreal pointHaloScale = 0.15;
    qreal ScaleX = 10;
    qreal ScaleY = 5;
    qreal Duration = 1.5;
    /*///////// Colors /////////*/
    QString widgetBackgroundColor = "#170D09";
    QString gridLinesColor = "#cc0000";
    QString borderColor = "#cc0000";
    QString pulseLineColor = "#00d200";
    QString pulseCircleColor = "#00ff00";


};

#endif // CONNECTIONPULSE_H
