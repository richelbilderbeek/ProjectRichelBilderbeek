#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtpvdbtestedgeitemdialog.h"


#include <cassert>

#ifdef COMPILER_SUPPORTS_THREADS_20130507
#include <thread>
#endif

#include <boost/lexical_cast.hpp>
#include <QKeyEvent>
#include "pvdbconceptfactory.h"
#include "pvdbconcept.h"
#include "pvdbedgefactory.h"
#include "pvdbedge.h"
#include "pvdbexample.h"
#include "pvdbexamples.h"
#include "pvdbnodefactory.h"
#include "pvdbnode.h"
#include "qtpvdbdisplayconceptitem.h"
#include "qtpvdbdisplayconceptitem.h"
#include "qtpvdbedgeitem.h"
#include "qtpvdbeditconceptitem.h"
#include "qtpvdbnodeitem.h"
#include "qtpvdbrateconceptitem.h"
#include "trace.h"
#include "ui_qtpvdbtestedgeitemdialog.h"

QtPvdbTestEdgeItemDialog::QtPvdbTestEdgeItemDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtPvdbTestEdgeItemDialog),
  m_edge_item(nullptr),
  m_from(CreateFrom()),
  m_to(CreateTo())
{
  ui->setupUi(this);
  #ifndef NDEBUG
  Test();
  #endif
  assert(ui->view->scene());
  assert(m_from);
  assert(m_to);
  {
    const std::size_t index = 0;
    assert(pvdb::EdgeFactory::GetTests(m_from,m_to).size());
    m_edge = pvdb::EdgeFactory::GetTests(m_from,m_to)[index];
  }

  //Edge is used in: m_edge
  //m_edge->GetConcept()->SetName("Edge with one example");

  assert(m_edge);
  #ifndef NDEBUG
  {
    const int edge_use_count = m_edge.use_count();
    assert(edge_use_count == 1);
  }
  #endif

  //Create three nodes that the edges can connect to
  QtPvdbNodeItem * node1 = nullptr;
  {
    //m_from->GetConcept()->SetName("1");
    const boost::shared_ptr<QtPvdbConceptItem> item(new QtPvdbDisplayConceptItem(m_from->GetConcept()));
    node1 = new QtPvdbNodeItem(m_from,item);
    node1->m_signal_request_scene_update.connect(
      boost::bind(&QtPvdbTestEdgeItemDialog::OnRequestSceneUpdate,this));
  }
  QtPvdbNodeItem * node2 = nullptr;
  {
    //m_to->GetConcept()->SetName("2");
    const boost::shared_ptr<QtPvdbConceptItem> item(new QtPvdbEditConceptItem(m_to->GetConcept()));
    node2 = new QtPvdbNodeItem(m_to,item);
    node2->m_signal_request_scene_update.connect(
      boost::bind(&QtPvdbTestEdgeItemDialog::OnRequestSceneUpdate,this));
  }
  assert(node1);
  assert(node2);
  assert(node1->GetNode());
  assert(node2->GetNode());
  assert(node1->GetNode()->GetConcept());
  assert(node2->GetNode()->GetConcept());

  //Create the edge
  {
    boost::shared_ptr<QtPvdbEditConceptItem> concept(new QtPvdbEditConceptItem(m_edge->GetConcept()));
    m_edge_item = new QtPvdbEdgeItem(m_edge,concept,node1,node2);
  }

  //Node is used in: m_edge and QtPvdbNodeConcept::m_edge
  //assert(m_edge.use_count() == 2);
  //Concept is used in: m_edge::m_concept, QtPvdbDisplayConcept::m_edge::m_concept and QtPvdbConcept::m_concept
  assert(m_edge.get() == m_edge_item->GetEdge().get());
  assert(m_edge->GetConcept().get() == m_edge_item->GetEdge()->GetConcept().get());

  #ifndef NDEBUG
  {
    const int edge_use_count = m_edge.use_count();
    assert(edge_use_count == 2);
  }
  #endif

  //Add items to the scene
  ui->view->scene()->addItem(node1);
  ui->view->scene()->addItem(node2);
  ui->view->scene()->addItem(m_edge_item);

  assert(ui->view->scene()->items().size() == 3);
  {
    QList<QGraphicsItem *> v = ui->view->scene()->items();
    assert(
      std::count_if(v.begin(),v.end(),
        [](const QGraphicsItem * const item)
        {
          return dynamic_cast<const QtPvdbEdgeItem*>(item);
        }
      ) == 1);
  }


  //Put nodes (not the edges) into place
  //The nodes must reposition themselves
  node1->setPos(-100.0,-100.0);
  m_edge_item->setPos(0.0,0.0);
  node2->setPos( 100.0, 100.0);

  {
    const std::vector<pvdb::Competency> v = pvdb::GetAllCompetencies();
    const std::size_t sz = boost::numeric_cast<int>(v.size());
    for (std::size_t i=0; i!=sz; ++i)
    {
      assert(i < v.size());
      const pvdb::Competency competency = v[i];
      const std::string s = pvdb::CompetencyToDutchStr(competency);
  TRACE_FUNC();
      const QString qs = s.c_str();
  TRACE_FUNC();
      ui->box_competency->addItem(qs);
  TRACE_FUNC();
    }
  }
  TRACE_FUNC();

  assert(this->GetEdge()->GetConcept()->GetExamples());
  assert(this->GetEdge()->GetConcept()->GetExamples()->Get().size() == 1);

  ui->box_complexity->setCurrentIndex(this->GetEdge()->GetConcept()->GetRatingComplexity() + 1);
  ui->box_concreteness->setCurrentIndex(this->GetEdge()->GetConcept()->GetRatingConcreteness() + 1);
  ui->box_specificity->setCurrentIndex(this->GetEdge()->GetConcept()->GetRatingSpecificity() + 1);

  ui->edit_name->setText(this->GetEdge()->GetConcept()->GetName().c_str());
  ui->edit_example_text->setText(this->GetEdge()->GetConcept()->GetExamples()->Get().at(0)->GetText().c_str());

  ui->box_arrow_head->setCurrentIndex(this->GetEdge()->HasHeadArrow());
  ui->box_arrow_tail->setCurrentIndex(this->GetEdge()->HasTailArrow());
  ui->box_competency->setCurrentIndex(static_cast<int>(this->GetEdge()->GetConcept()->GetExamples()->Get().at(0)->GetCompetency()));

  TRACE_FUNC();
}

