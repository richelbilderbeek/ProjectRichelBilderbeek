#ifndef QTDIALOG_H
#define QTDIALOG_H

#include <boost/shared_ptr.hpp>
#include <QDialog>

struct MyData;

namespace Ui {
  class QtDialog;
}

struct QStandardItemModel;

class QtDialog : public QDialog
{
  Q_OBJECT
  
public:
  explicit QtDialog(QWidget *parent = 0);
  ~QtDialog();
  
private slots:

private:
  Ui::QtDialog *ui;
  boost::shared_ptr<MyData> m_data;
};

#endif // QTDIALOG_H
