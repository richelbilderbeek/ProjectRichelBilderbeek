#include "qtconceptmaptesteditconceptmapwidget.h"

#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtconceptmapwidget.h"
#include "ui_qtconceptmaptesteditconceptmapwidget.h"
#pragma GCC diagnostic pop

ribi::cmap::QtTestEditConceptMapWidgetDialog::QtTestEditConceptMapWidgetDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtTestEditConceptMapWidgetDialog),
  m_widget(new QtTestEditConceptMapWidgetDialog)
{
  ui->setupUi(this);
  //Add the conceptmap widget
  {
    assert(!ui->frame->layout());

    assert(!ui->frame->layout());
  }

}

ribi::cmap::QtTestEditConceptMapWidgetDialog::~QtTestEditConceptMapWidgetDialog()
{
  delete ui;
}
