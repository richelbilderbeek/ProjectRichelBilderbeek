//---------------------------------------------------------------------------
/*
QtRoundedEditRectItem, editable rectangular-shaped QGraphicsItem
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
//From http://www.richelbilderbeek.nl/QtRoundedEditRectItem.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtroundededitrectitemdialog.h"

#include <boost/make_shared.hpp>
#include <boost/lambda/lambda.hpp>

#include <QKeyEvent>
#include <QFont>
#include <QFontDialog>
#include <QString>
#include "container.h"
#include "qtroundedrectitemdialog.h"
#include "qtroundededitrectitem.h"
#include "trace.h"
#include "ui_qtroundededitrectitemdialog.h"
#pragma GCC diagnostic pop

ribi::QtRoundedEditRectItemDialog::QtRoundedEditRectItemDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtRoundedEditRectItemDialog),
    m_dialog{boost::make_shared<QtRoundedRectItemDialog>()},
    m_item{}
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);

  assert(this->layout());
  this->layout()->addWidget(m_dialog.get());

  m_dialog->DisableSetSize();
}

ribi::QtRoundedEditRectItemDialog::~QtRoundedEditRectItemDialog() noexcept
{
  delete ui;
}

void ribi::QtRoundedEditRectItemDialog::CheckMe() const noexcept
{
  #ifndef NDEBUG
  if (!m_item) return;
  if (m_item->GetText() != Container().SeperateString(ui->text->toPlainText().toStdString(),'\n'))
  {
    TRACE("ERROR");
    TRACE(Container().ToStr(m_item->GetText()));
    TRACE(ui->text->toPlainText().toStdString());
    TRACE("BREAK");
  }
  assert(ui->box_padding_top->value() == m_item->GetPadding().top);
  assert(ui->box_padding_right->value() == m_item->GetPadding().right);
  assert(ui->box_padding_bottom->value() == m_item->GetPadding().bottom);
  assert(ui->box_padding_left->value() == m_item->GetPadding().left);
  assert(m_item->GetText() == Container().SeperateString(ui->text->toPlainText().toStdString(),'\n'));
  #endif
}

double ribi::QtRoundedEditRectItemDialog::GetUiX() const noexcept
{
  assert(m_dialog);
  return m_dialog->GetUiX();
}

double ribi::QtRoundedEditRectItemDialog::GetUiY() const noexcept
{
  assert(m_dialog);
  return m_dialog->GetUiY();
}

std::string ribi::QtRoundedEditRectItemDialog::GetVersion() noexcept
{
  return "1.1";
}

std::vector<std::string> ribi::QtRoundedEditRectItemDialog::GetVersionHistory() noexcept
{
  return {
    "2014-06-22: version 1.0: initial version",
    "2014-07-21: version 1.1: added CheckMe member functiom"
  };
}

void ribi::QtRoundedEditRectItemDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void ribi::QtRoundedEditRectItemDialog::on_button_font_clicked()
{
  static QFont font = m_item->GetFont();
  bool ok = false;
  const QFont new_font = QFontDialog::getFont(&ok, font, this);
  if (ok) { m_item->SetFont(new_font); }
}

void ribi::QtRoundedEditRectItemDialog::on_text_textChanged()
{
  const auto s = ui->text->toPlainText().toStdString();
  const auto text = Container().SeperateString(s,'\n');
  m_item->SetText(text);
  CheckMe();
}

void ribi::QtRoundedEditRectItemDialog::on_button_text_pen_clicked()
{
  const QPen pen(
    QBrush(qRgb(std::rand() % 256,std::rand() % 256,std::rand() % 256)),
    1.0 + (static_cast<double>(std::rand() % 100) / 10.0)
  );
  m_item->SetTextPen(pen);
}

void ribi::QtRoundedEditRectItemDialog::OnBaseChanged(QtRoundedEditRectItem * const qtitem) noexcept
{
  assert(m_item.get() == qtitem);
  //boost::shared_ptr<QtRoundedRectItem> base(m_item);
  m_dialog->SetItem(m_item);
}

void ribi::QtRoundedEditRectItemDialog::OnFontChanged(QtRoundedEditRectItem * const qtitem) noexcept
{
  ui->label_font->setText(
    qtitem->GetFont().toString()
  );
}

void ribi::QtRoundedEditRectItemDialog::OnPaddingChanged(QtRoundedEditRectItem * const qtitem) noexcept
{
  ui->box_padding_bottom->setValue(qtitem->GetPadding().bottom);
  ui->box_padding_left->setValue(qtitem->GetPadding().left);
  ui->box_padding_right->setValue(qtitem->GetPadding().right);
  ui->box_padding_top->setValue(qtitem->GetPadding().top);
}

void ribi::QtRoundedEditRectItemDialog::OnTextChanged(QtRoundedEditRectItem * const qtitem) noexcept
{
  std::string s;
  for (const auto t: qtitem->GetText())
  {
    s += t + '\n';
  }
  ui->text->setPlainText(s.c_str());
}

void ribi::QtRoundedEditRectItemDialog::OnTextPenChanged(QtRoundedEditRectItem * const qtitem) noexcept
{
  std::stringstream s;
  s << "Text pen: " << qtitem->GetTextPen().widthF();
  ui->label_text_pen->setText(s.str().c_str());
}

void ribi::QtRoundedEditRectItemDialog::SetItem(const boost::shared_ptr<QtRoundedEditRectItem>& item) noexcept
{
  const bool verbose{false};

  assert(item);
  if (m_item == item)
  {
    CheckMe();
    return;
  }
  if (verbose)
  {
    std::stringstream s;
    s << "Setting item '" << (*item) << "'\n";
  }

  const boost::shared_ptr<QtRoundedRectItem> base_after = item;
  const auto font_after = item->GetFont();
  const auto padding_after = item->GetPadding();
  const auto text_after = item->GetText();
  const auto text_pen_after = item->GetTextPen();

  bool base_changed  = true;
  bool font_changed  = true;
  bool padding_changed = true;
  bool text_changed = true;
  bool text_pen_changed = true;

  if (m_item)
  {
    const boost::shared_ptr<QtRoundedRectItem> base_before = m_item;
    const auto font_before = m_item->GetFont();
    const auto padding_before = m_item->GetPadding();
    const auto text_before = m_item->GetText();
    const auto text_pen_before = m_item->GetTextPen();

    base_changed = base_before != base_after;
    font_changed = font_before != font_after;
    padding_changed = padding_before != padding_after;
    text_changed = text_before != text_after;
    text_pen_changed = text_pen_before != text_pen_after;

    if (verbose)
    {
      if (base_changed)
      {
        std::stringstream s;
        s
          << "Base will change from "
          << (*base_before)
          << " to "
          << (*base_after)
          << '\n'
        ;
        TRACE(s.str());
      }
      if (font_changed)
      {
        std::stringstream s;
        s << "Font will change from " << font_before.toString().toStdString()
          << " to " << font_after.toString().toStdString() << '\n';
        TRACE(s.str());
      }
      if (padding_changed)
      {
        std::stringstream s;
        s << "Padding will change from '" << padding_before
          << "' to '" << padding_after << "'\n";
        TRACE(s.str());
      }
      if (text_changed)
      {
        std::stringstream s;
        s << "Text will change from " << Container().ToStr(text_before)
          << " to " << Container().ToStr(text_after) << '\n';
        TRACE(s.str());
      }
      if (text_pen_changed)
      {
        std::stringstream s;
        s << "Text pen will change from " << text_pen_before.widthF()
          << " to " << text_pen_after.widthF() << '\n'
        ;
        TRACE(s.str());
      }
    }

    //Disconnect m_item
    m_item->m_signal_base_changed.disconnect(
      boost::bind(&ribi::QtRoundedEditRectItemDialog::OnBaseChanged,this,boost::lambda::_1)
    );
    m_item->m_signal_font_changed.disconnect(
      boost::bind(&ribi::QtRoundedEditRectItemDialog::OnFontChanged,this,boost::lambda::_1)
    );
    m_item->m_signal_padding_changed.disconnect(
      boost::bind(&ribi::QtRoundedEditRectItemDialog::OnPaddingChanged,this,boost::lambda::_1)
    );
    m_item->m_signal_text_changed.disconnect(
      boost::bind(&ribi::QtRoundedEditRectItemDialog::OnTextChanged,this,boost::lambda::_1)
    );
    m_item->m_signal_text_pen_changed.disconnect(
      boost::bind(&ribi::QtRoundedEditRectItemDialog::OnTextPenChanged,this,boost::lambda::_1)
    );
  }

  //Replace m_item by the new one
  m_item = item;


  assert(m_item->GetFont() == font_after);
  assert(m_item->GetPadding() == padding_after);
  assert(m_item->GetText() == text_after);
  assert(m_item->GetTextPen() == text_pen_after);

  m_item->m_signal_base_changed.connect(
    boost::bind(&ribi::QtRoundedEditRectItemDialog::OnBaseChanged,this,boost::lambda::_1)
  );
  m_item->m_signal_font_changed.connect(
    boost::bind(&ribi::QtRoundedEditRectItemDialog::OnFontChanged,this,boost::lambda::_1)
  );
  m_item->m_signal_padding_changed.connect(
    boost::bind(&ribi::QtRoundedEditRectItemDialog::OnPaddingChanged,this,boost::lambda::_1)
  );
  m_item->m_signal_text_changed.connect(
    boost::bind(&ribi::QtRoundedEditRectItemDialog::OnTextChanged,this,boost::lambda::_1)
  );
  m_item->m_signal_text_pen_changed.connect(
    boost::bind(&ribi::QtRoundedEditRectItemDialog::OnTextPenChanged,this,boost::lambda::_1)
  );

  //Emit everything that has changed
  if (base_changed)
  {
    m_item->m_signal_base_changed(m_item.get());
  }
  if (font_changed)
  {
    m_item->m_signal_font_changed(m_item.get());
  }
  if (padding_changed)
  {
    m_item->m_signal_padding_changed(m_item.get());
  }
  if (text_changed)
  {
    m_item->m_signal_text_changed(m_item.get());
  }
  if (text_pen_changed)
  {
    m_item->m_signal_text_pen_changed(m_item.get());
  }
  assert( item ==  m_item);
  assert(*item == *m_item);
  CheckMe();
}

void ribi::QtRoundedEditRectItemDialog::SetUiX(const double x) noexcept
{
  this->m_dialog->SetUiX(x);
}

void ribi::QtRoundedEditRectItemDialog::SetUiY(const double y) noexcept
{
  this->m_dialog->SetUiY(y);
}


#ifndef NDEBUG
void ribi::QtRoundedEditRectItemDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::QtRoundedEditRectItemDialog::Test");
  TRACE("Finished ribi::QtRoundedEditRectItemDialog::Test successfully");
}
#endif

void ribi::QtRoundedEditRectItemDialog::on_box_padding_left_valueChanged(double arg1)
{
  auto padding = m_item->GetPadding();
  padding.left = arg1;
  m_item->SetPadding(padding);
}

void ribi::QtRoundedEditRectItemDialog::on_box_padding_top_valueChanged(double arg1)
{
  auto padding = m_item->GetPadding();
  padding.top = arg1;
  m_item->SetPadding(padding);
}

void ribi::QtRoundedEditRectItemDialog::on_box_padding_right_valueChanged(double arg1)
{
  auto padding = m_item->GetPadding();
  padding.right = arg1;
  m_item->SetPadding(padding);
}

void ribi::QtRoundedEditRectItemDialog::on_box_padding_bottom_valueChanged(double arg1)
{
  auto padding = m_item->GetPadding();
  padding.bottom = arg1;
  m_item->SetPadding(padding);
}
