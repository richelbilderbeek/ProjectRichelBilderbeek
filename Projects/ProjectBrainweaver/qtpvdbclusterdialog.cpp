#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtpvdbclusterdialog.h"

#include <fstream>

#ifdef COMPILER_SUPPORTS_THREADS_20130507
#include <thread>
#endif

#include <boost/algorithm/string/trim_all.hpp>
#include <QFileDialog>
#include <QKeyEvent>
#include <QMessageBox>

#include "pvdbcluster.h"
#include "pvdbconcept.h"
#include "pvdbconceptfactory.h"
#include "pvdbclusterfactory.h"
#include "pvdbconceptmap.h"
#include "pvdbcompetency.h"
#include "pvdbedge.h"
#include "pvdbedgefactory.h"
#include "pvdbnodefactory.h"
#include "pvdbconceptfactory.h"
#include "pvdbconceptmapfactory.h"
#include "pvdbexamplefactory.h"
#include "pvdbfile.h"
#include "pvdbfilefactory.h"
#include "pvdbnode.h"
#include "qtpvdbconceptmapdialog.h"
#include "trace.h"
#include "ui_qtpvdbclusterdialog.h"

QtPvdbClusterDialog::QtPvdbClusterDialog(const boost::shared_ptr<pvdb::File> file, QWidget* parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtPvdbClusterDialog),
    m_back_to_menu(false),
    m_file(file)
{
  ui->setupUi(this);
  #ifndef NDEBUG
  Test();
  assert(file);
  assert(m_file);
  assert(IsEqual(*file,*m_file));
  #endif

  ui->tree->ReadFromCluster(m_file->GetCluster());
  ui->label_question->setText(m_file->GetConceptMap()->GetQuestion().c_str());

  assert(!m_file->GetConceptMap()->GetNodes().empty());
  if (m_file->GetConceptMap()->GetNodes().size() > 1) //1, as node[0] is focal question
  {
    ui->tree->setEnabled(false);
    ui->button_add->setEnabled(false);
    ui->edit->setEnabled(false);
    assert(!this->GetWidget()->isEnabled());
  }

  #ifndef NDEBUG
  {
    //Check that writing to pvdb::File works
    const boost::shared_ptr<pvdb::File> file(pvdb::FileFactory::DeepCopy(m_file));
    assert(file);
    const boost::shared_ptr<pvdb::Cluster> cluster = GetWidget()->WriteToCluster();
    file->SetCluster(cluster);
    assert(IsEqual(*file->GetCluster(),*GetWidget()->WriteToCluster()));
  }
  #endif
}


QtPvdbClusterDialog::~QtPvdbClusterDialog()
{
  ///WARNING: assume ui->widget is not available anymore
  //const boost::shared_ptr<pvdb::Cluster> cluster = GetWidget()->WriteToCluster();
  //m_file->SetCluster(cluster);
  delete ui;
}


void QtPvdbClusterDialog::DoRandomStuff()
{
  assert(m_file->GetCluster() == this->GetWidget()->WriteToCluster());
  this->GetWidget()->DoRandomStuff();
  assert(m_file->GetCluster() != this->GetWidget()->WriteToCluster());
  m_file->SetCluster(this->GetWidget()->WriteToCluster());
  assert(m_file->GetCluster() == this->GetWidget()->WriteToCluster());

  assert(!m_file->GetCluster()->Empty());

  #ifndef NDEBUG
  {
    //Check that writing to pvdb::File works
    const boost::shared_ptr<pvdb::File> file(pvdb::FileFactory::DeepCopy(m_file));
    assert(file);
    const boost::shared_ptr<pvdb::Cluster> cluster = GetWidget()->WriteToCluster();
    file->SetCluster(cluster);
    assert(file->GetCluster() == GetWidget()->WriteToCluster());
  }
  #endif
}


const QtPvdbClusterWidget * QtPvdbClusterDialog::GetWidget() const
{
  assert(ui);
  assert(ui->tree);
  return ui->tree;
}

QtPvdbClusterWidget * QtPvdbClusterDialog::GetWidget()
{
  //Calls the const version of operator[]
  //To avoid duplication in const and non-const member functions [1]
  return const_cast<QtPvdbClusterWidget*>(
    const_cast<const QtPvdbClusterDialog*>(this)->GetWidget());
}

