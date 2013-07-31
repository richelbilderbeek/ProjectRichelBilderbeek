#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtpvdbclusterwidget.h"

#include <cassert>
#include <vector>

#ifdef COMPILER_SUPPORTS_THREADS_20130507
#include <thread>
#endif

#include "pvdbcluster.h"
#include "pvdbconcept.h"
#include "pvdbconceptfactory.h"
#include "pvdbexample.h"
#include "pvdbclusterfactory.h"
#include "pvdbexamplefactory.h"
#include "pvdbexamples.h"
#include "pvdbexamplesfactory.h"
#include "qtpvdbcompetency.h"
#include "trace.h"

///QTreeWidgetItem with the only function of storing a pvdb::Competency additionally
struct QtPvdbTreeWidgetItem : public QTreeWidgetItem
{
  QtPvdbTreeWidgetItem(
    const pvdb::Competency competency,
    const bool is_complex,
    const int rating_complexity,
    const int rating_concreteness,
    const int rating_specifity)
    : QTreeWidgetItem(0),
      m_competency(competency),
      m_is_complex(is_complex),
      m_rating_complexity(rating_complexity),
      m_rating_concreteness(rating_concreteness),
      m_rating_specifity(rating_specifity)
  {
    assert(rating_complexity >= -1);
    assert(rating_complexity <=  2);
  }
  const pvdb::Competency m_competency;
  const bool m_is_complex;
  const int m_rating_complexity;
  const int m_rating_concreteness;
  const int m_rating_specifity;
};

QtPvdbClusterWidget::QtPvdbClusterWidget(
  boost::shared_ptr<pvdb::Cluster> cluster,
  QWidget* parent)
  : QTreeWidget(parent),
    m_cluster(cluster)
{
  #ifndef NDEBUG
  Test();
  assert(m_cluster && "Must have a cluster to work on");
  #endif

  //Hide the header
  this->setHeaderHidden(true);

  //Let the row colors alternate
  this->setAlternatingRowColors(true);

  //Allow items to be drag and dropped inside of the widget
  this->setDragDropMode(QAbstractItemView::InternalMove);

  //Let the drag and drop be animated
  this->setAnimated(true);

  this->BuildCluster();

  QObject::connect(
    this,
    SIGNAL(itemChanged(QTreeWidgetItem*,int)),
    this,
    SLOT(RemoveEmptyItem(QTreeWidgetItem*,int)));
}

void QtPvdbClusterWidget::Add(const std::string& text)
{
  QtPvdbTreeWidgetItem * const item = new QtPvdbTreeWidgetItem(
    pvdb::Competency::uninitialized,true,-1,-1,-1);
  item->setText(0,text.c_str());
  this->addTopLevelItem(item);
}

void QtPvdbClusterWidget::DoRandomStuff()
{
  QtPvdbTreeWidgetItem * const top = new QtPvdbTreeWidgetItem(
    pvdb::Competency::misc,true,0,1,2);
  top->setText(0,"SOMETEXT");
  QtPvdbTreeWidgetItem * const child_item = new QtPvdbTreeWidgetItem(
    pvdb::Competency::uninitialized,true,-1,0,2);
  child_item->setText(0,"SOMETEXT");
  top->addChild(child_item);
  child_item->setFlags(
      Qt::ItemIsSelectable
    | Qt::ItemIsEnabled
    | Qt::ItemIsEditable
    | Qt::ItemIsDragEnabled);
  this->addTopLevelItem(top);
  top->setExpanded(true);
  top->setFlags(
        Qt::ItemIsSelectable
      | Qt::ItemIsEnabled
      | Qt::ItemIsEditable
      | Qt::ItemIsDragEnabled
      | Qt::ItemIsDropEnabled);
}


