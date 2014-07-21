//---------------------------------------------------------------------------
/*
QtRoundedRectItem, rectangular-shaped QGraphicsItem
Copyright (C) 2012-2014 Richel Bilderbeek

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

  CheckMe();
}

ribi::QtRoundedRectItemDialog::~QtRoundedRectItemDialog() noexcept
{
  delete ui;
}

void ribi::QtRoundedRectItemDialog::CheckMe() const noexcept
{
  #ifndef NDEBUG
  if (!GetItem()) return;

  if(std::abs(ui->box_contour_pen_width->value() - GetItem()->GetContourPen().widthF()) >= 1.0)
  {
    TRACE("ERROR");
    TRACE(ui->box_focus_pen_width->value());
    TRACE(GetItem()->GetFocusPen().widthF());
    TRACE("BREAK");
  }
  assert(std::abs(ui->box_contour_pen_width->value() - GetItem()->GetContourPen().widthF()) < 1.0);
  if(std::abs(ui->box_focus_pen_width->value() - GetItem()->GetFocusPen().widthF()) >= 1.0)
  {
    TRACE("ERROR");
    TRACE(ui->box_focus_pen_width->value());
    TRACE(GetItem()->GetFocusPen().widthF());
    TRACE("BREAK");
  }
  assert(std::abs(ui->box_focus_pen_width->value() - GetItem()->GetFocusPen().widthF()) < 1.0);
  assert(std::abs(ui->box_height->value() - GetItem()->GetHeight()) < 1.0);
  assert(std::abs(ui->box_height_including_pen->value() - GetItem()->GetHeightIncludingPen()) < 1.0);
  assert(std::abs(ui->box_radius_x->value() - GetItem()->GetRadiusX()) < 1.0);
  assert(std::abs(ui->box_radius_y->value() - GetItem()->GetRadiusY()) < 1.0);
  if(std::abs(ui->box_width->value() - GetItem()->GetWidth()) >= 1.0)
  {
    TRACE("ERROR");
    TRACE(ui->box_width->value());
    TRACE(GetItem()->GetWidth());
    TRACE("BREAK");
  }

  assert(std::abs(ui->box_width->value() - GetItem()->GetWidth()) < 1.0);
  assert(std::abs(ui->box_width_including_pen->value() - GetItem()->GetWidthIncludingPen()) < 1.0);
  assert(std::abs(ui->box_x->value() - GetItem()->GetPos().x()) < 1.0);
  assert(std::abs(ui->box_y->value() - GetItem()->GetPos().y()) < 1.0);
  #endif
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
  CheckMe();
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
  return "1.2";
}

std::vector<std::string> ribi::QtRoundedRectItemDialog::GetVersionHistory() noexcept
{
  return {
    "2014-06-15: version 1.0: initial version",
    "2014-06-23: version 1.1: allow cooperation with QtRoundedEditRectItemDialog",
    "2014-07-21: version 1.2: added CheckMe member function, for checking its invariants"
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
  const double new_x = qtitem->GetPos().x();
  const double new_y = qtitem->GetPos().y();
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

void ribi::QtRoundedRectItemDialog::OnRectChanged(QtRoundedRectItem * const qtitem) noexcept
{
  const double new_width = qtitem->GetRect().width();
  const double new_height = qtitem->GetRect().height();
  ui->box_width->setValue(new_width);
  ui->box_height->setValue(new_height);

  const double new_width_including_pen = qtitem->GetRectIncludingPen().width();
  const double new_height_including_pen = qtitem->GetRectIncludingPen().height();
  ui->box_width_including_pen->setValue(new_width_including_pen);
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
  m_item->SetHeight(arg1);
}

void ribi::QtRoundedRectItemDialog::on_box_height_including_pen_valueChanged(double arg1)
{
  m_item->SetHeightIncludingPen(arg1);
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
  m_item->SetWidth(arg1);
}

void ribi::QtRoundedRectItemDialog::on_box_width_including_pen_valueChanged(double arg1)
{
  m_item->SetWidthIncludingPen(arg1);
}

void ribi::QtRoundedRectItemDialog::on_box_x_valueChanged(double arg1)
{
  m_item->SetPos(arg1,m_item->GetPos().y());
}

void ribi::QtRoundedRectItemDialog::on_box_y_valueChanged(double arg1)
{
  m_item->SetPos(m_item->GetPos().x(),arg1);
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
    ui->box_height->setValue(GetItem()->GetHeight());
    ui->box_height_including_pen->setValue(GetItem()->GetHeightIncludingPen());
    ui->box_radius_x->setValue(GetItem()->GetRadiusX());
    ui->box_radius_y->setValue(GetItem()->GetRadiusY());
    ui->box_width->setValue(GetItem()->GetWidth());
    ui->box_width_including_pen->setValue(GetItem()->GetWidthIncludingPen());
    ui->box_x->setValue(GetItem()->GetX());
    ui->box_y->setValue(GetItem()->GetY());
    CheckMe();
    return;
  }
  if (verbose)
  {
    std::stringstream s;
    s << "Setting item '" << (*item) << "'\n";
  }

  const auto contour_pen_after = item->GetContourPen();
  const auto focus_pen_after = item->GetFocusPen();
  const auto pos_after = item->GetPos();
  const auto radius_x_after = item->GetRadiusX();
  const auto radius_y_after = item->GetRadiusY();
  const auto rect_after = item->GetRect();


  bool contour_pen_changed  = true;
  bool focus_pen_changed  = true;
  bool pos_changed = true;
  bool radius_x_changed = true;
  bool radius_y_changed = true;
  bool rect_changed = true;

  if (m_item)
  {
    const auto contour_pen_before = m_item->GetContourPen();
    const auto focus_pen_before = m_item->GetFocusPen();
    const auto pos_before = m_item->GetPos();
    const auto radius_x_before = m_item->GetRadiusX();
    const auto radius_y_before = m_item->GetRadiusY();
    const auto rect_before = m_item->GetRect();

    contour_pen_changed  = contour_pen_before != contour_pen_after;
    focus_pen_changed  = focus_pen_before != focus_pen_after;
    pos_changed = pos_before != pos_after;
    radius_x_changed = radius_x_before != radius_x_after;
    radius_y_changed = radius_y_before != radius_y_after;
    rect_changed = rect_before != rect_after;


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
      if (rect_changed)
      {
        std::stringstream s;
        s << "Rect will change from '" << rect_before
          << "' to '" << rect_after << "'\n";
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
    m_item->m_signal_rect_changed.disconnect(
      boost::bind(&ribi::QtRoundedRectItemDialog::OnRectChanged,this,boost::lambda::_1)
    );
  }

  //Replace m_item by the new one
  m_item = item;


  assert(m_item->GetContourPen() == contour_pen_after);
  assert(m_item->GetFocusPen()   == focus_pen_after  );
  assert(m_item->GetPos()        == pos_after        );
  assert(m_item->GetRadiusX()    == radius_x_after   );
  assert(m_item->GetRadiusY()    == radius_y_after   );
  assert(m_item->GetRect()       == rect_after       );

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
  m_item->m_signal_rect_changed.connect(
    boost::bind(&ribi::QtRoundedRectItemDialog::OnRectChanged,this,boost::lambda::_1)
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
  if (rect_changed)
  {
    m_item->m_signal_rect_changed(m_item.get());
  }
  assert( item ==  m_item);
  assert(*item == *m_item);
  CheckMe();
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
  TRACE("Starting ribi::QtRoundedRectItemDialog::Test");
  QtRoundedRectItemDialog dialog;
  boost::shared_ptr<QtRoundedRectItem> item{new QtRoundedRectItem};
  dialog.SetItem(item);
  //Change all, sorted by UI component name
  //Contour pen width
  {
    dialog.ui->box_contour_pen_width->setValue( item->GetContourPen().widthF() + 10.0 );
    dialog.CheckMe();
    QPen new_pen = item->GetContourPen();
    new_pen.setWidthF(dialog.ui->box_contour_pen_width->value() + 10.0);
    item->SetContourPen(new_pen);
    dialog.CheckMe();
  }
  //Focus pen width
  {
    dialog.ui->box_focus_pen_width->setValue( item->GetFocusPen().widthF() + 10.0);
    dialog.CheckMe();
    QPen new_pen = item->GetFocusPen();
    new_pen.setWidthF(dialog.ui->box_focus_pen_width->value() + 10.0);
    item->SetFocusPen(new_pen);
    dialog.CheckMe();
  }
  //Height
  {
    dialog.ui->box_height->setValue(item->GetHeight() + 10.0);
    dialog.CheckMe();
    const auto new_height = dialog.ui->box_height->value() + 10.0;
    item->SetHeight(new_height);
    dialog.CheckMe();
  }
  //Height including pen
  {
    dialog.ui->box_height_including_pen->setValue(item->GetHeightIncludingPen() + 10.0);
    dialog.CheckMe();
    const auto new_height = dialog.ui->box_height_including_pen->value() + 10.0;
    item->SetHeightIncludingPen(new_height);
    dialog.CheckMe();
  }
  //Radius X
  {
    dialog.ui->box_radius_x->setValue(item->GetRadiusX() + 10.0);
    dialog.CheckMe();
    const auto new_x = dialog.ui->box_radius_x->value() + 10.0;
    item->SetRadiusX(new_x);
    dialog.CheckMe();
  }
  //Radius Y
  {
    dialog.ui->box_radius_y->setValue(item->GetRadiusY() + 10.0);
    dialog.CheckMe();
    const auto new_y = dialog.ui->box_radius_y->value() + 10.0;
    item->SetRadiusY(new_y);
    dialog.CheckMe();
  }
  //Width
  {
    dialog.ui->box_width->setValue(item->GetWidth() + 10.0);
    dialog.CheckMe();
    const auto new_width = dialog.ui->box_width->value() + 10.0;
    item->SetWidth(new_width);
    dialog.CheckMe();
  }
  //Width including pen
  {
    dialog.ui->box_width_including_pen->setValue(item->GetWidthIncludingPen() + 10.0);
    dialog.CheckMe();
    const auto new_width = dialog.ui->box_width_including_pen->value() + 10.0;
    item->SetWidthIncludingPen(new_width);
    dialog.CheckMe();
  }
  // X
  {
    dialog.ui->box_x->setValue(item->GetPos().x() + 10.0);
    dialog.CheckMe();
    const auto new_x = dialog.ui->box_x->value() + 10.0;
    item->SetX(new_x);
    dialog.CheckMe();
  }
  // Y
  {
    dialog.ui->box_y->setValue(item->GetPos().y() + 10.0);
    dialog.CheckMe();
    const auto new_y = dialog.ui->box_y->value() + 10.0;
    item->SetY(new_y);
    dialog.CheckMe();
  }


  TRACE("Finished ribi::QtRoundedRectItemDialog::Test successfully");
}
#endif

