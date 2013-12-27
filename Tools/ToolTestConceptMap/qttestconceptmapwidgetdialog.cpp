#include "qttestconceptmapwidgetdialog.h"

#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtconceptmapwidget.h"
#include "ui_qttestconceptmapwidgetdialog.h"
#pragma GCC diagnostic pop

ribi::cmap::QtTestConceptMapWidgetDialog::QtTestConceptMapWidgetDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtTestConceptMapWidgetDialog m_widget(new QtTestConceptMapWidgetDialog))
{
  ui->setupUi(this);
  //Add the conceptmap widget
  {
    assert(!ui->frame->layout());

    assert(!ui->frame->layout());
  }

}

ribi::cmap::QtTestConceptMapWidgetDialog::~QtTestConceptMapWidgetDialog()
{
  delete ui;
}
