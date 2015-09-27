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
#include "qtpvdbclusterwidget.h"

#include <cassert>
#include <vector>

#include "conceptmapconceptfactory.h"
#include "conceptmapconcept.h"
#include "conceptmapexamplefactory.h"
#include "conceptmapexample.h"
#include "conceptmapexamplesfactory.h"
#include "conceptmapexamples.h"
#include "pvdbclusterfactory.h"
#include "pvdbcluster.h"
#include "qtconceptmapcompetency.h"
#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

///QTreeWidgetItem with the only function of storing a cmap::Competency additionally
struct QtPvdbTreeWidgetItem : public QTreeWidgetItem
{
  QtPvdbTreeWidgetItem(
    const ribi::cmap::Competency competency,
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
  const ribi::cmap::Competency m_competency;
  const bool m_is_complex;
  const int m_rating_complexity;
  const int m_rating_concreteness;
  const int m_rating_specifity;
};

ribi::pvdb::QtPvdbClusterWidget::QtPvdbClusterWidget(
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

  // Allow word-wrapping
  this->setWordWrap(true);
}

void ribi::pvdb::QtPvdbClusterWidget::Add(const std::string& text)
{
  QtPvdbTreeWidgetItem * const item = new QtPvdbTreeWidgetItem(
    cmap::Competency::uninitialized,true,-1,-1,-1);
  item->setText(0,text.c_str());
  this->addTopLevelItem(item);
  SetCorrectFlags();
}

void ribi::pvdb::QtPvdbClusterWidget::DoRandomStuff()
{
  QtPvdbTreeWidgetItem * const top = new QtPvdbTreeWidgetItem(
    cmap::Competency::misc,true,0,1,2);
  top->setText(0,"SOMETEXT");
  QtPvdbTreeWidgetItem * const child_item = new QtPvdbTreeWidgetItem(
    cmap::Competency::uninitialized,true,-1,0,2);
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


void ribi::pvdb::QtPvdbClusterWidget::dropEvent(QDropEvent *event)
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
  SetCorrectFlags();
}

//Process all items
void ribi::pvdb::QtPvdbClusterWidget::SetCorrectFlags() noexcept
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

const boost::shared_ptr<ribi::pvdb::Cluster> ribi::pvdb::QtPvdbClusterWidget::GetCluster()
{
  WriteToCluster();
  return m_cluster;
}

int ribi::pvdb::QtPvdbClusterWidget::GetDepth(const QTreeWidgetItem * const item) const
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

void ribi::pvdb::QtPvdbClusterWidget::keyPressEvent(QKeyEvent *event)
{
  //Without this seemingly useless member function,
  //the widget cannot be edited
  QTreeWidget::keyPressEvent(event);
}

void ribi::pvdb::QtPvdbClusterWidget::BuildCluster()
{
  assert(m_cluster);
  assert(this->isHeaderHidden());
  assert(this->alternatingRowColors());
  assert(this->dragDropMode() == QAbstractItemView::InternalMove);
  assert(this->isAnimated());

  this->clear();
  assert(m_cluster);
  const std::vector<boost::shared_ptr<ribi::cmap::Concept> >& v = m_cluster->Get();
  std::for_each(v.begin(),v.end(),
    [this](const boost::shared_ptr<const ribi::cmap::Concept>& concept)
    {
      assert(concept);
      assert(concept->GetRatingComplexity() >= -1);
      assert(concept->GetRatingComplexity() <=  2);
      QtPvdbTreeWidgetItem * const top
        = new QtPvdbTreeWidgetItem(
          cmap::Competency::uninitialized, //A concept is not classified in competencies
          concept->GetIsComplex(),
          concept->GetRatingComplexity(),
          concept->GetRatingConcreteness(),
          concept->GetRatingSpecificity()
          );
      top->setText(0,concept->GetName().c_str());
      const std::vector<boost::shared_ptr<const cmap::Example> > examples = concept->GetExamples()->Get();
      std::for_each(examples.begin(),examples.end(),
        [top,this](const boost::shared_ptr<const cmap::Example>& example)
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

void ribi::pvdb::QtPvdbClusterWidget::RemoveEmptyItem(QTreeWidgetItem* item,int col)
{

  if (item->text(col).isEmpty())
  {
    delete item;
    this->update();
  }
}

#ifndef NDEBUG
void ribi::pvdb::QtPvdbClusterWidget::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  {
    for (const boost::shared_ptr<pvdb::Cluster>& c: pvdb::ClusterFactory().GetTests())
    {
      if (!c) continue;
      assert(c);
      QtPvdbClusterWidget w(c);
      assert(w.topLevelItemCount() == static_cast<int>(c->Get().size()));
      const boost::shared_ptr<pvdb::Cluster> d = pvdb::ClusterFactory().DeepCopy(w.GetCluster());
      assert(c != d);
      assert(operator==(*c,*d));
      QtPvdbTreeWidgetItem * const item = new QtPvdbTreeWidgetItem(
        cmap::Competency::misc,true,0,1,2);
      item->setText(0,QString("An extra line"));
      w.addTopLevelItem(item);
      assert(w.topLevelItemCount() == static_cast<int>(c->Get().size()) + 1);
      const boost::shared_ptr<pvdb::Cluster> e = w.GetCluster();
      assert(c == e);
      assert(c != d);
      assert(!operator==(*c,*d));
      assert( operator==(*c,*e));
      assert(!operator==(*d,*e));
    }
  }
}
#endif

void ribi::pvdb::QtPvdbClusterWidget::WriteToCluster()
{
  std::vector<boost::shared_ptr<ribi::cmap::Concept> > concepts;
  const int n_top = this->topLevelItemCount();
  for (int i=0; i!=n_top; ++i)
  {
    QTreeWidgetItem * const top = this->topLevelItem(i); //FIX 2012-12-30
    //QtPvdbTreeWidgetItem * const top = dynamic_cast<QtPvdbTreeWidgetItem *>(this->topLevelItem(i)); //BUG 2012-12-30
    assert(top);
    const std::string name = top->text(0).toStdString();
    std::vector<boost::shared_ptr<cmap::Example> > examples;

    const int n_child = top->childCount();
    for (int j=0; j!=n_child; ++j)
    {
      const QtPvdbTreeWidgetItem * const pvdb_item
        = dynamic_cast<QtPvdbTreeWidgetItem *>(top->child(j));
      const cmap::Competency competency = pvdb_item ? pvdb_item->m_competency : cmap::Competency::uninitialized;
      assert(GetDepth(top->child(j))==1);
      boost::shared_ptr<cmap::Example> p(
        ribi::cmap::ExampleFactory().Create(
          top->child(j)->text(0).toStdString(),
          competency
        )
      );
      examples.push_back(p);
    }

    QtPvdbTreeWidgetItem * const pvdb_top = dynamic_cast<QtPvdbTreeWidgetItem *>(this->topLevelItem(i)); //FIX 2012-12-30
    using namespace cmap;

    concepts.push_back(
      ConceptFactory().Create(
        name,
        cmap::ExamplesFactory().Create(examples),
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
