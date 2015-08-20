#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qttesteditconceptmapdialog.h"

#include <cassert>

#include <boost/lexical_cast.hpp>

#include <QKeyEvent>

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

  m_concept_map->SetConceptMap(
    ribi::cmap::ConceptMapFactory().GetHeteromorphousTestConceptMaps().at(15)
  );


  assert(ui->widget->layout());
  ui->widget->layout()->addWidget(m_concept_map.get());
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


