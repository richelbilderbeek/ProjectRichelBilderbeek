#ifndef QTCONCEPTMAPTESTEDITCONCEPTMAPWIDGET_H
#define QTCONCEPTMAPTESTEDITCONCEPTMAPWIDGET_H

#include "qthideandshowdialog.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
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

private:
  Ui::QtTestConceptMapWidgetDialog *ui;

  boost::shared_ptr<QtTestConceptMapWidgetDialog> m_widget;
};

} //~namespace cmap
} //~namespace ribi

#endif // QTCONCEPTMAPTESTEDITCONCEPTMAPWIDGET_H
