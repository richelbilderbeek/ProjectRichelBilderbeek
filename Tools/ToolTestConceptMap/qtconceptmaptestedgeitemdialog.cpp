#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtconceptmaptestedgeitemdialog.h"


#include <cassert>

#ifdef COMPILER_SUPPORTS_THREADS_20130507
#include <thread>
#endif

#include <boost/lexical_cast.hpp>
#include <QKeyEvent>
#include "conceptmapconceptfactory.h"
#include "conceptmapconcept.h"
#include "conceptmapedgefactory.h"
#include "conceptmapedge.h"
#include "conceptmapexample.h"
#include "conceptmapexamples.h"
#include "conceptmapnodefactory.h"
#include "conceptmapnode.h"
#include "qtconceptmapdisplaystrategy.h"
#include "qtconceptmapdisplaystrategy.h"
#include "qtconceptmapedge.h"
#include "qtconceptmapeditstrategy.h"
#include "qtconceptmapnode.h"
#include "qtconceptmapratestrategy.h"
#include "trace.h"
#include "ui_qtconceptmaptestedgeitemdialog.h"
#pragma GCC diagnostic pop

ribi::cmap::QtConceptMapTestEdgeItemDialog::QtConceptMapTestEdgeItemDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtConceptMapTestEdgeItemDialog),
  m_edge{},
  m_edge_item{},
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
    const std::size_t index = 2; //Must have examples
    assert(index < cmap::EdgeFactory().GetTests(m_from,m_to).size());
    m_edge = cmap::EdgeFactory().GetTests(m_from,m_to)[index];
    assert(m_edge->GetConcept());
    assert(m_edge->GetConcept()->GetExamples());
    assert(!m_edge->GetConcept()->GetExamples()->Get().empty()
      && "Otherwise 'ui->box_competency->addItem(qs)' will fail, due to on_box_competency_currentIndexChanged");
  }

  assert(m_edge);
  #ifndef NDEBUG
  {
    const int edge_use_count = m_edge.use_count();
    assert(edge_use_count == 1);
  }
  #endif

  //Create three nodes that the edges can connect to
  cmap::QtNode * node1 = nullptr;
  {
    //m_from->GetConcept()->SetName("1");
    const boost::shared_ptr<QtDisplayStrategy> item(new QtDisplayStrategy(m_from->GetConcept()));
    node1 = new cmap::QtNode(m_from,item);
    node1->m_signal_request_scene_update.connect(
      boost::bind(&ribi::cmap::QtConceptMapTestEdgeItemDialog::OnRequestSceneUpdate,this));
  }
  cmap::QtNode * node2 = nullptr;
  {
    //m_to->GetConcept()->SetName("2");
    const boost::shared_ptr<QtEditStrategy> item(new QtEditStrategy(m_to->GetConcept()));
    node2 = new cmap::QtNode(m_to,item);
    node2->m_signal_request_scene_update.connect(
      boost::bind(&ribi::cmap::QtConceptMapTestEdgeItemDialog::OnRequestSceneUpdate,this));
  }
  assert(node1);
  assert(node2);
  assert(node1->GetNode());
  assert(node2->GetNode());
  assert(node1->GetNode()->GetConcept());
  assert(node2->GetNode()->GetConcept());

  //Create the edge
  {
    assert(m_edge);
    boost::shared_ptr<QtEditStrategy> concept(new QtEditStrategy(m_edge->GetConcept()));
    m_edge_item = new QtEdge(m_edge,concept,node1,node2);
  }

  //Node is used in: m_edge and QtConceptMapNodeConcept::m_edge
  //assert(m_edge.use_count() == 2);
  //Concept is used in: m_edge::m_concept, QtDisplayStrategy::m_edge::m_concept and QtConceptMapConcept::m_concept
  assert(m_edge.get() == m_edge_item->GetEdge().get());
  assert(m_edge->GetConcept().get() == m_edge_item->GetEdge()->GetConcept().get());

  #ifndef NDEBUG
  {
    const int edge_use_count = m_edge.use_count();
    assert(edge_use_count == 2);
  }
  #endif

  //Add items to the scene
  assert(node1);
  assert(node2);
  assert(m_edge_item);
  assert(!node1->scene());
  assert(!node2->scene());
  assert(!m_edge_item->scene());

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
          return dynamic_cast<const QtEdge*>(item);
        }
      ) == 1);
  }

  //Put nodes (not the edges) into place
  //The nodes must reposition themselves
  node1->SetPos(-100.0,-100.0);
  m_edge_item->SetPos(0.0,0.0);
  node2->SetPos( 100.0, 100.0);

  {
    const std::vector<cmap::Competency> v = cmap::GetAllCompetencies();
    const std::size_t sz = boost::numeric_cast<int>(v.size());
    for (std::size_t i=0; i!=sz; ++i)
    {
      assert(i < v.size());
      const cmap::Competency competency = v[i];
      const std::string s = cmap::CompetencyToDutchStr(competency);
      const QString qs = s.c_str();
      assert(ui);
      assert(ui->box_competency);
      assert(GetEdgeCurrentWay());
      assert(GetEdgeCurrentWay()->GetConcept());
      assert(GetEdgeCurrentWay()->GetConcept()->GetExamples());
      assert(!GetEdgeCurrentWay()->GetConcept()->GetExamples()->Get().empty()
        && "Otherwise 'ui->box_competency->addItem(qs)' will fail, due to on_box_competency_currentIndexChanged");
      ui->box_competency->addItem(qs); //2013-06-22: BUG: std::out_of_range' what():  vector::_M_range_check
    }
  }

  assert(this->GetEdgeCurrentWay()->GetConcept()->GetExamples());
  assert(!this->GetEdgeCurrentWay()->GetConcept()->GetExamples()->Get().empty());

  ui->box_complexity->setCurrentIndex(this->GetEdgeCurrentWay()->GetConcept()->GetRatingComplexity() + 1);
  ui->box_concreteness->setCurrentIndex(this->GetEdgeCurrentWay()->GetConcept()->GetRatingConcreteness() + 1);
  ui->box_specificity->setCurrentIndex(this->GetEdgeCurrentWay()->GetConcept()->GetRatingSpecificity() + 1);

  ui->edit_name->setText(this->GetEdgeCurrentWay()->GetConcept()->GetName().c_str());
  ui->edit_example_text->setText(this->GetEdgeCurrentWay()->GetConcept()->GetExamples()->Get().at(0)->GetText().c_str());

  ui->box_arrow_head->setCurrentIndex(this->GetEdgeCurrentWay()->HasHeadArrow());
  ui->box_arrow_tail->setCurrentIndex(this->GetEdgeCurrentWay()->HasTailArrow());
  ui->box_competency->setCurrentIndex(static_cast<int>(this->GetEdgeCurrentWay()->GetConcept()->GetExamples()->Get().at(0)->GetCompetency()));
}

