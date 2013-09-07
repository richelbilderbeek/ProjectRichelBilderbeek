#include "qtpvdbconceptmapwidget.h"

#include <set>

#include <boost/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <QKeyEvent>

#include "fuzzy_equal_to.h"
#include "pvdbcenternode.h"
#include "pvdbconceptfactory.h"
#include "pvdbconcept.h"
#include "pvdbconceptmapfactory.h"
#include "pvdbconceptmap.h"
#include "pvdbedgefactory.h"
#include "pvdbedge.h"
#include "pvdbhelper.h"
#include "pvdbnodefactory.h"
#include "pvdbnode.h"
#include "qtarrowitem.h"
#include "qtpvdbdisplayconceptitem.h"
#include "qtpvdbbrushfactory.h"
#include "qtpvdbcenternodeitem.h"
#include "qtpvdbconcepteditdialog.h"
#include "qtpvdbconceptitem.h"
#include "qtpvdbedgeitem.h"
#include "qtpvdbexamplesitem.h"
#include "qtpvdbitemhighlighter.h"
#include "qtpvdbnewarrow.h"
#include "qtpvdbnodeitem.h"
#include "qtpvdbtoolsitem.h"
#include "qtscopeddisable.h"
#include "trace.h"

///Collect all QGraphicsItems with class T in an unorderly way
template <class T>
std::vector<T*> Collect(const QGraphicsScene* const scene)
{
  std::vector<T*> v;
  const QList<QGraphicsItem *> items = scene->items();
  std::transform(items.begin(),items.end(),std::back_inserter(v),
    [](QGraphicsItem* const item)
    {
      return dynamic_cast<T*>(item);
    }
  );
  v.erase(std::remove(v.begin(),v.end(),nullptr),v.end());
  assert(std::count(v.begin(),v.end(),nullptr)==0);
  return v;
}

///Returns a sorted vector
template <class T>
const std::vector<T> Sort(const std::vector<T>& v)
{
  std::vector<T> w(v);
  std::sort(w.begin(),w.end());
  return w;
}

template <>
const std::vector<ribi::pvdb::QtPvdbNodeItem*>
  Sort(
    const std::vector<ribi::pvdb::QtPvdbNodeItem*>& v)
{
  typedef std::vector<ribi::pvdb::QtPvdbNodeItem*>::iterator Iterator;
  std::vector<ribi::pvdb::QtPvdbNodeItem*> w(v);
  std::sort(w.begin(),w.end());
  const Iterator i = std::find_if(w.begin(),w.end(),
    [](const ribi::pvdb::QtPvdbNodeItem* const node)
    {
      return dynamic_cast<const ribi::pvdb::QtPvdbCenterNodeItem*>(node);
    }
  );
  if (i != w.end())
  {
    std::swap(*i,*w.begin());
    assert(dynamic_cast<const ribi::pvdb::QtPvdbCenterNodeItem*>(*w.begin()));
  }
  return w;
}



ribi::pvdb::QtPvdbConceptMapWidget::QtPvdbConceptMapWidget(
  const boost::shared_ptr<ribi::pvdb::ConceptMap> concept_map,
  QWidget* parent)
  : QtKeyboardFriendlyGraphicsView(parent),
    m_concept_map(concept_map),
    m_examples_item(new QtPvdbExamplesItem)
{
  assert( (concept_map || !concept_map)
    && "Also empty concept maps must be displayed");

  //Cannot test this ABC here, its derived classes will test themselves

  this->setScene(new QGraphicsScene(this));

  assert(!m_examples_item->scene());
  scene()->addItem(m_examples_item); //Add the examples so it has a parent

  assert(Collect<QtPvdbNodeItem>(scene()).empty());

  //Without this line, mouseMoveEvent won't be called
  this->setMouseTracking(true);


  {
    //QLinearGradient linearGradient(-500,-500,500,500);
    //linearGradient.setColorAt(0.0,QColor(214,214,214));
    //linearGradient.setColorAt(1.0,QColor(255,255,255));
    assert(this->scene());
    //this->scene()->setBackgroundBrush(linearGradient);
    this->scene()->setBackgroundBrush(QBrush(QColor(255,255,255)));
  }

  assert(GetConceptMap() == concept_map);
  assert( (!concept_map || concept_map->IsValid())
    && "Expect no or a valid concept map");
}


