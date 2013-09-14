#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtpvdbcreateassessmentmenudialog.h"

#include <QKeyEvent>

#include "qtpvdbcreateassessmentcompletedialog.h"
#include "qtpvdbcreateassessmentpartialdialog.h"
#include "trace.h"


#include "ui_qtpvdbcreateassessmentmenudialog.h"

#include "pvdbfile.h"
#pragma GCC diagnostic pop

ribi::pvdb::QtPvdbCreateAssessmentMenuDialog::QtPvdbCreateAssessmentMenuDialog(QWidget* parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtPvdbCreateAssessmentMenuDialog),
    m_back_to_menu{false},
    m_question{}
{
  ui->setupUi(this);
}

ribi::pvdb::QtPvdbCreateAssessmentMenuDialog::~QtPvdbCreateAssessmentMenuDialog()
{
  delete ui;
}

void ribi::pvdb::QtPvdbCreateAssessmentMenuDialog::keyPressEvent(QKeyEvent* e)
{
  if (e->key()  == Qt::Key_Escape) close();
}

void ribi::pvdb::QtPvdbCreateAssessmentMenuDialog::on_button_create_assessment_complete_clicked()
{
  QtPvdbCreateAssessmentCompleteDialog d;
  d.SetQuestion(m_question);
  this->ShowChild(&d);
  m_question = d.GetQuestion();
  if (d.GoBackToMenu())
  {
    this->close();
  }
}