ribi::cmap::QtConceptMapTestEdgeItemDialog::~QtConceptMapTestEdgeItemDialog() noexcept
{
  delete ui;
}

const boost::shared_ptr<ribi::cmap::Node> ribi::cmap::QtConceptMapTestEdgeItemDialog::CreateFrom()
{
  const std::size_t index = 2;
  assert(index < cmap::NodeFactory().GetTests().size());
  const boost::shared_ptr<Node> node = cmap::NodeFactory().GetTests().at(index);
  assert(node);
  return node;
}

const boost::shared_ptr<ribi::cmap::Node> ribi::cmap::QtConceptMapTestEdgeItemDialog::CreateTo()
{
  const std::size_t index = 2;
  assert(index < cmap::NodeFactory().GetTests().size());
  const boost::shared_ptr<Node> node = cmap::NodeFactory().GetTests().at(index);
  assert(node);
  return node;
}

boost::shared_ptr<ribi::cmap::Edge> ribi::cmap::QtConceptMapTestEdgeItemDialog::GetEdgeCurrentWay()
{
  return GetEdge(ui->box_edit->currentIndex());
}

boost::shared_ptr<ribi::cmap::Edge> ribi::cmap::QtConceptMapTestEdgeItemDialog::GetEdge(const int index)
{
  switch(index)
  {
    case 0:
      assert(m_edge);
      return m_edge;
    case 1:
    {
      const auto v = ui->view->scene()->items();
      const auto iter = std::find_if(v.begin(),v.end(),
        [](const QGraphicsItem * const item)
        {
          return dynamic_cast<const QtEdge*>(item);
        }
      );
      assert(iter!=v.end());
      QtEdge * const qtedge = dynamic_cast<QtEdge*>(*iter);
      assert(qtedge);
      return qtedge->GetEdge();
    }
    default:
      assert(!"Should not get here");
  }
  assert(!"Should not get here");
  throw std::logic_error("ribi::cmap::QtConceptMapTestEdgeItemDialog::GetEdge: current index unknown");
}

