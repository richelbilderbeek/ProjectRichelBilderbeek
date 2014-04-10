#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>
#include <QDialog>
#pragma GCC diagnostic pop

struct QPushButton;
struct QHBoxLayout;

class MyDialog : public QDialog
{
  Q_OBJECT

public:
  MyDialog(const QString s = "");
  const QString m_string;

private:
  boost::shared_ptr<QPushButton> m_button1;
  boost::shared_ptr<QPushButton> m_button2;
  std::vector<boost::shared_ptr<MyDialog> > m_children;
  boost::shared_ptr<QHBoxLayout> m_layout;

private slots:
  void button1clicked();
  void button2clicked();
};

#endif // MYDIALOG_H
