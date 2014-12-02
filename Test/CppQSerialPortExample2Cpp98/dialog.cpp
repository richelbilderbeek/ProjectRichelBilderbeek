#include <cassert>
#include <string>
#include <stdexcept>
#include <sstream>

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
    QTimer * const timer(new QTimer);
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

//Get access to the serial port
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
  //Read the value from the dial
  const int position = ui->dial->value();

  //Convert it to string, that can be send to the Arduino
  std::string s = IntToStr(position);

  //Make sure the string has size 4
  if (s.size() < 4) s = " " + s;

  //Show this string on screen
  ui->label->setText(s.c_str());

  //Write this string to the serial port
  m_serial->write(s.c_str(),4);
}


//From http://www.richelbilderbeek.nl/CppIntToStr.htm
std::string Dialog::IntToStr(const int x)
{
  std::ostringstream s;
  if (!(s << x)) throw std::logic_error("IntToStr failed");
  return s.str();
}
