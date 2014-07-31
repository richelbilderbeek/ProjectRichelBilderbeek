#ifndef QTQUADBEZIERARROWDIALOG_H
#define QTQUADBEZIERARROWDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtQuadBezierArrowDialog;
}

namespace ribi {

struct QtQuadBezierArrowItem;

///Dialog to display the members of a QtQuadBezierArrowItem
class QtQuadBezierArrowDialog final : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  typedef boost::shared_ptr<QtQuadBezierArrowItem> Arrow;

  explicit QtQuadBezierArrowDialog(QWidget *parent = 0);
  QtQuadBezierArrowDialog(const QtQuadBezierArrowDialog&) = delete;
  QtQuadBezierArrowDialog& operator=(const QtQuadBezierArrowDialog&) = delete;
  ~QtQuadBezierArrowDialog() noexcept;

  ///Checks the invariants, empty at release
  void CheckMe() const noexcept;

  Arrow GetArrow() const noexcept { return m_arrow; }

  double GetUiMidX() const noexcept;
  double GetUiMidY() const noexcept;

  static std::string GetVersion() noexcept;
  static std::vector<std::string> GetVersionHistory() noexcept;

  ///Set the arrow to work on
  void SetArrow(const Arrow& arrow) noexcept;

  void SetUiMidX(const double x) noexcept;
  void SetUiMidY(const double y) noexcept;

private slots:
  void keyPressEvent(QKeyEvent * event) noexcept override final;
  void on_box_focus_pen_width_valueChanged(double arg1);
  void on_box_from_x_valueChanged(double arg1);
  void on_box_from_y_valueChanged(double arg1);
  void on_box_has_head_clicked();
  void on_box_has_tail_clicked();
  void on_box_mid_x_valueChanged(double arg1);
  void on_box_mid_y_valueChanged(double arg1);
  void on_box_normal_pen_width_valueChanged(double arg1);
  void on_box_to_x_valueChanged(double arg1);
  void on_box_to_y_valueChanged(double arg1);

private:
  Ui::QtQuadBezierArrowDialog *ui;

  ///The arrow to work on
  Arrow m_arrow;

  void OnItemUpdated(const QtQuadBezierArrowItem * const item) noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTQUADBEZIERARROWDIALOG_H
