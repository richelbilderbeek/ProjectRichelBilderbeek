#ifndef QTDIALOG_H
#define QTDIALOG_H

/*

#include <string>
#include <tuple>
#include <vector>

#include <boost/ref.hpp>
#include <QDialog>

struct QTableWidget;

namespace Ui {
  class QtDialog;
}

class QtDialog : public QDialog
{
  Q_OBJECT

public:
  typedef std::tuple<bool,bool,bool,std::string> Tuple;
  typedef std::tuple<
    boost::reference_wrapper<bool>,
    boost::reference_wrapper<bool>,
    boost::reference_wrapper<bool>,
    boost::reference_wrapper<std::string> >RefTuple;
  explicit QtDialog(QWidget *parent = 0);
  ~QtDialog();

private:
  Ui::QtDialog *ui;

  std::vector<Tuple> m_data;

  static const std::vector<Tuple> CreateData();

  ///Dump display of data
  static void DataToTable(const std::vector<Tuple>& data, QTableWidget * const table);

signals:
  void OnCellChanged(int row, int column);
};

*/

#endif // QTDIALOG_H
