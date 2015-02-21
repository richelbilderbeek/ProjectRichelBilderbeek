//---------------------------------------------------------------------------
/*
QtRoundedRectItem, rectangular-shaped QGraphicsItem
Copyright (C) 2012-2015 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppQtRoundedRectItem.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtroundedrectitemdialog.h"

#include <boost/make_shared.hpp>
#include <boost/lambda/lambda.hpp>

#include <QKeyEvent>

#include "geometry.h"
#include "qtroundedrectitem.h"
#include "testtimer.h"
#include "trace.h"
#include "ui_qtroundedrectitemdialog.h"
#pragma GCC diagnostic pop

ribi::QtRoundedRectItemDialog::QtRoundedRectItemDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtRoundedRectItemDialog),
    m_item()
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtRoundedRectItemDialog::~QtRoundedRectItemDialog() noexcept
{
  delete ui;
}

void ribi::QtRoundedRectItemDialog::DisableSetSize() noexcept
{
  ui->box_height->setReadOnly(true);
  ui->box_height_including_pen->setReadOnly(true);
  ui->box_width->setReadOnly(true);
  ui->box_width_including_pen->setReadOnly(true);
}

void ribi::QtRoundedRectItemDialog::DoSomethingRandom() noexcept
{
  ui->box_contour_pen_width->setValue(
    ui->box_contour_pen_width->value()
    + static_cast<double>(std::rand() % 3) - 1.0
  );

  ui->box_focus_pen_width->setValue(
    ui->box_focus_pen_width->value()
    + static_cast<double>(std::rand() % 3) - 1.0
  );

  ui->box_height->setValue(
    ui->box_height->value()
    + static_cast<double>(std::rand() % 3) - 1.0
  );

  ui->box_height_including_pen->setValue(
    ui->box_height_including_pen->value()
    + static_cast<double>(std::rand() % 3) - 1.0
  );

  ui->box_radius_x->setValue(
    ui->box_radius_x->value()
    + static_cast<double>(std::rand() % 3) - 1.0
  );

  ui->box_radius_y->setValue(
    ui->box_radius_y->value()
    + static_cast<double>(std::rand() % 3) - 1.0
  );

  ui->box_width->setValue(
    ui->box_width->value()
    + static_cast<double>(std::rand() % 3) - 1.0
  );

  ui->box_width_including_pen->setValue(
    ui->box_width_including_pen->value()
    + static_cast<double>(std::rand() % 3) - 1.0
  );

  ui->box_x->setValue(
    ui->box_x->value()
    + static_cast<double>(std::rand() % 3) - 1.0
  );

  ui->box_y->setValue(
    ui->box_y->value()
    + static_cast<double>(std::rand() % 3) - 1.0
  );
}

boost::shared_ptr<const ribi::QtRoundedRectItem> ribi::QtRoundedRectItemDialog::GetItem() const noexcept
{
  return m_item;
}

double ribi::QtRoundedRectItemDialog::GetUiX() const noexcept
{
  return ui->box_x->value();
}

double ribi::QtRoundedRectItemDialog::GetUiY() const noexcept
{
  return ui->box_y->value();
}

std::string ribi::QtRoundedRectItemDialog::GetVersion() noexcept
{
  return "1.3";
}

std::vector<std::string> ribi::QtRoundedRectItemDialog::GetVersionHistory() noexcept
{
  return {
    "2014-06-15: version 1.0: initial version",
    "2014-06-23: version 1.1: allow cooperation with QtRoundedEditRectItemDialog",
    "2014-07-21: version 1.2: added CheckMe member function, for checking its invariants",
    "2014-08-04: version 1.3: removed CheckMe member function in favor of TDD"
  };
}

void ribi::QtRoundedRectItemDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void ribi::QtRoundedRectItemDialog::OnContourPenChanged(QtRoundedRectItem * const qtitem) noexcept
{
  ui->box_contour_pen_width->setValue(qtitem->GetContourPen().widthF());
}

void ribi::QtRoundedRectItemDialog::OnFocusPenChanged(QtRoundedRectItem * const qtitem) noexcept
{
  ui->box_focus_pen_width->setValue(qtitem->GetFocusPen().widthF());
}

void ribi::QtRoundedRectItemDialog::OnPosChanged(QtRoundedRectItem * const qtitem) noexcept
{
  const double new_x = qtitem->GetCenterPos().x();
  const double new_y = qtitem->GetCenterPos().y();
  ui->box_x->setValue(new_x);
  ui->box_y->setValue(new_y);
}

void ribi::QtRoundedRectItemDialog::OnRadiusXchanged(QtRoundedRectItem * const qtitem) noexcept
{
  ui->box_radius_x->setValue(qtitem->GetRadiusX());
}

void ribi::QtRoundedRectItemDialog::OnRadiusYchanged(QtRoundedRectItem * const qtitem) noexcept
{
  ui->box_radius_y->setValue(qtitem->GetRadiusY());
}

void ribi::QtRoundedRectItemDialog::OnWidthChanged(QtRoundedRectItem * const qtitem) noexcept
{
  const double new_width = qtitem->GetInnerWidth();
  ui->box_width->setValue(new_width);
  const double new_width_including_pen = qtitem->GetOuterWidth();
  ui->box_width_including_pen->setValue(new_width_including_pen);
}

void ribi::QtRoundedRectItemDialog::OnHeightChanged(QtRoundedRectItem * const qtitem) noexcept
{
  const double new_height = qtitem->GetInnerHeight();
  ui->box_height->setValue(new_height);
  const double new_height_including_pen = qtitem->GetOuterHeight();
  ui->box_height_including_pen->setValue(new_height_including_pen);
}

void ribi::QtRoundedRectItemDialog::on_box_contour_pen_width_valueChanged(double arg1)
{
  const QPen pen(
    QBrush(qRgb(0,0,0)),
    arg1
  );
  m_item->SetContourPen(pen);
}

void ribi::QtRoundedRectItemDialog::on_box_focus_pen_width_valueChanged(double arg1)
{
  const QPen pen(
    QBrush(qRgb(0,0,0)),
    arg1,
    Qt::DashLine
  );
  m_item->SetFocusPen(pen);
}

void ribi::QtRoundedRectItemDialog::on_box_height_valueChanged(double arg1)
{
  m_item->SetInnerHeight(arg1);
}

void ribi::QtRoundedRectItemDialog::on_box_height_including_pen_valueChanged(double arg1)
{
  m_item->SetOuterHeight(arg1);
}

void ribi::QtRoundedRectItemDialog::on_box_radius_x_valueChanged(double arg1)
{
  m_item->SetRadiusX(arg1);
}

void ribi::QtRoundedRectItemDialog::on_box_radius_y_valueChanged(double arg1)
{
  m_item->SetRadiusY(arg1);
}

void ribi::QtRoundedRectItemDialog::on_box_width_valueChanged(double arg1)
{
  m_item->SetInnerWidth(arg1);
}

void ribi::QtRoundedRectItemDialog::on_box_width_including_pen_valueChanged(double arg1)
{
  m_item->SetOuterWidth(arg1);
}

void ribi::QtRoundedRectItemDialog::on_box_x_valueChanged(double arg1)
{
  m_item->SetCenterPos(arg1,m_item->GetCenterPos().y());
}

void ribi::QtRoundedRectItemDialog::on_box_y_valueChanged(double arg1)
{
  m_item->SetCenterPos(m_item->GetCenterPos().x(),arg1);
}

void ribi::QtRoundedRectItemDialog::SetItem(const boost::shared_ptr<QtRoundedRectItem>& item) noexcept
{
  const bool verbose{false};

  assert(item);
  if (m_item == item)
  {
    //Let the GUI follow
    ui->box_contour_pen_width->setValue(GetItem()->GetContourPen().widthF());
    ui->box_focus_pen_width->setValue(GetItem()->GetFocusPen().widthF());
    ui->box_height->setValue(GetItem()->GetInnerHeight());
    ui->box_height_including_pen->setValue(GetItem()->GetOuterHeight());
    ui->box_radius_x->setValue(GetItem()->GetRadiusX());
    ui->box_radius_y->setValue(GetItem()->GetRadiusY());
    ui->box_width->setValue(GetItem()->GetInnerWidth());
    ui->box_width_including_pen->setValue(GetItem()->GetOuterWidth());
    ui->box_x->setValue(GetItem()->GetCenterX());
    ui->box_y->setValue(GetItem()->GetCenterY());
    return;
  }
  if (verbose)
  {
    std::stringstream s;
    s << "Setting item '" << (*item) << "'\n";
  }

  const auto contour_pen_after = item->GetContourPen();
  const auto focus_pen_after = item->GetFocusPen();
  const auto pos_after = item->GetCenterPos();
  const auto radius_x_after = item->GetRadiusX();
  const auto radius_y_after = item->GetRadiusY();
  const auto width_after = item->GetInnerWidth();
  const auto height_after = item->GetInnerHeight();


  bool contour_pen_changed{true};
  bool focus_pen_changed{true};
  bool pos_changed{true};
  bool radius_x_changed{true};
  bool radius_y_changed{true};
  bool width_changed{true};
  bool height_changed{true};

  if (m_item)
  {
    const auto contour_pen_before = m_item->GetContourPen();
    const auto focus_pen_before = m_item->GetFocusPen();
    const auto pos_before = m_item->GetCenterPos();
    const auto radius_x_before = m_item->GetRadiusX();
    const auto radius_y_before = m_item->GetRadiusY();
    const auto width_before = m_item->GetInnerWidth();
    const auto height_before = m_item->GetInnerHeight();

    contour_pen_changed  = contour_pen_before != contour_pen_after;
    focus_pen_changed  = focus_pen_before != focus_pen_after;
    pos_changed = pos_before != pos_after;
    radius_x_changed = radius_x_before != radius_x_after;
    radius_y_changed = radius_y_before != radius_y_after;
    width_changed = width_before != width_after;
    height_changed = height_before != height_after;


    if (verbose)
    {
      if (contour_pen_changed)
      {
        std::stringstream s;
        s
          << "Contour pen will change from "
          << contour_pen_before
          << " to "
          << contour_pen_after
          << '\n'
        ;
        TRACE(s.str());
      }
      if (focus_pen_changed)
      {
        std::stringstream s;
        s << "FocusPen will change from " << focus_pen_before
          << " to " << focus_pen_after << '\n';
        TRACE(s.str());
      }
      if (pos_changed)
      {
        std::stringstream s;
        s << "Pos will change from '" << pos_before
          << "' to '" << pos_after << "'\n";
        TRACE(s.str());
      }
      if (radius_x_changed)
      {
        std::stringstream s;
        s << "RadiusX will change from " << radius_x_before
          << " to " << radius_x_after << '\n';
        TRACE(s.str());
      }
      if (radius_y_changed)
      {
        std::stringstream s;
        s << "RadiusY will change from " << radius_y_before
          << " to " << radius_y_after << '\n';
        TRACE(s.str());
      }
      if (width_changed)
      {
        std::stringstream s;
        s << "Inner width will change from '" << width_before
          << "' to '" << width_after << "'\n";
        TRACE(s.str());
      }
      if (height_changed)
      {
        std::stringstream s;
        s << "Inner height will change from '" << height_before
          << "' to '" << height_after << "'\n";
        TRACE(s.str());
      }
    }

    //Disconnect m_item
    m_item->m_signal_contour_pen_changed.disconnect(
      boost::bind(&ribi::QtRoundedRectItemDialog::OnContourPenChanged,this,boost::lambda::_1)
    );
    m_item->m_signal_focus_pen_changed.disconnect(
      boost::bind(&ribi::QtRoundedRectItemDialog::OnFocusPenChanged,this,boost::lambda::_1)
    );
    m_item->m_signal_pos_changed.disconnect(
      boost::bind(&ribi::QtRoundedRectItemDialog::OnPosChanged,this,boost::lambda::_1)
    );
    m_item->m_signal_radius_x_changed.disconnect(
      boost::bind(&ribi::QtRoundedRectItemDialog::OnRadiusXchanged,this,boost::lambda::_1)
    );
    m_item->m_signal_radius_y_changed.disconnect(
      boost::bind(&ribi::QtRoundedRectItemDialog::OnRadiusYchanged,this,boost::lambda::_1)
    );
    m_item->m_signal_width_changed.disconnect(
      boost::bind(&ribi::QtRoundedRectItemDialog::OnWidthChanged,this,boost::lambda::_1)
    );
    m_item->m_signal_height_changed.disconnect(
      boost::bind(&ribi::QtRoundedRectItemDialog::OnHeightChanged,this,boost::lambda::_1)
    );
  }

  //Replace m_item by the new one
  m_item = item;


  assert(m_item->GetContourPen() == contour_pen_after);
  assert(m_item->GetFocusPen()   == focus_pen_after  );
  assert(m_item->GetCenterPos()   == pos_after        );
  assert(m_item->GetRadiusX()    == radius_x_after   );
  assert(m_item->GetRadiusY()    == radius_y_after   );
  assert(std::abs(m_item->GetInnerWidth() - width_after) < 1.0);

  m_item->m_signal_contour_pen_changed.connect(
    boost::bind(&ribi::QtRoundedRectItemDialog::OnContourPenChanged,this,boost::lambda::_1)
  );
  m_item->m_signal_focus_pen_changed.connect(
    boost::bind(&ribi::QtRoundedRectItemDialog::OnFocusPenChanged,this,boost::lambda::_1)
  );
  m_item->m_signal_pos_changed.connect(
    boost::bind(&ribi::QtRoundedRectItemDialog::OnPosChanged,this,boost::lambda::_1)
  );
  m_item->m_signal_radius_x_changed.connect(
    boost::bind(&ribi::QtRoundedRectItemDialog::OnRadiusXchanged,this,boost::lambda::_1)
  );
  m_item->m_signal_radius_y_changed.connect(
    boost::bind(&ribi::QtRoundedRectItemDialog::OnRadiusYchanged,this,boost::lambda::_1)
  );
  m_item->m_signal_width_changed.connect(
    boost::bind(&ribi::QtRoundedRectItemDialog::OnWidthChanged,this,boost::lambda::_1)
  );
  m_item->m_signal_height_changed.connect(
    boost::bind(&ribi::QtRoundedRectItemDialog::OnHeightChanged,this,boost::lambda::_1)
  );

  //Emit everything that has changed
  if (contour_pen_changed)
  {
    m_item->m_signal_contour_pen_changed(m_item.get());
  }
  if (focus_pen_changed)
  {
    m_item->m_signal_focus_pen_changed(m_item.get());
  }
  if (pos_changed)
  {
    m_item->m_signal_pos_changed(m_item.get());
  }
  if (radius_x_changed)
  {
    m_item->m_signal_radius_x_changed(m_item.get());
  }
  if (radius_y_changed)
  {
    m_item->m_signal_radius_y_changed(m_item.get());
  }
  if (width_changed)
  {
    m_item->m_signal_width_changed(m_item.get());
  }
  if (height_changed)
  {
    m_item->m_signal_height_changed(m_item.get());
  }
  assert( item ==  m_item);
  assert(*item == *m_item);
}

void ribi::QtRoundedRectItemDialog::SetUiX(const double x) noexcept
{
  this->ui->box_x->setValue(x);
}

void ribi::QtRoundedRectItemDialog::SetUiY(const double y) noexcept
{
  this->ui->box_y->setValue(y);
}

#ifndef NDEBUG
void ribi::QtRoundedRectItemDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  QtRoundedRectItem();

  const TestTimer test_timer(__func__,__FILE__,1.0);
  const bool verbose{false};
  QtRoundedRectItemDialog dialog;
  boost::shared_ptr<QtRoundedRectItem> item{new QtRoundedRectItem};
  dialog.SetItem(item);
  //Change all, sorted by UI component name
  if (verbose) { TRACE("Set/Get Contour pen must be symmetric"); }
  {
    dialog.ui->box_contour_pen_width->setValue( item->GetContourPen().widthF() + 10.0 );
    QPen new_pen = item->GetContourPen();
    new_pen.setWidthF(dialog.ui->box_contour_pen_width->value() + 10.0);
    item->SetContourPen(new_pen);
    assert(item->GetContourPen() == new_pen);
  }
  if (verbose) { TRACE("Set/Get Focus pen width must be symmetric"); }
  {
    dialog.ui->box_focus_pen_width->setValue( item->GetFocusPen().widthF() + 10.0);
    QPen new_pen = item->GetFocusPen();
    new_pen.setWidthF(dialog.ui->box_focus_pen_width->value() + 10.0);
    item->SetFocusPen(new_pen);
    assert(item->GetFocusPen() == new_pen);
  }
  if (verbose) { TRACE("Set/Get InnerHeight must be symmetric"); }
  {
    dialog.ui->box_height->setValue(item->GetInnerHeight() + 10.0);
    const auto new_height = dialog.ui->box_height->value() + 10.0;
    item->SetInnerHeight(new_height);
    assert(std::abs(item->GetInnerHeight() - new_height) < 2.0);
  }
  if (verbose) { TRACE("Set/Get OuterHeight must be symmetric"); }
  {
    dialog.ui->box_height_including_pen->setValue(item->GetOuterHeight() + 10.0);
    const auto new_height = dialog.ui->box_height_including_pen->value() + 10.0;
    item->SetOuterHeight(new_height);
    assert(std::abs(item->GetOuterHeight() - new_height) < 2.0);
  }
  if (verbose) { TRACE("Set/Get Radius X must be symmetric"); }
  {
    dialog.ui->box_radius_x->setValue(item->GetRadiusX() + 10.0);
    const auto new_x = dialog.ui->box_radius_x->value() + 10.0;
    item->SetRadiusX(new_x);
    assert(std::abs(item->GetRadiusX() - new_x) < 2.0);
  }
  if (verbose) { TRACE("Set/Get Radius Y must be symmetric"); }
  {
    dialog.ui->box_radius_y->setValue(item->GetRadiusY() + 10.0);
    const auto new_y = dialog.ui->box_radius_y->value() + 10.0;
    item->SetRadiusY(new_y);
    assert(std::abs(item->GetRadiusY() - new_y) < 2.0);
  }
  if (verbose) { TRACE("Set/Get InnerWidth must be symmetric"); }
  {
    const double old_width{item->GetInnerWidth()};
    const double new_width{old_width + 10.0};
    item->SetInnerWidth(new_width);
    assert(std::abs(item->GetInnerWidth() - new_width) < 2.0);
  }
  if (verbose) { TRACE("Set/Get OuterWidth must be symmetric"); }
  {
    dialog.ui->box_width_including_pen->setValue(item->GetOuterWidth() + 10.0);
    const auto new_width = dialog.ui->box_width_including_pen->value() + 10.0;
    item->SetOuterWidth(new_width);
    assert(std::abs(item->GetOuterWidth() - new_width) < 2.0);
  }
  if (verbose) { TRACE("Set/Get X must be symmetric"); }
  {
    dialog.ui->box_x->setValue(item->GetCenterX() + 10.0);
    const auto new_x = dialog.ui->box_x->value() + 10.0;
    item->SetCenterX(new_x);
    assert(std::abs(item->GetCenterX() - new_x) < 2.0);
  }
  if (verbose) { TRACE("Set/Get Y must be symmetric"); }
  {
    dialog.ui->box_y->setValue(item->GetCenterY() + 10.0);
    const auto new_y = dialog.ui->box_y->value() + 10.0;
    item->SetCenterY(new_y);
    assert(std::abs(item->GetCenterY() - new_y) < 2.0);
  }
  if (verbose) { TRACE("SetItem with other item"); }
  {
    boost::shared_ptr<QtRoundedRectItem> new_item{new QtRoundedRectItem};
    dialog.SetItem(new_item);
    assert(dialog.GetItem() == new_item);
  }
  if (verbose) { TRACE("SetItem with original item"); }
  {
    dialog.SetItem(item);
    assert(dialog.GetItem() == item);
  }
  if (verbose) { TRACE("Changing a contour pen does not change the inner height"); }
  {
    assert(!item->GetIsSelected() && "Work with contour pen");
    const double old_height{item->GetInnerHeight()};
    const double new_height{old_height + 10.0};
    item->SetInnerHeight(new_height);
    QPen pen(item->GetContourPen());
    pen.setWidthF(pen.widthF() + 5.0);
    item->SetContourPen(pen);
    assert(std::abs(item->GetInnerHeight() - new_height) < 4.0);
  }
  if (verbose) { TRACE("Changing a contour pen does not change the inner width"); }
  {
    assert(!item->GetIsSelected() && "Work with contour pen");
    const double old_width{item->GetInnerWidth()};
    const double new_width{old_width + 10.0};
    item->SetInnerWidth(new_width);
    QPen pen(item->GetContourPen());
    pen.setWidthF(pen.widthF() + 5.0);
    item->SetContourPen(pen);
    assert(std::abs(item->GetInnerWidth() - new_width) < 4.0);
  }
  if (verbose) { TRACE("Changing a contour pen does change the outer height"); }
  {
    assert(!item->GetIsSelected() && "Work with contour pen");
    const double old_height{item->GetInnerHeight()};
    const double new_height{old_height + 10.0};
    item->SetOuterHeight(new_height);
    QPen pen(item->GetContourPen());
    pen.setWidthF(pen.widthF() + 5.0);
    item->SetContourPen(pen);
    assert(std::abs(item->GetOuterHeight() - new_height) > 4.0);
  }
  if (verbose) { TRACE("Changing a contour pen does change the outer width"); }
  {
    assert(!item->GetIsSelected() && "Work with contour pen");
    const double old_width{item->GetInnerWidth()};
    const double new_width{old_width + 10.0};
    item->SetOuterWidth(new_width);
    QPen pen(item->GetContourPen());
    pen.setWidthF(pen.widthF() + 5.0);
    item->SetContourPen(pen);
    assert(std::abs(item->GetOuterWidth() - new_width) > 4.0);
  }
  if (verbose) { TRACE("Brute-force some random items"); }
  {
    for (int i{0}; i!=10; ++i) { dialog.DoSomethingRandom(); }
  }
}
#endif

