#ifndef QTFILTEROPERATIONERMAINDIALOG_H
#define QTFILTEROPERATIONERMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtFilterOperationerMainDialog;
}

struct QPixmap;
struct QLabel;

namespace ribi {

struct QtUblasMatrixDoubleModel;

class QtFilterOperationerMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtFilterOperationerMainDialog(QWidget *parent = 0);
  QtFilterOperationerMainDialog(const QtFilterOperationerMainDialog&) = delete;
  QtFilterOperationerMainDialog& operator=(const QtFilterOperationerMainDialog&) = delete;
  ~QtFilterOperationerMainDialog() noexcept;

private slots:
  void on_button_do_clicked();
  void on_button_load_clicked();

  void on_button_save_clicked();

  void on_box_filter_cols_valueChanged(int arg1);

  void on_box_filter_rows_valueChanged(int arg1);

private:
  Ui::QtFilterOperationerMainDialog *ui;

  QtUblasMatrixDoubleModel * const m_model;
  ///The normal result
  QLabel * m_result;

  ///The source
  QLabel * m_source;

  void OnAnyChange() noexcept;
  void ShowLoadedPixmap(const QPixmap& pixmap);
  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTFILTEROPERATIONERMAINDIALOG_H
