#ifndef MYDIALOG_H
#define MYDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/scoped_ptr.hpp>
#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#pragma GCC diagnostic pop

class MyDialog : public QDialog
{
  Q_OBJECT

public:

  MyDialog()
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
    this->setWindowTitle("CppQtExample13");
    this->setLayout(m_layout.get());
  }

private:
  boost::scoped_ptr<QVBoxLayout> m_layout;
  boost::scoped_ptr<QPushButton> m_button1;
  boost::scoped_ptr<QPushButton> m_button2;
  int m_clicks;

private slots:
  void buttonClicked()
  {
    ++m_clicks;
    QString s; s = s.number(m_clicks);
    this->setWindowTitle("Top button is clicked " + s + " times");
  }
};

#endif // MYDIALOG_H
