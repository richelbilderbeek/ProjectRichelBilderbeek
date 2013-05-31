#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtpvdbconceptmapwidget.h"

#include <set>

#include <boost/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <QKeyEvent>

#include "qtpvdbitemhighlighter.h"
#include "pvdbconcept.h"
#include "pvdbconceptfactory.h"
#include "pvdbconceptmap.h"
#include "qtpvdbcenternodeitem.h"
#include "pvdbedgefactory.h"
#include "pvdbedge.h"
#include "qtpvdbbrushfactory.h"
#include "pvdbconceptmapfactory.h"
#include "pvdbhelper.h"
#include "pvdbhints.h"
#include "pvdbnode.h"
#include "pvdbnodefactory.h"
#include "qtarrowitem.h"
#include "qtpvdbconcepteditdialog.h"
#include "qtpvdbconceptitem.h"
#include "qtpvdbedgeitem.h"
#include "qtpvdbcenternodeitem.h"
#include "qtpvdbnodeitem.h"
#include "qtpvdbexamplesitem.h"
#include "qtpvdbtoolsitem.h"
#include "qtpvdbnewarrow.h"
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

QtPvdbConceptMapWidget::QtPvdbConceptMapWidget(QWidget* parent)
  : QtKeyboardFriendlyGraphicsView(parent),
    m_examples(new QtPvdbExamplesItem)
{
  //Cannot test this ABC here, its derived classes will test themselves

  this->setScene(new QGraphicsScene(this));
  scene()->addItem(m_examples); //Add the examples so it has a parent

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
}


QtPvdbConceptMapWidget::~QtPvdbConceptMapWidget()
{
  m_examples = nullptr;
}

