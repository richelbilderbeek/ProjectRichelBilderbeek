#include "qtdialog.h"

#include <cassert>
#include <iostream>
#include <stdexcept>

#include <boost/lexical_cast.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <QHeaderView>
#include <QStandardItemModel>
#include "ui_qtdialog.h"

struct MyModel : public QStandardItemModel
{
  MyModel(QObject *parent = 0)
    : QStandardItemModel(parent)
  {
    const int n_rows = 3;
    const int n_cols = 4;
    this->setColumnCount(n_cols);
    this->setRowCount(n_rows);
    for (int row = 0; row!=n_rows; ++row)
    {
      for (int col = 0; col!=n_cols; ++col)
      {
        QStandardItem * const item = new QStandardItem;
        const std::string s
          =
            std::string("(")
          + boost::lexical_cast<std::string>(row)
          + std::string(",")
          + boost::lexical_cast<std::string>(row)
          + std::string(")");
        item->setText(s.c_str());
        this->setItem(row,col,item);

      }
    }
  }
};

QtDialog::QtDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtDialog),
  m_model(new MyModel(this))
{
  ui->setupUi(this);

  ui->table_left->setModel(m_model);
  ui->table_right->setModel(m_model);
  assert(ui->table_left->model());
  assert(ui->table_right->model());
  assert(m_model);
  assert(ui->table_left->model() == m_model);
  assert(ui->table_right->model() == m_model);
}

QtDialog::~QtDialog()
{
  delete ui;
}