ribi::pvdb::QtPvdbConceptMapWidget::~QtPvdbConceptMapWidget()
{
  delete m_examples_item; //Why did I forget this?
  m_examples_item = nullptr;
}

void ribi::pvdb::QtPvdbConceptMapWidget::BuildQtConceptMap()
{

  CleanMe();
  assert(m_concept_map);
  assert(m_concept_map->IsValid());
  assert(this->scene());
  //This std::vector keeps the QtNodes in the same order as the nodes in the concept map
  //You cannot rely on Collect<QtPvdbNodeConcept*>(scene), as this shuffles the order
  std::vector<QtPvdbNodeItem*> qtnodes;

  assert(Collect<QtPvdbNodeItem>(scene()).empty());

  //Add the nodes to the scene
  {
    //Add the main question as the first node
    const boost::shared_ptr<ribi::pvdb::Node> node = m_concept_map->GetNodes()[0];
    QtPvdbNodeItem* const qtnode = new QtPvdbCenterNodeItem(node);
    #ifdef USE_NEW_STYLE
    QtPvdbNodeItem* qtnode = nullptr;
    if (const boost::shared_ptr<pvdb::CenterNode> center_node = boost::dynamic_pointer_cast<pvdb::CenterNode>(node))
    {
      qtnode = new QtPvdbCenterNodeItem(center_node);
    }
    else
    {
      assert(node);
      const boost::shared_ptr<QtPvdbConceptItem> item(new QtPvdbDisplayConceptItem(node->GetConcept()));
      assert(item);
      qtnode = new QtPvdbNodeItem(node,item);
    }
    #endif
    assert(qtnode);
    //Let the center node respond to mouse clicks
    qtnode->m_signal_request_scene_update.connect(
      boost::bind(&ribi::pvdb::QtPvdbConceptMapWidget::OnRequestSceneUpdate,this));
    qtnode->m_signal_item_has_updated.connect(
      boost::bind(&ribi::pvdb::QtPvdbConceptMapWidget::OnItemRequestsUpdate,this,boost::lambda::_1));
    //Add the center node to scene
    assert(!qtnode->scene());
    this->scene()->addItem(qtnode);
    qtnodes.push_back(qtnode);
    assert(Collect<QtPvdbNodeItem>(scene()).size() == 1);

    //Add the regular nodes to the scene
    const std::vector<boost::shared_ptr<ribi::pvdb::Node> > nodes = m_concept_map->GetNodes();
    const std::size_t n_nodes = nodes.size();
    assert(n_nodes >= 1);
    for (std::size_t i=1; i!=n_nodes; ++i) //+1 to skip center node
    {
      assert(Collect<QtPvdbNodeItem>(scene()).size() == i && "Node not yet added to scene");
      assert(i < nodes.size());
      boost::shared_ptr<ribi::pvdb::Node> node = nodes[i];
      assert(node);
      QtPvdbNodeItem * const qtnode = AddNode(node);
      qtnodes.push_back(qtnode);
      assert(Collect<QtPvdbNodeItem>(scene()).size() == i + 1 && "Node is added to scene");
    }
  }
  #ifndef NDEBUG
  {
    //Check the number of
    const auto qtnodes = Collect<QtPvdbNodeItem>(scene());
    const auto n_qtnodes = qtnodes.size();
    const auto nodes = m_concept_map->GetNodes();
    const auto n_nodes = nodes.size();
    assert(n_qtnodes == n_nodes
      && "There must as much nodes in the scene as there were in the concept map");
  }
  #endif
  //Add the Concepts on the Edges
  {
    const std::vector<boost::shared_ptr<ribi::pvdb::Edge> > edges = m_concept_map->GetEdges();
    std::for_each(edges.begin(),edges.end(),
      [this,qtnodes](const boost::shared_ptr<ribi::pvdb::Edge> edge)
      {
        assert(edge->GetFrom());
        assert(edge->GetTo());
        assert(edge->GetFrom() != edge->GetTo());
        this->AddEdge(edge);
      }
    );
  }

  #ifndef NDEBUG
  {
    //Check the number of edges
    const auto qtedges = Collect<QtPvdbEdgeItem>(scene());
    const auto n_qtedges = qtedges.size();
    const auto edges = m_concept_map->GetEdges();
    const auto n_edges = edges.size();
    assert(n_qtedges == n_edges
      && "There must as much edges in the scene as there were in the concept map");
  }
  #endif

  //Put the nodes around the focal question in an initial position
  if (MustReposition(AddConst(m_concept_map->GetNodes())))
  {
    RepositionItems();
  }

  #ifndef NDEBUG
  assert(m_concept_map->IsValid());
  const auto nodes = m_concept_map->GetNodes();
  const auto items = Collect<QtPvdbNodeItem>(this->scene());
  const std::size_t n_items = items.size();
  const std::size_t n_nodes = nodes.size();
  if (n_items != n_nodes)
  {
    TRACE(m_concept_map->GetNodes().size());
    TRACE(n_items);
    TRACE(n_nodes);
  }
  assert(n_items == n_nodes && "GUI and non-GUI concept map must match");
  TestMe(m_concept_map);
  #endif
}