void QtPvdbClusterWidget::dropEvent(QDropEvent *event)
{
  QTreeWidget::dropEvent(event);
  //Fix the possibility of dropping a tree with depth three
  while (1)
  {
    bool done = true;
    const int n_top = this->topLevelItemCount();
    for (int i=0; i!=n_top; ++i)
    {
      assert(i < this->topLevelItemCount());
      QTreeWidgetItem * const top = this->topLevelItem(i); //FIX
      //QtPvdbTreeWidgetItem * const top = dynamic_cast<QtPvdbTreeWidgetItem *>(this->topLevelItem(i));  //BUG 2012-12-30
      assert(top);
      const int n_child = top->childCount();
      for (int j=0; j!=n_child; ++j)
      {
        assert(j < top->childCount());
        //Check if top->child(j) has children
        if (top->child(j)->childCount() > 0)
        {
          //Move top->child(j) to top
          QTreeWidgetItem * const clone = top->child(j)->clone(); //FIX
          //QtPvdbTreeWidgetItem * const clone = dynamic_cast<QtPvdbTreeWidgetItem *>(top->child(j)->clone()); //BUG 2012-12-29
          assert(clone);
          this->addTopLevelItem(clone);
          top->removeChild(top->child(j));
          done = false;
          j = n_child - 1;
          i = n_top - 1;
        }
      }
    }
    //End the while loop if no parents were moved
    if (done) break;
  }
  #ifndef NDEBUG
  //Check that there are no items at depth three
  {
    const int n_top = this->topLevelItemCount();
    for (int i=0; i!=n_top; ++i)
    {
      QTreeWidgetItem * const top = this->topLevelItem(i); //FIX
      //QtPvdbTreeWidgetItem * const top = dynamic_cast<QtPvdbTreeWidgetItem *>(this->topLevelItem(i)); //BUG 2012-12-30
      assert(top);

      const int n_child = top->childCount();
      for (int j=0; j!=n_child; ++j)
      {
        if (top->child(j)->childCount() > 0)
        {
          assert(!"Should not find a child item within a child item");
        }
      }
    }
  }
  #endif
  //Process all items
  {
    const int n_top = this->topLevelItemCount();
    for (int i=0; i!=n_top; ++i)
    {
      QTreeWidgetItem * const top = this->topLevelItem(i); //FIX
      //QtPvdbTreeWidgetItem * const top = dynamic_cast<QtPvdbTreeWidgetItem *>(this->topLevelItem(i)); //BUG 2012-12-30
      assert(top);

      //Let all top items auto-expand
      top->setExpanded(true);

      //Allow dropping on top-level items
      top->setFlags(
            Qt::ItemIsSelectable
          | Qt::ItemIsEnabled
          | Qt::ItemIsEditable
          | Qt::ItemIsDragEnabled
          | Qt::ItemIsDropEnabled);
      assert(GetDepth(top)==0);
      const int n_child = top->childCount();
      for (int j=0; j!=n_child; ++j)
      {
          assert(GetDepth(top->child(j))==1);
          //Disallow dropping on non-top-level items
          top->child(j)->setFlags(
                Qt::ItemIsSelectable
            | Qt::ItemIsEnabled
            | Qt::ItemIsEditable
            | Qt::ItemIsDragEnabled);
      }
    }
  }
}

const boost::shared_ptr<pvdb::Cluster> QtPvdbClusterWidget::GetCluster()
{
  WriteToCluster();
  return m_cluster;
}

int QtPvdbClusterWidget::GetDepth(const QTreeWidgetItem * const item) const
{
  assert(item);
  int depth = 0;
  const QTreeWidgetItem * copy = item->parent();
  while(copy)
  {
    ++depth;
    copy = copy->parent();
  }
  return depth;
}

void QtPvdbClusterWidget::keyPressEvent(QKeyEvent *event)
{
  //Without this seemingly useless member function,
  //the widget cannot be edited
  QTreeWidget::keyPressEvent(event);
}

void QtPvdbClusterWidget::BuildCluster()
{
  assert(m_cluster);
  assert(this->isHeaderHidden());
  assert(this->alternatingRowColors());
  assert(this->dragDropMode() == QAbstractItemView::InternalMove);
  assert(this->isAnimated());

  this->clear();
  assert(m_cluster);
  const std::vector<boost::shared_ptr<pvdb::Concept> >& v = m_cluster->Get();
  std::for_each(v.begin(),v.end(),
    [this](const boost::shared_ptr<const pvdb::Concept>& concept)
    {
      assert(concept);
      assert(concept->GetRatingComplexity() >= -1);
      assert(concept->GetRatingComplexity() <=  2);
      QtPvdbTreeWidgetItem * const top
        = new QtPvdbTreeWidgetItem(
          pvdb::Competency::uninitialized, //A concept is not classified in competencies
          concept->GetIsComplex(),
          concept->GetRatingComplexity(),
          concept->GetRatingConcreteness(),
          concept->GetRatingSpecificity()
          );
      top->setText(0,concept->GetName().c_str());
      const std::vector<boost::shared_ptr<const pvdb::Example> > examples = concept->GetExamples()->Get();
      std::for_each(examples.begin(),examples.end(),
        [top,this](const boost::shared_ptr<const pvdb::Example>& example)
        {
          QtPvdbTreeWidgetItem * const child_item
            = new QtPvdbTreeWidgetItem(
              example->GetCompetency(),
              example->GetIsComplex(),
              -1, //An example is not rated for complexity   //FIX 2013-02-03
              -1, //An example is not rated for concreteness //FIX 2013-02-03
              -1  //An example is not rated for specifity    //FIX 2013-02-03
            );
          child_item->setText(0,example->GetText().c_str());
          top->addChild(child_item);
          child_item->setFlags(
              Qt::ItemIsSelectable
            | Qt::ItemIsEnabled
            | Qt::ItemIsEditable
            | Qt::ItemIsDragEnabled);
        }
      );
      this->addTopLevelItem(top);
      top->setExpanded(true);
      top->setFlags(
            Qt::ItemIsSelectable
          | Qt::ItemIsEnabled
          | Qt::ItemIsEditable
          | Qt::ItemIsDragEnabled
          | Qt::ItemIsDropEnabled);
    }
  );
}

