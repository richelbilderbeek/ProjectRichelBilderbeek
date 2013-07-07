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
    const std::size_t index = 4; //Must have examples
    assert(index < pvdb::EdgeFactory::GetTests(m_from,m_to).size());
    m_edge = pvdb::EdgeFactory::GetTests(m_from,m_to)[index];
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
    assert(m_edge);
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
  assert(node1);
  assert(node2);
  assert(m_edge_item);
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
  node1->SetPos(-100.0,-100.0);
  m_edge_item->SetPos(0.0,0.0);
  node2->SetPos( 100.0, 100.0);

  {
    const std::vector<pvdb::Competency> v = pvdb::GetAllCompetencies();
    const std::size_t sz = boost::numeric_cast<int>(v.size());
    for (std::size_t i=0; i!=sz; ++i)
    {
      assert(i < v.size());
      const pvdb::Competency competency = v[i];
      const std::string s = pvdb::CompetencyToDutchStr(competency);
      const QString qs = s.c_str();
      assert(ui);
      assert(ui->box_competency);
      assert(GetEdge());
      assert(GetEdge()->GetConcept());
      assert(GetEdge()->GetConcept()->GetExamples());
      assert(!GetEdge()->GetConcept()->GetExamples()->Get().empty()
        && "Otherwise 'ui->box_competency->addItem(qs)' will fail, due to on_box_competency_currentIndexChanged");
      ui->box_competency->addItem(qs); //2013-06-22: BUG: std::out_of_range' what():  vector::_M_range_check
    }
  }

  assert(this->GetEdge()->GetConcept()->GetExamples());
  assert(!this->GetEdge()->GetConcept()->GetExamples()->Get().empty());

  ui->box_complexity->setCurrentIndex(this->GetEdge()->GetConcept()->GetRatingComplexity() + 1);
  ui->box_concreteness->setCurrentIndex(this->GetEdge()->GetConcept()->GetRatingConcreteness() + 1);
  ui->box_specificity->setCurrentIndex(this->GetEdge()->GetConcept()->GetRatingSpecificity() + 1);

  ui->edit_name->setText(this->GetEdge()->GetConcept()->GetName().c_str());
  ui->edit_example_text->setText(this->GetEdge()->GetConcept()->GetExamples()->Get().at(0)->GetText().c_str());

  ui->box_arrow_head->setCurrentIndex(this->GetEdge()->HasHeadArrow());
  ui->box_arrow_tail->setCurrentIndex(this->GetEdge()->HasTailArrow());
  ui->box_competency->setCurrentIndex(static_cast<int>(this->GetEdge()->GetConcept()->GetExamples()->Get().at(0)->GetCompetency()));
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
    case 0:
      assert(m_edge);
      return m_edge;
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
  assert(GetEdge());
  assert(GetEdge()->GetConcept());
  assert(GetEdge()->GetConcept()->GetExamples());
  assert(!GetEdge()->GetConcept()->GetExamples()->Get().empty());
  this->GetEdge()->GetConcept()->GetExamples()->Get().at(0)->SetCompetency(c);
}

void QtPvdbTestEdgeItemDialog::on_edit_name_textChanged(const QString &arg1)
{
  assert(GetEdge());
  assert(GetEdge()->GetConcept());
  this->GetEdge()->GetConcept()->SetName(arg1.toStdString());
  assert(this->GetEdge()->GetConcept()->GetName() == arg1.toStdString());
}

void QtPvdbTestEdgeItemDialog::on_box_complexity_currentIndexChanged(const QString &arg1)
{
  const int rating_complexity = boost::lexical_cast<int>(arg1.toStdString());
  assert(rating_complexity >= -1);
  assert(rating_complexity <=  2);
  assert(GetEdge());
  assert(GetEdge()->GetConcept());
  this->GetEdge()->GetConcept()->SetRatingComplexity(rating_complexity);
}

void QtPvdbTestEdgeItemDialog::on_box_concreteness_currentIndexChanged(const QString &arg1)
{
  assert(GetEdge());
  assert(GetEdge()->GetConcept());
  this->GetEdge()->GetConcept()->SetRatingConcreteness(boost::lexical_cast<int>(arg1.toStdString()));
}

