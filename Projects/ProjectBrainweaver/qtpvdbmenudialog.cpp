#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtpvdbmenudialog.h"

#ifdef COMPILER_SUPPORTS_THREADS_20130507
#include <thread>
#endif

#include <boost/lexical_cast.hpp>

#include <QFile>
#include <QFileDialog>
#include <QKeyEvent>
#include <QLayout>
#include <QVBoxLayout>

#include "pvdbconceptfactory.h"
#include "pvdbconcept.h"
#include "pvdbconceptmapfactory.h"
#include "pvdbconceptmap.h"
#include "qtpvdbrateconceptautodialog.h"
#include "pvdbexamples.h"
#include "qtpvdbtestcreatesubconceptmapdialog.h"
#include "pvdbfilefactory.h"
#include "pvdbfile.h"
#include "qtpvdbaboutdialog.h"
#include "qtpvdbassessormenudialog.h"
#include "qtpvdbclusterdialog.h"
#include "qtpvdbclusterwidget.h"
#include "pvdbnode.h"
#include "pvdbconcept.h"
#include "pvdbexample.h"
#include "pvdbexamples.h"
#include "qtpvdbconcepteditdialog.h"
#include "qtpvdbconceptmapdialog.h"
#include "qtpvdbcreateassessmentcompletedialog.h"
#include "qtpvdboverviewdialog.h"
#include "qtpvdbprintconceptmapdialog.h"
#include "qtpvdbprintratingdialog.h"
#include "qtpvdbrateconceptdialog.h"
#include "qtpvdbrateconceptmapdialog.h"
#include "qtpvdbrateexamplesdialog.h"
#include "qtpvdbratingdialog.h"
#include "qtpvdbstudentmenudialog.h"
#include "qtpvdbtestconceptitemdialog.h"
#include "qtpvdbtestconceptmapdisplaywidgetdialog.h"
#include "qtpvdbtestconceptmapeditwidgetdialog.h"
#include "qtpvdbtestconceptmapratewidgetdialog.h"
#include "qtpvdbtestedgeitemdialog.h"
#include "qtpvdbtestnodeitemdialog.h"
#include "qtpvdbviewfilesdialog.h"
#include "qtpvdbviewtestsdialog.h"
#include "toolstylesheetsettermaindialog.h"


#include "qttestqtarrowitemsmenudialog.h"
#include "qttestqtroundededitrectitemmenudialog.h"
#include "qttestqtroundedtextrectitemmenudialog.h"
#include "trace.h"
#include "ui_qtpvdbmenudialog.h"

QtPvdbMenuDialog::QtPvdbMenuDialog(QWidget* parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtPvdbMenuDialog)
{
  ui->setupUi(this);
  #ifndef NDEBUG
  Test();
  #else
  ui->widget_debug_1->setVisible(false);
  ui->widget_debug_2->setVisible(false);
  #endif
}

QtPvdbMenuDialog::~QtPvdbMenuDialog()
{
  delete ui;
}

void QtPvdbMenuDialog::keyPressEvent(QKeyEvent* e)
{
  assert(e);
  if (e->key()  == Qt::Key_Escape) { close(); return; }
}

void QtPvdbMenuDialog::on_button_assessor_clicked()
{
  QtPvdbAssessorMenuDialog d;
  this->ShowChild(&d);
}

void QtPvdbMenuDialog::on_button_rate_concept_clicked()
{
  //Obtain a random file
  const std::vector<boost::shared_ptr<pvdb::File> > v = pvdb::File::GetTests();
  const boost::shared_ptr<pvdb::File> file = v[ std::rand() % v.size() ];
  //Set HeteromorphousTestConceptMap[15]
  {
    const boost::shared_ptr<pvdb::ConceptMap> concept_map
      = pvdb::ConceptMapFactory::GetHeteromorphousTestConceptMaps().at(15);
    assert(concept_map);
    file->SetConceptMap(concept_map);
  }
  //Obtain a random sub-concept-map
  const std::vector<boost::shared_ptr<pvdb::ConceptMap> > concept_maps = file->GetConceptMap()->CreateSubs();
  //Display this random concept map
  const boost::shared_ptr<pvdb::ConceptMap> concept_map = concept_maps[ std::rand() % concept_maps.size() ];
  //Create and show the dialog
  boost::shared_ptr<QtPvdbRateConceptDialog> d(
    new QtPvdbRateConceptDialog(concept_map));
  this->ShowChild(d.get());
}

