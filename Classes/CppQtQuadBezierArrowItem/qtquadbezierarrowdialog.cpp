#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtquadbezierarrowdialog.h"

#include <boost/lambda/bind.hpp>
#include <boost/lambda/lambda.hpp>

#include <QGraphicsItem>
#include <QKeyEvent>

#include <cassert>

#include "qtquadbezierarrowitem.h"
#include "trace.h"
#include "ui_qtquadbezierarrowdialog.h"
#pragma GCC diagnostic pop

ribi::QtQuadBezierArrowDialog::QtQuadBezierArrowDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtQuadBezierArrowDialog),
    m_arrow{}
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtQuadBezierArrowDialog::~QtQuadBezierArrowDialog() noexcept
{
  delete ui;
}

void ribi::QtQuadBezierArrowDialog::CheckMe() const noexcept
{
  #ifndef NDEBUG
  assert(std::abs(ui->box_focus_pen_width->value() - m_arrow->GetFocusPen().widthF()) < 2.0);
  assert(std::abs(ui->box_from_x->value() - m_arrow->GetFromItem()->x()) < 2.0);
  assert(std::abs(ui->box_from_y->value() - m_arrow->GetFromItem()->y()) < 2.0);
  assert(ui->box_has_head->isChecked() == m_arrow->HasHead());
  assert(ui->box_has_tail->isChecked() == m_arrow->HasTail());
  assert(std::abs(ui->box_mid_x->value() - m_arrow->GetMidItem()->x()) < 2.0);
  assert(std::abs(ui->box_mid_y->value() - m_arrow->GetMidItem()->y()) < 2.0);
  assert(std::abs(ui->box_normal_pen_width->value() - m_arrow->GetPen().widthF()) < 2.0);
  assert(std::abs(ui->box_to_x->value() - m_arrow->GetToItem()->x()) < 2.0);
  assert(std::abs(ui->box_to_y->value() - m_arrow->GetToItem()->y()) < 2.0);
  #endif
}

double ribi::QtQuadBezierArrowDialog::GetUiMidX() const noexcept
{
  return ui->box_mid_x->value();
}

double ribi::QtQuadBezierArrowDialog::GetUiMidY() const noexcept
{
  return ui->box_mid_y->value();
}

std::string ribi::QtQuadBezierArrowDialog::GetVersion() noexcept
{
  return "1.0";
}


std::vector<std::string> ribi::QtQuadBezierArrowDialog::GetVersionHistory() noexcept
{
  return {
    "2014-07-29: version 1.0: initial version"
  };
}

void ribi::QtQuadBezierArrowDialog::on_box_from_x_valueChanged(double arg1)
{
  this->m_arrow->SetFromX(arg1);
}

void ribi::QtQuadBezierArrowDialog::on_box_from_y_valueChanged(double arg1)
{
  this->m_arrow->SetFromY(arg1);
}

void ribi::QtQuadBezierArrowDialog::on_box_has_head_clicked()
{
  m_arrow->SetHasHead(ui->box_has_head->isChecked());
}

void ribi::QtQuadBezierArrowDialog::on_box_has_tail_clicked()
{
  m_arrow->SetHasTail(ui->box_has_tail->isChecked());
}

void ribi::QtQuadBezierArrowDialog::on_box_mid_x_valueChanged(double arg1)
{
  this->m_arrow->SetMidX(arg1);
}

void ribi::QtQuadBezierArrowDialog::on_box_mid_y_valueChanged(double arg1)
{
  this->m_arrow->SetMidY(arg1);
}

void ribi::QtQuadBezierArrowDialog::on_box_normal_pen_width_valueChanged(double arg1)
{
  QPen new_pen = m_arrow->GetPen();
  new_pen.setWidthF(arg1);
  m_arrow->SetPen(new_pen);
}

void ribi::QtQuadBezierArrowDialog::on_box_focus_pen_width_valueChanged(double arg1)
{
  QPen new_pen = m_arrow->GetFocusPen();
  new_pen.setWidthF(arg1);
  m_arrow->SetFocusPen(new_pen);

}

void ribi::QtQuadBezierArrowDialog::on_box_to_x_valueChanged(double arg1)
{
  this->m_arrow->SetToX(arg1);
}

void ribi::QtQuadBezierArrowDialog::on_box_to_y_valueChanged(double arg1)
{
  this->m_arrow->SetToY(arg1);
}

