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
  class QtTestEditConceptMapWidgetDialog;
}

namespace ribi {
namespace cmap {

class QtTestEditConceptMapWidgetDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTestEditConceptMapWidgetDialog(QWidget *parent = 0);
  QtTestEditConceptMapWidgetDialog(const QtTestEditConceptMapWidgetDialog&) = delete;
  QtTestEditConceptMapWidgetDialog& operator=(const QtTestEditConceptMapWidgetDialog&) = delete;
  ~QtTestEditConceptMapWidgetDialog() noexcept;

private:
  Ui::QtTestEditConceptMapWidgetDialog *ui;
  boost::shared_ptr<QtTestEditConceptMapWidgetDialog> m_widget;
};

} //~namespace cmap
} //~namespace ribi

#endif // QTCONCEPTMAPTESTEDITCONCEPTMAPWIDGET_H