void QtPvdbMenuDialog::on_button_rate_concept_map_clicked()
{
  const std::vector<boost::shared_ptr<pvdb::File> > v = pvdb::File::GetTests();
  const boost::shared_ptr<pvdb::File> file = v[ std::rand() % v.size() ];
  const boost::shared_ptr<pvdb::ConceptMap> concept_map
    = pvdb::ConceptMapFactory::GetHeteromorphousTestConceptMaps().at(15);
  file->SetConceptMap(concept_map);
  QtPvdbRateConceptMapDialog d(file);
  this->ShowChild(&d);
}

void QtPvdbMenuDialog::on_button_rate_examples_clicked()
{
  const boost::shared_ptr<pvdb::Concept> concept = pvdb::ConceptFactory::GetTests().at(4);
  boost::shared_ptr<QtPvdbRateExamplesDialog> d(new QtPvdbRateExamplesDialog(concept));
  this->ShowChild(d.get());
}

void QtPvdbMenuDialog::on_button_rating_clicked()
{
  const boost::shared_ptr<pvdb::File> file = pvdb::FileFactory::GetTests().at(4);
  assert(file);
  QtPvdbRatingDialog d(file);
  this->ShowChild(&d);
}

void QtPvdbMenuDialog::on_button_student_clicked()
{
  const std::string filter_str = std::string("*.") + pvdb::File::GetFilenameExtension();
  const std::string filename
    = QFileDialog::getOpenFileName(0,"Kies een assessment bestand",QString(),
      filter_str.c_str()).toStdString();
  if (!filename.empty())
  {
    try
    {
      const boost::shared_ptr<pvdb::File> file(pvdb::File::Load(filename));
      assert(file);
      QtPvdbStudentMenuDialog d(file);
      this->ShowChild(&d);
    }
    catch (...)
    {
      //Gotta catch 'm all
    }
  }

}

void QtPvdbMenuDialog::on_button_test_cluster_clicked()
{
  const std::vector<boost::shared_ptr<pvdb::File> > files = pvdb::File::GetTests();
  boost::shared_ptr<pvdb::File>  file = files[ std::rand() % files.size() ];
  {
    const std::string question = "qtvdbmenudialog.cpp 79?";
    boost::shared_ptr<pvdb::ConceptMap> concept_map(pvdb::ConceptMapFactory::Create(question));
    assert(concept_map);
    file->SetConceptMap(concept_map);
    //file->SetQuestion("Wat zal ik als test focusvraag schrijven?");
    assert(file->GetQuestion() == question);
  }
  QtPvdbClusterDialog d(file);
  this->ShowChild(&d);
}

void QtPvdbMenuDialog::on_button_overview_clicked()
{

  const QString old_title = this->windowTitle();
  this->setWindowTitle("Loading, please wait...");
  QtPvdbOverviewDialog d;
  this->ShowChild(&d);
}

void QtPvdbMenuDialog::on_button_about_clicked()
{
  const auto d = QtPvdbAboutDialog::Get();
  this->hide();
  d->exec();
  this->show();
}

void QtPvdbMenuDialog::on_button_test_conceptmap_clicked()
{
  const std::vector<boost::shared_ptr<pvdb::File> > v = pvdb::File::GetTests();
  const boost::shared_ptr<pvdb::File> file = v[ std::rand() % v.size() ];
  const boost::shared_ptr<pvdb::ConceptMap> concept_map
    = pvdb::ConceptMapFactory::GetHeteromorphousTestConceptMaps().at(15);
  file->SetConceptMap(concept_map);
  QtPvdbConceptMapDialog d(file);
  assert(file);
  this->ShowChild(&d);
}

