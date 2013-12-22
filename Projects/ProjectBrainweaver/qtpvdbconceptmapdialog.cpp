#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtpvdbconceptmapdialog.h"

#include <cassert>
#include <boost/lambda/lambda.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <QDesktopWidget>
#include <QFileDialog>
#include <QKeyEvent>
#include <QLayout>
#include <QLabel>
#include <QMessageBox>

#include "conceptmapcenternode.h"
#include "pvdbcluster.h"
#include "conceptmapconcept.h"
#include "conceptmapfactory.h"
#include "conceptmap.h"
#include "conceptmapedge.h"
#include "pvdbfile.h"
#include "conceptmapnodefactory.h"
#include "conceptmapnode.h"
#include "qtconceptmapconcepteditdialog.h"
#include "qtconceptmapeditwidget.h"
#include "qtconceptmapitem.h"
#include "qtconceptmap.h"
#include "qtconceptmapedge.h"
#include "qtpvdbfiledialog.h"
#include "qtconceptmapnode.h"
#include "qtpvdbprintconceptmapdialog.h"
#include "qtscopeddisable.h"
#include "trace.h"
#include "ui_qtpvdbconceptmapdialog.h"
#pragma GCC diagnostic pop

///Collect all QGraphicsItems with class T in an unorderly way
template <class T>
std::vector<T*> Collect(const QGraphicsScene* const scene)
{
  std::vector<T*> v;
  const QList<QGraphicsItem *> items = scene->items();
  std::transform(items.begin(),items.end(),std::back_inserter(v),
    [](QGraphicsItem* const item)
    {
      assert(item);
      return dynamic_cast<T*>(item);
    }
  );
  v.erase(std::remove(v.begin(),v.end(),nullptr),v.end());
  assert(std::count(v.begin(),v.end(),nullptr)==0);
  return v;
}

ribi::pvdb::QtPvdbConceptMapDialog::QtPvdbConceptMapDialog(
  const boost::shared_ptr<pvdb::File> file,
  QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtPvdbConceptMapDialog),
    m_back_to_menu(false),
    m_file(file),
    m_widget(CreateWidget(file))
{
  ui->setupUi(this);
  #ifndef NDEBUG
  Test();
  assert(m_file);
  assert(m_file->GetConceptMap());
  assert(!m_file->GetConceptMap()->GetNodes().empty());
  assert(boost::dynamic_pointer_cast<cmap::CenterNode>(m_file->GetConceptMap()->GetNodes()[0])
    && "The first node in a file's ConceptMap must be a CenterNode");

  assert(file == m_file);
  assert(m_widget);
  assert(m_widget->GetConceptMap() == m_file->GetConceptMap());
  assert(this->layout());
  #endif

  
  this->layout()->addWidget(m_widget);

  assert(!Collect<cmap::QtNode>(m_widget->scene()).empty());

  //Center the dialog
  {
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->setGeometry(screen.adjusted(64,64,-64,-64));
    this->move( screen.center() - this->rect().center() );
  }

  m_widget->m_signal_conceptmapitem_requests_edit.connect(
    boost::bind(
      &ribi::pvdb::QtPvdbConceptMapDialog::OnConceptMapItemRequestsEdit,
      this,boost::lambda::_1));
}

ribi::pvdb::QtPvdbConceptMapDialog::~QtPvdbConceptMapDialog() noexcept
{
  delete ui;
}