QtPvdbTestEdgeItemDialog::~QtPvdbTestEdgeItemDialog()
{
  delete ui;
}

const boost::shared_ptr<pvdb::Node> QtPvdbTestEdgeItemDialog::CreateFrom()
{
  const std::size_t index = 2;
  assert(index < pvdb::NodeFactory::GetTests().size());
  const boost::shared_ptr<pvdb::Node> node = pvdb::NodeFactory::GetTests()[index];
  assert(node);
  return node;
}

const boost::shared_ptr<pvdb::Node> QtPvdbTestEdgeItemDialog::CreateTo()
{
  const std::size_t index = 3;
  assert(index < pvdb::NodeFactory::GetTests().size());
  const boost::shared_ptr<pvdb::Node> node = pvdb::NodeFactory::GetTests()[index];
  assert(node);
  return node;
}

const boost::shared_ptr<pvdb::Edge> QtPvdbTestEdgeItemDialog::GetEdge()
{
  switch(ui->box_edit->currentIndex())
  {
    case 0: return m_edge;
    case 1:
    {
      const auto v = ui->view->scene()->items();
      const auto iter = std::find_if(v.begin(),v.end(),
        [](const QGraphicsItem * const item)
        {
          return dynamic_cast<const QtPvdbEdgeItem*>(item);
        }
      );
      assert(iter!=v.end());
      QtPvdbEdgeItem * const qtedge = dynamic_cast<QtPvdbEdgeItem*>(*iter);
      assert(qtedge);
      return qtedge->GetEdge();
    }
    default:
      assert(!"Should not get here");
  }
  assert(!"Should not get here");
  throw std::logic_error("QtPvdbTestEdgeItemDialog::GetEdge: current index unknown");
}

