#include "trafficlightdialog.h"

#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QVBoxLayout>
#include "ui_trafficlightdialog.h"
#include "image.h"
#pragma GCC diagnostic pop

TrafficLightDialog::TrafficLightDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TrafficLightDialog),
    m_red(new Image(":/images/RedOff64x64.png")),
    m_orange(new Image(":/images/OrangeOff64x64.png")),
    m_green(new Image(":/images/GreenOff64x64.png")),
    m_red_on(new Image(":/images/Red64x64.png")),
    m_orange_on(new Image(":/images/Orange64x64.png")),
    m_green_on(new Image(":/images/Green64x64.png")),
    m_red_off(new Image(":/images/RedOff64x64.png")),
    m_orange_off(new Image(":/images/OrangeOff64x64.png")),
    m_green_off(new Image(":/images/GreenOff64x64.png"))
    //m_red_on(false),
    //m_orange_on(false),
    //m_green_on(false)

{
  ui->setupUi(this);

  m_red->setAlignment(Qt::AlignHCenter);
  m_orange->setAlignment(Qt::AlignHCenter);
  m_green->setAlignment(Qt::AlignHCenter);
  QVBoxLayout * layout = new QVBoxLayout(this);

  layout->addWidget(m_red.get());
  layout->addWidget(m_orange.get());
  layout->addWidget(m_green.get());

  m_red->connect(m_red.get(),SIGNAL(onClick()),this,SLOT(onRedClicked()));
  m_red->connect(m_orange.get(),SIGNAL(onClick()),this,SLOT(onOrangeClicked()));
  m_red->connect(m_green.get(),SIGNAL(onClick()),this,SLOT(onGreenClicked()));

}

TrafficLightDialog::~TrafficLightDialog()
{
  delete ui;
}

void TrafficLightDialog::onRedClicked()
{
  std::clog << "Red clicked\n";
  m_red->setPixmap(*m_red_on->pixmap());
  m_orange->setPixmap(*m_orange_off->pixmap());
  m_green->setPixmap(*m_green_off->pixmap());
}

void TrafficLightDialog::onOrangeClicked()
{
  std::clog << "Orange clicked\n";
  m_red->setPixmap(*m_red_off->pixmap());
  m_orange->setPixmap(*m_orange_on->pixmap());
  m_green->setPixmap(*m_green_off->pixmap());
}

void TrafficLightDialog::onGreenClicked()
{
  std::clog << "Green clicked\n";
  m_red->setPixmap(*m_red_off->pixmap());
  m_orange->setPixmap(*m_orange_off->pixmap());
  m_green->setPixmap(*m_green_on->pixmap());
}
