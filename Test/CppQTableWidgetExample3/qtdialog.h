#ifndef QTDIALOG_H
#define QTDIALOG_H

#include <string>
#include <tuple>
#include <vector>
#include <QDialog>

namespace Ui {
  class QtDialog;
}

class QtDialog : public QDialog
{
  Q_OBJECT

public:
  typedef std::tuple<bool,bool,bool,std::string> Tuple;
  explicit QtDialog(QWidget *parent = 0);
  ~QtDialog();

private:
  Ui::QtDialog *ui;

  std::vector<std::tuple<bool,bool,bool,std::string> > m_data;

  static const std::vector<Tuple> CreateData();
};

#endif // QTDIALOG_H
