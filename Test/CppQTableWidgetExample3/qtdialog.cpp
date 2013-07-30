#include "qtdialog.h"

#include <string>

#include <boost/lexical_cast.hpp>

#include "ui_qtdialog.h"

QtDialog::QtDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QtDialog),
    m_data(CreateData())
{
  ui->setupUi(this);

  QTableWidget * const t = ui->table_edit;
  t->setRowCount(10);
  const int n_rows = t->rowCount();
  const int n_cols = t->columnCount();
  for (int col=0; col!=n_cols; ++col)
  {
    for (int row=0; row!=n_rows; ++row)
    {
      QTableWidgetItem * const i = new QTableWidgetItem;
      if (col != 3)
      {
        //Checkbox
        i->setFlags(
            Qt::ItemIsSelectable
          | Qt::ItemIsUserCheckable
          | Qt::ItemIsEnabled
        );
        i->setCheckState(Qt::Unchecked);
      }
      else
      {
        //Text
        i->setFlags(
            Qt::ItemIsSelectable
          | Qt::ItemIsEditable
          | Qt::ItemIsEnabled);
        const std::string s = "("
          + boost::lexical_cast<std::string>(col)
          + ","
          + boost::lexical_cast<std::string>(row)
          + ")";
        i->setText(s.c_str());
      }
      t->setItem(row, col, i);
    }
  }
  t->setColumnWidth(0,24);
  t->setColumnWidth(1,24);
  t->setColumnWidth(2,24);
}

QtDialog::~QtDialog()
{
  delete ui;
}

const std::vector<std::tuple<bool,bool,bool,std::string> > QtDialog::CreateData()
{
  return
  {
    std::make_tuple(false,false,false,"One"),
    std::make_tuple(false,false, true,"Two"),
    std::make_tuple(false, true,false,"Three"),
    std::make_tuple(false, true, true,"Four"),
    std::make_tuple( true,false,false,"Five"),
    std::make_tuple( true,false, true,"Six"),
    std::make_tuple( true, true,false,"Seven"),
    std::make_tuple( true, true, true,"Eight")
  };

}