const std::vector<ribi::pvdb::QtPvdbEdgeItem*> ribi::pvdb::QtPvdbConceptMapWidget::FindEdges(
  const QtPvdbNodeItem* const from) const
{
  assert(from);
  const std::vector<QtPvdbEdgeItem*> v = Collect<QtPvdbEdgeItem>(scene());
  std::vector<QtPvdbEdgeItem*> w;
  std::copy_if(v.begin(),v.end(),std::back_inserter(w),
    [from](const QtPvdbEdgeItem* const edge)
    {
      return edge->GetFrom() == from || edge->GetTo() == from;
    }
  );
  return w;
}

const ribi::pvdb::QtPvdbEdgeItem * ribi::pvdb::QtPvdbConceptMapWidget::FindQtEdge(
  const QtPvdbNodeItem* const from,
  const QtPvdbNodeItem* const to) const
{

  assert(from);
  assert(to);
  assert(from != to);
  const std::vector<QtPvdbEdgeItem*> edge_concepts = Collect<QtPvdbEdgeItem>(scene());
  const auto iter = std::find_if(edge_concepts.begin(),edge_concepts.end(),
    [from,to](const QtPvdbEdgeItem* const edge)
    {
      return
        (edge->GetFrom() == from && edge->GetTo() == to)
     || (edge->GetFrom() == to && edge->GetTo() == from);
    }
  );
  if (iter == edge_concepts.end()) return nullptr;
  return * iter;
}

ribi::pvdb::QtPvdbNodeItem * ribi::pvdb::QtPvdbConceptMapWidget::FindQtNode(const boost::shared_ptr<ribi::pvdb::Node> node) const
{
  const std::vector<QtPvdbNodeItem *> qtnodes = Collect<QtPvdbNodeItem>(scene());
  for (QtPvdbNodeItem * qtnode: qtnodes)
  {
    if (qtnode->GetNode() == node) return qtnode;
  }
  assert(!"Should always find QtNode");
  throw std::logic_error("ribi::pvdb::QtPvdbConceptMapWidget::FindQtNode");
}

