#ifndef QTDIALOG_H
#define QTDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <QDialog>
#include <QtSql>
#pragma GCC diagnostic pop

namespace Ui {
  class QtDialog;
}

class QtDialog : public QDialog
{
  Q_OBJECT
  
public:
  explicit QtDialog(QWidget *parent = 0);
  QtDialog(const QtDialog&) = delete;
  QtDialog& operator=(const QtDialog&) = delete;
  ~QtDialog();
  
private:
  Ui::QtDialog *ui;
  QSqlDatabase m_database;

  static const QSqlDatabase CreateDatabase();
};

#endif // QTDIALOG_H
