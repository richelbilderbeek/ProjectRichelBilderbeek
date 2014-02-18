#ifndef QTIMAGEROTATERMAINDIALOG_H
#define QTIMAGEROTATERMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#include <QImage>
#pragma GCC diagnostic pop

namespace Ui {
  class QtImageRotaterMainDialog;
}

struct QLabel;

namespace ribi {

class QtImageRotaterMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtImageRotaterMainDialog(QWidget *parent = 0);
  QtImageRotaterMainDialog(const QtImageRotaterMainDialog&) = delete;
  QtImageRotaterMainDialog& operator=(const QtImageRotaterMainDialog&) = delete;
  ~QtImageRotaterMainDialog() noexcept;

private slots:
  void on_button_load_clicked();
  void on_button_save_clicked();

  void on_dial_angle_sliderMoved(int position);

private:
  Ui::QtImageRotaterMainDialog *ui;
  QImage m_source;
  QLabel * m_target;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  double GetAngle() const noexcept;

  void OnAnyChange();

};

} //~namespace ribi

#endif // QTIMAGEROTATERMAINDIALOG_H