void ribi::QtQuadBezierArrowDialog::OnItemUpdated(const QtQuadBezierArrowItem * const item) noexcept
{
  ui->box_focus_pen_width->setValue(item->GetFocusPen().widthF());
  ui->box_from_x->setValue(item->GetFromItem()->x());
  ui->box_from_y->setValue(item->GetFromItem()->y());
  ui->box_has_head->setChecked(item->HasHead());
  ui->box_has_tail->setChecked(item->HasTail());
  ui->box_mid_x->setValue(item->GetMidItem()->x());
  ui->box_mid_y->setValue(item->GetMidItem()->y());
  ui->box_normal_pen_width->setValue(item->GetPen().widthF());
  ui->box_to_x->setValue(item->GetToItem()->x());
  ui->box_to_y->setValue(item->GetToItem()->y());
}

void ribi::QtQuadBezierArrowDialog::keyPressEvent(QKeyEvent * event) noexcept
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void ribi::QtQuadBezierArrowDialog::SetArrow(const Arrow& arrow) noexcept
{
  const bool verbose{false};

  assert(arrow);
  if (m_arrow == arrow)
  {
    CheckMe();
    return;
  }
  if (verbose)
  {
    std::stringstream s;
    s << "Setting arrow '" << (*arrow) << "'\n";
  }

  const auto focus_pen_after = arrow->GetFocusPen();
  const auto from_item_after = arrow->GetFromItem();
  const auto has_head_after = arrow->HasHead();
  const auto mid_item_after = arrow->GetMidItem();
  const auto pen_after = arrow->GetPen();
  const auto has_tail_after = arrow->HasTail();
  const auto to_item_after = arrow->GetToItem();

  bool focus_pen_changed{true};
  bool from_item_changed{true};
  bool has_head_changed{true};
  bool mid_item_changed{true};
  bool pen_changed{true};
  bool has_tail_changed{true};
  bool to_item_changed{true};

  if (m_arrow)
  {
    const auto focus_pen_before = m_arrow->GetFocusPen();
    const auto from_item_before = m_arrow->GetFromItem();
    const auto has_head_before = m_arrow->HasHead();
    const auto mid_item_before = m_arrow->GetMidItem();
    const auto pen_before = m_arrow->GetPen();
    const auto has_tail_before = m_arrow->HasTail();
    const auto to_item_before = m_arrow->GetToItem();

    focus_pen_changed = focus_pen_before != focus_pen_after;
    from_item_changed = from_item_before != from_item_after;
    has_head_changed = has_head_before != has_head_after;
    mid_item_changed = mid_item_before != mid_item_after;
    pen_changed = pen_before != pen_after;
    has_tail_changed = has_tail_before != has_tail_after;
    to_item_changed = to_item_before != to_item_after;

    if (verbose)
    {
      if (focus_pen_changed)
      {
        std::stringstream s;
        s
          << "Focus pen will change from width "
          << focus_pen_before.widthF()
          << " to "
          << focus_pen_after.widthF()
          << '\n'
        ;
        TRACE(s.str());
      }
      if (from_item_changed)
      {
        std::stringstream s;
        s << "From item will change from " << from_item_before
          << " to " << from_item_after << '\n';
        TRACE(s.str());
      }
      if (has_head_changed)
      {
        std::stringstream s;
        s << "Has head will change from '" << has_head_before
          << "' to '" << has_head_after << "'\n";
        TRACE(s.str());
      }
      if (mid_item_changed)
      {
        std::stringstream s;
        s << "Mid item will change from " << mid_item_before
          << " to " << mid_item_after << '\n';
        TRACE(s.str());
      }
      if (pen_changed)
      {
        std::stringstream s;
        s << "Normal pen will change from " << pen_before.widthF()
          << " to " << pen_after.widthF() << '\n'
        ;
        TRACE(s.str());
      }
    }

    //Disconnect m_arrow
    m_arrow->m_signal_item_updated.disconnect(
      boost::bind(&ribi::QtQuadBezierArrowDialog::OnItemUpdated,this,boost::lambda::_1)
    );
    /*
    Not sure if I need this high detailed granulity

    m_arrow->m_signal_base_changed.disconnect(
      boost::bind(&ribi::QtQuadBezierArrowDialog::OnBaseChanged,this,boost::lambda::_1)
    );
    m_arrow->m_signal_font_changed.disconnect(
      boost::bind(&ribi::QtQuadBezierArrowDialog::OnFontChanged,this,boost::lambda::_1)
    );
    m_arrow->m_signal_padding_changed.disconnect(
      boost::bind(&ribi::QtQuadBezierArrowDialog::OnPaddingChanged,this,boost::lambda::_1)
    );
    m_arrow->m_signal_text_changed.disconnect(
      boost::bind(&ribi::QtQuadBezierArrowDialog::OnTextChanged,this,boost::lambda::_1)
    );
    m_arrow->m_signal_text_pen_changed.disconnect(
      boost::bind(&ribi::QtQuadBezierArrowDialog::OnTextPenChanged,this,boost::lambda::_1)
    );
  */
  }

  //Replace m_arrow by the new one
  m_arrow = arrow;

  assert(m_arrow->GetFocusPen() == focus_pen_after);
  assert(m_arrow->GetFromItem() == from_item_after);
  assert(m_arrow->GetMidItem() == mid_item_after);
  assert(m_arrow->GetPen() == pen_after);
  assert(m_arrow->GetToItem() == to_item_after);
  assert(m_arrow->HasHead() == has_head_after);
  assert(m_arrow->HasTail() == has_tail_after);

  m_arrow->m_signal_item_updated.connect(
    boost::bind(&ribi::QtQuadBezierArrowDialog::OnItemUpdated,this,boost::lambda::_1)
  );

  /* Not sure if I need this high detailed granulity

  m_arrow->m_signal_base_changed.connect(
    boost::bind(&ribi::QtQuadBezierArrowDialog::OnBaseChanged,this,boost::lambda::_1)
  );
  m_arrow->m_signal_font_changed.connect(
    boost::bind(&ribi::QtQuadBezierArrowDialog::OnFontChanged,this,boost::lambda::_1)
  );
  m_arrow->m_signal_padding_changed.connect(
    boost::bind(&ribi::QtQuadBezierArrowDialog::OnPaddingChanged,this,boost::lambda::_1)
  );
  m_arrow->m_signal_text_changed.connect(
    boost::bind(&ribi::QtQuadBezierArrowDialog::OnTextChanged,this,boost::lambda::_1)
  );
  m_arrow->m_signal_text_pen_changed.connect(
    boost::bind(&ribi::QtQuadBezierArrowDialog::OnTextPenChanged,this,boost::lambda::_1)
  );
  */

  //Emit everything that has changed
  if (
     focus_pen_changed
  || from_item_changed
  || has_head_changed
  || mid_item_changed
  || pen_changed
  || has_tail_changed
  || to_item_changed
  )
  {
     m_arrow->m_signal_item_updated(m_arrow.get());
  }

  /* Not sure if I need this high detailed granulity
  if (focus_pen_changed)
  {
    m_arrow->m_signal_base_changed(m_arrow.get());
  }
  if (from_item_changed)
  {
    m_arrow->m_signal_font_changed(m_arrow.get());
  }
  if (has_head_changed)
  {
    m_arrow->m_signal_padding_changed(m_arrow.get());
  }
  if (mid_item_changed)
  {
    m_arrow->m_signal_text_changed(m_arrow.get());
  }
  if (pen_changed)
  {
    m_arrow->m_signal_text_pen_changed(m_arrow.get());
  }
  */
  assert( arrow ==  m_arrow);
  assert(*arrow == *m_arrow);
  CheckMe();
}

