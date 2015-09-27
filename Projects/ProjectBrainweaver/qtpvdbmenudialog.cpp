//---------------------------------------------------------------------------
/*
Brainweaver, tool to create and assess concept maps
Copyright (C) 2012-2015 The Brainweaver Team

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ProjectBrainweaver.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtpvdbmenudialog.h"

#include <boost/lexical_cast.hpp>

#include <QFile>
#include <QFileDialog>
#include <QKeyEvent>
#include <QLayout>
#include <QVBoxLayout>

#include "conceptmapconceptfactory.h"
#include "conceptmapconcept.h"
#include "conceptmapfactory.h"
#include "fileio.h"
#include "conceptmap.h"
#include "counter.h"
#include "qtconceptmaprateconcepttallydialognewname.h"
#include "conceptmapexamples.h"
#include "qtpvdbfiledialog.h"
#include "testtimer.h"
#include "qtpvdbtestcreatesubconceptmapdialog.h"
#include "pvdbfilefactory.h"
#include "container.h"
#include "plane.h"
#include "ribi_regex.h"
#include "pvdbfile.h"
#include "qtpvdbaboutdialog.h"
#include "qtpvdbassessormenudialog.h"
#include "qtpvdbclusterdialog.h"
#include "qtpvdbclusterwidget.h"
#include "conceptmapnode.h"
#include "conceptmapconcept.h"
#include "conceptmapexample.h"
#include "qttestconceptmapmenudialog.h"
#include "conceptmapexamples.h"
#include "qtconceptmapconcepteditdialog.h"
#include "qtpvdbconceptmapdialog.h"
#include "qtpvdbcreateassessmentcompletedialog.h"
#include "qttesteditconceptmapdialog.h"
#include "qtpvdboverviewdialog.h"
#include "qtpvdbprintconceptmapdialog.h"
#include "qtpvdbprintratingdialog.h"
#include "qtconceptmaprateconceptdialognewname.h"
#include "qtpvdbrateconceptmapdialog.h"
#include "qtconceptmaprateexamplesdialognewname.h"
#include "qtpvdbratingdialog.h"
#include "qtpvdbstudentmenudialog.h"
#include "qtpvdbviewfilesdialog.h"
//#include "qtconceptmapviewtestsdialog.h"
#include "qtstylesheetsettermaindialog.h"
#include "qttestqtarrowitemsmenudialog.h"
#include "qttestqtroundededitrectitemmenudialog.h"
#include "qttestqtroundedrectitemmenudialog.h"
#include "trace.h"
#include "ui_qtpvdbmenudialog.h"
#pragma GCC diagnostic pop

ribi::pvdb::QtPvdbMenuDialog::QtPvdbMenuDialog(QWidget* parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtPvdbMenuDialog),
    m_file{},
    m_show_child_dialogs_modal(true)
{
  ui->setupUi(this);
  #ifndef NDEBUG
  Test();
  #endif
}

ribi::pvdb::QtPvdbMenuDialog::~QtPvdbMenuDialog() noexcept
{
  delete ui;
}

void ribi::pvdb::QtPvdbMenuDialog::keyPressEvent(QKeyEvent* e) noexcept
{
  assert(e);
  if (e->key()  == Qt::Key_Escape) { close(); return; }
}

void ribi::pvdb::QtPvdbMenuDialog::on_button_assessor_clicked() noexcept
{
  QtPvdbAssessorMenuDialog d;
  if (m_show_child_dialogs_modal) { this->ShowChild(&d); } else { d.close(); } //For testing
}

void ribi::pvdb::QtPvdbMenuDialog::on_button_rate_concept_clicked() noexcept
{
  //Obtain an empty file
  const boost::shared_ptr<pvdb::File> file = pvdb::FileFactory().Create();
  //Use HeteromorphousTestConceptMap[17] to check for subconcept maps with many examples
  //Use HeteromorphousTestConceptMap[18] to check for subconcept maps with large texts
  //Use HeteromorphousTestConceptMap[19] to check for connection to focus with ...
  {
    const boost::shared_ptr<cmap::ConceptMap> concept_map
      = ribi::cmap::ConceptMapFactory().GetHeteromorphousTestConceptMaps().at(19);
    assert(concept_map);
    assert(!file->GetConceptMap() && "Can only set a concept map once");
    file->SetConceptMap(concept_map);
  }
  //Obtain a random sub-concept-map
  const std::vector<boost::shared_ptr<ribi::cmap::ConceptMap> > concept_maps = file->GetConceptMap()->CreateSubs();
  //Display this random concept map
  const int index = std::rand() % concept_maps.size();
  const boost::shared_ptr<ribi::cmap::ConceptMap> concept_map = concept_maps[ index ];
  assert( (!concept_map || concept_map->IsValid())
    && "Expect no or a valid concept map");
  //Create and show the dialog
  boost::shared_ptr<cmap::QtRateConceptDialogNewName> d(
    new cmap::QtRateConceptDialogNewName(concept_map));
  if (m_show_child_dialogs_modal) { this->ShowChild(d.get()); } else { d->close(); } //For testing
}

void ribi::pvdb::QtPvdbMenuDialog::on_button_rate_concept_map_clicked() noexcept
{
  const boost::shared_ptr<pvdb::File> file = pvdb::FileFactory().Create();
  //Use HeteromorphousTestConceptMap[17] to check for subconcept maps with many examples
  //Use HeteromorphousTestConceptMap[18] to check for subconcept maps with large texts
  //Use HeteromorphousTestConceptMap[19] to check for connection to focus with ...
  const boost::shared_ptr<ribi::cmap::ConceptMap> concept_map
    = ribi::cmap::ConceptMapFactory().GetHeteromorphousTestConceptMaps().at(19);
  file->SetConceptMap(concept_map);
  QtPvdbRateConceptMapDialog d(file);
  if (m_show_child_dialogs_modal) { this->ShowChild(&d); } else { d.close(); }
}

void ribi::pvdb::QtPvdbMenuDialog::on_button_rate_examples_clicked() noexcept
{
  using namespace cmap;
  const int index = 2;
  assert(index < static_cast<int>(ConceptFactory().GetTests().size()));
  const boost::shared_ptr<Concept> concept = ConceptFactory().GetTests().at(index);
  boost::shared_ptr<QtRateExamplesDialogNewName> d(new QtRateExamplesDialogNewName(concept));
  if (m_show_child_dialogs_modal) { this->ShowChild(d.get()); } else { d->close(); } //For testing
}

void ribi::pvdb::QtPvdbMenuDialog::on_button_rating_clicked() noexcept
{
  const int test = 4;
  assert(test < static_cast<int>(pvdb::FileFactory().GetTests().size()));
  const boost::shared_ptr<pvdb::File> file = pvdb::FileFactory().GetTests().at(test);
  assert(file);
  QtPvdbRatingDialog d(file);
  if (m_show_child_dialogs_modal) { this->ShowChild(&d); } else { d.close(); }
}

void ribi::pvdb::QtPvdbMenuDialog::on_button_student_clicked() noexcept
{
  if (!m_show_child_dialogs_modal) return;

  const auto d = pvdb::QtFileDialog::GetOpenFileDialog();
  d->setWindowTitle("Kies een assessment bestand");
  const int status = d->exec();
  if (status == QDialog::Rejected) return;
  const auto v = d->selectedFiles();
  if (!v.isEmpty())
  {
    assert(v.size() == 1);
    const std::string filename = v[0].toStdString();
    try
    {
      const boost::shared_ptr<pvdb::File> file(pvdb::File::Load(filename));
      assert(file);
      QtPvdbStudentMenuDialog d(file);
      if (m_show_child_dialogs_modal) { this->ShowChild(&d); } else { d.close(); } //For testing
    }
    catch (...)
    {
      //Gotta catch 'm all
    }
  }

}

void ribi::pvdb::QtPvdbMenuDialog::on_button_test_cluster_clicked() noexcept
{
  const boost::shared_ptr<pvdb::File> file = pvdb::FileFactory().Create();
  assert(!file->GetCluster());
  assert(!file->GetConceptMap());
  {
    const std::string question = "qtvdbmenudialog.cpp 79?";
    boost::shared_ptr<ribi::cmap::ConceptMap> concept_map(File::CreateConceptMap(question));
    assert(concept_map);
    assert(!file->GetConceptMap() && "Can only set concept map once");
    file->SetQuestion(question);
    file->SetConceptMap(concept_map);

    assert(!file->GetCluster());
    assert( file->GetConceptMap());

    assert(file->GetQuestion() == question);
  }
  QtPvdbClusterDialog d(file);

  assert(!file->GetCluster());
  assert( file->GetConceptMap());
  if (m_show_child_dialogs_modal) { this->ShowChild(&d); } else { d.close(); }
}

void ribi::pvdb::QtPvdbMenuDialog::on_button_overview_clicked() noexcept
{
  const QString old_title = this->windowTitle();
  this->setWindowTitle("Loading, please wait...");
  QtPvdbOverviewDialog d;
  if (m_show_child_dialogs_modal) { this->ShowChild(&d); } else { d.close(); }
}

void ribi::pvdb::QtPvdbMenuDialog::on_button_about_clicked() noexcept
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

void ribi::pvdb::QtPvdbMenuDialog::on_button_view_files_clicked() noexcept
{
  QtPvdbViewFilesDialog d;
  if (m_show_child_dialogs_modal) { this->ShowChild(&d); } else { d.close(); }
}

#ifndef NDEBUG
void ribi::pvdb::QtPvdbMenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  {
    Counter();
    Container();
    fileio::FileIo();
    const boost::shared_ptr<Plane> p{
      new Plane(
        Plane::Coordinat3D(1.0,0.0,0.0),
        Plane::Coordinat3D(0.0,1.0,0.0),
        Plane::Coordinat3D(0.0,0.0,1.0)
      )
    };
    ::ribi::Regex();
    QtPvdbOverviewDialog d; //Creates all screens, does all tests
    QtStyleSheetSetterMainDialog();
  }
  //Press all buttons
  {
    QtPvdbMenuDialog d;
    d.m_show_child_dialogs_modal = false;
    Ui::QtPvdbMenuDialog * const ui = d.ui;
    const std::vector<QPushButton*> buttons
      =
      {
        //Duplication of tests, the ones I am most interested in now

        //Normal alphabetical order of tests
        ui->button_about,
        ui->button_assessor,
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
        ui->button_test_conceptmap,
        ui->button_test_create_sub_concept_map,
        ui->button_test_conceptmaps,
        ui->button_test_qtroundededitrectitem,
        ui->button_view_files
      };
    const std::size_t n_buttons = buttons.size();
    for (std::size_t i = 0; i!=n_buttons; ++i)
    {
      assert(i < buttons.size());
      QPushButton * const button = buttons[i];
      assert(button);
      if (button->isEnabled()) button->click();
    }

  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
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
    #ifdef NOT_NOW_20141142
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
        && "If the file has no cluster, the cluster dialog creates it,"
        && "if no concept map was present");
      QtPvdbClusterDialog d(file);
      if (file->GetConceptMap() && !file->GetConceptMap())
      {
        assert(d.GetWidget());
        assert(!d.GetWidget()->isEnabled()
          && "Cluster widget should be disabled for a file with a filled in ConceptMap");
      }
    }
    #endif // NOT_NOW_20141142
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
        && "If the file has no cluster, the cluster dialog creates it,"
           "if and only if there is no concept map");
      QtPvdbClusterDialog d(file);
      if (!file->GetConceptMap())
      {
        assert(file->GetCluster() && "the cluster dialog used an existing or created a cluster");
      }
      assert(file->GetQuestion() == question);
      assert(file->GetStudentName() == name);
      assert(!file->GetConceptMap());
      if (file->GetCluster())
      {
        assert(d.GetWidget());
        d.DoRandomStuff();
      }
      assert(!file->GetConceptMap());
      d.Save(filename);
    }
    //5) Start with concept map
    //6) Save
    #ifdef NOT_NOW_20141142
    {
      boost::shared_ptr<pvdb::File> file(pvdb::File::Load(filename));
      assert(file->GetQuestion() == question);
      assert(file->GetStudentName() == name);
      assert(!file->GetConceptMap());
      QtPvdbConceptMapDialog d(file);
      assert(file->GetQuestion() == question);
      assert(file->GetStudentName() == name);
      assert(file->GetConceptMap());
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
        && "If the file has no cluster, the cluster dialog creates it,"
           "if and only if there is no concept map");
      QtPvdbClusterDialog d(file);
      if (!file->GetConceptMap())
      {
        assert(file->GetCluster() && "the cluster dialog used an existing or created a cluster");
        assert(d.GetWidget());
        assert(!d.GetWidget()->isEnabled()
          && "Cluster widget should be disabled for a file with a filled in ConceptMap");
      }
    }
    #endif // NOT_NOW_20141142
    std::remove(pvdb::File::GetTestFileName().c_str());
  }

}
#endif

void ribi::pvdb::QtPvdbMenuDialog::on_button_test_qtroundededitrectitem_clicked() noexcept
{
  QtTestQtRoundedEditRectItemMenuDialog d;
  if (m_show_child_dialogs_modal) { this->ShowChild(&d); } else { d.close(); }
}

void ribi::pvdb::QtPvdbMenuDialog::on_button_test_arrowitems_clicked() noexcept
{
  QtTestQtArrowItemsMenuDialog d;
  if (m_show_child_dialogs_modal) { this->ShowChild(&d); } else { d.close(); }
}

void ribi::pvdb::QtPvdbMenuDialog::on_button_create_test_files_clicked() noexcept
{
  //Obtain the human student concept maps
  {
    for (int i=0; ; ++i)  //Break when no file is found
    {
      //Base 1 counting
      const std::string filename = boost::lexical_cast<std::string>(i+1) + "." + pvdb::File::GetFilenameExtension();
      //Copy the file from Qt resources to local file
      {
        const std::string qtfilename = ":/files/" + filename;
        QFile qtfile(qtfilename.c_str());
        qtfile.copy(filename.c_str());
        qtfile.close();
      }
      if (!fileio::FileIo().IsRegularFile(filename))
      {
        break;
      }

      assert(fileio::FileIo().IsRegularFile(filename));
    }
  }
  //Obtain the artificial concept maps
  const std::vector<boost::shared_ptr<pvdb::File> > v = pvdb::FileFactory().GetTests();
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

void ribi::pvdb::QtPvdbMenuDialog::on_button_modify_stylesheet_clicked() noexcept
{
  QtStyleSheetSetterMainDialog d(qApp->styleSheet().toStdString());
  if (m_show_child_dialogs_modal) { this->ShowChild(&d); } else { d.close(); }
  qApp->setStyleSheet(d.GetStyleSheet().c_str());
}

void ribi::pvdb::QtPvdbMenuDialog::on_button_print_concept_map_clicked() noexcept
{
  on_button_create_test_files_clicked();
  const std::string filename = "1." + pvdb::File::GetFilenameExtension();
  assert(fileio::FileIo().IsRegularFile(filename));
  const boost::shared_ptr<pvdb::File> file = pvdb::File::Load(filename);
  assert(file);
  QtPvdbPrintConceptMapDialog d(file);
  if (m_show_child_dialogs_modal) { this->ShowChild(&d); } else { d.close(); }
}

void ribi::pvdb::QtPvdbMenuDialog::on_button_print_rating_clicked() noexcept
{
  on_button_create_test_files_clicked();
  const std::string filename = "1." + pvdb::File::GetFilenameExtension();
  assert(fileio::FileIo().IsRegularFile(filename));
  const boost::shared_ptr<pvdb::File> file = pvdb::File::Load(filename);
  assert(file);
  QtPvdbPrintRatingDialog d(file);
  if (m_show_child_dialogs_modal) { this->ShowChild(&d); } else { d.close(); }
}

void ribi::pvdb::QtPvdbMenuDialog::on_button_rate_concept_auto_clicked() noexcept
{

  const boost::shared_ptr<ribi::cmap::ConceptMap> concept_map
    = cmap::QtRateConceptTallyDialogNewName::CreateTestConceptMap();
  boost::shared_ptr<cmap::QtRateConceptTallyDialogNewName> d(
    new cmap::QtRateConceptTallyDialogNewName(concept_map));
  if (m_show_child_dialogs_modal) { this->ShowChild(d.get()); } else { d->close(); }
}

void ribi::pvdb::QtPvdbMenuDialog::on_button_test_create_sub_concept_map_clicked() noexcept
{
  QtPvdbTestCreateSubConceptMapDialog d;
  if (m_show_child_dialogs_modal) { this->ShowChild(&d); } else { d.close(); }
}

void ribi::pvdb::QtPvdbMenuDialog::on_button_test_conceptmaps_clicked()
{
  cmap::QtTestMenuDialog d;
  if (m_show_child_dialogs_modal) { this->ShowChild(&d); } else { d.close(); }
}

void ribi::pvdb::QtPvdbMenuDialog::on_button_test_conceptmap_clicked()
{
  const int test = 4;
  assert(test < static_cast<int>(pvdb::FileFactory().GetNumberOfTests()));
  const boost::shared_ptr<pvdb::File> file = pvdb::FileFactory().GetTests().at(test);
  assert(file);
  QtPvdbConceptMapDialog d(file);
  if (m_show_child_dialogs_modal) { this->ShowChild(&d); } else { d.close(); }
}

void ribi::pvdb::QtPvdbMenuDialog::on_button_test_qtroundedrectitem_clicked()
{
  QtTestQtRoundedRectItemMenuDialog d;
  if (m_show_child_dialogs_modal) { this->ShowChild(&d); } else { d.close(); }
}
