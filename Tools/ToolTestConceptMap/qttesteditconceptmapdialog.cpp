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
#include <QUndoView>

#include "conceptmapconcept.h"
#include "conceptmapfactory.h"
#include "conceptmap.h"
#include "conceptmapexample.h"
#include "conceptmapnodefactory.h"
#include "conceptmapnode.h"
#include "qtconceptmapbrushfactory.h"
#include "qtconceptmapexamplesitem.h"
#include "qtconceptmaptoolsitem.h"
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
  m_conceptmap(new QtConceptMap)

{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);



  //Create an empty concept map
  m_conceptmap->SetConceptMap(
    ribi::cmap::ConceptMapFactory().GetHeteromorphousTestConceptMaps().at(0)
  );
  assert(ui->widget->layout());
  ui->widget->layout()->addWidget(m_conceptmap.get());

  {
    QUndoView * const view{new QUndoView};
    view->setStack(&m_conceptmap->GetConceptMap()->GetUndo());
    assert(ui->widget_menu->layout());
    ui->widget_menu->layout()->addWidget(view);
  }
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

  const QList<QGraphicsItem *> v = m_conceptmap->GetScene()->items();
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
  m_conceptmap->GetScene()->update();
}


void ribi::cmap::QtTestEditConceptMapDialog::OnCheck()
{
  std::stringstream s;
  s
    << "m_conceptmap \n"
    << "  ->GetScene()->items().size(): "
    << m_conceptmap->GetScene()->items().size() << '\n'
    << "  (which includes m_conceptmap->m_examples: " << (m_conceptmap->GetQtExamplesItem()->scene() ? "yes" : "no") << ")\n"
    << "  (which includes m_conceptmap->m_tools: " << (m_conceptmap->GetQtToolItem()->scene() ? "yes" : "no") << ")\n"
    << "  ->GetConceptMap()->GetNodes().size(): "
    << m_conceptmap->GetConceptMap()->GetNodes().size() << '\n'
    << "  ->GetConceptMap()->GetEdges().size(): "
    << m_conceptmap->GetConceptMap()->GetEdges().size() << '\n'
    << "  ->GetScene()->selectedItems().size(): "
    << m_conceptmap->GetScene()->selectedItems().size() << '\n'
    << "  ->GetConceptMap()->GetSelectedNodes().size(): "
    << m_conceptmap->GetConceptMap()->GetSelectedNodes().size() << '\n'
    << "  ->GetConceptMap()->GetSelectedEdges().size(): "
    << m_conceptmap->GetConceptMap()->GetSelectedEdges().size() << '\n'
  ;
  const auto qtnodes = m_conceptmap->GetQtNodes();
  const int n_qtnodes{static_cast<int>(qtnodes.size())};
  s << "# QtNodes: " << n_qtnodes << '\n';
  for (int i=0; i!=n_qtnodes; ++i)
  {
    const auto qtnode = qtnodes[i];
    s << "[" << i << "] " << qtnode->GetNode()->GetConcept()->GetName() << ": "  << qtnode->isSelected() << '\n';
  }
  const auto qtedges = m_conceptmap->GetQtEdges();
  const int n_qtedges{static_cast<int>(qtedges.size())};
  s << "# QtEdges: " << n_qtedges << '\n';
  for (int i=0; i!=n_qtedges; ++i)
  {
    s << "[" << i << "] " << qtedges[i]->isSelected() << '\n';
  }
  s << "Focus item: ";
  if (m_conceptmap->GetScene()->focusItem())
  {
    if (QtNode* const qtnode = dynamic_cast<QtNode*>(m_conceptmap->GetScene()->focusItem())) { s << qtnode->GetNode()->GetConcept()->GetName(); }
    if (QtEdge* const qtedge = dynamic_cast<QtEdge*>(m_conceptmap->GetScene()->focusItem())) { s << qtedge->GetQtNode()->GetNode()->GetConcept()->GetName(); }
  }
  else { s << "(none)";}
  s << '\n';

  ui->label_nodes_selected->setText(s.str().c_str());
}