const boost::shared_ptr<ribi::cmap::ConceptMap> ribi::pvdb::QtPvdbConceptMapDialog::CreateFromCluster(
  const std::string& question,
  const boost::shared_ptr<pvdb::Cluster>& cluster)
{
  std::vector<boost::shared_ptr<ribi::cmap::Node> > nodes {
    cmap::ConceptMap::CreateNodes(question, {} )
  };
  std::vector<boost::shared_ptr<ribi::cmap::Edge> > edges;

  const std::vector<boost::shared_ptr<ribi::cmap::Concept> >& v = cluster->Get();
  const int n = boost::numeric_cast<int>(v.size());
  for (int i=0; i!=n; ++i)
  {
    const int x = 0;
    const int y = 0;
    const boost::shared_ptr<ribi::cmap::Node> node = cmap::NodeFactory::Create(v[i],x,y);
    assert(node);
    nodes.push_back(node);
  }
  assert(v.size() + 1 == nodes.size()
    && "Assume the ConceptMap has as much nodes as the cluster has concepts + one focal question");
  const boost::shared_ptr<ribi::cmap::ConceptMap> p {
    cmap::ConceptMapFactory::Create(nodes,edges)
  };
  assert(p);
  assert(p->IsValid());
  return p;
}

ribi::cmap::QtConceptMapEditWidget * ribi::pvdb::QtPvdbConceptMapDialog::CreateWidget(const boost::shared_ptr<pvdb::File> file)
{
  assert(file);

  const bool had_cluster = file->GetCluster().get();
  const bool had_concept_map = file->GetConceptMap().get();

  if (!had_cluster && !had_concept_map)
  {
    TRACE("User starts building a concept map from scratch");
    boost::shared_ptr<ribi::cmap::ConceptMap> concept_map
      = ribi::cmap::ConceptMapFactory::Create(file->GetQuestion());
    file->SetConceptMap(concept_map);
  }
  else if ( had_cluster && !had_concept_map)
  {
    TRACE("User supplied a filled-in cluster");
    assert(file->GetCluster());

    boost::shared_ptr<ribi::cmap::ConceptMap> concept_map {
      QtPvdbConceptMapDialog::CreateFromCluster(
      //= ribi::cmap::ConceptMapFactory::Create(
        file->GetQuestion(),
        file->GetCluster()
      )
    };

    file->SetConceptMap(concept_map);

    assert((file->GetCluster()->Get().size() + 1)
      == (concept_map->GetNodes().size())
      && "As much cluster items as nodes + focus question");
  }

  if (!had_cluster && !had_concept_map)
  {
    assert(!file->GetCluster());
    assert( file->GetConceptMap()); //Created
  }
  if ( had_cluster && !had_concept_map)
  {
    assert( file->GetCluster());
    assert( file->GetConceptMap()); //Created from concept map
  }
  if (!had_cluster &&  had_concept_map)
  {
    assert(!file->GetCluster());
    assert( file->GetConceptMap());
  }
  if ( had_cluster &&  had_concept_map)
  {
    assert( file->GetCluster());
    assert( file->GetConceptMap());
  }

  cmap::QtConceptMapEditWidget * const widget = new cmap::QtConceptMapEditWidget(file->GetConceptMap());
  assert(widget);
  return widget;
}

#ifndef NDEBUG
void ribi::pvdb::QtPvdbConceptMapDialog::DoRandomStuff()
{
  //Do random stuff
  assert(m_file);
  assert(m_file->GetConceptMap());
  assert(!m_file->GetConceptMap()->GetNodes().empty());
  assert(boost::dynamic_pointer_cast<cmap::CenterNode>(m_file->GetConceptMap()->GetNodes()[0])
    && "The first node in a file's ConceptMap must be a CenterNode");

  const int n_edges_before = boost::numeric_cast<int>(m_file->GetConceptMap()->GetEdges().size());
  const int n_nodes_before = boost::numeric_cast<int>(m_file->GetConceptMap()->GetNodes().size());
  this->GetWidget()->DoRandomStuff();
  const int n_edges_after = boost::numeric_cast<int>(m_file->GetConceptMap()->GetEdges().size());
  const int n_nodes_after = boost::numeric_cast<int>(m_file->GetConceptMap()->GetNodes().size());
  assert(n_edges_after > n_edges_before);
  assert(n_nodes_after > n_nodes_before);
}
#endif

