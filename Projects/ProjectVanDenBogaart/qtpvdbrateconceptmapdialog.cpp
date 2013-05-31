#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtpvdbrateconceptmapdialog.h"

#include <QDesktopWidget>
#include <QFileDialog>
#include <QKeyEvent>

#include "pvdbconceptmapfactory.h"
#include "pvdbconceptmap.h"
#include "pvdbfilefactory.h"
#include "qtscopeddisable.h"
#include "pvdbfile.h"
#include "qtpvdbconceptmapratewidget.h"
#include "trace.h"
#include "qtpvdbratingdialog.h"
#include "ui_qtpvdbrateconceptmapdialog.h"

QtPvdbRateConceptMapDialog::QtPvdbRateConceptMapDialog(
  boost::shared_ptr<pvdb::File> file,
  QWidget* parent)
  : QtHideAndShowDialog(parent),
  ui(new Ui::QtPvdbRateConceptMapDialog),
  m_file(file)
{
  ui->setupUi(this);
  #ifndef NDEBUG
  Test();
  assert(file);
  #endif
  boost::shared_ptr<pvdb::ConceptMap> concept_map = m_file->GetConceptMap();
  assert(concept_map);
  ui->widget->ReadFromConceptMap(concept_map);
  {
    const std::string s = std::string("Naam student: ") + m_file->GetStudentName();
    ui->label_name->setText(s.c_str());
  }

  //Center the dialog
  {
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->setGeometry(screen.adjusted(64,64,-64,-64));
    this->move( screen.center() - this->rect().center() );
  }
}

QtPvdbRateConceptMapDialog::~QtPvdbRateConceptMapDialog()
{
  delete ui;
}

QtPvdbConceptMapRateWidget * QtPvdbRateConceptMapDialog::GetWidget()
{
  assert(ui); assert(ui->widget);
  return ui->widget;
}

void QtPvdbRateConceptMapDialog::keyPressEvent(QKeyEvent* e)
{
  if (e->key()  == Qt::Key_Escape) { close(); return; }
  if ((e->modifiers() & Qt::ControlModifier) && e->key() == Qt::Key_S) { Save(); return; }
  QDialog::keyPressEvent(e);
}

void QtPvdbRateConceptMapDialog::on_button_next_clicked()
{
  const boost::shared_ptr<pvdb::ConceptMap> concept_map
    = ui->widget->WriteToConceptMap();
  assert(concept_map);
  m_file->SetConceptMap(concept_map);
  QtPvdbRatingDialog d(m_file);
  ShowChild(&d);
  if (d.GetBackToMenu())
  {
    close();
  }
}

void QtPvdbRateConceptMapDialog::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("QtPvdbRateConceptMapDialog::Test started");
  {
    const std::vector<boost::shared_ptr<pvdb::File> > v = pvdb::FileFactory::GetTests();
    const int sz = static_cast<int>(v.size());
    for (int i=0; i!=sz; ++i)
    {
      const boost::shared_ptr<pvdb::File> file = v[i];
      const boost::shared_ptr<pvdb::ConceptMap> old_concept_map
        = pvdb::ConceptMapFactory::DeepCopy(file->GetConceptMap());
      QtPvdbRateConceptMapDialog d(file);
      assert(pvdb::ConceptMap::HasSameContent(
        old_concept_map,d.GetWidget()->WriteToConceptMap()));
    }
  }
  TRACE("QtPvdbRateConceptMapDialog::Test finished successfully");
}

void QtPvdbRateConceptMapDialog::Save()
{
  this->hide(); //Obligatory, otherwise program will freeze
  const std::string filter_str = std::string("*.") + pvdb::File::GetFilenameExtension();
  const std::string filename_raw = QFileDialog::getSaveFileName(0,"Sla de beoordeling op",
    QString(),
    filter_str.c_str()).toStdString();
  if (!filename_raw.empty())
  {
    const std::string filename
      =  (filename_raw.size() < pvdb::File::GetFilenameExtension().size()
        || filename_raw.substr( filename_raw.size() - 3, 3 ) != pvdb::File::GetFilenameExtension()
       ? filename_raw + std::string(".") + pvdb::File::GetFilenameExtension()
       : filename_raw);
    assert(filename.size() > 3
      && filename.substr( filename.size() - 3, 3 ) == pvdb::File::GetFilenameExtension()
      && "File must have correct file extension name");
    Save(filename);
    close();
  }
  this->show();
}


void QtPvdbRateConceptMapDialog::Save(const std::string& filename)
{
  assert(filename.size() > 3
    && filename.substr( filename.size() - 3, 3 ) == pvdb::File::GetFilenameExtension()
    && "File must have correct file extension name");
  const boost::shared_ptr<pvdb::ConceptMap> concept_map = GetWidget()->WriteToConceptMap();
  assert(concept_map);
  m_file->SetConceptMap(concept_map);
  assert(m_file->GetConceptMap() == GetWidget()->WriteToConceptMap());
  m_file->Save(filename);
}

void QtPvdbRateConceptMapDialog::on_button_save_clicked()
{
  Save();
}