void QtPvdbClusterWidget::RemoveEmptyItem(QTreeWidgetItem* item,int col)
{

  if (item->text(col).isEmpty())
  {
    delete item;
    this->update();
  }
}

#ifndef NDEBUG
void QtPvdbClusterWidget::Test()
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
  TRACE("Started QtPvdbClusterWidget::Test");
  {
    //const std::vector<boost::shared_ptr<pvdb::Cluster> > v = pvdb::ClusterFactory::GetTests();
    for (const boost::shared_ptr<pvdb::Cluster>& c: pvdb::ClusterFactory::GetTests())
      {
        if (!c) continue;
        assert(c);
        QtPvdbClusterWidget w(c);
        assert(w.topLevelItemCount() == static_cast<int>(c->Get().size()));
        const boost::shared_ptr<pvdb::Cluster> d = pvdb::ClusterFactory::DeepCopy(w.GetCluster());
        assert(c != d);
        assert(IsEqual(*c,*d));
        QtPvdbTreeWidgetItem * const item = new QtPvdbTreeWidgetItem(
          pvdb::Competency::misc,true,0,1,2);
        item->setText(0,QString("An extra line"));
        w.addTopLevelItem(item);
        assert(w.topLevelItemCount() == static_cast<int>(c->Get().size()) + 1);
        const boost::shared_ptr<pvdb::Cluster> e = w.GetCluster();
        assert(c == e);
        assert(c != d);
        assert(!IsEqual(*c,*d));
        assert( IsEqual(*c,*e));
        assert(!IsEqual(*d,*e));
      }
    //);
  }
  TRACE("QtPvdbClusterWidget::Test completed successfully");
  #ifdef COMPILER_SUPPORTS_THREADS_20130507
    }
  );
  t.detach();
  #endif
}
#endif

void QtPvdbClusterWidget::WriteToCluster()
{
  std::vector<boost::shared_ptr<pvdb::Concept> > concepts;
  const int n_top = this->topLevelItemCount();
  for (int i=0; i!=n_top; ++i)
  {
    QTreeWidgetItem * const top = this->topLevelItem(i); //FIX 2012-12-30
    //QtPvdbTreeWidgetItem * const top = dynamic_cast<QtPvdbTreeWidgetItem *>(this->topLevelItem(i)); //BUG 2012-12-30
    assert(top);
    const std::string name = top->text(0).toStdString();
    std::vector<boost::shared_ptr<pvdb::Example> > examples;

    const int n_child = top->childCount();
    for (int j=0; j!=n_child; ++j)
    {
      const QtPvdbTreeWidgetItem * const pvdb_item
        = dynamic_cast<QtPvdbTreeWidgetItem *>(top->child(j));
      const pvdb::Competency competency = pvdb_item ? pvdb_item->m_competency : pvdb::Competency::uninitialized;
      assert(GetDepth(top->child(j))==1);
      boost::shared_ptr<pvdb::Example> p(
        pvdb::ExampleFactory::Create(
          top->child(j)->text(0).toStdString(),
          competency
        )
      );
      examples.push_back(p);
    }

    QtPvdbTreeWidgetItem * const pvdb_top = dynamic_cast<QtPvdbTreeWidgetItem *>(this->topLevelItem(i)); //FIX 2012-12-30

    concepts.push_back(
      pvdb::ConceptFactory::Create(
        name,
        pvdb::ExamplesFactory::Create(examples),
        pvdb_top ? pvdb_top->m_is_complex : true,
        pvdb_top ? pvdb_top->m_rating_complexity : -1,
        pvdb_top ? pvdb_top->m_rating_concreteness : -1,
        pvdb_top ? pvdb_top->m_rating_specifity : -1
      )
    );
    assert(concepts.back());
  }

  m_cluster->SetConcepts(concepts);
  assert(m_cluster);
  assert(n_top == static_cast<int>(m_cluster->Get().size())
    && "As much top-level items in a QtClusterWidget as Concepts in a Cluster");
}
