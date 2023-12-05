#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  composeData();
  connect(ui->joyStick,SIGNAL(thumbMoved(double,double)),this,SLOT(onJoystickUpdate(double,double)));
  comPortSetUp("COM15");
  applyStyleSheet();
}



MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::onJoystickUpdate(double power, double angle)
{
  dataInstance.Joystick_Power = (int)power;
  dataInstance.Joystick_Angle = (int)(angle*57.2957795131);
  double motor_1 = 10*cos((150-dataInstance.Joystick_Angle)/57.2957795131);
  double motor_2 = 10*cos((30-dataInstance.Joystick_Angle)/57.2957795131);
  double motor_3 = 10*cos((270-dataInstance.Joystick_Angle)/57.2957795131);
}

void MainWindow::onReadyRead()
{
  inpBuff = _comPort->readAll();
  //if(inpBuff.toStdString()=="ok\n")
  {
    auto dataToWrite = toByteArray();
    _comPort->write(dataToWrite);
  }
}

void MainWindow::applyStyleSheet()
{
  QFile file(":/styleSheet/styles.qss");
  file.open(QFile::ReadOnly);
  setStyleSheet(QLatin1String(file.readAll()));
  qDebug()<<"Style applied";
}

void MainWindow::composeData()
{
  dataInstance.MessageType = 128;
  dataInstance.MessageLength = 38;
  dataInstance.Joystick_Angle = 0;
  dataInstance.Joystick_Power = 0;
  dataInstance.Chassis_Turn = 0;
  dataInstance.AxisIncrement = 0;
  dataInstance.grabState = 0;
  dataInstance.Servo_1 = 0;
  dataInstance.Servo_2 = 0;
  dataInstance.Servo_3 = 0;
  dataInstance.Servo_4 = 0;
  dataInstance.firstEOF = 1;
  dataInstance.secondEOF = 254;
}

QByteArray MainWindow::toByteArray()
{
  QByteArray data;
  QDataStream out(&data, QIODevice::WriteOnly);
  out << (qint8)dataInstance.MessageType;
  out << (qint16)dataInstance.MessageLength;
  out << (qint32)dataInstance.Joystick_Angle;
  out << (qint32)dataInstance.Joystick_Power;
  out << (qint32)dataInstance.Chassis_Turn;
  out << (qint32)dataInstance.AxisIncrement;
  out << (qint32)dataInstance.grabState;
  out << (qint32)dataInstance.Servo_1;
  out << (qint32)dataInstance.Servo_2;
  out << (qint32)dataInstance.Servo_3;
  out << (qint32)dataInstance.Servo_4;
  out << (qint8)dataInstance.firstEOF;
  out << (qint8)dataInstance.secondEOF;
  return data;
}

void MainWindow::comPortSetUp(QString comName)
{
  _comPort = new QSerialPort(comName);
  _comPort->setBaudRate(QSerialPort::Baud9600);
  _comPort->setDataBits(QSerialPort::Data8);
  connect(_comPort,SIGNAL(readyRead()),this,SLOT(onReadyRead()));
  qDebug()<<_comPort->open(QIODevice::ReadWrite);
  qDebug()<<_comPort->errorString();
}
