#include "qtdialog.h"

#include <cassert>
#include <iostream>
#include <stdexcept>

#include <boost/numeric/conversion/cast.hpp>

#include <QHeaderView>
#include <QStandardItemModel>
#include "ui_qtdialog.h"

struct MyDataRow
{
  MyDataRow(
    const bool any_blue,
    const bool any_green,
    const std::string any_name,
    const bool any_red)
    : blue(any_blue),
      green(any_green),
      name(any_name),
      red(any_red)
  {

  }
  bool blue;
  bool green;
  std::string name;
  bool red;
};

struct MyDataTable
{
  MyDataTable() : data(CreateTable())  {}
  std::vector<MyDataRow> data;
  static const std::vector<MyDataRow> CreateTable()
  {
    return
    {
      MyDataRow(true,true,"White",true),
      MyDataRow(false,false,"Black",false),
      MyDataRow(false,false,"Red",true),
      MyDataRow(false,true,"Yellow",true),
      MyDataRow(false,true ,"Green",false),
      MyDataRow(true,true ,"Cyan",false),
      MyDataRow(true ,false,"Blue",false),
      MyDataRow(true,false,"Magenta",true)
    };
  }
};

struct MyModel : public QStandardItemModel
{

  MyModel(QObject *parent = 0)
    : QStandardItemModel(
        0, //rows, will become 8
        4, //columns
        parent
      ),
      m_data(MyDataTable())
  {
    setColumnCount(4);
    setHeaderData(0,Qt::Horizontal,"R");
    setHeaderData(1,Qt::Horizontal,"G");
    setHeaderData(2,Qt::Horizontal,"B");
    setHeaderData(3,Qt::Horizontal,"Color");
    const int n_rows = boost::numeric_cast<int>(m_data.data.size());
    for (int i=0; i!=n_rows; ++i)
    {
      QList<QStandardItem*> items;
      //Add 'R' checkbox
      {
        QStandardItem * const item = new QStandardItem;
        item->setEditable(true);
        item->setCheckable(true);
        items.push_back(item);
      }
      //Add 'G' checkbox
      {
        QStandardItem * const item = new QStandardItem;
        item->setEditable(true);
        item->setCheckable(true);
        items.push_back(item);
      }
      //Add 'B' checkbox
      {
        QStandardItem * const item = new QStandardItem;
        item->setEditable(true);
        item->setCheckable(true);
        items.push_back(item);
      }
      //Add 'Color' checkbox
      {
        QStandardItem * const item = new QStandardItem;
        item->setFlags(
          Qt::ItemIsSelectable
          | Qt::ItemIsEditable
          | Qt::ItemIsEnabled);
        items.push_back(item);
      }
      assert(this->columnCount() == items.size());
      this->appendRow(items);
    }
    if (!(this->rowCount() == boost::numeric_cast<int>(m_data.data.size())))
    {
      std::cout << this->rowCount() << '\n';
    }
    assert(this->rowCount() == boost::numeric_cast<int>(m_data.data.size()));
  }
  ///Implement virtual member function
  QVariant data(const QModelIndex &index, int role) const
  {
    assert(index.isValid());

    //Removing this line will cause checkboxes to appear
    if (index.column() == 3 && role != Qt::EditRole &&  role != Qt::DisplayRole) return QVariant();

    if (!(index.row() < boost::numeric_cast<int>(m_data.data.size())))
    {
      std::cout << index.row();
    }
    assert(index.row() < boost::numeric_cast<int>(m_data.data.size()));
    assert(index.column() < 4);
    const MyDataRow& row = m_data.data[ index.row() ];
    switch (index.column())
    {
      case 0: return row.red   ? Qt::Checked : Qt::Unchecked;
      case 1: return row.green ? Qt::Checked : Qt::Unchecked;
      case 2: return row.blue  ? Qt::Checked : Qt::Unchecked;
      case 3: return QString(row.name.c_str());
      default:
        assert(!"Should not get here");
        throw std::logic_error("MyModel::data");
    }
  }
  ///Implement virtual member function
  bool setData(const QModelIndex &index, const QVariant &value, int /* role = Qt::EditRole */)
  {
    assert(index.isValid());
    assert(index.row() < boost::numeric_cast<int>(m_data.data.size()));
    assert(index.column() < 4);
    MyDataRow& row = m_data.data[ index.row() ];
    switch (index.column())
    {
      case 0: row.red = value.toBool(); break;
      case 1: row.green = value.toBool(); break;
      case 2: row.blue = value.toBool(); break;
      case 3: row.name = value.toString().toStdString(); break;
      default:
        assert(!"Should not get here");
        throw std::logic_error("MyModel::setData");
    }
    emit dataChanged(index,index);
    return true;
  }
  private:
  MyDataTable m_data;
};


QtDialog::QtDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtDialog),
  m_model(new MyModel(this))
{
  ui->setupUi(this);

  ui->table->setModel(m_model);
  assert(ui->table->model());
  assert(m_model);
  assert(ui->table->model() == m_model);

  ui->table->setColumnWidth(0, 24);
  ui->table->setColumnWidth(1, 24);
  ui->table->setColumnWidth(2, 24);
  ui->table->setColumnWidth(3,175);
}

QtDialog::~QtDialog()
{
  delete ui;
}
