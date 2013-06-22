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
#include "qtpvdbrateconcepttallydialog.h"
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
#include "qtpvdbtestedgeitemdialog.h"

#include "qttestqtarrowitemsmenudialog.h"
#include "qttestqtroundededitrectitemmenudialog.h"
#include "qttestqtroundedtextrectitemmenudialog.h"
#include "trace.h"
#include "ui_qtpvdbmenudialog.h"

QtPvdbMenuDialog::QtPvdbMenuDialog(QWidget* parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtPvdbMenuDialog),
    m_show_child_dialogs_modal(true)
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
  if (m_show_child_dialogs_modal) { this->ShowChild(&d); } else { d.close(); }
}

void QtPvdbMenuDialog::on_button_rate_concept_clicked()
{
  //Obtain an empty file
  const boost::shared_ptr<pvdb::File> file = pvdb::FileFactory::Create();
  //Set HeteromorphousTestConceptMap[15]
  {
    const boost::shared_ptr<pvdb::ConceptMap> concept_map
      = pvdb::ConceptMapFactory::GetHeteromorphousTestConceptMaps().at(15);
    assert(concept_map);
    assert(!file->GetConceptMap() && "Can only set a concept map once");
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
  const boost::shared_ptr<pvdb::File> file = pvdb::FileFactory::Create();
  const boost::shared_ptr<pvdb::ConceptMap> concept_map
    = pvdb::ConceptMapFactory::GetHeteromorphousTestConceptMaps().at(15);
  file->SetConceptMap(concept_map);
  QtPvdbRateConceptMapDialog d(file);
  if (m_show_child_dialogs_modal) { this->ShowChild(&d); } else { d.close(); }
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
  if (m_show_child_dialogs_modal) { this->ShowChild(&d); } else { d.close(); }
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
      if (m_show_child_dialogs_modal) { this->ShowChild(&d); } else { d.close(); }
    }
    catch (...)
    {
      //Gotta catch 'm all
    }
  }

}

void QtPvdbMenuDialog::on_button_test_cluster_clicked()
{
  const boost::shared_ptr<pvdb::File> file = pvdb::FileFactory::Create();
  {
    const std::string question = "qtvdbmenudialog.cpp 79?";
    boost::shared_ptr<pvdb::ConceptMap> concept_map(pvdb::ConceptMapFactory::Create(question));
    assert(concept_map);
    assert(!file->GetConceptMap() && "Can only set concept map once");
    file->SetConceptMap(concept_map);
    //file->SetQuestion("Wat zal ik als test focusvraag schrijven?");
    assert(file->GetQuestion() == question);
  }
  assert((file->GetCluster() || !file->GetCluster())
    && "If the file has no cluster, the cluster dialog creates it");
  QtPvdbClusterDialog d(file);
  assert(file->GetCluster() && "the cluster dialog used an existing or created a cluster");
  if (m_show_child_dialogs_modal) { this->ShowChild(&d); } else { d.close(); }
}

void QtPvdbMenuDialog::on_button_overview_clicked()
{
  const QString old_title = this->windowTitle();
  this->setWindowTitle("Loading, please wait...");
  QtPvdbOverviewDialog d;
  if (m_show_child_dialogs_modal) { this->ShowChild(&d); } else { d.close(); }
}

void QtPvdbMenuDialog::on_button_about_clicked()
{
  const auto d = QtPvdbAboutDialog::Get();
  if (m_show_child_dialogs_modal)
  {
    this->hide();
    d->exec();
    this->show();
  }
  else
  {
    d->close();
  }
}

void QtPvdbMenuDialog::on_button_test_conceptmap_clicked()
{
  const boost::shared_ptr<pvdb::File> file = pvdb::FileFactory::Create();
  const boost::shared_ptr<pvdb::ConceptMap> concept_map
    = pvdb::ConceptMapFactory::GetHeteromorphousTestConceptMaps().at(15);
  assert(concept_map);
  assert(!file->GetConceptMap() && "Can only set a concept map once");
  file->SetConceptMap(concept_map);
  QtPvdbConceptMapDialog d(file);
  assert(file);
  if (m_show_child_dialogs_modal) { this->ShowChild(&d); } else { d.close(); }
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
  if (m_show_child_dialogs_modal) { this->ShowChild(&d); } else { d.close(); }
}

void QtPvdbMenuDialog::on_button_view_files_clicked()
{
  QtPvdbViewFilesDialog d;
  if (m_show_child_dialogs_modal) { this->ShowChild(&d); } else { d.close(); }
}

