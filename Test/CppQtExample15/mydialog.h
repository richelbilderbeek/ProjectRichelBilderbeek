#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <vector>
#include <boost/shared_ptr.hpp>
#include <QDialog>

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
  boost::shared_ptr<QHBoxLayout> m_layout;
  std::vector<boost::shared_ptr<MyDialog> > m_children;

private slots:
  void button1clicked();
  void button2clicked();
};

#endif // MYDIALOG_H
