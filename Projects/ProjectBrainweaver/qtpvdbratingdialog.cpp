#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtpvdbratingdialog.h"

#include <cassert>

#include <boost/lexical_cast.hpp>

#include <QKeyEvent>
#include <QFileDialog>
#include <QDesktopWidget>
#include <QPainter>

#if (QT_VERSION >= QT_VERSION_CHECK(5,5,0))

#include <QPrinter>
#else

#include <QPrinter>
#endif

#include "pvdbconceptmap.h"
#include "qtpvdbconceptmapwidget.h"
#include "qtpvdbprintratingdialog.h"
#include "qtpvdbconceptmapeditwidget.h"
#include "qtpvdbdisplay.h"
#include "qtpvdbfiledialog.h"
#include "qtpvdbdisplayconceptitem.h"
#include "pvdbfile.h"
#include "trace.h"
#include "ui_qtpvdbratingdialog.h"

QtPvdbRatingDialog::QtPvdbRatingDialog(
  const boost::shared_ptr<pvdb::File> file,
  QWidget* parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtPvdbRatingDialog),
    m_back_to_menu(false),
    m_file(file)
{
  ui->setupUi(this);
  assert(file);
  assert(file->GetConceptMap());
  //Student name
  {
    const std::string s = "Naam student: " + file->GetStudentName();
    ui->label_student_name->setText(s.c_str());
  }
  //Assessor name
  {
    ui->label_assessor_name->setText("Naam assessor: ");
    if (!file->GetAssessorName().empty())
    {
      ui->edit_name->setText(file->GetAssessorName().c_str());
      //ui->edit_name->setReadOnly(true); //TVDB request
      ui->button_print->setEnabled(true);
    }
    else
    {
      ui->button_print->setEnabled(false);
    }
  }

  pvdb::QtDisplay::DisplayRatedConcepts(file,ui->table_concepts);
  pvdb::QtDisplay::DisplayExamples(file,ui->table_examples);
  pvdb::QtDisplay::DisplayValues(file,ui->table_values);

  //Center the dialog
  {
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->setGeometry(screen.adjusted(64,64,-64,-64));
    this->move( screen.center() - this->rect().center() );
  }
}

QtPvdbRatingDialog::~QtPvdbRatingDialog()
{
  delete ui;
}

void QtPvdbRatingDialog::keyPressEvent(QKeyEvent* e)
{
  if (e->key() == Qt::Key_Escape) { close(); }
}

void QtPvdbRatingDialog::on_button_save_clicked()
{
  //Temporarily disable to widget, otherwise saving cannot succeed
  this->hide();

  const auto d = pvdb::QtFileDialog::GetSaveFileDialog(pvdb::QtFileDialog::FileType::cmp);
  d->setWindowTitle("Sla het assessment invoer-bestand op");
  const int status = d->exec();
  if (status == QDialog::Rejected)
  {
    this->show();
    return;
  }
  assert(d->selectedFiles().size() == 1);
  const std::string filename_raw = d->selectedFiles()[0].toStdString();
  assert(!filename_raw.empty());

  const std::string filename
    =  (filename_raw.size() < pvdb::File::GetFilenameExtension().size()
      || filename_raw.substr( filename_raw.size() - 3, 3 ) != pvdb::File::GetFilenameExtension()
     ? filename_raw + std::string(".") + pvdb::File::GetFilenameExtension()
     : filename_raw);
  assert(filename.size() > 3
    && filename.substr( filename.size() - 3, 3 ) == pvdb::File::GetFilenameExtension()
    && "File must have correct file extension name");
  Save(filename);
  this->m_back_to_menu = true;
  close();
}

void QtPvdbRatingDialog::Save(const std::string& filename) const
{
  assert(filename.size() > 3
    && filename.substr( filename.size() - 3, 3 ) == pvdb::File::GetFilenameExtension()
    && "File must have correct file extension name");

  m_file->Save(filename);
  //{ const std::string debug_str = "File saved as " + filename; TRACE(debug_str); }
}



void QtPvdbRatingDialog::on_button_print_clicked()
{
  QtPvdbPrintRatingDialog d(this->m_file);

  //Put this in QtPvdbPrintRatingDialog itself..
  //pvdb::QtDisplay::DisplayRatedConcepts(m_file,d.GetTableConcepts());
  //{
  //  const int sz = static_cast<int>(m_file->GetConceptMap()->GetNodes().size());
  //  d.GetTableConcepts()->setMinimumHeight( ((sz-1) * 30) + 26 ); //Standard row is 30 pixels high, header 25 pixels
  //}
  //pvdb::QtDisplay::DisplayExamples(m_file,d.GetTableExamples());
  //pvdb::QtDisplay::DisplayValues(m_file,d.GetTableValues());

  //Center the dialog
  {
    const QRect screen = QApplication::desktop()->screenGeometry();
    d.setGeometry(screen.adjusted(64,64,-64,-64));
    d.move( screen.center() - d.rect().center() );
  }

  this->ShowChild(&d);
}

void QtPvdbRatingDialog::on_edit_name_textEdited(const QString &arg1)
{
  if (arg1.size() > 1)
  {
    m_file->SetAssessorName(arg1.toStdString());
    ui->button_print->setEnabled(true);
  }
  else
  {
    ui->button_print->setEnabled(false);
  }
}
