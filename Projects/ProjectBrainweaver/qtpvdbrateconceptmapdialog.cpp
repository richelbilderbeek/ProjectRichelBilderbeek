#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtpvdbrateconceptmapdialog.h"

#ifdef COMPILER_SUPPORTS_THREADS_20130507
#include <thread>
#endif

#include <cassert>
#include <boost/numeric/conversion/cast.hpp>
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
  m_file(file),
  m_widget(new QtPvdbConceptMapRateWidget(file->GetConceptMap()))
{
  ui->setupUi(this);
  #ifndef NDEBUG
  Test();
  assert(file);
  #endif
  boost::shared_ptr<pvdb::ConceptMap> concept_map = m_file->GetConceptMap();
  assert(concept_map);

  {
    assert(!ui->widget->layout());
    QLayout * const layout = new QGridLayout;
    ui->widget->setLayout(layout);
    layout->addWidget(m_widget);
  }

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
  assert(m_widget);
  return m_widget;
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
    = m_widget->WriteToConceptMap();
  assert(concept_map);
  m_file->SetConceptMap(concept_map);
  QtPvdbRatingDialog d(m_file);
  ShowChild(&d);
  if (d.GetBackToMenu())
  {
    close();
  }
}

#ifndef NDEBUG
void QtPvdbRateConceptMapDialog::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  #ifdef COMPILER_SUPPORTS_THREADS_20130507
  std::thread t(
    []
    {
  #endif
  TRACE("QtPvdbRateConceptMapDialog::Test started");
  {
    const std::vector<boost::shared_ptr<pvdb::File> > v = pvdb::FileFactory::GetTests();
    const int sz = boost::numeric_cast<int>(v.size());
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
  #ifdef COMPILER_SUPPORTS_THREADS_20130507
    }
  );
  t.detach();
  #endif
}
#endif

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
    //close(); //Do not close after saving
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
  assert(IsEqual(*m_file->GetConceptMap(),*GetWidget()->WriteToConceptMap()));
  m_file->Save(filename);
}

void QtPvdbRateConceptMapDialog::on_button_save_clicked()
{
  Save();
}
