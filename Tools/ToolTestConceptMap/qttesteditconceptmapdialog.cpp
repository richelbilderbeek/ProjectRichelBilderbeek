#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qttesteditconceptmapdialog.h"

#include <cassert>
#include <sstream>

#include <boost/lexical_cast.hpp>

#include <QKeyEvent>
#include <QTimer>

#include "conceptmapconcept.h"
#include "conceptmapfactory.h"
#include "conceptmap.h"
#include "conceptmapexample.h"
#include "conceptmapnodefactory.h"
#include "conceptmapnode.h"
#include "qtconceptmapbrushfactory.h"

#include "conceptmapexamplesfactory.h"
#include "qtconceptmapdisplaystrategy.h"
#include "qtconceptmapqtedge.h"
#include "qtconceptmapeditstrategy.h"
#include "qtconceptmapqtnode.h"
#include "qtconceptmapratestrategy.h"
#include "qtconceptmap.h"
#include "testtimer.h"
#include "trace.h"
#include "ui_qttesteditconceptmapdialog.h"
#pragma GCC diagnostic pop


ribi::cmap::QtTestEditConceptMapDialog::QtTestEditConceptMapDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtTestEditConceptMapDialog),
  m_concept_map(new QtConceptMap)

{
  ui->setupUi(this);
  #ifndef NDEBUG
  Test();
  #endif

  //Create an empty concept map
  m_concept_map->SetConceptMap(
    ribi::cmap::ConceptMapFactory().GetHeteromorphousTestConceptMaps().at(0)
  );


  assert(ui->widget->layout());
  ui->widget->layout()->addWidget(m_concept_map.get());

  {
    QTimer * const timer{new QTimer(this)};
    connect(timer,SIGNAL(timeout()),this,SLOT(OnCheck()));
    timer->setInterval(100);
    timer->start();
  }
}

ribi::cmap::QtTestEditConceptMapDialog::~QtTestEditConceptMapDialog() noexcept
{
  delete ui;
}

void ribi::cmap::QtTestEditConceptMapDialog::keyPressEvent(QKeyEvent *event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
  if (event->key() == Qt::Key_1
     && event->modifiers() & Qt::AltModifier)
  {
    DoSomethingRandom();
  }
}

#ifndef NDEBUG
void ribi::cmap::QtTestEditConceptMapDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  {
    QtTestEditConceptMapDialog();
  }
  const ribi::TestTimer test_timer(__func__,__FILE__,1.0);
  QtTestEditConceptMapDialog d;
  d.DoSomethingRandom();
}
#endif

void ribi::cmap::QtTestEditConceptMapDialog::DoSomethingRandom()
{

  const QList<QGraphicsItem *> v = m_concept_map->GetScene()->items();
  std::for_each(v.begin(),v.end(),
    [](QGraphicsItem * const item)
    {
      if (QtNode* const qtitem = dynamic_cast<QtNode*>(item))
      {
        assert(qtitem->GetNode());
        assert(!qtitem->GetNode()->GetConcept()->GetName().empty());
        assert(qtitem->GetNode()->GetConcept()->GetExamples());
        qtitem->GetNode()->GetConcept()->SetName(qtitem->GetNode()->GetConcept()->GetName() + "N");
        const std::vector<boost::shared_ptr<Examples> > v = ExamplesFactory().GetTests();
        qtitem->GetNode()->GetConcept()->SetExamples(v [ std::rand() % v.size() ] );
        qtitem->update();
      }
      if (QtEdge* const qtitem = dynamic_cast<QtEdge*>(item))
      {
        assert(qtitem->GetQtNode());
        assert( (!qtitem->GetQtNode()->GetNode()->GetConcept()->GetName().empty() || qtitem->GetQtNode()->GetNode()->GetConcept()->GetName().empty())
          && "An item can contain no text: when connected to the center node");
        assert(qtitem->GetQtNode()->GetNode()->GetConcept()->GetExamples());
        qtitem->GetQtNode()->GetNode()->GetConcept()->SetName(qtitem->GetQtNode()->GetNode()->GetConcept()->GetName() + "E");
        const std::vector<boost::shared_ptr<Examples> > v = ExamplesFactory().GetTests();
        qtitem->GetQtNode()->GetNode()->GetConcept()->SetExamples(v [ std::rand() % v.size() ] );
        qtitem->update();
      }
    }
  );
  m_concept_map->GetScene()->update();
}


void ribi::cmap::QtTestEditConceptMapDialog::OnCheck()
{
  std::stringstream s;
  s
    << "m_concept_map \n"
    << "  ->GetScene()->selectedItems().size(): "
    << m_concept_map->GetScene()->selectedItems().size() << '\n'
    << "  ->GetConceptMap()->GetSelectedNodes().size(): "
    << m_concept_map->GetConceptMap()->GetSelectedNodes().size() << '\n'
    << "  ->GetConceptMap()->GetSelectedEdges().size(): "
    << m_concept_map->GetConceptMap()->GetSelectedEdges().size() << '\n'
  ;
  const auto qtnodes = m_concept_map->GetQtNodes();
  const int n_qtnodes{static_cast<int>(qtnodes.size())};
  s << "# QtNodes: " << n_qtnodes << '\n';
  for (int i=0; i!=n_qtnodes; ++i)
  {
    const auto qtnode = qtnodes[i];
    s << "[" << i << "] " << qtnode->GetNode()->GetConcept()->GetName() << ": "  << qtnode->isSelected() << '\n';
  }
  const auto qtedges = m_concept_map->GetQtEdges();
  const int n_qtedges{static_cast<int>(qtedges.size())};
  s << "# QtEdges: " << n_qtedges << '\n';
  for (int i=0; i!=n_qtedges; ++i)
  {
    s << "[" << i << "] " << qtedges[i]->isSelected() << '\n';
  }
  s << "Focus item: ";
  if (m_concept_map->GetScene()->focusItem())
  {
    if (QtNode* const qtnode = dynamic_cast<QtNode*>(m_concept_map->GetScene()->focusItem())) { s << qtnode->GetNode()->GetConcept()->GetName(); }
    if (QtEdge* const qtedge = dynamic_cast<QtEdge*>(m_concept_map->GetScene()->focusItem())) { s << qtedge->GetQtNode()->GetNode()->GetConcept()->GetName(); }
  }
  else { s << "(none)";}
  s << '\n';

  ui->label_nodes_selected->setText(s.str().c_str());
}