void QtPvdbClusterDialog::keyPressEvent(QKeyEvent* e)
{
  if (e->key()  == Qt::Key_Escape)
  {
    close();
    return;
  }
  if ((e->modifiers() & Qt::ControlModifier) && e->key() == Qt::Key_S)
  {
    Save();
    return;
  }
  if ((e->modifiers() & Qt::ControlModifier)
    && !(e->modifiers() & Qt::ShiftModifier)
    && e->key() == Qt::Key_Z)
  {
    QMessageBox box;
    box.setText("TODO: Undo");
    box.exec();
    return;
  }
  if ( (e->modifiers() & Qt::ControlModifier)
    && (e->modifiers() & Qt::ShiftModifier)
    && e->key() == Qt::Key_Z)
  {
    QMessageBox box;
    box.setText("TODO: Redo");
    box.exec();
    return;
  }
  QDialog::keyPressEvent(e);

  #ifndef NDEBUG
  {
    //Check that writing to pvdb::File works
    const boost::shared_ptr<pvdb::File> file(pvdb::FileFactory::DeepCopy(m_file));
    assert(file);
    const boost::shared_ptr<pvdb::Cluster> cluster = GetWidget()->WriteToCluster();
    file->SetCluster(cluster);
    assert(file->GetCluster() == GetWidget()->WriteToCluster());
  }
  #endif
}

void QtPvdbClusterDialog::on_button_add_clicked()
{
  assert(boost::algorithm::trim_all_copy(std::string(" \t x \t ")) == std::string("x"));
  const std::string text = boost::algorithm::trim_all_copy(ui->edit->text().toStdString());
  if (text.empty()) return;
  //QStringList v;
  //v.append(text.c_str());
  //ui->tree->addTopLevelItem(new QTreeWidgetItem(v));
  ui->tree->Add(text);
  ui->edit->clear();
  ui->edit->setFocus();
  #ifndef NDEBUG
  {
    //Check that writing to pvdb::File works
    const boost::shared_ptr<pvdb::File> file(pvdb::FileFactory::DeepCopy(m_file));
    assert(file);
    assert(file != m_file);
    const boost::shared_ptr<pvdb::Cluster> cluster = GetWidget()->WriteToCluster();
    file->SetCluster(cluster);
    assert(IsEqual(*file->GetCluster(),*GetWidget()->WriteToCluster()));
  }
  #endif
}

void QtPvdbClusterDialog::on_button_next_clicked()
{
  assert(m_file);
  if (GetWidget()->isEnabled()) //Save concept map, when user is all
  {

    const boost::shared_ptr<pvdb::Cluster> cluster = GetWidget()->WriteToCluster();
    m_file->SetCluster(cluster);
  }
  //File's cluster and widget's cluster should be the same
  assert(m_file->GetCluster() == GetWidget()->WriteToCluster());


  QtPvdbConceptMapDialog d(m_file);
  this->ShowChild(&d);
  if (d.GoBackToMenu())
  {
    m_back_to_menu = true;
    close();
  }
  //Same test as in constructor
  if (m_file->GetConceptMap()->GetNodes().size() > 1) //1, as node[0] is focal question
  {
    ui->tree->setEnabled(false);
    ui->button_add->setEnabled(false);
    ui->edit->setEnabled(false);
    assert(!this->GetWidget()->isEnabled());
  }
}

