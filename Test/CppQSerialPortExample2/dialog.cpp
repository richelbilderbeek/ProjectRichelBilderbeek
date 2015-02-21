#include <cassert>
#include <string>

#include <boost/lexical_cast.hpp>
#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTimer>
#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Dialog),
  m_serial{AcquireSerialPort()}
{
  ui->setupUi(this);

  if (!m_serial)
  {
    this->setWindowTitle("No serial port found");
  }
  else
  {
    QTimer * const timer{new QTimer};
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(OnTimer()));
    timer->setInterval(100);
    timer->start();
  }
}

Dialog::~Dialog()
{
  delete ui;
}

std::shared_ptr<QSerialPort> Dialog::AcquireSerialPort() noexcept
{
  for(const QSerialPortInfo &info: QSerialPortInfo::availablePorts())
  {
    std::shared_ptr<QSerialPort> serial{new QSerialPort};
    serial->setPort(info);
    if (serial->open(QIODevice::ReadWrite))
    {
      return serial;
    }
  }
  return std::shared_ptr<QSerialPort>();
}

void Dialog::OnTimer()
{
  const int position{ui->dial->value()};
  std::string s{boost::lexical_cast<std::string>(position)};
  if (s.size() < 4) s = " " + s;
  ui->label->setText(s.c_str());
  m_serial->write(s.c_str(),4);
}