const ribi::pvdb::QtPvdbNodeItem * ribi::pvdb::QtPvdbConceptMapWidget::GetCenterNode() const
{

  assert(scene());
  assert(!scene()->items().isEmpty());
  assert(scene()->items()[0]);
  QList<QGraphicsItem *> v = scene()->items();
  assert(std::count_if(v.begin(),v.end(),
    [this](const QGraphicsItem * const item) { return this->IsCenterNode(item); }
    ) == 1 && "There must be exactly one center node");
  const auto iter = std::find_if(v.begin(),v.end(),
    [this](const QGraphicsItem * const item) { return this->IsCenterNode(item); } );
  assert(iter != v.end());
  const QtPvdbNodeItem * const center_node = dynamic_cast<QtPvdbNodeItem*>(*iter);
  assert(center_node);
  assert(IsCenterNode(center_node));
  return center_node;
}

const ribi::pvdb::QtPvdbExamplesItem * ribi::pvdb::QtPvdbConceptMapWidget::GetExamplesItem() const
{
  assert(m_examples_item || !m_examples_item);
  return m_examples_item;
}

ribi::pvdb::QtPvdbExamplesItem * ribi::pvdb::QtPvdbConceptMapWidget::GetExamplesItem()
{
  //Calls the const version of this member function
  //To avoid duplication in const and non-const member functions [1]
  //[1] Scott Meyers. Effective C++ (3rd edition). ISBN: 0-321-33487-6.
  //    Item 3, paragraph 'Avoid duplication in const and non-const member functions'
  return const_cast<QtPvdbExamplesItem*>(
    const_cast<const QtPvdbConceptMapWidget*>(this)->GetExamplesItem());
}

ribi::pvdb::QtPvdbNodeItem* ribi::pvdb::QtPvdbConceptMapWidget::GetItemBelowCursor(const QPointF& pos) const
{
  #if (QT_VERSION >= QT_VERSION_CHECK(5,0,0))
  const QList<QGraphicsItem*> v = this->scene()->items(pos.x(),pos.y(),2.0,2.0,Qt::IntersectsItemShape,Qt::AscendingOrder);
  #else
  const QList<QGraphicsItem*> v = this->scene()->items(pos.x(),pos.y(),2.0,2.0);
  #endif
  std::vector<QtPvdbNodeItem*> qtnodes;
  std::for_each(v.begin(),v.end(),
    [&qtnodes](QGraphicsItem* const item)
    {
      if (QtPvdbNodeItem * const qtnode = dynamic_cast<QtPvdbNodeItem*>(item))
      {
        assert(!dynamic_cast<QtPvdbToolsItem*>(item) && "Cannot draw arrow to ToolsItem");
        qtnodes.push_back(qtnode);
      }
    }
  );
  if (!qtnodes.empty())
  {
    return qtnodes[0];
  }
  return nullptr;
}

const std::vector<const ribi::pvdb::QtPvdbEdgeItem *> ribi::pvdb::QtPvdbConceptMapWidget::GetQtEdges() const
{
  const std::vector<const QtPvdbEdgeItem *> qtedges
    = Collect<const QtPvdbEdgeItem>(this->scene());
  assert(qtedges.size() == GetConceptMap()->GetNodes().size()
      && "GUI and non-GUI must contain an equal amount of edges");
  return qtedges;
}

const std::vector<const ribi::pvdb::QtPvdbNodeItem *> ribi::pvdb::QtPvdbConceptMapWidget::GetQtNodes() const
{
  const std::vector<const QtPvdbNodeItem *> qtnodes
    = Collect<const QtPvdbNodeItem>(this->scene());
  assert(qtnodes.size() == GetConceptMap()->GetNodes().size()
      && "GUI and non-GUI must contain an equal amount of nodes");
  return qtnodes;
}

QGraphicsScene* ribi::pvdb::QtPvdbConceptMapWidget::GetScene() const
{

  return this->scene();
}

