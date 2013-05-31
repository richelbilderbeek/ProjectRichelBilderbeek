#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtpvdbcreateassessmentmenudialog.h"

#include <QKeyEvent>

#include "qtpvdbcreateassessmentcompletedialog.h"
#include "qtpvdbcreateassessmentpartialdialog.h"
#include "trace.h"


#include "ui_qtpvdbcreateassessmentmenudialog.h"



#include "pvdbfile.h"

QtPvdbCreateAssessmentMenuDialog::QtPvdbCreateAssessmentMenuDialog(QWidget* parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtPvdbCreateAssessmentMenuDialog)
{
  ui->setupUi(this);
}

QtPvdbCreateAssessmentMenuDialog::~QtPvdbCreateAssessmentMenuDialog()
{
  delete ui;
}

void QtPvdbCreateAssessmentMenuDialog::keyPressEvent(QKeyEvent* e)
{
  if (e->key()  == Qt::Key_Escape) close();
}

void QtPvdbCreateAssessmentMenuDialog::on_button_create_assessment_complete_clicked()
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