void QtPvdbClusterDialog::Test()
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

  typedef std::vector<boost::shared_ptr<pvdb::Edge> > Edges;
  typedef std::vector<boost::shared_ptr<pvdb::Node> > Nodes;

  //Regular tests
  {
    const std::vector<boost::shared_ptr<pvdb::File> > v = pvdb::File::GetTests();
    std::for_each(v.begin(),v.end(),
      [](const boost::shared_ptr<pvdb::File> & file)
      {
        boost::shared_ptr<QtPvdbClusterDialog> d(new QtPvdbClusterDialog(file));
        assert(IsEqual(*file->GetCluster(),*d->GetWidget()->WriteToCluster()));
        d->GetWidget()->Add("Modification!");
        assert(!IsEqual(*file->GetCluster(),*d->GetWidget()->WriteToCluster()));
      }
    );
  }
  {
    const std::vector<boost::shared_ptr<pvdb::File> > v = pvdb::File::GetTests();
    std::for_each(v.begin(),v.end(),
      [](const boost::shared_ptr<pvdb::File> & file)
      {
        boost::shared_ptr<QtPvdbClusterDialog> d(new QtPvdbClusterDialog(file));
        assert(IsEqual(*file->GetCluster(),*d->GetWidget()->WriteToCluster()));
        d->ui->edit->setText("modification");
        d->on_button_add_clicked();
        assert(!IsEqual(*file->GetCluster(),*d->GetWidget()->WriteToCluster()));
      }
    );
  }
  //QtPvdbClusterDialog must be enabled if there is only a center node at the concept map
  {
    const std::string question = "TESTQUESTION";
    const boost::shared_ptr<pvdb::File> file(new pvdb::File);

    const boost::shared_ptr<pvdb::Cluster> cluster = pvdb::ClusterFactory::GetTest( {0,1,2} );

    file->SetCluster(cluster);

    const boost::shared_ptr<pvdb::Node> node_a(
      pvdb::NodeFactory::Create(
        pvdb::ConceptFactory::Create(question),
        0,
        0
      )
    );

    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      pvdb::ConceptMapFactory::Create( { node_a } ));
    assert(concept_map);
    file->SetConceptMap(concept_map);
    assert(file->GetQuestion() == question);
    const QtPvdbClusterDialog d(file);
    assert(d.GetWidget()->isEnabled()
      && "QtClusterWidget is enabled when there is only a question in the ConceptMap");
  }

  //QtPvdbClusterDialog must be disabled if there are more nodes in the concept map
  {
    const std::string question = "TESTQUESTION";
    const boost::shared_ptr<pvdb::File> file(new pvdb::File);
    const boost::shared_ptr<pvdb::Cluster> cluster = pvdb::ClusterFactory::GetTest( { 0,1,2 } );

    file->SetCluster(cluster);

    const boost::shared_ptr<pvdb::Concept> concept_d(pvdb::ConceptFactory::Create("Concept F"));
    const boost::shared_ptr<pvdb::Concept> concept_e(pvdb::ConceptFactory::GetTests().at(3));
    const boost::shared_ptr<pvdb::Concept> concept_f(pvdb::ConceptFactory::GetTests().at(4));
    const boost::shared_ptr<pvdb::Node> node_a(pvdb::NodeFactory::Create(question));
    const boost::shared_ptr<pvdb::Node> node_b(pvdb::NodeFactory::GetTests().at(1));
    const boost::shared_ptr<pvdb::Node> node_c(pvdb::NodeFactory::GetTests().at(2));
    const Nodes nodes = { node_a, node_b, node_c };
    const boost::shared_ptr<pvdb::Edge> edge_a(pvdb::EdgeFactory::Create(concept_d,1.2,3.4,nodes.at(0),false,nodes.at(1),true));
    const boost::shared_ptr<pvdb::Edge> edge_b(pvdb::EdgeFactory::Create(concept_e,2.3,4.5,nodes.at(1),false,nodes.at(2),true));
    const boost::shared_ptr<pvdb::Edge> edge_c(pvdb::EdgeFactory::Create(concept_f,3.4,5.6,nodes.at(2),false,nodes.at(0),true));
    const Edges edges = { edge_a, edge_b, edge_c };

    const boost::shared_ptr<pvdb::ConceptMap> concept_map(
      pvdb::ConceptMapFactory::Create(nodes,edges));
    assert(concept_map);
    file->SetConceptMap(concept_map);

    assert(file->GetQuestion() == question);
    const QtPvdbClusterDialog d(file);
    assert(!d.GetWidget()->isEnabled()
      && "QtClusterWidget is disabled when there is a filled ConceptMap");
  }
  #ifdef COMPILER_SUPPORTS_THREADS_20130507
    }
  );
  t.detach();
  #endif
}

void QtPvdbClusterDialog::on_edit_textChanged(const QString &arg1)
{
  assert(ui->edit->text() == arg1);
  ui->button_add->setEnabled( arg1.size() > 0);

  #ifndef NDEBUG
  {
    //Check that writing to pvdb::File works
    const boost::shared_ptr<pvdb::File> file(pvdb::FileFactory::DeepCopy(m_file));
    assert(file);
    const boost::shared_ptr<pvdb::Cluster> cluster = GetWidget()->WriteToCluster();
    file->SetCluster(cluster);
    assert(IsEqual(*file->GetCluster(),*GetWidget()->WriteToCluster()));
  }
  #endif
}

void QtPvdbClusterDialog::Save()
{
  const std::string filter_str = std::string("*.") + pvdb::File::GetFilenameExtension();
  const std::string filename_raw = QFileDialog::getSaveFileName(0,"Sla de clustering op",
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
    //this->m_back_to_menu = true; //2013-04-19 Request by client
    //close(); //2013-04-19 Request by client
  }
}

void QtPvdbClusterDialog::Save(const std::string& filename)
{
  assert(filename.size() > 3
    && filename.substr( filename.size() - 3, 3 ) == pvdb::File::GetFilenameExtension()
    && "File must have correct file extension name");
  const boost::shared_ptr<pvdb::Cluster> cluster = this->GetWidget()->WriteToCluster();
  assert(cluster);
  m_file->SetCluster(cluster);
  assert(m_file->GetCluster() == GetWidget()->WriteToCluster());
  m_file->Save(filename);
}

void QtPvdbClusterDialog::on_button_save_clicked()
{
  Save();
}
