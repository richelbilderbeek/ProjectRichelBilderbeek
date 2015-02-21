#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <memory>

namespace Ui {
  class Dialog;
}

struct QSerialPort;

class Dialog : public QDialog
{
  Q_OBJECT
  
public:
  explicit Dialog(QWidget *parent = 0);
  ~Dialog();
  
private slots:
  void OnTimer();

private:
  Ui::Dialog *ui;
  QSerialPort * const m_serial;
  static QSerialPort * AcquireSerialPort();
};

#endif // DIALOG_H
