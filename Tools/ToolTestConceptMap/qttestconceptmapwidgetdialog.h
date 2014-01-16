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

  int GetNumberOfButtons() const noexcept { return static_cast<int>(m_buttons.size()); }

protected:
  void keyPressEvent(QKeyEvent *);
  void mouseDoubleClickEvent(QMouseEvent *);
  void mouseMoveEvent(QMouseEvent *);
  void mousePressEvent(QMouseEvent *);

private slots:
  ///Called when user clicks a button
  ///OnClick determines the clicked button its index
  ///by finding the focused button. Then it
  ///calls DoClick
  void OnClick();

private:
  Ui::QtTestConceptMapWidgetDialog *ui;

  std::vector<QPushButton *> m_buttons;
  const boost::shared_ptr<QtConceptMapWidget> m_qtwidget;

  static const boost::shared_ptr<QtConceptMapWidget> CreateWidget() noexcept;

  ///Click the ith button
  void DoClick(const int i);

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace cmap
} //~namespace ribi

#endif // QTCONCEPTMAPTESTEDITCONCEPTMAPWIDGET_H
