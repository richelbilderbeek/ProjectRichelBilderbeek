#include "qtdialog.h"

/*
#include <string>

#include <boost/lexical_cast.hpp>

#include "ui_qtdialog.h"

QtDialog::QtDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QtDialog),
    m_data(CreateData())
{
  ui->setupUi(this);


  DataToTable(m_data,ui->table_edit);
  DataToTable(m_data,ui->table_display);

  QObject::connect(ui->table_edit,SIGNAL(cellChanged(int,int)),this,OnCellChanged(int,int));
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

void QtDialog::DataToTable(const std::vector<Tuple>& data, QTableWidget * const t)
{
  const int n_rows = static_cast<int>(data.size());
  const int n_cols = std::tuple_size<Tuple>::value;
  assert(n_cols == 4);
  t->setRowCount(n_rows);
  t->setColumnCount(n_cols);

  for (int row=0; row!=n_rows; ++row)
  {
    const Tuple& tuple = data[row];
    for (int col=0; col!=n_cols; ++col)
    {
      QTableWidgetItem * const i = new QTableWidgetItem;
      switch (col)
      {
        case 0:
          static_assert(std::is_same<std::tuple_element<0,Tuple>::type,bool>(),"First element is bool");
          //Checkbox
          i->setFlags(
              Qt::ItemIsSelectable
            | Qt::ItemIsUserCheckable
            | Qt::ItemIsEnabled
          );
          i->setCheckState(std::get<0>(tuple) ? Qt::Checked : Qt::Unchecked);
          break;

        case 1:
          static_assert(std::is_same<std::tuple_element<1,Tuple>::type,bool>(),"Second element is bool");
          //Checkbox
          i->setFlags(
              Qt::ItemIsSelectable
            | Qt::ItemIsUserCheckable
            | Qt::ItemIsEnabled
          );
          i->setCheckState(std::get<1>(tuple) ? Qt::Checked : Qt::Unchecked);
          break;

        case 2:
          static_assert(std::is_same<std::tuple_element<2,Tuple>::type,bool>(),"Third element is bool");
            //Checkbox
          i->setFlags(
              Qt::ItemIsSelectable
            | Qt::ItemIsUserCheckable
            | Qt::ItemIsEnabled
          );
          i->setCheckState(std::get<2>(tuple) ? Qt::Checked : Qt::Unchecked);
          break;

        case 3:
          static_assert(std::is_same<std::tuple_element<3,Tuple>::type,std::string>(),"Fourth element is std::string");
          i->setFlags(
              Qt::ItemIsSelectable
            | Qt::ItemIsEditable
            | Qt::ItemIsEnabled);
          i->setText(std::get<3>(tuple).c_str());
          break;
        default:
          assert(!"Should not get here");
          break;

      }
      t->setItem(row, col, i);
    }
  }
  t->setColumnWidth(0,24);
  t->setColumnWidth(1,24);
  t->setColumnWidth(2,24);
}

void QtDialog::OnCellChanged(int row, int column)
{
  qDebug() << "Cell changed: " << row << "," << column << "\n";
  ui->table_edit->itemAt(row,col)->checkState()

}
*/
