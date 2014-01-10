#ifndef QTTESTTEXTCANVASMAINDIALOG_H
#define QTTESTTEXTCANVASMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtTestTextCanvasMainDialog;
}

namespace ribi {

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

private:
  Ui::QtTestTextCanvasMainDialog *ui;
  boost::shared_ptr<TextCanvas> m_canvas;

  static const boost::shared_ptr<TextCanvas> CreateCanvas();
  void ShowCanvas(const TextCanvas * const canvas = nullptr);

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTESTTEXTCANVASMAINDIALOG_H
