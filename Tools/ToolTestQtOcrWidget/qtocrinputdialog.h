#ifndef QTOCRDIALOG_H
#define QTOCRDIALOG_H

#include <boost/shared_ptr.hpp>

#include <QDialog>

namespace Ui {
  class QtOcrInputDialog;
}

struct QtOcrWidget;

///QtOcrInputDialog displays a GUI for the QtOcrWidget
class QtOcrInputDialog : public QDialog
{
  Q_OBJECT

public:
  explicit QtOcrInputDialog(
    const std::string& path,
    const std::string& whitelist,
    QWidget *parent = 0);
  ~QtOcrInputDialog();

protected:
  void paintEvent(QPaintEvent *);

private slots:
  void on_button_clear_clicked();

private:
  Ui::QtOcrInputDialog *ui;
  boost::shared_ptr<QtOcrWidget> m_ocr_widget;
};

#endif // QTOCRDIALOG_H

