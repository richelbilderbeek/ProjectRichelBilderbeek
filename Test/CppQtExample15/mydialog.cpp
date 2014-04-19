#include "mydialog.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QPushButton>
#include <QHBoxLayout>
#pragma GCC diagnostic pop

MyDialog::MyDialog(const QString s)
  : m_string(s),
  m_button1(new QPushButton),
  m_button2(new QPushButton),
  m_children{},
  m_layout(new QHBoxLayout)
{
  m_button1->setText("Left");
  m_button2->setText("Right");
  m_layout->addWidget(m_button1.get());
  m_layout->addWidget(m_button2.get());
  this->setLayout(m_layout.get());

  m_button1->connect(
    m_button1.get(),SIGNAL(clicked()),
    this,SLOT(button1clicked()));
  m_button2->connect(
    m_button2.get(),SIGNAL(clicked()),
    this,SLOT(button2clicked()));
  this->setWindowTitle(s);
}

void MyDialog::button1clicked()
{
  boost::shared_ptr<MyDialog> new_dialog(new MyDialog(m_string + "L"));
  m_children.push_back(new_dialog);
  new_dialog->setModal(true);
  new_dialog->show();
}

void MyDialog::button2clicked()
{
  boost::shared_ptr<MyDialog> new_dialog(new MyDialog(m_string + "R"));
  m_children.push_back(new_dialog);
  new_dialog->setModal(true);
  new_dialog->show();
}
