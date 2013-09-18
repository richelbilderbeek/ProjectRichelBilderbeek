#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtpvdbstudentstartcompletedialog.h"

#include <fstream>
#include <QKeyEvent>
#include <QFileDialog>
#include "pvdbfile.h"
#include "pvdbclusterfactory.h"
#include "pvdbconceptmapfactory.h"
//#include "pvdbmenudialog.h"
#include "qtpvdbfiledialog.h"
#include "qtpvdbclusterdialog.h"
#include "qtpvdbconceptmapdialog.h"
#include "qtpvdbcreateassessmentmenudialog.h"
#include "trace.h"
#include "ui_qtpvdbstudentstartcompletedialog.h"
#pragma GCC diagnostic pop

ribi::pvdb::QtPvdbStudentStartCompleteDialog::QtPvdbStudentStartCompleteDialog(
  const boost::shared_ptr<pvdb::File> file,
  QWidget* parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtPvdbStudentStartCompleteDialog),
    m_back_to_menu(false),
    m_file(file)
{
  ui->setupUi(this);
  assert(m_file);
  assert(IsEqual(*file,*m_file));
}

ribi::pvdb::QtPvdbStudentStartCompleteDialog::~QtPvdbStudentStartCompleteDialog() noexcept
{
  delete ui;
}

void ribi::pvdb::QtPvdbStudentStartCompleteDialog::keyPressEvent(QKeyEvent* e)
{
  if (e->key()  == Qt::Key_Escape) { close(); return; }
  if ((e->modifiers() & Qt::ControlModifier) && e->key() == Qt::Key_S) { Save(); return; }
  QDialog::keyPressEvent(e);
}

void ribi::pvdb::QtPvdbStudentStartCompleteDialog::on_button_start_associate_clicked()
{
  assert(m_file);
  assert((m_file->GetCluster() || !m_file->GetCluster())
    && "If the file has no cluster, the cluster dialog creates it,"
       "if and only if there is no concept map");
  QtPvdbClusterDialog d(m_file);

  if (!m_file->GetConceptMap())
  {
    assert(m_file->GetCluster()
      && "If the file has no cluster, the cluster dialog creates it,"
         "if and only if there is no concept map");
  }
  this->ShowChild(&d);
  if (d.GoBackToMenu())
  {
    m_back_to_menu = true;
    close();
  }
}

void ribi::pvdb::QtPvdbStudentStartCompleteDialog::on_button_start_construct_clicked()
{
  QtPvdbConceptMapDialog d(m_file);
  this->ShowChild(&d);
  if (d.GoBackToMenu())
  {
    m_back_to_menu = true;
    close();
  }
}

void ribi::pvdb::QtPvdbStudentStartCompleteDialog::Save()
{
  const auto d = pvdb::QtFileDialog::GetSaveFileDialog(pvdb::QtFileDialog::FileType::cmp);
  d->setWindowTitle("Sla de concept map op");
  const int status = d->exec();
  if (status == QDialog::Rejected)
  {
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
  m_file->Save(filename);
  { const std::string debug_str = "File saved as " + filename; TRACE(debug_str); }
}
