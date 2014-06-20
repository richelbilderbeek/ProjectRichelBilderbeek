//---------------------------------------------------------------------------
/*
QtLedWidget, Qt widget for displaying the Led class
Copyright (C) 2011-2014 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppQtLedWidget.htm
//---------------------------------------------------------------------------
#include "qtledwidgetdialog.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <cassert>

#include "ledwidget.h"
#include "ui_qtledwidgetdialog.h"
#pragma GCC diagnostic pop

ribi::QtLedWidgetDialog::QtLedWidgetDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtLedWidgetDialog),
  m_widget{}
{
  ui->setupUi(this);
}

ribi::QtLedWidgetDialog::~QtLedWidgetDialog()
{
  delete ui;
}

void ribi::QtLedWidgetDialog::SetWidget(const boost::shared_ptr<LedWidget>& /* widget */) noexcept
{
  /*
  const bool verbose = false;

  assert(widget);
  if (m_widget == widget)
  {
    return;
  }
  if (verbose)
  {
    std::stringstream s;
    s << "Setting widget '" << widget->ToStr() << "'\n";
  }

  const auto competency_after  = widget->GetL
  const auto is_complex_after  = widget->GetIsComplex();
  const auto is_concrete_after = widget->GetIsConcrete();
  const auto is_specific_after = widget->GetIsSpecific();
  const auto text_after        = widget->GetText();


  bool competency_changed  = true;
  bool is_complex_changed  = true;
  bool is_concrete_changed = true;
  bool is_specific_changed = true;
  bool text_changed = true;

  if (m_widget)
  {
    const auto competency_before  = m_widget->GetCompetency();
    const auto is_complex_before  = m_widget->GetIsComplex();
    const auto is_concrete_before = m_widget->GetIsConcrete();
    const auto is_specific_before = m_widget->GetIsSpecific();
    const auto text_before        = m_widget->GetText();

    competency_changed  = competency_before != competency_after;
    is_complex_changed  = is_complex_before != is_complex_after;
    is_concrete_changed = is_concrete_before != is_concrete_after;
    is_specific_changed = is_specific_before != is_specific_after;
    text_changed = text_before != text_after;


    if (verbose)
    {
      if (competency_changed)
      {
        std::stringstream s;
        s
          << "Competency will change from "
          << Competencies().ToStr(competency_before)
          << " to "
          << Competencies().ToStr(competency_after)
          << '\n'
        ;
        TRACE(s.str());
      }
      if (is_complex_changed)
      {
        std::stringstream s;
        s << "IsComplex will change from " << is_complex_before
          << " to " << is_complex_after << '\n';
        TRACE(s.str());
      }
      if (is_concrete_changed)
      {
        std::stringstream s;
        s << "IsConcrete will change from " << is_concrete_before
          << " to " << is_concrete_after << '\n';
        TRACE(s.str());
      }
      if (is_specific_changed)
      {
        std::stringstream s;
        s << "IsSpecific will change from " << is_specific_before
          << " to " << is_specific_after << '\n';
        TRACE(s.str());
      }
      if (text_changed)
      {
        std::stringstream s;
        s << "Text will change from '" << text_before
          << "' to '" << text_after << "'\n";
        TRACE(s.str());
      }
    }

    //Disconnect m_widget
    m_widget->m_signal_competency_changed.disconnect(
      boost::bind(&ribi::cmap::QtExampleDialog::OnCompetencyChanged,this,boost::lambda::_1)
    );
    m_widget->m_signal_is_complex_changed.disconnect(
      boost::bind(&ribi::cmap::QtExampleDialog::OnIsComplexChanged,this,boost::lambda::_1)
    );
    m_widget->m_signal_is_concrete_changed.disconnect(
      boost::bind(&ribi::cmap::QtExampleDialog::OnIsConcreteChanged,this,boost::lambda::_1)
    );
    m_widget->m_signal_is_specific_changed.disconnect(
      boost::bind(&ribi::cmap::QtExampleDialog::OnIsSpecificChanged,this,boost::lambda::_1)
    );
    m_widget->m_signal_text_changed.disconnect(
      boost::bind(&ribi::cmap::QtExampleDialog::OnTextChanged,this,boost::lambda::_1)
    );
  }

  //Replace m_widget by the new one
  m_widget = widget;


  assert(m_widget->GetCompetency() == competency_after );
  assert(m_widget->GetIsComplex()  == is_complex_after );
  assert(m_widget->GetIsConcrete() == is_concrete_after);
  assert(m_widget->GetIsSpecific() == is_specific_after);
  assert(m_widget->GetText()       == text_after       );

  m_widget->m_signal_competency_changed.connect(
    boost::bind(&ribi::cmap::QtExampleDialog::OnCompetencyChanged,this,boost::lambda::_1)
  );
  m_widget->m_signal_is_complex_changed.connect(
    boost::bind(&ribi::cmap::QtExampleDialog::OnIsComplexChanged,this,boost::lambda::_1)
  );
  m_widget->m_signal_is_concrete_changed.connect(
    boost::bind(&ribi::cmap::QtExampleDialog::OnIsConcreteChanged,this,boost::lambda::_1)
  );
  m_widget->m_signal_is_specific_changed.connect(
    boost::bind(&ribi::cmap::QtExampleDialog::OnIsSpecificChanged,this,boost::lambda::_1)
  );
  m_widget->m_signal_text_changed.connect(
    boost::bind(&ribi::cmap::QtExampleDialog::OnTextChanged,this,boost::lambda::_1)
  );

  //Emit everything that has changed
  if (competency_changed)
  {
    m_widget->m_signal_competency_changed(m_widget.get());
  }
  if (is_complex_changed)
  {
    m_widget->m_signal_is_complex_changed(m_widget.get());
  }
  if (is_concrete_changed)
  {
    m_widget->m_signal_is_concrete_changed(m_widget.get());
  }
  if (is_specific_changed)
  {
    m_widget->m_signal_is_specific_changed(m_widget.get());
  }
  if (text_changed)
  {
    m_widget->m_signal_text_changed(m_widget.get());
  }
  assert( widget ==  m_widget);
  assert(*widget == *m_widget);
  */
}
