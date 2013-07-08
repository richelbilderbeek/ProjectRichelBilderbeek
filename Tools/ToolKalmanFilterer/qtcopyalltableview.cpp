#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtcopyalltableview.h"

#include <QApplication>
#include <QClipboard>
#include <QHeaderView>
#include <QKeyEvent>

#include "trace.h"

QtCopyAllTableView::QtCopyAllTableView(QWidget *parent)
  : QTableView(parent)
{
}

void QtCopyAllTableView::keyPressEvent(QKeyEvent *event)
{
  if(event->key() == Qt::Key_A
    && event->modifiers() & Qt::ControlModifier)
  {
    this->selectAll();
    return;
  }
  if(event->key() == Qt::Key_C
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
}
