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
}

ribi::QtRoundedRectItemDialog::~QtRoundedRectItemDialog() noexcept
{
  delete ui;
}

std::string ribi::QtRoundedRectItemDialog::GetVersion() noexcept
{
  return "1.0";
}

std::vector<std::string> ribi::QtRoundedRectItemDialog::GetVersionHistory() noexcept
{
  return {
    "2014-06-15: version 1.0: initial version"
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
}

void ribi::QtRoundedRectItemDialog::on_box_radius_x_valueChanged(double arg1)
{
  m_item->SetRadiusX(arg1);
}

void ribi::QtRoundedRectItemDialog::on_box_radius_y_valueChanged(double arg1)
{
  m_item->SetRadiusY(arg1);
}

void ribi::QtRoundedRectItemDialog::on_box_x_valueChanged(double arg1)
{
  m_item->SetPos(arg1,m_item->GetPos().y());
}

void ribi::QtRoundedRectItemDialog::on_box_y_valueChanged(double arg1)
{
  m_item->SetPos(m_item->GetPos().x(),arg1);
}

void ribi::QtRoundedRectItemDialog::on_box_width_valueChanged(double arg1)
{
  m_item->SetWidth(arg1);
}

void ribi::QtRoundedRectItemDialog::on_box_height_valueChanged(double arg1)
{
  m_item->SetHeight(arg1);
}

void ribi::QtRoundedRectItemDialog::SetItem(const boost::shared_ptr<QtRoundedRectItem>& item) noexcept
{
  const bool verbose = false;

  assert(item);
  if (m_item == item)
  {
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
}

#ifndef NDEBUG
void ribi::QtRoundedRectItemDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::QtRoundedRectItemDialog::Test");
  TRACE("Finished ribi::QtRoundedRectItemDialog::Test successfully");
}
#endif

/*
void ribi::QtRoundedRectItemDialog::on_button_contour_pen_clicked()
{
  const QPen pen(
    QBrush(qRgb(std::rand() % 256,std::rand() % 256,std::rand() % 256)),
    1.0 + (static_cast<double>(std::rand() % 100) / 10.0)
  );
  m_item->SetContourPen(pen);
}
*/

void ribi::QtRoundedRectItemDialog::on_box_contour_pen_width_valueChanged(double arg1)
{
  const QPen pen(
    //QBrush(qRgb(std::rand() % 256,std::rand() % 256,std::rand() % 256)),
    QBrush(qRgb(0,0,0)),
    arg1
  );
  m_item->SetContourPen(pen);
}

void ribi::QtRoundedRectItemDialog::on_box_focus_pen_width_valueChanged(double arg1)
{
  const QPen pen(
    //QBrush(qRgb(std::rand() % 256,std::rand() % 256,std::rand() % 256)),
    QBrush(qRgb(0,0,0)),
    arg1,
    Qt::DashLine
  );
  m_item->SetFocusPen(pen);
}