void QtPvdbMenuDialog::on_button_view_test_concept_maps_clicked()
{
  QtPvdbViewTestsDialog d;
  if (m_show_child_dialogs_modal) { this->ShowChild(&d); } else { d.close(); }
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
  //Press all buttons
  {
    QtPvdbMenuDialog d;
    d.m_show_child_dialogs_modal = false;
    Ui::QtPvdbMenuDialog * const ui = d.ui;
    const std::vector<QPushButton*> buttons
      =
      {
        ui->button_about,
        ui->button_assessor,
        ui->button_concept,
        ui->button_create_test_files,
        ui->button_modify_stylesheet,
        ui->button_overview,
        ui->button_print_concept_map,
        ui->button_print_rating,
        ui->button_rate_concept,
        ui->button_rate_concept_auto,
        ui->button_rate_concept_map,
        ui->button_rate_examples,
        ui->button_rating,
        ui->button_student,
        ui->button_test_arrowitems,
        ui->button_test_cluster,
        ui->button_test_conceptedit,
        ui->button_test_conceptmap,
        ui->button_test_create_sub_concept_map,
        ui->button_test_edge_item,
        ui->button_test_node_item,
        ui->button_test_qtconceptmapdisplaywidget,
        ui->button_test_qtconceptmapeditwidget,
        ui->button_test_qtconceptmapratewidget,
        ui->button_test_qtroundededitrectitem,
        ui->button_test_qtroundedtextrectitem,
        ui->button_view_files,
        ui->button_view_test_concept_maps
      };
    const std::size_t n_buttons = buttons.size();
    for (std::size_t i = 0; i!=n_buttons; ++i)
    {
      assert(i < buttons.size());
      QPushButton * const button = buttons[i];
      assert(button);

      TRACE(button->text().toStdString());
      if (button->text() == QString("&M. QtPvdbEdgeItem")
      {
        TRACE("BREAK");
      }
      if (button->isEnabled()) button->click();
    }

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
      assert((file->GetCluster() || !file->GetCluster())
        && "If the file has no cluster, the cluster dialog creates it");
      QtPvdbClusterDialog d(file);
        assert(file->GetCluster() && "the cluster dialog used an existing or created a cluster");
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
      assert((file->GetCluster() || !file->GetCluster())
        && "If the file has no cluster, the cluster dialog creates it");
      QtPvdbClusterDialog d(file);
      assert(file->GetCluster() && "the cluster dialog used an existing or created a cluster");
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
      assert(file->GetConceptMap()->GetNodes().size() == 1);
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
      assert((file->GetCluster() || !file->GetCluster())
        && "If the file has no cluster, the cluster dialog creates it");
      QtPvdbClusterDialog d(file);
      assert(file->GetCluster() && "the cluster dialog used an existing or created a cluster");
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
  if (m_show_child_dialogs_modal) { this->ShowChild(&d); } else { d.close(); }
}

void QtPvdbMenuDialog::on_button_test_node_item_clicked()
{
  QtPvdbTestNodeItemDialog d;
  if (m_show_child_dialogs_modal) { this->ShowChild(&d); } else { d.close(); }
}


void QtPvdbMenuDialog::on_button_test_qtroundedtextrectitem_clicked()
{
  QtTestQtRoundedTextRectItemMenuDialog d;
  if (m_show_child_dialogs_modal) { this->ShowChild(&d); } else { d.close(); }
}

void QtPvdbMenuDialog::on_button_test_qtroundededitrectitem_clicked()
{
  QtTestQtRoundedEditRectItemMenuDialog d;
  if (m_show_child_dialogs_modal) { this->ShowChild(&d); } else { d.close(); }
}

void QtPvdbMenuDialog::on_button_test_edge_item_clicked()
{
  QtPvdbTestEdgeItemDialog d;
  if (m_show_child_dialogs_modal) { this->ShowChild(&d); } else { d.close(); }
}

void QtPvdbMenuDialog::on_button_test_arrowitems_clicked()
{
  QtTestQtArrowItemsMenuDialog d;
  if (m_show_child_dialogs_modal) { this->ShowChild(&d); } else { d.close(); }
}

void QtPvdbMenuDialog::on_button_test_qtconceptmapeditwidget_clicked()
{
  #ifdef SUPPORT_TEST_CONCEPT_MAP_DIALOGS_86543723642
  QtPvdbTestConceptMapEditWidgetDialog d;
  if (m_show_child_dialogs_modal) { this->ShowChild(&d); } else { d.close(); }
  #endif
}

void QtPvdbMenuDialog::on_button_test_qtconceptmapratewidget_clicked()
{
  #ifdef SUPPORT_TEST_CONCEPT_MAP_DIALOGS_86543723642
  QtPvdbTestConceptMapRateWidgetDialog d;
  if (m_show_child_dialogs_modal) { this->ShowChild(&d); } else { d.close(); }
  #endif
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
  if (m_show_child_dialogs_modal) { this->ShowChild(&d); } else { d.close(); }
  qApp->setStyleSheet(d.GetStyleSheet().c_str());
}

void QtPvdbMenuDialog::on_button_test_qtconceptmapdisplaywidget_clicked()
{
  #ifdef SUPPORT_TEST_CONCEPT_MAP_DIALOGS_86543723642
  QtPvdbTestConceptMapDisplayWidgetDialog d;
  if (m_show_child_dialogs_modal) { this->ShowChild(&d); } else { d.close(); }
  #endif
}

void QtPvdbMenuDialog::on_button_print_concept_map_clicked()
{
  on_button_create_test_files_clicked();
  const std::string filename = "1." + pvdb::File::GetFilenameExtension();
  assert(QFile::exists(filename.c_str()));
  const boost::shared_ptr<pvdb::File> file = pvdb::File::Load(filename);
  assert(file);
  QtPvdbPrintConceptMapDialog d(file);
  if (m_show_child_dialogs_modal) { this->ShowChild(&d); } else { d.close(); }
}

void QtPvdbMenuDialog::on_button_print_rating_clicked()
{
  on_button_create_test_files_clicked();
  const std::string filename = "1." + pvdb::File::GetFilenameExtension();
  assert(QFile::exists(filename.c_str()));
  const boost::shared_ptr<pvdb::File> file = pvdb::File::Load(filename);
  assert(file);
  QtPvdbPrintRatingDialog d(file);
  if (m_show_child_dialogs_modal) { this->ShowChild(&d); } else { d.close(); }
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
    boost::shared_ptr<QtPvdbRateConceptTallyDialog> d(
      new QtPvdbRateConceptTallyDialog(concept_map));
    this->ShowChild(d.get());
    break;
  }
}

void QtPvdbMenuDialog::on_button_test_create_sub_concept_map_clicked()
{
  #ifdef SUPPORT_TEST_CONCEPT_MAP_DIALOGS_86543723642
  QtPvdbTestCreateSubConceptMapDialog d;
  if (m_show_child_dialogs_modal) { this->ShowChild(&d); } else { d.close(); }
  #endif
}
