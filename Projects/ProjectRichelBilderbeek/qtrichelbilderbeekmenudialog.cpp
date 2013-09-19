//---------------------------------------------------------------------------
/*
Project Richel Bilderbeek, Richel Bilderbeek's work
Copyright (C) 2010-2013 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ProjectRichelBilderbeek.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtrichelbilderbeekmenudialog.h"

#include <algorithm>

#include <string>

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/lambda/lambda.hpp>

#include <QFile>
#include <QKeyEvent>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>

#include "qtaboutdialog.h"
#include "qtarrowitem.h"
#include "qtarrowitem.h"
#include "qtconnectthreewidget.h"
#include "qtdialwidget.h"
#include "qtdisplaypositem.h"
#include "qtexercise.h"
#include "qtgaborfilterwidget.h"
#include "qtkeyboardfriendlygraphicsview.h"
#include "qtlabeledquadbezierarrowitem.h"
#include "qtledwidget.h"
#include "qtleftrightrectitem.h"
#include "qtmatrix.h"
#include "qtmultiplechoicequestiondialog.h"
#include "qtmysterymachinewidget.h"
#include "qtopenquestiondialog.h"
#include "qtpatharrowitem.h"
#include "qtpyloswidget.h"
#include "qtquadbezierarrowitem.h"
#include "qtquestiondialog.h"
#include "qtrichelbilderbeekgallerydialog.h"
#include "qtrichelbilderbeekmenuitemwidget.h"
#include "qtrichelbilderbeekprogram.h"
#include "qtroundededitrectitem.h"
#include "qtroundedtextrectitem.h"
#include "qtshapewidget.h"
#include "qtshinybuttonwidget.h"
#include "qtsprites.h"
#include "qtstdvectorfunctionmodel.h"
#include "qtstdvectorstringmodel.h"
#include "qttictactoewidget.h"
#include "qttogglebuttonwidget.h"
#include "qtublasmatrixdoublemodel.h"
#include "qtublasvectordoublemodel.h"
#include "richelbilderbeekmenudialog.h"
#include "richelbilderbeekprogram.h"
#include "testqtarrowitemsmenudialog.h"
#include "testqtkeyboardfriendlygraphicsviewmenudialog.h"
#include "testtogglebuttonmenudialog.h"
#include "tooltestqtmodelsmenudialog.h"
#include "trace.h"
#include "ui_qtrichelbilderbeekmenudialog.h"

#pragma GCC diagnostic pop

ribi::QtRichelBilderbeekMenuDialog::QtRichelBilderbeekMenuDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtRichelBilderbeekMenuDialog)
{
  ui->setupUi(this);
  #ifndef NDEBUG
  Test();
  #endif
  //Set the style sheet using Qt Resources
  {
    this->setStyleSheet( "QDialog { background-image: url(:/images/RichelbilderbeekNlBackground.png);}");
  }

  {
    QtRichelBilderbeekMenuItemWidget * const widget = new QtRichelBilderbeekMenuItemWidget;
    assert(!this->layout());
    QLayout * const layout = new QVBoxLayout;
    this->setLayout(layout);
    layout->addWidget(widget);
    widget->setFocus();

    QPushButton * const button = new QPushButton("&About");
    button->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Maximum);
    QObject::connect(button,SIGNAL(clicked()),this,SLOT(OnAbout()));
    layout->addWidget(button);
  }
}

ribi::QtRichelBilderbeekMenuDialog::~QtRichelBilderbeekMenuDialog() noexcept
{
  delete ui;
}

const ribi::About ribi::QtRichelBilderbeekMenuDialog::GetAbout() noexcept
{
  About a = RichelBilderbeek::MenuDialog::GetAbout();
  a.AddLibrary("QtArrowItem version: " + QtArrowItem::GetVersion());
  a.AddLibrary("QtConnectThreeWidget version: " + QtConnectThreeWidget::GetVersion());
  a.AddLibrary("QtDialWidget version: " + QtDialWidget::GetVersion());
  a.AddLibrary("QtDisplayPosItem version: " + QtDisplayPosItem::GetVersion());
  a.AddLibrary("QtDisplayPosItem version: " + QtDisplayPosItem::GetVersion());
  a.AddLibrary("QtExercise version: " + QtExercise::GetVersion());
  a.AddLibrary("QtGaborFilterWidget version: " + QtGaborFilterWidget::GetVersion());
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  a.AddLibrary("QtKeyboardFriendlyGraphicsView version: " + QtKeyboardFriendlyGraphicsView::GetVersion());
  a.AddLibrary("QtLabeledQuadBezierArrowItem version: " + QtLabeledQuadBezierArrowItem::GetVersion());
  a.AddLibrary("QtLedWidget version: " + QtLedWidget::GetVersion());
  a.AddLibrary("QtLeftRightRectItem version: " + QtLeftRightRectItem::GetVersion());
  a.AddLibrary("QtMatrix version: " + QtMatrix::GetVersion());
  a.AddLibrary("QtMultipleChoiceQuestionDialog version: " + QtMultipleChoiceQuestionDialog::GetVersion());
  a.AddLibrary("QtMysteryMachineWidget version: " + QtMysteryMachineWidget::GetVersion());
  a.AddLibrary("QtOpenQuestionDialog version: " + QtOpenQuestionDialog::GetVersion());
  a.AddLibrary("QtPathArrowItem version: " + QtPathArrowItem::GetVersion());
  a.AddLibrary("QtPylosWidget version: " + QtPylosWidget::GetVersion());
  a.AddLibrary("QtQuadBezierArrowItem version: " + QtQuadBezierArrowItem::GetVersion());
  a.AddLibrary("QtQuestionDialog version: " + QtQuestionDialog::GetVersion());
  a.AddLibrary("QtRichelBilderbeekGalleryDialog version: " + QtRichelBilderbeekGalleryDialog::GetVersion());
  a.AddLibrary("QtRoundedEditRectItem version: " + QtRoundedEditRectItem::GetVersion());
  a.AddLibrary("QtRoundedRectItem version: " + QtRoundedRectItem::GetVersion());
  a.AddLibrary("QtRoundedTextRectItem version: " + QtRoundedTextRectItem::GetVersion());
  a.AddLibrary("QtShapeWidget version: " + QtShapeWidget::GetVersion());
  a.AddLibrary("QtShinyButtonWidget version: " + QtShinyButtonWidget::GetVersion());
  //a.AddLibrary("QtSprites version: " + QtSprites::GetVersion());
  a.AddLibrary("QtStdVectorFunctionModel version: " + QtStdVectorFunctionModel::GetVersion());
  a.AddLibrary("QtStdVectorStringModel version: " + QtStdVectorStringModel::GetVersion());
  a.AddLibrary("QtTicTacToeWidget version: " + QtTicTacToeWidget::GetVersion());
  a.AddLibrary("QtToggleButtonWidget version: " + QtToggleButtonWidget::GetVersion());
  a.AddLibrary("QtUblasMatrixDoubleModel version: " + QtUblasMatrixDoubleModel::GetVersion());
  a.AddLibrary("QtUblasVectorDoubleModel version: " + QtUblasVectorDoubleModel::GetVersion());
  a.AddLibrary("TestKeyboardFriendlyGraphicsView version: " + TestKeyboardFriendlyGraphicsViewMenuDialog::GetVersion());
  a.AddLibrary("TestQtArrowItems version: " + TestQtArrowItemsMenuDialog::GetVersion());
  a.AddLibrary("TestQtModels version: " + ToolTestQtModelsMenuDialog::GetVersion());
  return a;
}

void ribi::QtRichelBilderbeekMenuDialog::keyPressEvent(QKeyEvent * event)
{
 if (event->key() == Qt::Key_Escape) { close(); return; }
}

void ribi::QtRichelBilderbeekMenuDialog::OnAbout()
{
  QtAboutDialog d(this->GetAbout());
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  d.exec();
}

#ifndef NDEBUG
void ribi::QtRichelBilderbeekMenuDialog::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  {
    const std::vector<RichelBilderbeek::ProgramType> v = RichelBilderbeek::GetAllProgramTypes();
    for (const RichelBilderbeek::ProgramType type: v)
    {
      #ifndef NDEBUG
      const std::string progress
        = boost::lexical_cast<std::string>(static_cast<int>(type))
        + "/"
        + boost::lexical_cast<std::string>(v.size());
      TRACE(progress);
      #endif
      const boost::shared_ptr<QDialog> d(
        QtRichelBilderbeekProgram::CreateQtMenuDialog(type));
    }
  }
}
#endif
