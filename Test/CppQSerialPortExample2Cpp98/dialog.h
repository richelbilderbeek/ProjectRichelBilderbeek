#ifndef DIALOG_H
#define DIALOG_H

#include <memory>
#include <QDialog>

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
  static std::string IntToStr(const int x);
};

#endif // DIALOG_H
