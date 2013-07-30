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

  const int n_rows = static_cast<int>(m_data.size());
  const int n_cols = std::tuple_size<Tuple>::value;
  t->setRowCount(n_rows);
  t->setColumnCount(n_cols);

  for (int row=0; row!=n_rows; ++row)
  {
    const Tuple& tuple = m_data[row];
    for (int col=0; col!=n_cols; ++col)
    {
      QTableWidgetItem * const i = new QTableWidgetItem;
      if (std::tuple_element<col,Tuple>::type == bool)
      {
        //Checkbox
        i->setFlags(
            Qt::ItemIsSelectable
          | Qt::ItemIsUserCheckable
          | Qt::ItemIsEnabled
        );
        i->setCheckState(std::get<col>(tuple) ? Qt::Checked : Qt::Unchecked);
      }
      else
      {
        static_assert(std::is_same<std::tuple_element<col,Tuple>::type,std::string>(),
          "Either have bools or std::strings");
        //Text
        i->setFlags(
            Qt::ItemIsSelectable
          | Qt::ItemIsEditable
          | Qt::ItemIsEnabled);
        const std::string s = std::get<col>(tuple);
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
