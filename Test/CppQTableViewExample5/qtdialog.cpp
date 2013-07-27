#include "qtdialog.h"

#include <cassert>
#include <iostream>
#include <stdexcept>

#include <boost/numeric/conversion/cast.hpp>

#include <QHeaderView>
#include <QStandardItemModel>
#include "ui_qtdialog.h"

///A simple custom data type
///For now, its just contains a std::vector<std::string>
struct MyDataTable
{
  MyDataTable() : data(CreateTable())  {}
  std::vector<std::string> data;
  static const std::vector<std::string> CreateTable()
  {
    return
    {
      "Black",
      "Blue",
      "Cyan",
      "Green",
      "Magenta"
      "Red",
      "White",
      "Yellow",
    };
  }
};

struct MyModel : public QStandardItemModel
{

  MyModel(QObject *parent = 0)
    : QStandardItemModel(
        0, //rows, will become 8
        1, //columns, only 1 for now
        parent
      ),
      m_data(MyDataTable())
  {
    setColumnCount(1); //Only 1 for now
    setHeaderData(0,Qt::Horizontal,"Color");
    const int n_rows = boost::numeric_cast<int>(m_data.data.size());
    for (int i=0; i!=n_rows; ++i)
    {
      QList<QStandardItem*> items;
      //Add text
      {
        QStandardItem * const item = new QStandardItem;
        item->setCheckable(false); //NO CHECKBOX!
        items.push_back(item);
      }
      //Only have one column for now
      assert(this->columnCount() == items.size());
      this->appendRow(items);
    }
    assert(this->rowCount() == boost::numeric_cast<int>(m_data.data.size()));
  }
  ///Implement virtual member function
  QVariant data(const QModelIndex &index, int role) const
  {
    //Removing this line will cause checkboxes to appear
    if (role != Qt::EditRole &&  role != Qt::DisplayRole) return QVariant();

    assert(index.isValid());
    assert(index.row() < boost::numeric_cast<int>(m_data.data.size()));
    assert(index.column() < 1);
    const std::string& row = m_data.data[ index.row() ];
    switch (index.column())
    {

      case 0:
        //Only 1 column for now
        return QString(row.c_str());
      default:
        assert(!"Should not get here");
        throw std::logic_error("MyModel::data");
    }
  }
  ///Implement virtual member function
  bool setData(const QModelIndex &index, const QVariant &value, int /*role = Qt::EditRole*/)
  {
    assert(index.isValid());
    assert(index.row() < boost::numeric_cast<int>(m_data.data.size()));
    assert(index.column() < 1);
    std::string& row = m_data.data[ index.row() ];
    switch (index.column())
    {

      case 0:
        //Only 1 column for now
        row = value.toString().toStdString(); break;
      default:
        assert(!"Should not get here");
        throw std::logic_error("MyModel::setData");
    }

    //Allows other views to synchronize on this model update
    emit dataChanged(index,index); //From C++ GUI programming with Qt 4, 2nd edition
    return false;
  }
  private:
  ///My custom data type
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
  //Only one column for now
  ui->table->setColumnWidth(0,175);
}

QtDialog::~QtDialog()
{
  delete ui;
}
