#include "qtdialog.h"

#include <string>

#include <boost/lexical_cast.hpp>

#include "ui_qtdialog.h"

QtDialog::QtDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QtDialog)
{
  ui->setupUi(this);

  QTableWidget * const t = ui->tableWidget;
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
          //| Qt::ItemIsEnabled
        );
        //i->setFlags(
        //    Qt::ItemIsSelectable
        //  | Qt::ItemIsUserCheckable
        //  | Qt::ItemIsEnabled
        //);
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

void QtDialog::changeEvent(QEvent *e)
{
  QDialog::changeEvent(e);
  switch (e->type()) {
  case QEvent::LanguageChange:
    ui->retranslateUi(this);
    break;
  default:
    break;
  }
}