void QtPvdbTestEdgeItemDialog::keyPressEvent(QKeyEvent *event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void QtPvdbTestEdgeItemDialog::on_box_competency_currentIndexChanged(int index)
{
  const pvdb::Competency c = static_cast<pvdb::Competency>(index);
  this->GetEdge()->GetConcept()->GetExamples()->Get().at(0)->SetCompetency(c);
}

void QtPvdbTestEdgeItemDialog::on_edit_name_textChanged(const QString &arg1)
{
  this->GetEdge()->GetConcept()->SetName(arg1.toStdString());
}

void QtPvdbTestEdgeItemDialog::on_box_complexity_currentIndexChanged(const QString &arg1)
{
  const int rating_complexity = boost::lexical_cast<int>(arg1.toStdString());
  assert(rating_complexity >= -1);
  assert(rating_complexity <=  2);
  this->GetEdge()->GetConcept()->SetRatingComplexity(rating_complexity);
}

void QtPvdbTestEdgeItemDialog::on_box_concreteness_currentIndexChanged(const QString &arg1)
{
  this->GetEdge()->GetConcept()->SetRatingConcreteness(boost::lexical_cast<int>(arg1.toStdString()));
}

void QtPvdbTestEdgeItemDialog::on_box_specificity_currentIndexChanged(const QString &arg1)
{
  this->GetEdge()->GetConcept()->SetRatingSpecificity(boost::lexical_cast<int>(arg1.toStdString()));
}

void QtPvdbTestEdgeItemDialog::on_edit_example_text_textChanged(const QString &arg1)
{
  this->GetEdge()->GetConcept()->GetExamples()->Get().at(0)->SetText(arg1.toStdString());
}

void QtPvdbTestEdgeItemDialog::on_box_arrow_head_currentIndexChanged(int index)
{
  this->GetEdge()->SetHeadArrow(index);
}

void QtPvdbTestEdgeItemDialog::on_box_arrow_tail_currentIndexChanged(int index)
{
  this->GetEdge()->SetTailArrow(index);
}

void QtPvdbTestEdgeItemDialog::OnRequestSceneUpdate()
{
  ui->view->scene()->update();
}

void QtPvdbTestEdgeItemDialog::Test()
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
  TRACE("QtPvdbTestEdgeItemDialog::Test started");
  QtPvdbTestEdgeItemDialog d;
  assert(d.m_edge);
  assert(d.m_edge->GetConcept());
  assert(d.m_edge_item);
  assert(d.m_edge_item->GetEdge());

  assert(d.m_edge.get() == d.m_edge_item->GetEdge().get());
  assert(d.m_edge->GetConcept().get() == d.m_edge_item->GetEdge()->GetConcept().get());

  //Test resizing due to longer text being set
  {
    TRACE("TODO");
    /*
    const std::string s = d.m_edge->GetConcept()->GetName();
    const double w = d.m_edge_item->GetConceptItem()->boundingRect().width();
    d.m_edge->GetConcept()->SetName(s + "*");
    assert(d.m_edge_item->GetConceptItem()->boundingRect().width() > w);
    */
  }
  //Test resizing due to shorter text being set
  {
    TRACE("TODO");
    /*
    d.m_edge->GetConcept()->SetName("1234567890");
    const double w = d.m_edge_item->GetConceptItem()->boundingRect().width();
    d.m_edge->GetConcept()->SetName("123456789");
    assert(d.m_edge_item->GetConceptItem()->boundingRect().width() < w);
    */
  }
  TRACE("QtPvdbTestEdgeItemDialog::Test finished successfully");
  #ifdef COMPILER_SUPPORTS_THREADS_20130507
    }
  );
  t.detach();
  #endif
}