const std::vector<QtPvdbEdgeItem*> QtPvdbConceptMapWidget::FindEdges(
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

const QtPvdbEdgeItem * QtPvdbConceptMapWidget::FindEdge(
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

const QtPvdbNodeItem * QtPvdbConceptMapWidget::GetCenterNode() const
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

QtPvdbNodeItem* QtPvdbConceptMapWidget::GetItemBelowCursor(const QPointF& pos) const
{
  const QList<QGraphicsItem*> v = this->scene()->items(pos.x(),pos.y(),2.0,2.0);
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

QGraphicsScene* QtPvdbConceptMapWidget::GetScene() const
{
  return this->scene();
}

bool QtPvdbConceptMapWidget::IsCenterNode(const QGraphicsItem* const item)
{
  const QtPvdbNodeItem * const qtnode = dynamic_cast<const QtPvdbNodeItem*>(item);
  return qtnode && !(item->flags() & QGraphicsItem::ItemIsMovable);
}

void QtPvdbConceptMapWidget::keyPressEvent(QKeyEvent *event)
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

bool QtPvdbConceptMapWidget::MustReposition(const std::vector<boost::shared_ptr<const pvdb::Node> >& nodes) const
{
  //If all are at the origin, the nodes must be (re)positioned
  return std::count_if(nodes.begin(),nodes.end(),
    [](const boost::shared_ptr<const pvdb::Node>& node)
    {
      return node->GetX() == 0.0 && node->GetY() == 0.0;
    }
  ) == static_cast<int>(nodes.size());
}

void QtPvdbConceptMapWidget::OnItemRequestsUpdate(const QGraphicsItem* const item)
{
  OnItemRequestUpdateImpl(item);
}

void QtPvdbConceptMapWidget::OnRequestSceneUpdate()
{
  scene()->update();
}

void QtPvdbConceptMapWidget::ReadFromConceptMap(const boost::shared_ptr<pvdb::ConceptMap>& map)
{
  CleanMe();
  assert(map);
  assert(this->scene());
  assert(!map->GetNodes().empty());

  //This std::vector keeps the QtNodes in the same order as the nodes in the concept map
  //You cannot rely on Collect<QtPvdbNodeConcept*>(scene), as this shuffles the order
  std::vector<QtPvdbNodeItem*> qtnodes;

  //The initial count of the items
  const int init_count = scene()->items().count();

  //Add the nodes to the scene
  {
    //Add the main question as the first node
    const boost::shared_ptr<pvdb::Node> node = map->GetNodes()[0];
    QtPvdbNodeItem* const qtnode = new QtPvdbCenterNodeItem(node);
    //Let the center node respond to mouse clicks
    qtnode->m_signal_request_scene_update.connect(
      boost::bind(&QtPvdbConceptMapWidget::OnRequestSceneUpdate,this));
    qtnode->m_signal_item_has_updated.connect(
      boost::bind(&QtPvdbConceptMapWidget::OnItemRequestsUpdate,this,boost::lambda::_1));
    //Add the center node to scene
    this->scene()->addItem(qtnode);
    qtnodes.push_back(qtnode);
    assert(scene()->items().count() == init_count + 1);
    assert(scene()->items().count() == init_count + static_cast<int>(qtnodes.size()));

    //Add the regular nodes to the scene
    const std::vector<boost::shared_ptr<pvdb::Node> >& nodes = map->GetNodes();
    std::for_each(nodes.begin() + 1, //+1 to skip center node
      nodes.end(),
      [this,&qtnodes,init_count](const boost::shared_ptr<pvdb::Node>& node)
      {
        QtPvdbNodeItem * const qtnode = AddNode(node);
        qtnodes.push_back(qtnode);
        assert(scene()->items().count() == init_count + static_cast<int>(qtnodes.size()));
      }
    );

  }
  assert(scene()->items().count() == init_count + static_cast<int>(map->GetNodes().size())
    && "There must as much nodes in the scene as there were in the concept map");

  //Add the Concepts on the Edges
  {
    const std::vector<boost::shared_ptr<pvdb::Edge> >& edges = map->GetEdges();
    std::for_each(edges.begin(),edges.end(),
      [this,qtnodes](const boost::shared_ptr<pvdb::Edge>& edge)
      {
        this->AddEdge(edge,qtnodes);
      }
    );
  }
  assert(scene()->items().count()
    == init_count +static_cast<int>(map->GetNodes().size() + map->GetEdges().size())
    && "There must be as much NodeConcepts and EdgeConcepts in the scene as the number of edges and nodes in the concept map");

  //Put the nodes around the focal question in an initial position
  if (MustReposition(AddConst(map->GetNodes()))) RepositionItems();

  //qtnodes[0]->setFocus();

  #ifndef NDEBUG
  assert(map);
  TestMe(map);
  #endif
}

void QtPvdbConceptMapWidget::RepositionItems()
{
  {
    //The ray of the upcoming circle of nodes, is the larger of
    //(1) half of the diagonal of the focal question (e.g. for short concepts)
    //(2) calculated from the circumference by adding the nodes' length
    const std::vector<QtPvdbNodeItem *> node_concepts_unsorted = Collect<QtPvdbNodeItem>(scene());
    const std::vector<QtPvdbNodeItem *> node_concepts = Sort(node_concepts_unsorted);
    assert(!node_concepts.empty());
    assert(node_concepts[0]);
    const QtPvdbNodeItem * const center_node
      = dynamic_cast<const QtPvdbNodeItem *>(node_concepts[0]);
    assert(center_node);
    assert(center_node->pos().x() > -0.5);
    assert(center_node->pos().x() <  0.5);
    assert(center_node->pos().y() > -0.5);
    assert(center_node->pos().y() <  0.5);

    const double r1
      = 0.5 * pvdb::GetDistance(
        center_node->boundingRect().width(),
        center_node->boundingRect().height());
    const double r3 = 50.0;
    const double r = std::max(r1,r3);
    const int n_nodes = node_concepts.size();
    for (int i = 1; i!=n_nodes; ++i) //+1 to skip center node
    {
      //Added +0 (instead of -1) to n_nodes, to prevent, in a setup with two concepts and
      //one edge, the edge to overlap the central question
      const double angle
        = 2.0 * M_PI * boost::numeric_cast<double>(i)
        / boost::numeric_cast<double>(n_nodes - 1);
      const double x =  std::cos(angle) * r;
      const double y = -std::sin(angle) * r;
      node_concepts[i]->setPos(x,y);
    }
  }

  {
    //Put the edge concepts in the middle of the nodes
    const std::vector<QtPvdbEdgeItem *> edge_concepts = Collect<QtPvdbEdgeItem>(scene());
    std::for_each(edge_concepts.begin(), edge_concepts.end(),
      [](QtPvdbEdgeItem* const edge_concept)
      {
        const QPointF p((edge_concept->GetFrom()->pos() + edge_concept->GetTo()->pos()) / 2.0);
        edge_concept->setPos(p);
      }
    );
  }

  //Put the nodes around the focal question in their improved position
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

    std::vector<QtRoundedTextRectItem*> items;
    std::copy(qtnodes.begin(),qtnodes.end(),std::back_inserter(items));
    assert(IsCenterNode(items[0]));
    std::copy(qtedges.begin(),qtedges.end(),std::back_inserter(items));

    //Move the nodes away from the center
    std::for_each(
      items.begin() + 1, //+1 to skip the center node at [0]
      items.end(),
      [center_node,&done](QtRoundedTextRectItem* const node)
      {
        if (center_node->boundingRect().intersects(
          node->boundingRect().translated(-node->pos())))
        {
          node->setPos(QPointF(
            node->pos().x() < center_node->pos().x() ? node->pos().x()-1 : node->pos().x() + 1,
            node->pos().y() < center_node->pos().y() ? node->pos().y()-1 : node->pos().y() + 1
            )
          );
          done = false;
        }
      }
    );

    if (done) break;
  }
}

void QtPvdbConceptMapWidget::Shuffle()
{
  const std::vector<QtPvdbNodeItem*> nodes = Collect<QtPvdbNodeItem>(scene());
  std::for_each(nodes.begin(),nodes.end(),
    [this](QtPvdbNodeItem* node)
    {
      if (!IsCenterNode(node))
      {
        double x = node->pos().x();
        double y = node->pos().y();
        const int i = (std::rand() >> 4) % 4;
        switch(i)
        {
          case 0: x+= 1.0; break;
          case 1: y+= 1.0; break;
          case 2: x+=-1.0; break;
          case 3: y+=-1.0; break;
          default: assert(!"Should not get here");
        }
        assert(QPointF(x,y) != node->pos());
        node->setPos(x,y);
      }
    }
  );
  scene()->update();
}

const std::vector<QtPvdbNodeItem*> QtPvdbConceptMapWidget::Sort(const std::vector<QtPvdbNodeItem*>& v_original) const
{
  std::vector<QtPvdbNodeItem*> v(v_original);
  assert(!v.empty()
    && "There must be one center node in each scene");
  assert(std::count_if(v.begin(),v.end(),
    [this](const QtPvdbNodeItem* const qtnode)
    {
      return QtPvdbConceptMapWidget::IsCenterNode(qtnode);
    }
  ) == 1 && "There must be one unmovable node, which is the center node");
  auto center_node_iter = std::find_if(v.begin(),v.end(),
    [this](const QtPvdbNodeItem* const qtnode)
    {
      return QtPvdbConceptMapWidget::IsCenterNode(qtnode);
    }
  );
  std::swap(*center_node_iter,v[0]);
  assert(QtPvdbConceptMapWidget::IsCenterNode(v[0])
    && "Focus question must be at index zero");
  return v;
}

#ifndef NDEBUG
void QtPvdbConceptMapWidget::TestMe(const boost::shared_ptr<const pvdb::ConceptMap>& map) const
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
  #ifdef REALLY_USE_DELETELEFTOVERS_FOR_TESTING_784578634075630458630
  //Sure, I miss this test, but otherwise DeleteLeftovers must be moved
  //to this class, which I intend to keep as read-only as possible
  {
    const std::vector<QtPvdbNodeConcept *> node_concepts = Collect<QtPvdbNodeConcept>(scene());
    const std::vector<QtPvdbEdgeConcept *> edge_concepts = Collect<QtPvdbEdgeConcept>(scene());
    const std::vector<QtPvdbArrow *> arrows = Collect<QtPvdbArrow>(scene());

    const int n_arrows = static_cast<int>(arrows.size());
    const int n_edges  = static_cast<int>(edge_concepts.size());
    const int n_nodes  = static_cast<int>(node_concepts.size());
    DeleteLeftovers();
    assert(n_arrows == static_cast<int>(arrows.size())        && "Assume no leftovers");
    assert(n_edges  == static_cast<int>(edge_concepts.size()) && "Assume no leftovers");
    assert(n_nodes  == static_cast<int>(node_concepts.size()) && "Assume no leftovers");
  }
  #endif
  {
    ///Note that the ConceptMap read out again differs from the original,
    ///because the Nodes are placed
    if (!pvdb::ConceptMap::HasSameContent(WriteToConceptMap(),map))
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
          = pvdb::XmlToPretty(pvdb::ConceptMap::ToXml(WriteToConceptMap()));
        std::clog << "WriteToConceptMap():\n";
        std::clog << "\n";
        std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(std::clog,"\n"));
        std::clog << "\n";
      }

      TRACE(pvdb::ConceptMap::ToXml(WriteToConceptMap()));
      TRACE(pvdb::ConceptMap::ToXml(map));
    }
  }
  assert(pvdb::ConceptMap::HasSameContent(WriteToConceptMap(),map)
    && "The concept map supplied must be homomorphous to the one created in the widget");

}
#endif

