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
  const std::shared_ptr<QSerialPort> m_serial;
  static std::shared_ptr<QSerialPort> AcquireSerialPort() noexcept;
};

#endif // DIALOG_H
