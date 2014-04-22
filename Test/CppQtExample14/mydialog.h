#ifndef MYDIALOG_H
#define MYDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>
#include <QDialog>
#pragma GCC diagnostic pop

//Forward declarations
class QVBoxLayout;
class QPushButton;

class MyDialog : public QDialog
{
  Q_OBJECT

public:

  MyDialog();

private:

  boost::shared_ptr<QVBoxLayout> m_layout;
  boost::shared_ptr<QPushButton> m_button1;
  boost::shared_ptr<QPushButton> m_button2;
  int m_clicks;

private slots:
  void buttonClicked();

};

#endif // MYDIALOG_H