const boost::shared_ptr<pvdb::ConceptMap> QtPvdbConceptMapWidget::WriteToConceptMap() const
{
  //Get the Nodes
  std::vector<boost::shared_ptr<pvdb::Node> > nodes;

  const std::vector<QtPvdbNodeItem*> qtnodes = Sort(Collect<QtPvdbNodeItem>(scene()));
  {
    assert(IsCenterNode(qtnodes[0]) && "Now the first index must be the unmovable center node");
    std::transform(qtnodes.begin(),qtnodes.end(),
      std::back_inserter(nodes),
      [](const QtPvdbNodeItem* const qtnode)
      {
        assert(qtnode);
        assert(qtnode->GetNode());
        boost::shared_ptr<pvdb::Node> new_node = pvdb::NodeFactory::DeepCopy(qtnode->GetNode());
        assert(new_node);
        assert(IsEqual(*qtnode->GetNode(),*new_node));
        new_node->SetX( qtnode->x() );
        new_node->SetY( qtnode->y() );
        return new_node;
      }
    );
    assert(nodes.size() == qtnodes.size());
  }

  //Get the Edges
  std::vector<boost::shared_ptr<pvdb::Edge> > edges;
  const std::vector<QtPvdbEdgeItem*> qtedges = Collect<QtPvdbEdgeItem>(scene());
  std::for_each(qtedges.begin(),qtedges.end(),
    [this,&edges,qtnodes](QtPvdbEdgeItem* const qtedge)
    {
      assert(qtedge);
      const boost::shared_ptr<pvdb::Concept> concept = qtedge->GetConcept(); //FIX? 2012-12-31
      //const boost::shared_ptr<pvdb::Concept> concept(new pvdb::Concept(*qtedge->GetConcept())); //BUG? 2012-12-31
      const auto from_iter = std::find(qtnodes.begin(),qtnodes.end(),qtedge->GetFrom());
      assert(from_iter != qtnodes.end());
      const int from_index = std::distance(qtnodes.begin(),from_iter);
      assert(from_index >= 0 && from_index < static_cast<int>(qtnodes.size()));
      //const QtPvdbNodeItem* const from = qtnodes[from_index];
      const auto to_iter = std::find(qtnodes.begin(),qtnodes.end(),qtedge->GetTo());
      assert(to_iter != qtnodes.end());
      const int to_index = std::distance(qtnodes.begin(),to_iter);
      assert(to_index >= 0 && to_index < static_cast<int>(qtnodes.size()));
      const bool tail_arrow = qtedge->GetEdge()->HasTailArrow();
      const bool head_arrow = qtedge->GetEdge()->HasHeadArrow();

      boost::shared_ptr<pvdb::Edge> edge(
        pvdb::EdgeFactory::Create(
          concept,
          qtedge->pos().x(),
          qtedge->pos().y(),
          from_index,
          tail_arrow,
          to_index,
          head_arrow));
      edges.push_back(edge);
    }
  );

  const boost::shared_ptr<pvdb::ConceptMap> concept_map(
    pvdb::ConceptMapFactory::Create(nodes,edges));
  return concept_map;
}