bool ribi::pvdb::QtPvdbConceptMapWidget::IsCenterNode(const QGraphicsItem* const item)
{

  const QtPvdbNodeItem * const qtnode = dynamic_cast<const QtPvdbNodeItem*>(item);
  return qtnode && !(item->flags() & QGraphicsItem::ItemIsMovable);
}

void ribi::pvdb::QtPvdbConceptMapWidget::keyPressEvent(QKeyEvent *event)
{

  switch (event->key())
  {
    case Qt::Key_Equal:
      this->scale(1.1,1.1);
      break;
    case Qt::Key_Minus:
      this->scale(0.9,0.9);
      break;
  }

  QtKeyboardFriendlyGraphicsView::keyPressEvent(event);
  scene()->update();
}

bool ribi::pvdb::QtPvdbConceptMapWidget::MustReposition(const std::vector<boost::shared_ptr<const pvdb::Node> >& nodes) const
{
  //If all are at the origin, the nodes must be (re)positioned
  return std::count_if(nodes.begin(),nodes.end(),
    [](const boost::shared_ptr<const pvdb::Node>& node)
    {
      return node->GetX() == 0.0 && node->GetY() == 0.0;
    }
  ) == static_cast<int>(nodes.size());
}

void ribi::pvdb::QtPvdbConceptMapWidget::OnItemRequestsUpdate(const QGraphicsItem* const item)
{
  OnItemRequestUpdateImpl(item);
}

void ribi::pvdb::QtPvdbConceptMapWidget::OnRequestSceneUpdate()
{
  scene()->update();
}