void ribi::cmap::QtConceptMapTestEdgeItemDialog::keyPressEvent(QKeyEvent *event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

int ribi::cmap::QtConceptMapTestEdgeItemDialog::GetTestIndex() const noexcept
{
  //return ui->box_index->value();
  return 1;
}

void ribi::cmap::QtConceptMapTestEdgeItemDialog::on_box_competency_currentIndexChanged(int index)
{
  const cmap::Competency c = static_cast<cmap::Competency>(index);
  assert(GetEdgeCurrentWay());
  assert(GetEdgeCurrentWay()->GetConcept());
  assert(GetEdgeCurrentWay()->GetConcept()->GetExamples());
  assert(!GetEdgeCurrentWay()->GetConcept()->GetExamples()->Get().empty());
  this->GetEdgeCurrentWay()->GetConcept()->GetExamples()->Get().at(0)->SetCompetency(c);
}

void ribi::cmap::QtConceptMapTestEdgeItemDialog::on_edit_name_textChanged(const QString &arg1)
{
  assert(GetEdgeCurrentWay());
  assert(GetEdgeCurrentWay()->GetConcept());
  this->GetEdgeCurrentWay()->GetConcept()->SetName(arg1.toStdString());
  assert(this->GetEdgeCurrentWay()->GetConcept()->GetName() == arg1.toStdString());
}

void ribi::cmap::QtConceptMapTestEdgeItemDialog::on_box_complexity_currentIndexChanged(const QString &arg1)
{
  const int rating_complexity = boost::lexical_cast<int>(arg1.toStdString());
  assert(rating_complexity >= -1);
  assert(rating_complexity <=  2);
  assert(GetEdgeCurrentWay());
  assert(GetEdgeCurrentWay()->GetConcept());
  this->GetEdgeCurrentWay()->GetConcept()->SetRatingComplexity(rating_complexity);
}

void ribi::cmap::QtConceptMapTestEdgeItemDialog::on_box_concreteness_currentIndexChanged(const QString &arg1)
{
  assert(GetEdgeCurrentWay());
  assert(GetEdgeCurrentWay()->GetConcept());
  this->GetEdgeCurrentWay()->GetConcept()->SetRatingConcreteness(boost::lexical_cast<int>(arg1.toStdString()));
}

void ribi::cmap::QtConceptMapTestEdgeItemDialog::on_box_specificity_currentIndexChanged(const QString &arg1)
{
  assert(GetEdgeCurrentWay());
  assert(GetEdgeCurrentWay()->GetConcept());
  this->GetEdgeCurrentWay()->GetConcept()->SetRatingSpecificity(boost::lexical_cast<int>(arg1.toStdString()));
}

void ribi::cmap::QtConceptMapTestEdgeItemDialog::on_edit_example_text_textChanged(const QString &arg1)
{
  assert(GetEdgeCurrentWay());
  assert(GetEdgeCurrentWay()->GetConcept());
  assert(GetEdgeCurrentWay()->GetConcept()->GetExamples());
  this->GetEdgeCurrentWay()->GetConcept()->GetExamples()->Get().at(0)->SetText(arg1.toStdString());
}

void ribi::cmap::QtConceptMapTestEdgeItemDialog::on_box_arrow_head_currentIndexChanged(int index)
{
  assert(GetEdgeCurrentWay());
  this->GetEdgeCurrentWay()->SetHeadArrow(index);
  assert(this->GetEdge(0)->HasHeadArrow() == static_cast<bool>(index));
  assert(this->GetEdge(1)->HasHeadArrow() == static_cast<bool>(index));
}

void ribi::cmap::QtConceptMapTestEdgeItemDialog::on_box_arrow_tail_currentIndexChanged(int index)
{
  assert(GetEdgeCurrentWay());
  this->GetEdgeCurrentWay()->SetTailArrow(index);
  assert(this->GetEdge(0)->HasTailArrow() == static_cast<bool>(index));
  assert(this->GetEdge(1)->HasTailArrow() == static_cast<bool>(index));
}

void ribi::cmap::QtConceptMapTestEdgeItemDialog::OnRequestSceneUpdate()
{
  assert(ui);
  assert(ui->view);
  assert(ui->view->scene());
  ui->view->scene()->update();
}

void ribi::cmap::QtConceptMapTestEdgeItemDialog::SetEdge(const boost::shared_ptr<ribi::cmap::Edge>& /* edge */) noexcept
{
  //
}

#ifndef NDEBUG
void ribi::cmap::QtConceptMapTestEdgeItemDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("ribi::cmap::QtConceptMapTestEdgeItemDialog::Test started");
  //boost::shared_ptr<QtConceptMapTestEdgeItemDialog> parent(new QtConceptMapTestEdgeItemDialog);
  boost::shared_ptr<QtConceptMapTestEdgeItemDialog> d(new QtConceptMapTestEdgeItemDialog);
  //assert(parent);
  assert(d);
  //parent->ShowChild(d.get());
  assert(d->m_edge);
  assert(d->m_edge->GetConcept());
  assert(d->m_edge_item);
  assert(d->m_edge_item->GetEdge());
  assert(d->m_edge.get() == d->m_edge_item->GetEdge().get());
  assert(d->m_edge->GetConcept().get() == d->m_edge_item->GetEdge()->GetConcept().get());

  //Test resizing due to longer text being set
  {
    const std::string s = d->m_edge->GetConcept()->GetName();
    const double concept_item_width_before = d->m_edge_item->GetDisplayStrategy()->boundingRect().width();
    const double edge_item_width_before = d->m_edge_item->boundingRect().width();
    d->m_edge->GetConcept()->SetName(s + "******************************");
    //There must be no discrepancy between these boundingRects
    const double concept_item_width_after = d->m_edge_item->GetDisplayStrategy()->boundingRect().width();
    const double edge_item_width_after = d->m_edge_item->boundingRect().width();
    assert(concept_item_width_after >= concept_item_width_before);
    assert(edge_item_width_after >= edge_item_width_before);
  }
  //Test resizing due to shorter text being set
  {
    d->m_edge->GetConcept()->SetName("1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890");

    const double concept_item_height_before = d->m_edge_item->GetDisplayStrategy()->boundingRect().height();
    const double concept_item_width_before = d->m_edge_item->GetDisplayStrategy()->boundingRect().width();
    const double concept_item_area_before = concept_item_width_before * concept_item_height_before;
    const double edge_item_height_before = d->m_edge_item->boundingRect().height();
    const double edge_item_width_before = d->m_edge_item->boundingRect().width();
    const double edge_item_area_before = edge_item_width_before * edge_item_height_before;

    d->m_edge->GetConcept()->SetName(std::string(1,'*'));

    const double concept_item_height_after = d->m_edge_item->GetDisplayStrategy()->boundingRect().height();
    const double concept_item_width_after = d->m_edge_item->GetDisplayStrategy()->boundingRect().width();
    const double concept_item_area_after = concept_item_width_after * concept_item_height_after;
    const double edge_item_height_after = d->m_edge_item->boundingRect().height();
    const double edge_item_width_after = d->m_edge_item->boundingRect().width();
    const double edge_item_area_after = edge_item_width_after * edge_item_height_after;

    assert(concept_item_area_before > concept_item_area_after
      && "Concept item must shrink with shorter text");
    assert(edge_item_area_before > edge_item_area_after
      && "The edge as a whole does not need to shrink, as the to and from nodes remain in place,"
      && "but with a very long to a very short text will enforce this");
  }
  //Push all buttons
  assert(d->ui);
  assert(d->ui->box_edit);
  const int n_edit_types = d->ui->box_edit->count();
  assert(n_edit_types > 0);
  for (int type=0; type!=n_edit_types; ++type)
  {
    //Set the way to obtain the pointer to the edge
    d->ui->box_edit->setCurrentIndex(type);

    //Set some texts to enforce growth and shrinking in the text
    {
      const std::string text = std::string(30,'*') + boost::lexical_cast<std::string>(type);
      d->ui->edit_name->setText(text.c_str());
    }
    {
      const std::string text = std::string(1,'*') + boost::lexical_cast<std::string>(type);
      d->ui->edit_name->setText(text.c_str());
    }
    {
      const std::string text = std::string(30,'*') + boost::lexical_cast<std::string>(type);
      d->ui->edit_name->setText(text.c_str());
    }

    //Change the arrow head
    {
      const int n = d->ui->box_arrow_head->count();
      assert(n > 0);
      for (int i=0; i!=n; ++i)
      {
        d->ui->box_arrow_head->setCurrentIndex(i);
        assert(d->m_edge->HasHeadArrow() == i); //i == 0 -> false
      }
    }
    //Change the arrow tail
    {
      const int n = d->ui->box_arrow_tail->count();
      assert(n > 0);
      for (int i=0; i!=n; ++i)
      {
        d->ui->box_arrow_tail->setCurrentIndex(i);
        assert(d->m_edge->HasTailArrow() == i); //i == 0 -> false
      }
    }
  }
  d->close();
  TRACE("ribi::cmap::QtConceptMapTestEdgeItemDialog::Test finished successfully");
}
#endif

void ribi::cmap::QtConceptMapTestEdgeItemDialog::on_button_load_test_clicked()
{
  //
}
