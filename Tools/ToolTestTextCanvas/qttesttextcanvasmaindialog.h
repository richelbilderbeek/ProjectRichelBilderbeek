#ifndef QTTESTTEXTCANVASMAINDIALOG_H
#define QTTESTTEXTCANVASMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"
#include "textcanvas.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtTestTextCanvasMainDialog;
}

namespace ribi {

struct QtCanvas;
struct TextCanvas;

class QtTestTextCanvasMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtTestTextCanvasMainDialog(QWidget *parent = 0);
  QtTestTextCanvasMainDialog(const QtTestTextCanvasMainDialog&) = delete;
  QtTestTextCanvasMainDialog& operator=(const QtTestTextCanvasMainDialog&) = delete;
  ~QtTestTextCanvasMainDialog() noexcept;
  
private slots:

  void on_box_coordinat_system_currentIndexChanged(int index);
  void on_button_char_clicked();
  void on_button_clear_clicked();
  void on_button_text_clicked();

  void on_button_as_dialog_clicked();

private:
  Ui::QtTestTextCanvasMainDialog *ui;
  TextCanvas m_canvas;
  QtCanvas * const m_qtcanvas;

  static TextCanvas CreateCanvas();

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTESTTEXTCANVASMAINDIALOG_H
