#include <cassert>
#include <string>

#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTimer>
#include "dialog.h"
#include "ui_dialog.h"

//Constructor
//Let it be
Dialog::Dialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Dialog),
  m_serial(AcquireSerialPort())
{
  ui->setupUi(this);

  if (!m_serial)
  {
    this->setWindowTitle("No serial port found");
  }
  else
  {
    QTimer * const timer(new QTimer(this));
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(OnTimer()));
    timer->setInterval(100);
    timer->start();
  }
}

//Destructor
//Let it be
Dialog::~Dialog()
{
  delete m_serial;
  delete ui;
}

//Member function to get access to the serial port
//Let it be
QSerialPort * Dialog::AcquireSerialPort()
{
  foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
  {
    QSerialPort * const serial(new QSerialPort);
    serial->setPort(info);
    if (serial->open(QIODevice::ReadWrite))
    {
      return serial;
    }
  }
  return 0;
}

//Change this code
void Dialog::OnTimer()
{
  //Read data from the serial port
  const QByteArray b = m_serial->readAll();

  //If nothing is read, return
  if (b.isEmpty()) return;

  //Convert the raw data to a string
  const std::string s(b);

  //Because we know the string can also be converted to an int, do so
  const int i = std::atoi(b);

  //Display the int as the value in the progress bar
  this->ui->progressBar->setValue(i);
}

