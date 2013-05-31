#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtpvdbcreateassessmentpartialdialog.h"

#include <QKeyEvent>
#include <QFileDialog>
#include "pvdbfile.h"


#include "ui_qtpvdbcreateassessmentpartialdialog.h"


QtPvdbCreateAssessmentPartialDialog::QtPvdbCreateAssessmentPartialDialog(
  const boost::shared_ptr<pvdb::File> file, QWidget* parent)
  : QDialog(parent),
    ui(new Ui::QtPvdbCreateAssessmentPartialDialog),
    m_file(file)
{
  ui->setupUi(this);
  assert(!"TODO");
  /*
  {
    const std::vector<std::string> v = m_file->GetQuestion();
    if (v.size() == 4)
    {
      ui->edit_1->setText(v[0].c_str());
      ui->edit_2->setText(v[1].c_str());
      ui->edit_3->setText(v[2].c_str());
      ui->edit_complete->setText(v[3].c_str());
    }
    else
    {
      ui->edit_1->setText("");
      ui->edit_2->setText("");
      ui->edit_3->setText("");
      ui->edit_complete->setText("");
    }
  }
  */
  QObject::connect(ui->edit_1,SIGNAL(textChanged(QString)),this,SLOT(AnyEditChanged()));
  QObject::connect(ui->edit_2,SIGNAL(textChanged(QString)),this,SLOT(AnyEditChanged()));
  QObject::connect(ui->edit_3,SIGNAL(textChanged(QString)),this,SLOT(AnyEditChanged()));
  QObject::connect(ui->edit_complete,SIGNAL(textChanged(QString)),this,SLOT(AnyEditChanged()));
}

void QtPvdbCreateAssessmentPartialDialog::AnyEditChanged()
{
  /*
  m_file.SetQuestions(
    {
      ui->edit_1->text().toStdString(),
      ui->edit_2->text().toStdString(),
      ui->edit_3->text().toStdString(),
      ui->edit_complete->text().toStdString()
    }
  );
  */
}

QtPvdbCreateAssessmentPartialDialog::~QtPvdbCreateAssessmentPartialDialog()
{
  delete ui;
}

void QtPvdbCreateAssessmentPartialDialog::keyPressEvent(QKeyEvent* e)
{
  if (e->key()  == Qt::Key_Escape) close();
}

void QtPvdbCreateAssessmentPartialDialog::on_button_save_clicked()
{

  //const QString filename = QFileDialog::getSaveFileName(0,"Sla het assessment invoer-bestand op",QString(),"*.txt");

  //if (!filename.isEmpty())
  //{
  //  pvdb::ProgramFlow::GetInstance()->GoBack(pvdb::State::assessor_menu);
  //  this->hide();
  //}
}