void QtPvdbMenuDialog::on_button_test_conceptedit_clicked()
{
  const auto concepts = pvdb::ConceptFactory::GetTests();
  boost::shared_ptr<pvdb::Concept>  concept = concepts[ std::rand() % concepts.size() ];
  while (concept->GetExamples()->Get().empty())
  {
    concept = concepts[ std::rand() % concepts.size() ];
  }
  assert(concept);
  QtPvdbConceptEditDialog d(concept);
  this->ShowChild(&d);
}

void QtPvdbMenuDialog::on_button_view_files_clicked()
{
  QtPvdbViewFilesDialog d;
  this->ShowChild(&d);
}

void QtPvdbMenuDialog::on_button_view_test_concept_maps_clicked()
{
  QtPvdbViewTestsDialog d;
  TRACE("BEFORE ERROR");
  this->ShowChild(&d);
  TRACE("AFTER ERROR");
}

void QtPvdbMenuDialog::Test()
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
  TRACE("Started QtPvdbMenuDialog::Test");
  {
    QtPvdbOverviewDialog d; //Creates all screens, does all tests
  }
  //THE MULTI DIALOG TESTS HERE
  //MULTI DIALOG TEST #1
  //1) Create an assessor question file
  //2) Load the assessor file (as a student)
  //3) Fill in a name
  //4) Start with concept map
  //5) Save
  //6) Test if clustering is disabled
  {
    const std::string question = "DEBUG_QUESTION";
    const std::string filename = pvdb::File::GetTestFileName();
    const std::string name = "DEBUG_NAME";
    //1) Create an assessor question file
    {
      QtPvdbCreateAssessmentCompleteDialog d;
      d.SetQuestion(question);
      assert(d.GetQuestion() == question);
      d.Save(filename);
    }
    //2) Load the assessor file (as a student)
    //3) Fill in a name
    {
      boost::shared_ptr<pvdb::File> file(pvdb::File::Load(filename));
      assert(file->GetQuestion() == question);
      assert(file->GetStudentName().empty());
      QtPvdbStudentMenuDialog d(file);
      d.SetName(name);
      assert(d.GetName() == name);
      d.Save(filename);
    }
    //4) Start with concept map
    //5) Save
    {
      boost::shared_ptr<pvdb::File> file(pvdb::File::Load(filename));
      assert(file->GetQuestion() == question);
      assert(file->GetStudentName() == name);
      QtPvdbConceptMapDialog d(file);
      assert(file->GetQuestion() == question);
      assert(file->GetStudentName() == name);
      assert(file->GetConceptMap()->GetNodes().size() == 1);
      assert(file->GetConceptMap()->GetEdges().empty());
      d.DoRandomStuff();
      assert(file->GetConceptMap()->GetNodes().size() > 1);
      assert(!file->GetConceptMap()->GetEdges().empty());
      d.Save(filename);
    }
    //6) Test if clustering is disabled
    {
      boost::shared_ptr<pvdb::File> file(pvdb::File::Load(filename));
      assert(file->GetQuestion() == question);
      assert(file->GetStudentName() == name);
      assert(file->GetConceptMap()->GetNodes().size() > 1);
      assert(!file->GetConceptMap()->GetEdges().empty());
      QtPvdbClusterDialog d(file);
      assert(!d.GetWidget()->isEnabled()
        && "Cluster widget should be disabled for a file with a filled in ConceptMap");
    }
    std::remove(pvdb::File::GetTestFileName().c_str());
  }
  //Long test #2
  //1) Create an assessor question file
  //2) Load the assessor file (as a student)
  //3) Fill in a name
  //4) Start with clustering
  //5) Start with concept map
  //6) Save
  {
    const std::string question = "DEBUG_QUESTION";
    const std::string filename = pvdb::File::GetTestFileName();
    const std::string name = "DEBUG_NAME";
    //1) Create an assessor question file
    {
      QtPvdbCreateAssessmentCompleteDialog d;
      d.SetQuestion(question);
      assert(d.GetQuestion() == question);
      d.Save(filename);
    }
    //2) Load the assessor file (as a student)
    //3) Fill in a name
    {
      boost::shared_ptr<pvdb::File> file(pvdb::File::Load(filename));
      assert(file->GetQuestion() == question);
      assert(file->GetStudentName().empty());
      QtPvdbStudentMenuDialog d(file);
      d.SetName(name);
      assert(d.GetName() == name);
      d.Save(filename);
    }
    //4) Start with clustering
    {
      boost::shared_ptr<pvdb::File> file(pvdb::File::Load(filename));
      assert(file->GetQuestion() == question);
      assert(file->GetStudentName() == name);
      QtPvdbClusterDialog d(file);
      assert(file->GetQuestion() == question);
      assert(file->GetStudentName() == name);
      assert(file->GetCluster()->Empty());
      assert(file->GetConceptMap()->GetNodes().size() == 1);
      assert(file->GetConceptMap()->GetEdges().empty());
      d.DoRandomStuff();
      assert(!file->GetCluster()->Empty());
      assert(file->GetConceptMap()->GetNodes().size() == 1);
      assert(file->GetConceptMap()->GetEdges().empty());
      d.Save(filename);
    }
    //5) Start with concept map
    //6) Save
    {
      boost::shared_ptr<pvdb::File> file(pvdb::File::Load(filename));
      assert(file->GetQuestion() == question);
      assert(file->GetStudentName() == name);
      QtPvdbConceptMapDialog d(file);
      assert(file->GetQuestion() == question);
      assert(file->GetStudentName() == name);
      assert(file->GetConceptMap()->GetNodes().size() > 1);
      assert(file->GetConceptMap()->GetEdges().empty());
      d.DoRandomStuff();
      assert(file->GetConceptMap()->GetNodes().size() > 1);
      assert(!file->GetConceptMap()->GetEdges().empty());
      d.Save(filename);
    }
    //7) Test if clustering is disabled
    {
      boost::shared_ptr<pvdb::File> file(pvdb::File::Load(filename));
      assert(file->GetQuestion() == question);
      assert(file->GetStudentName() == name);
      assert(file->GetConceptMap()->GetNodes().size() > 1);
      assert(!file->GetConceptMap()->GetEdges().empty());
      QtPvdbClusterDialog d(file);
      assert(!d.GetWidget()->isEnabled()
        && "Cluster widget should be disabled for a file with a filled in ConceptMap");
    }
    std::remove(pvdb::File::GetTestFileName().c_str());
  }
  TRACE("Finished QtPvdbMenuDialog::Test successfully");
  #ifdef COMPILER_SUPPORTS_THREADS_20130507
    }
  );
  t.detach();
  #endif
}

