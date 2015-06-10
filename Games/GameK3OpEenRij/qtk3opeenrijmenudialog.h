#ifndef QTK3OPEENRIJMENUDIALOG_H
#define QTK3OPEENRIJMENUDIALOG_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtK3OpEenRijMenuDialog;
}

namespace ribi {

struct QtK3OpEenRijSelectPlayerWidget;
struct QtK3OpEenRijResources;

class QtK3OpEenRijMenuDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT

public:
  ///Won't throw, as all resources are present
  explicit QtK3OpEenRijMenuDialog(
    const boost::shared_ptr<const QtK3OpEenRijResources> resources,
    QWidget *parent = 0) noexcept;
  QtK3OpEenRijMenuDialog(const QtK3OpEenRijMenuDialog&) = delete;
  QtK3OpEenRijMenuDialog& operator=(const QtK3OpEenRijMenuDialog&) = delete;
  ~QtK3OpEenRijMenuDialog() noexcept;

private:
  Ui::QtK3OpEenRijMenuDialog *ui;
  boost::shared_ptr<QtK3OpEenRijSelectPlayerWidget> m_select;
  const boost::shared_ptr<const QtK3OpEenRijResources> m_resources;

private slots:

  void on_button_about_clicked() noexcept;
  void on_button_instructions_clicked() noexcept;
  void on_button_quit_clicked() noexcept;
  void on_button_start_clicked() noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

};

} //~namespace ribi

#endif // QTK3OPEENRIJMENUDIALOG_H