const ribi::cmap::QtConceptMap * ribi::pvdb::QtPvdbConceptMapDialog::GetWidget() const
{
  assert(m_widget);
  return m_widget;
}

ribi::cmap::QtConceptMap * ribi::pvdb::QtPvdbConceptMapDialog::GetWidget()
{
  //Calls the const version of this member function
  //To avoid duplication in const and non-const member functions [1]
  //[1] Scott Meyers. Effective C++ (3rd edition). ISBN: 0-321-33487-6.
  //    Item 3, paragraph 'Avoid duplication in const and non-const member functions'
  return const_cast<cmap::QtConceptMap*>(
    const_cast<const QtPvdbConceptMapDialog*>(this)->GetWidget()); //?Why Dialog

}

void ribi::pvdb::QtPvdbConceptMapDialog::keyPressEvent(QKeyEvent* e)
{
  if (e->key()  == Qt::Key_Escape) { close(); return; }
  if ((e->modifiers() & Qt::ControlModifier) && e->key() == Qt::Key_S) { on_button_save_clicked(); return; }
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
  if ( (e->modifiers() & Qt::ControlModifier)
    && (e->modifiers() & Qt::ShiftModifier)
    && e->key() == Qt::Key_T)
  {
    //Translate
    this->setWindowTitle("Construction screen");
    ui->button_print->setText("Save as PDF-format");
    ui->button_save->setText("Save concept map");
    return;
  }

  QDialog::keyPressEvent(e);
}

void ribi::pvdb::QtPvdbConceptMapDialog::on_button_print_clicked()
{
  Save();
  QtPvdbPrintConceptMapDialog d(this->m_file);
  this->ShowChild(&d);
}

void ribi::pvdb::QtPvdbConceptMapDialog::OnConceptMapItemRequestsEdit(cmap::QtConceptMapItem* const item)
{
  assert(item);
  {
    assert(this);
    assert(item);
    assert(item->GetConcept());
    cmap::QtConceptMapConceptEditDialog d(item->GetConcept());
    this->ShowChild(&d);
  }
  //item->GetConcept()->m_signal_examples_changed(item->GetConcept().get()); //NEW 2013-01-08 21:40
  item->m_signal_item_has_updated(item);
  item->update();
}

void ribi::pvdb::QtPvdbConceptMapDialog::on_button_save_clicked()
{
  //Temporarily disable to widget, otherwise saving cannot succeed
  const QtScopedDisable<cmap::QtConceptMap> scoped_disable1(GetWidget());
  const QtScopedDisable<QtPvdbConceptMapDialog> scoped_disable2(this);
  this->hide();

  const auto d = pvdb::QtFileDialog::GetSaveFileDialog(pvdb::QtFileDialog::FileType::cmp);
  d->setWindowTitle("Sla de concept map op");
  const int status = d->exec();
  if (status == QDialog::Rejected)
  {
    this->show();
    return;
  }
  assert(d->selectedFiles().size() == 1);
  const std::string filename_raw = d->selectedFiles()[0].toStdString();
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

void ribi::pvdb::QtPvdbConceptMapDialog::Save() const
{
  //const boost::shared_ptr<ribi::cmap::ConceptMap> concept_map = GetWidget()->GetConceptMap();
  //assert(concept_map);
  assert(m_file->GetConceptMap() == GetWidget()->GetConceptMap());
  //m_file->SetConceptMap(concept_map);
}

void ribi::pvdb::QtPvdbConceptMapDialog::Save(const std::string& filename) const
{
  assert(filename.size() > 3
    && filename.substr( filename.size() - 3, 3 ) == pvdb::File::GetFilenameExtension()
    && "File must have correct file extension name");
  Save();
  m_file->Save(filename);
}

#ifndef NDEBUG
void ribi::pvdb::QtPvdbConceptMapDialog::Shuffle()
{
  this->GetWidget()->Shuffle();
}
#endif