void QtPvdbMenuDialog::on_button_concept_clicked()
{
  QtPvdbTestConceptItemDialog d;
  this->ShowChild(&d);
}

void QtPvdbMenuDialog::on_button_test_node_item_clicked()
{
  QtPvdbTestNodeItemDialog d;
  this->ShowChild(&d);
}


void QtPvdbMenuDialog::on_button_test_qtroundedtextrectitem_clicked()
{
  QtTestQtRoundedTextRectItemMenuDialog d;
  this->ShowChild(&d);
}

void QtPvdbMenuDialog::on_button_test_qtroundededitrectitem_clicked()
{
  QtTestQtRoundedEditRectItemMenuDialog d;
  this->ShowChild(&d);
}

void QtPvdbMenuDialog::on_button_test_edge_item_clicked()
{
  QtPvdbTestEdgeItemDialog d;
  this->ShowChild(&d);
}

void QtPvdbMenuDialog::on_button_test_arrowitems_clicked()
{
  QtTestQtArrowItemsMenuDialog d;
  this->ShowChild(&d);
}

void QtPvdbMenuDialog::on_button_test_qtconceptmapeditwidget_clicked()
{
  QtPvdbTestConceptMapEditWidgetDialog d;
  this->ShowChild(&d);
}

void QtPvdbMenuDialog::on_button_test_qtconceptmapratewidget_clicked()
{
  QtPvdbTestConceptMapRateWidgetDialog d;
  this->ShowChild(&d);
}