void ribi::pvdb::QtPvdbConceptMapWidget::RepositionItems()
{
  {
    //The ray of the upcoming circle of nodes, is the larger of
    //(1) half of the diagonal of the focal question (e.g. for short concepts)
    //(2) calculated from the circumference by adding the nodes' length
    const std::vector<QtPvdbNodeItem *> qtnode_concepts_unsorted = Collect<QtPvdbNodeItem>(scene());
    const std::vector<QtPvdbNodeItem *> qtnode_concepts = Sort(qtnode_concepts_unsorted);
    assert(!qtnode_concepts.empty());
    assert(qtnode_concepts[0]);
    const QtPvdbNodeItem * const qtcenter_node
      = dynamic_cast<const QtPvdbNodeItem *>(qtnode_concepts[0]);
    assert(qtcenter_node);
    assert(qtcenter_node->pos().x() > -0.5);
    assert(qtcenter_node->pos().x() <  0.5);
    assert(qtcenter_node->pos().y() > -0.5);
    assert(qtcenter_node->pos().y() <  0.5);

    const double r1
      = 0.5 * pvdb::GetDistance(
        qtcenter_node->boundingRect().width(),
        qtcenter_node->boundingRect().height());
    const double r3 = 50.0;
    const double r = std::max(r1,r3);
    assert(r > 10.0);
    const int n_nodes = qtnode_concepts.size();
    for (int i = 1; i!=n_nodes; ++i) //+1 to skip center node
    {
      //Added +0 (instead of -1) to n_nodes, to prevent, in a setup with two concepts and
      //one edge, the edge to overlap the central question
      const double pi = boost::math::constants::pi<double>();
      const double angle
        = 2.0 * pi * boost::numeric_cast<double>(i)
        / boost::numeric_cast<double>(n_nodes - 1);
      const double x =  std::cos(angle) * r;
      const double y = -std::sin(angle) * r;
      QtPvdbNodeItem * const qtnode = qtnode_concepts[i];
      qtnode->GetNode()->SetPos(x,y);
      //qtnode->setPos(x,y);
      #ifndef NDEBUG
      const double epsilon = 0.000001;
      #endif
      assert(std::abs(x - qtnode->pos().x()) < epsilon);
      assert(std::abs(x - qtnode->GetNode()->GetX()) < epsilon);
      assert(std::abs(x - qtnode->GetConceptItem()->pos().x()) < epsilon);
      assert(std::abs(y - qtnode->pos().y()) < epsilon);
      assert(std::abs(y - qtnode->GetNode()->GetY()) < epsilon);
      assert(std::abs(y - qtnode->GetConceptItem()->pos().y()) < epsilon);

    }
  }

  {
    //Put the edge concepts in the middle of the nodes
    const std::vector<QtPvdbEdgeItem *> qtedge_concepts = Collect<QtPvdbEdgeItem>(scene());
    std::for_each(qtedge_concepts.begin(), qtedge_concepts.end(),
      [](QtPvdbEdgeItem * const qtedge)
      {
        const QPointF p((qtedge->GetFrom()->pos() + qtedge->GetTo()->pos()) / 2.0);
        const double new_x = p.x();
        const double new_y = p.y();
        //qtedge->GetEdge()->SetX(new_x);
        //qtedge->GetEdge()->SetY(new_y);
        qtedge->GetEdge()->SetPos(new_x,new_y);
        #ifndef NDEBUG
        const double epsilon = 0.000001;
        #endif
        assert(std::abs(qtedge->pos().x() - qtedge->GetEdge()->GetX()) < epsilon);
        assert(std::abs(qtedge->pos().y() - qtedge->GetEdge()->GetY()) < epsilon);
      }
    );
  }

  //Put the nodes around the focal question in their improved position
  //If there is no focal node, the non-focal nodes are put around an empty spot
  while (1)
  {
    bool done = true;
    const std::vector<QtPvdbNodeItem *> qtnodes = Sort(Collect<QtPvdbNodeItem>(scene()));
    assert(!qtnodes.empty());
    assert(qtnodes[0]);
    assert(IsCenterNode(qtnodes[0]));
    const std::vector<QtPvdbEdgeItem* > qtedges = Collect<QtPvdbEdgeItem>(scene());
    const QtPvdbNodeItem * const center_node
      = dynamic_cast<const QtPvdbNodeItem *>(qtnodes[0]);
    assert(center_node);

    std::vector<QtRoundedTextRectItem*> nodes_and_edges;
    std::copy(qtnodes.begin(),qtnodes.end(),std::back_inserter(nodes_and_edges));
    assert(IsCenterNode(nodes_and_edges[0]));
    std::copy(qtedges.begin(),qtedges.end(),std::back_inserter(nodes_and_edges));

    //Move the nodes away from the center
    std::for_each(
      nodes_and_edges.begin() + 1, //+1 to skip the center node at [0]
      nodes_and_edges.end(),
      [center_node,&done](QtRoundedTextRectItem* const node_or_edge)
      {
        if (center_node->boundingRect().intersects(
          node_or_edge->boundingRect().translated(-node_or_edge->pos())))
        {
          const double cur_x = node_or_edge->pos().x();
          const double cur_y = node_or_edge->pos().y();
          const double new_x = cur_x + (node_or_edge->pos().x() < center_node->pos().x() ? -1.0 : 1.0);
          const double new_y = cur_y + (node_or_edge->pos().y() < center_node->pos().y() ? -1.0 : 1.0);
          if (QtPvdbNodeItem * const qtnode = dynamic_cast<QtPvdbNodeItem *>(node_or_edge))
          {
            qtnode->GetNode()->SetX(new_x);
            qtnode->GetNode()->SetY(new_y);
          }
          else
          {
            QtPvdbEdgeItem * const qtedge = dynamic_cast<QtPvdbEdgeItem *>(node_or_edge);
            assert(qtedge && "Every item is either a Qt node or Qt edge");
            qtedge->GetEdge()->SetX(new_x);
            qtedge->GetEdge()->SetY(new_y);
            //node->setPos(QPointF(new_x,new_y));
          }
          done = false;
        }
      }
    );

    if (done) break;
  }
}

void ribi::pvdb::QtPvdbConceptMapWidget::SetExamplesItem(QtPvdbExamplesItem * const item)
{
  assert((item || !item) && "Can be both");
  m_examples_item = item;
}

