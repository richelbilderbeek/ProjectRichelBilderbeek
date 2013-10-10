#ifndef QTTOOLTESTCANVASMAINDIALOG_H
#define QTTOOLTESTCANVASMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtToolTestCanvasMainDialog;
}

namespace ribi {

struct Canvas;

class QtToolTestCanvasMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtToolTestCanvasMainDialog(QWidget *parent = 0);
  QtToolTestCanvasMainDialog(const QtToolTestCanvasMainDialog&) = delete;
  QtToolTestCanvasMainDialog& operator=(const QtToolTestCanvasMainDialog&) = delete;
  ~QtToolTestCanvasMainDialog() noexcept;
  
private slots:

  void on_box_color_system_currentIndexChanged(int index);

  void on_box_coordinat_system_currentIndexChanged(int index);

  void on_button_dot_clicked();

  void on_button_clear_clicked();

  void on_button_circle_clicked();

  void on_button_line_clicked();

private:
  Ui::QtToolTestCanvasMainDialog *ui;
  boost::shared_ptr<Canvas> m_canvas;

  static const boost::shared_ptr<Canvas> CreateCanvas();
  void ShowCanvas(const ribi::Canvas * const canvas = nullptr);
};

} //~namespace ribi

#endif // QTTOOLTESTCANVASMAINDIALOG_H
