#include "mydialog.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QPushButton>
#include <QVBoxLayout>
#pragma GCC diagnostic pop

MyDialog::MyDialog()
  : m_layout(new QVBoxLayout),
  m_button1(new QPushButton),
  m_button2(new QPushButton),
  m_clicks(0)
{
  m_button1->setText("Count");
  m_button1->connect(
      m_button1.get(),SIGNAL(clicked()),
      this,SLOT(buttonClicked()));
  m_button2->setText("Quit");
  m_button2->connect(
      m_button2.get(),SIGNAL(clicked()),
      this,SLOT(close()));
  m_layout->addWidget(m_button1.get());
  m_layout->addWidget(m_button2.get());

  this->setGeometry(0,0,300,100);
  this->setWindowTitle("CppQtExample14");
  this->setLayout(m_layout.get());
}

void MyDialog::buttonClicked()
{
  ++m_clicks;
  QString s; s = s.number(m_clicks);
  this->setWindowTitle("Top button is clicked " + s + " times");
}