#ifndef NDEBUG
void ribi::pvdb::QtPvdbConceptMapWidget::Shuffle()
{
  const std::vector<QtPvdbNodeItem*> nodes = Collect<QtPvdbNodeItem>(scene());
  std::for_each(nodes.begin(),nodes.end(),
    [this](QtPvdbNodeItem* qtnode)
    {
      if (!IsCenterNode(qtnode))
      {
        double x = qtnode->pos().x();
        double y = qtnode->pos().y();
        const int i = (std::rand() >> 4) % 4;
        switch(i)
        {
          case 0: x+= 1.0; break;
          case 1: y+= 1.0; break;
          case 2: x+=-1.0; break;
          case 3: y+=-1.0; break;
          default: assert(!"Should not get here");
        }
        assert(QPointF(x,y) != qtnode->pos());
        qtnode->SetPos(x,y);
      }
    }
  );
  scene()->update();
}
#endif

#ifndef NDEBUG
void ribi::pvdb::QtPvdbConceptMapWidget::TestMe(const boost::shared_ptr<const ribi::pvdb::ConceptMap> map) const
{
  {
    std::set<const pvdb::Node*> w;
    const std::vector<boost::shared_ptr<const pvdb::Node> > v = map->GetNodes();
    std::transform(v.begin(),v.end(),std::inserter(w,w.begin()),
      [](const boost::shared_ptr<const pvdb::Node>  ptr)
      {
        return ptr.get();
      }
    );
    assert(v.size() == w.size() && "All nodes must be unique");
  }
  {
    std::set<const pvdb::Edge*> w;
    const std::vector<boost::shared_ptr<const pvdb::Edge> > v = map->GetEdges();
    std::transform(v.begin(),v.end(),std::inserter(w,w.begin()),
      [](const boost::shared_ptr<const pvdb::Edge>  ptr)
      {
        return ptr.get();
      }
    );
    assert(v.size() == w.size() && "All edges must be unique");
  }
  {
    std::set<QtPvdbConceptMapItem*> v;
    const std::vector<QtPvdbNodeItem*> node_concepts = Collect<QtPvdbNodeItem>(scene());
    std::copy(node_concepts.begin(),node_concepts.end(),std::inserter(v,v.begin()));
    const std::vector<QtPvdbEdgeItem*> edge_concepts = Collect<QtPvdbEdgeItem>(scene());
    std::copy(edge_concepts.begin(),edge_concepts.end(),std::inserter(v,v.begin()));
    assert(v.size() == (node_concepts.size() + edge_concepts.size()) && "All Qt nodes must be unique");
  }
  {
    ///Note that the ConceptMap read out again differs from the original,
    ///because the Nodes are placed
    if (!pvdb::ConceptMap::HasSameContent(*GetConceptMap(),*map))
    {
      //OH OH, AN ERROR! HELP ME OUT AND GIMME LOTS OF DEBUG INFO!
      {
        const std::vector<std::string> v
          = pvdb::XmlToPretty(pvdb::ConceptMap::ToXml(map));
        std::clog << "original map:\n";
        std::clog << "\n";
        std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(std::clog,"\n"));
        std::clog << "\n";
      }
      {
        const std::vector<std::string> v
          = pvdb::XmlToPretty(pvdb::ConceptMap::ToXml(GetConceptMap()));
        std::clog << "GetConceptMap():\n";
        std::clog << "\n";
        std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(std::clog,"\n"));
        std::clog << "\n";
      }

      TRACE(pvdb::ConceptMap::ToXml(GetConceptMap()));
      TRACE(pvdb::ConceptMap::ToXml(map));
    }
  }
  assert(pvdb::ConceptMap::HasSameContent(*GetConceptMap(),*map)
    && "The concept map supplied must be homomorphous to the one created in the widget");

}
#endif
