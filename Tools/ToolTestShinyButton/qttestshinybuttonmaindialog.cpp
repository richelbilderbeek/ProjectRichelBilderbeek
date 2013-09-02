//---------------------------------------------------------------------------
/*
TestShinyButton, tool to test the ShinyButton class
Copyright (C) 2011 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolTestShinyButton.htm
//---------------------------------------------------------------------------
//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qttestshinybuttonmaindialog.h"

#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/lexical_cast.hpp>
#pragma GCC diagnostic pop

#include "shinybutton.h"
#include "shinybuttonwidget.h"
#include "qtshinybuttonwidget.h"
#include "ui_qttestshinybuttonmaindialog.h"

QtTestShinyButtonMainDialog::QtTestShinyButtonMainDialog(QWidget *parent)
 : QDialog(parent),
   ui(new Ui::QtTestShinyButtonMainDialog),
   m_shiny_button(new QtShinyButtonWidget)
{
  ui->setupUi(this);

  ui->my_layout->addWidget(m_shiny_button.get());

  m_shiny_button->m_signal_changed.connect(boost::bind(
    &QtTestShinyButtonMainDialog::OnChanged,this));
  //m_shiny_button->GetWidget()->GetShinyButton()->m_signal_color_changed.connect(boost::bind(
  //  &QtTestShinyButtonMainDialog::OnChanged,this));
  //m_shiny_button->GetWidget()->GetShinyButton()->m_signal_text_changed.connect(boost::bind(
  //  &QtTestShinyButtonMainDialog::OnChanged,this));

  m_shiny_button->GetWidget()->m_signal_clicked.connect(boost::bind(
    &QtTestShinyButtonMainDialog::OnClicked,this));

  on_edit_text_textChanged(QString());
}

QtTestShinyButtonMainDialog::~QtTestShinyButtonMainDialog()
{
  delete ui;
}

void QtTestShinyButtonMainDialog::changeEvent(QEvent *e)
{
  QDialog::changeEvent(e);
  switch (e->type()) {
  case QEvent::LanguageChange:
    ui->retranslateUi(this);
    break;
  default:
    break;
  }
}

void QtTestShinyButtonMainDialog::OnChanged()
{
  const double color
    = static_cast<double>(ui->dial_main_color->value())
    / static_cast<double>(ui->dial_main_color->maximum());
  const double gradient
    = static_cast<double>(ui->dial_gradient->value())
    / static_cast<double>(ui->dial_gradient->maximum());
  const std::string s
    = std::string("Color: (")
    + boost::lexical_cast<std::string>(color)
    + ","
    + boost::lexical_cast<std::string>(gradient)
    + ") (color,gradient)";

  ui->label_color->setText(s.c_str());
}

void QtTestShinyButtonMainDialog::OnClicked()
{
  this->m_shiny_button->GetWidget()->GetShinyButton()->SetColor(0.5,0.5);
}

void QtTestShinyButtonMainDialog::on_edit_text_textChanged(const QString&)
{
  this->m_shiny_button->GetWidget()->GetShinyButton()->SetText(
    ui->edit_text->text().toStdString());
}

void QtTestShinyButtonMainDialog::on_dial_main_color_sliderMoved(int)
{
  const double color
    = static_cast<double>(ui->dial_main_color->value())
    / static_cast<double>(ui->dial_main_color->maximum());
  const double gradient
    = static_cast<double>(ui->dial_gradient->value())
    / static_cast<double>(ui->dial_gradient->maximum());

  m_shiny_button->GetWidget()->GetShinyButton()->SetColor(color,gradient);
}

void QtTestShinyButtonMainDialog::on_dial_gradient_sliderMoved(int)
{
  const double color
    = static_cast<double>(ui->dial_main_color->value())
    / static_cast<double>(ui->dial_main_color->maximum());
  const double gradient
    = static_cast<double>(ui->dial_gradient->value())
    / static_cast<double>(ui->dial_gradient->maximum());

  m_shiny_button->GetWidget()->GetShinyButton()->SetColor(color,gradient);
}

