#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtcopyalltableview.h"

#include <string>
#include <vector>

#include <boost/algorithm/string/split.hpp>

#include <QApplication>
#include <QClipboard>
#include <QHeaderView>
#include <QKeyEvent>
#include <QMimeData>

#include "container.h"
#include "trace.h"

#pragma GCC diagnostic pop

ribi::QtCopyAllTableView::QtCopyAllTableView(QWidget *parent)
  : QTableView(parent)
{

}

void ribi::QtCopyAllTableView::keyPressEvent(QKeyEvent *event)
{
  if(event->key() == Qt::Key_A
    && event->modifiers() & Qt::ControlModifier)
  {
    this->selectAll();
  }
  else if(event->key() == Qt::Key_C
    && event->modifiers() & Qt::ControlModifier)
  {
    this->selectAll();
    const int n_rows = this->model()->rowCount();
    const int n_cols = this->model()->columnCount();
    QByteArray byte_array;
    //Header
    {
      byte_array.append(" \t"); //Topleft header cell
      for (int col = 0; col!=n_cols; ++col)
      {
        const QString s = this->model()->headerData(col,Qt::Horizontal).toString();
        const QString text = s.isEmpty()
          ? QString(" ")
          : s;
        byte_array.append(text);
        byte_array.append(col < n_cols - 1 ? '\t' : '\n');
      }
    }
    for (int row = 0; row!=n_rows; ++row)
    {
      //Vertical header
      {
        const QString s = this->model()->headerData(row,Qt::Vertical).toString();
        const QString text = s.isEmpty()
          ? QString(" ")
          : s;
        byte_array.append(text);
        byte_array.append('\t');
      }
      //Normal items
      for (int col = 0; col!=n_cols; ++col)
      {
        const QString s = this->model()->data( this->model()->index( row,col) ).toString();
        const QString text = s.isEmpty()
          ? QString(" ")
          : s;
        byte_array.append(text);
        byte_array.append(col < n_cols - 1 ? '\t' : '\n');
      }
    }
    QMimeData * mimeData = new QMimeData();
    mimeData->setData("text/plain",byte_array);
    QApplication::clipboard()->setMimeData(mimeData);
  }
  else if (event->modifiers() & Qt::ControlModifier && event->key() == Qt::Key_V)
  {
    std::vector<std::vector<std::string> > table;
    {
      const std::string raw_str = QApplication::clipboard()->text().toStdString();
      const std::vector<std::string> rows = Container().SeperateString(raw_str,'\n');
      const std::size_t n_rows = rows.size();
      for (std::size_t row_index=0; row_index!=n_rows; ++row_index)
      {
        const std::string& row_str = rows[row_index];
        const std::vector<std::string> cols = Container().SeperateString(row_str,'\t');
        table.push_back(cols);
      }
    }

    const std::size_t n_rows = table.size();
    if (n_rows == 0) return;
    for (std::size_t row_index=0; row_index!=n_rows; ++row_index)
    {
      const std::vector<std::string>& row = table[row_index];
      const std::size_t n_cols = row.size(); //Note that n_cols might change per row
      for (std::size_t col_index=0; col_index!=n_cols; ++col_index)
      {
        const std::string str = row[col_index];
        const QString q = str.c_str();
        const QModelIndex index = model()->index(row_index,col_index);
        model()->setData(index,q);
      }
    }
    this->selectAll();
  }
  else
  {
    QTableView::keyPressEvent(event);
  }
}

