#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtcopyalltablewidget.h"

#include <QApplication>
#include <QClipboard>
#include <QKeyEvent>

#include "trace.h"

QtCopyAllTableWidget::QtCopyAllTableWidget(QWidget *parent)
  : QTableWidget(parent)
{
}

void QtCopyAllTableWidget::keyPressEvent(QKeyEvent *event)
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
}
