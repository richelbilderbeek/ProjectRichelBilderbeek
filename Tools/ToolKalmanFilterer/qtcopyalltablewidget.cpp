#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtcopyalltablewidget.h"

#include <string>
#include <vector>

#include <boost/algorithm/string/split.hpp>

#include <QApplication>
#include <QClipboard>
#include <QKeyEvent>
#include <QMimeData>

#include "trace.h"

#pragma GCC diagnostic pop

ribi::QtCopyAllTableWidget::QtCopyAllTableWidget(QWidget *parent)
  : QTableWidget(parent)
{

}

void ribi::QtCopyAllTableWidget::keyPressEvent(QKeyEvent *event)
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
    const int n_rows = this->rowCount();
    const int n_cols = this->columnCount();
    QByteArray byte_array;
    //Header
    {
      byte_array.append(" \t"); //Topleft header cell
      for (int col = 0; col!=n_cols; ++col)
      {
        const QTableWidgetItem * const item = this->horizontalHeaderItem(col);
        const QString text = item
          ? item->text()
          : QString(" ");
        byte_array.append(text);
        byte_array.append(col < n_cols - 1 ? '\t' : '\n');
      }
    }
    for (int row = 0; row!=n_rows; ++row)
    {
      //Vertical header
      {
        const QTableWidgetItem * const item = this->verticalHeaderItem(row);
        const QString text = item
          ? item->text()
          : QString(" ");
        byte_array.append(text);
        byte_array.append('\t');
      }
      //Normal items
      for (int col = 0; col!=n_cols; ++col)
      {
        const QTableWidgetItem * const item = this->item(row,col);
        const QString text = item
          ? item->text()
          : QString(" ");
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
      const std::vector<std::string> rows = SeperateString(raw_str,'\n');
      const std::size_t n_rows = rows.size();
      for (std::size_t row_index=0; row_index!=n_rows; ++row_index)
      {
        const std::string& row_str = rows[row_index];
        const std::vector<std::string> cols = SeperateString(row_str,'\t');
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
        QTableWidgetItem * const item = new QTableWidgetItem;
        item->setText(q);
        this->setItem(row_index,col_index,item);
      }
    }
    this->selectAll();
  }
  else
  {
    QTableWidget::keyPressEvent(event);
  }
}

std::vector<std::string> ribi::QtCopyAllTableWidget::SeperateString(
  const std::string& input,
  const char seperator)
{
  std::vector<std::string> v;
  boost::algorithm::split(v,input,
    std::bind2nd(std::equal_to<char>(),seperator),
    boost::algorithm::token_compress_on);
  return v;
}