void QtPvdbTestEdgeItemDialog::on_box_specificity_currentIndexChanged(const QString &arg1)
{
  assert(GetEdge());
  assert(GetEdge()->GetConcept());
  this->GetEdge()->GetConcept()->SetRatingSpecificity(boost::lexical_cast<int>(arg1.toStdString()));
}

void QtPvdbTestEdgeItemDialog::on_edit_example_text_textChanged(const QString &arg1)
{
  assert(GetEdge());
  assert(GetEdge()->GetConcept());
  assert(GetEdge()->GetConcept()->GetExamples());
  this->GetEdge()->GetConcept()->GetExamples()->Get().at(0)->SetText(arg1.toStdString());
}

void QtPvdbTestEdgeItemDialog::on_box_arrow_head_currentIndexChanged(int index)
{
  assert(GetEdge());
  this->GetEdge()->SetHeadArrow(index);
}

void QtPvdbTestEdgeItemDialog::on_box_arrow_tail_currentIndexChanged(int index)
{
  assert(GetEdge());
  this->GetEdge()->SetTailArrow(index);
}

void QtPvdbTestEdgeItemDialog::OnRequestSceneUpdate()
{
  assert(ui);
  assert(ui->view);
  assert(ui->view->scene());
  ui->view->scene()->update();
}

#ifndef NDEBUG
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
  boost::shared_ptr<QtPvdbTestEdgeItemDialog> d(new QtPvdbTestEdgeItemDialog);
  assert(d);
  assert(d->m_edge);
  assert(d->m_edge->GetConcept());
  assert(d->m_edge_item);
  assert(d->m_edge_item->GetEdge());
  assert(d->m_edge.get() == d->m_edge_item->GetEdge().get());
  assert(d->m_edge->GetConcept().get() == d->m_edge_item->GetEdge()->GetConcept().get());

  //Test resizing due to longer text being set
  {
    const std::string s = d->m_edge->GetConcept()->GetName();
    const double concept_item_width = d->m_edge_item->GetConceptItem()->boundingRect().width();
    const double edge_item_width = d->m_edge_item->boundingRect().width();
    d->m_edge->GetConcept()->SetName(s + "*");
    //There must be no discrepancy between these boundingRects
    assert(d->m_edge_item->GetConceptItem()->boundingRect().width() > 1 + concept_item_width);
    assert(d->m_edge_item->boundingRect().width() > 1 + edge_item_width);
  }
  //Test resizing due to shorter text being set
  {
    d->m_edge->GetConcept()->SetName(std::string(80,'*'));

    const double concept_item_width_before = d->m_edge_item->GetConceptItem()->boundingRect().width();
    const double edge_item_width_before = d->m_edge_item->boundingRect().width();

    d->m_edge->GetConcept()->SetName(std::string(1,'*'));

    const double concept_item_width_after = d->m_edge_item->GetConceptItem()->boundingRect().width();
    const double edge_item_width_after = d->m_edge_item->boundingRect().width();

    assert(concept_item_width_before > concept_item_width_after
      && "Concept item must shrink with shorter text");
    assert(edge_item_width_before > edge_item_width_after
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
      const std::string text = std::string(100,'*') + boost::lexical_cast<std::string>(type);
      d->ui->edit_name->setText(text.c_str());
    }
    {
      const std::string text = std::string(1,'*') + boost::lexical_cast<std::string>(type);
      d->ui->edit_name->setText(text.c_str());
    }
    {
      const std::string text = std::string(100,'*') + boost::lexical_cast<std::string>(type);
      d->ui->edit_name->setText(text.c_str());
    }

    //Change the arrow head
    {
      const int n = d->ui->box_arrow_head->count();
      assert(n > 0);
      for (int i=0; i!=n; ++i)
      {
        d->ui->box_arrow_head->setCurrentIndex(i);
      }
    }
    //Change the arrow tail
    {
      const int n = d->ui->box_arrow_tail->count();
      assert(n > 0);
      for (int i=0; i!=n; ++i)
      {
        d->ui->box_arrow_tail->setCurrentIndex(i);
      }
    }
  }
  TRACE("QtPvdbTestEdgeItemDialog::Test finished successfully");
  #ifdef COMPILER_SUPPORTS_THREADS_20130507
    }
  );
  t.detach();
  #endif
}
#endif
