#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QtSerialPort>
#include <joystick.h>
#include <QString>
#include <QByteArray>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT
private:
  struct Data
  {
    int8_t MessageType;
    int16_t MessageLength;
    int32_t Joystick_Angle;
    int32_t Joystick_Power;
    int32_t Chassis_Turn;
    int32_t AxisIncrement;
    int32_t grabState;
    int32_t Servo_1;
    int32_t Servo_2;
    int32_t Servo_3;
    int32_t Servo_4;
    int8_t firstEOF;
    int8_t secondEOF;
  };

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:
  void onJoystickUpdate(double power,double angle);
  void onReadyRead();
private:
  void applyStyleSheet();
  QByteArray inpBuff;
  QSerialPort* _comPort = NULL;
  Ui::MainWindow *ui;
  Data dataInstance;
private:
  void composeData();
  QByteArray toByteArray();
  void comPortSetUp(QString comName);
};

#endif // MAINWINDOW_H