void ribi::QtQuadBezierArrowDialog::SetUiMidX(const double x) noexcept
{
  ui->box_mid_x->setValue(x);
}

void ribi::QtQuadBezierArrowDialog::SetUiMidY(const double y) noexcept
{
  ui->box_mid_y->setValue(y);
}


#ifndef NDEBUG
void ribi::QtQuadBezierArrowDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::QtQuadBezierArrowDialog::Test");
  const bool verbose{false};
  const boost::shared_ptr<QGraphicsItem> from{new QGraphicsSimpleTextItem};
  const bool tail{false};
  const boost::shared_ptr<QGraphicsItem> mid{new QGraphicsSimpleTextItem};
  const bool head{true};
  const boost::shared_ptr<QGraphicsItem> to{new QGraphicsSimpleTextItem};
  QtQuadBezierArrowDialog d;
  const boost::shared_ptr<QtQuadBezierArrowItem> arrow{
    new QtQuadBezierArrowItem(from.get(),tail,mid.get(),head,to.get())
  };
  d.SetArrow(arrow);
  if (verbose) { TRACE("Get/SetUiMidX must be symmetric"); }
  {
    const double old_x{d.GetUiMidX()};
    const double new_x{old_x + 10.0};
    d.SetUiMidX(new_x);
    assert(std::abs(d.GetUiMidX() - new_x) < 2.0);
  }
  if (verbose) { TRACE("Get/SetUiMidY must be symmetric"); }
  {
    const double old_y{d.GetUiMidY()};
    const double new_y{old_y + 10.0};
    d.SetUiMidY(new_y);
    assert(std::abs(d.GetUiMidY() - new_y) < 2.0);
  }
  TRACE("Finished ribi::QtQuadBezierArrowDialog::Test successfully");
}
#endif


