#ifndef QTCONCEPTMAPTESTEDITCONCEPTMAPWIDGET_H
#define QTCONCEPTMAPTESTEDITCONCEPTMAPWIDGET_H

#include "qthideandshowdialog.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>

#include "qtconceptmapfwd.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtTestConceptMapWidgetDialog;
}

namespace ribi {
namespace cmap {

class QtTestConceptMapWidgetDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTestConceptMapWidgetDialog(QWidget *parent = 0);
  QtTestConceptMapWidgetDialog(const QtTestConceptMapWidgetDialog&) = delete;
  QtTestConceptMapWidgetDialog& operator=(const QtTestConceptMapWidgetDialog&) = delete;
  ~QtTestConceptMapWidgetDialog() noexcept;

private slots:
  void OnClick();

private:
  Ui::QtTestConceptMapWidgetDialog *ui;

  std::vector<QPushButton *> m_buttons;
  const std::vector<boost::shared_ptr<Command> > m_commands;
  const std::vector<boost::shared_ptr<QtConceptMapWidget>> m_qtwidgets;

  static const std::vector<boost::shared_ptr<QtConceptMapWidget>> CreateWidgets() noexcept;
};

} //~namespace cmap
} //~namespace ribi

#endif // QTCONCEPTMAPTESTEDITCONCEPTMAPWIDGET_H