void QtPvdbMenuDialog::on_button_create_test_files_clicked()
{
  //Obtain the four human student concept maps
  {
    for (int i=1; i!=4+1; ++i) //Base 1 counting
    {
      const std::string filename = boost::lexical_cast<std::string>(i) + "." + pvdb::File::GetFilenameExtension();
      const std::string qtpath = ":/files/";
      QFile file((qtpath + filename).c_str());

      //assert(file.isReadable());
      //assert(file.isWritable());
      assert(file.size() > 0);

      file.copy(filename.c_str());

      assert(QFile::exists(filename.c_str()));
    }
  }
  //Obtain the artificial concept maps
  const std::vector<boost::shared_ptr<pvdb::File> > v = pvdb::FileFactory::GetTests();
  const int sz = boost::numeric_cast<int>(v.size());
  for(int i=0; i!=sz; ++i)
  {
    boost::shared_ptr<pvdb::File> file = v[i];
    const std::string s
      = boost::lexical_cast<std::string>(i + 5)
      + "."
      + pvdb::File::GetFilenameExtension();
    file->Save(s);
  }
}

void QtPvdbMenuDialog::on_button_modify_stylesheet_clicked()
{
  ToolStyleSheetSetterMainDialog d(qApp->styleSheet().toStdString());
  this->ShowChild(&d);
  qApp->setStyleSheet(d.GetStyleSheet().c_str());
}

void QtPvdbMenuDialog::on_button_test_qtconceptmapdisplaywidget_clicked()
{
  QtPvdbTestConceptMapDisplayWidgetDialog d;
  this->ShowChild(&d);
}

void QtPvdbMenuDialog::on_button_print_concept_map_clicked()
{
  on_button_create_test_files_clicked();
  const std::string filename = "1." + pvdb::File::GetFilenameExtension();
  assert(QFile::exists(filename.c_str()));
  const boost::shared_ptr<pvdb::File> file = pvdb::File::Load(filename);
  assert(file);
  QtPvdbPrintConceptMapDialog d(file);
  this->ShowChild(&d);

}

void QtPvdbMenuDialog::on_button_print_rating_clicked()
{
  on_button_create_test_files_clicked();
  const std::string filename = "1." + pvdb::File::GetFilenameExtension();
  assert(QFile::exists(filename.c_str()));
  const boost::shared_ptr<pvdb::File> file = pvdb::File::Load(filename);
  assert(file);
  QtPvdbPrintRatingDialog d(file);
  this->ShowChild(&d);
}

void QtPvdbMenuDialog::on_button_rate_concept_auto_clicked()
{
  //Obtain a random file
  //const std::vector<boost::shared_ptr<pvdb::File> > v = pvdb::File::GetTests();
  //const int file_index = std::rand() % v.size();
  //assert(file_index < boost::numeric_cast<int>(v.size()));
  //const boost::shared_ptr<pvdb::File> file = v[ file_index ];
  //Set HeteromorphousTestConceptMap[15]
  //{
    const boost::shared_ptr<pvdb::ConceptMap> concept_map
      = pvdb::ConceptMapFactory::GetHeteromorphousTestConceptMaps().at(17);
    assert(concept_map);
    //file->SetConceptMap(concept_map);
  //}
  //Obtain a random sub-concept-map
  #ifndef NDEBUG
  const auto nodes = concept_map->GetNodes();
  const auto edges = concept_map->GetEdges();
  assert(pvdb::ConceptMap::CanConstruct(nodes,edges));
  #endif
  while (1)
  {
    const std::vector<boost::shared_ptr<pvdb::ConceptMap> > concept_maps
      = concept_map->CreateSubs();
    assert(!concept_maps.empty());
    //Display this random concept map
    const int sub_index = std::rand() % concept_maps.size();
    assert(sub_index < boost::numeric_cast<int>(concept_maps.size()));
    const boost::shared_ptr<pvdb::ConceptMap> concept_map = concept_maps[ sub_index ];
    if (concept_map->GetNodes()[0]->GetConcept()->GetExamples()->Get().empty()) continue;
    //Create and show the dialog
    boost::shared_ptr<QtPvdbRateConceptAutoDialog> d(
      new QtPvdbRateConceptAutoDialog(concept_map));
    this->ShowChild(d.get());
    break;
  }
}

void QtPvdbMenuDialog::on_button_test_create_sub_concept_map_clicked()
{
  QtPvdbTestCreateSubConceptMapDialog d;
  this->ShowChild(&d);
}
