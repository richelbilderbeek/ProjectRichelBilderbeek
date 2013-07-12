#ifndef QTDIALOG_H
#define QTDIALOG_H

#include <QDialog>
#include <QtSql>

namespace Ui {
  class QtDialog;
}

class QtDialog : public QDialog
{
  Q_OBJECT
  
public:
  explicit QtDialog(QWidget *parent = 0);
  ~QtDialog();
  
private slots:
  void on_edit_sql_textChanged(const QString &arg1);

private:
  Ui::QtDialog *ui;
  QSqlDatabase m_database;

  static const QSqlDatabase CreateDatabase();
};

#endif // QTDIALOG_H
