#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qttestrateconceptmapdialog.h"

#include <cassert>
#include <cstdlib>

#include <boost/lexical_cast.hpp>

#include <QKeyEvent>

#include "conceptmapcompetency.h"
#include "conceptmapconcept.h"
#include "conceptmapfactory.h"
#include "conceptmap.h"
#include "conceptmapexample.h"
#include "conceptmapexample.h"
#include "conceptmapexamples.h"
#include "conceptmapexamples.h"
#include "conceptmapnodefactory.h"
#include "conceptmapnode.h"
#include "qtconceptmapbrushfactory.h"
#include "qtrateconceptmap.h"
#include "qtconceptmapdisplaystrategy.h"
#include "qtconceptmapdisplaystrategy.h"
#include "qtconceptmapeditstrategy.h"
#include "qtconceptmapnode.h"
#include "qtconceptmapratestrategy.h"
#include "trace.h"
#include "ui_qttestrateconceptmapdialog.h"
#pragma GCC diagnostic pop


ribi::cmap::QtTestRateConceptMapDialog::QtTestRateConceptMapDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtTestRateConceptMapDialog),
  m_concept_map(
    new QtRateConceptMap(
      ribi::cmap::ConceptMapFactory::GetHeteromorphousTestConceptMaps().at(15)
    )
  )

{
  ui->setupUi(this);
  #ifndef NDEBUG
  Test();
  #endif
  assert(ui->widget->layout());
  ui->widget->layout()->addWidget(m_concept_map.get());
}

ribi::cmap::QtTestRateConceptMapDialog::~QtTestRateConceptMapDialog() noexcept
{
  delete ui;
}

void ribi::cmap::QtTestRateConceptMapDialog::DoSomethingRandom()
{

  const QList<QGraphicsItem *> v = m_concept_map->GetScene()->items();
  std::for_each(v.begin(),v.end(),
    [](QGraphicsItem * const item)
    {
      if (QtNode* const qtitem = dynamic_cast<QtNode*>(item))
      {
        assert(qtitem->GetConcept());
        assert(!qtitem->GetConcept()->GetName().empty());
        assert(qtitem->GetConcept()->GetExamples());
        const int rating_complexity = -1 + (std::rand() % 4);
        assert(rating_complexity >= -1);
        assert(rating_complexity <=  2);
        qtitem->GetConcept()->SetRatingComplexity(rating_complexity);
        qtitem->GetConcept()->SetRatingConcreteness(-1 + (std::rand() % 4));
        qtitem->GetConcept()->SetRatingSpecificity(-1 + (std::rand() % 4));
        const auto v = qtitem->GetConcept()->GetExamples()->Get();
        std::for_each(v.begin(),v.end(),
          [](const boost::shared_ptr<cmap::Example>& example)
          {
            if ( (std::rand() >> 4) % 2)
            {
              const std::vector<cmap::Competency> w = cmap::GetAllCompetencies();
              example->SetCompetency(w[ std::rand() % w.size() ]);
            }
            else
            {
              example->SetCompetency(cmap::Competency::uninitialized);
            }
          }
        );

        qtitem->update();
      }
    }
  );
  m_concept_map->GetScene()->update();
}

void ribi::cmap::QtTestRateConceptMapDialog::keyPressEvent(QKeyEvent *e)
{
  if (e->key() == Qt::Key_Escape) { close(); return; }
  if (e->modifiers() & Qt::AltModifier && e->key() == Qt::Key_1)
  {
    DoSomethingRandom();
    return;
  }
}

#ifndef NDEBUG
void ribi::cmap::QtTestRateConceptMapDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("ribi::cmap::QtTestRateConceptMapDialog::Test started");
  //Doing random stuff
  {
    QtTestRateConceptMapDialog d;
    for (int i=0; i!=100; ++i) d.DoSomethingRandom();
  }
  TRACE("ribi::cmap::QtTestRateConceptMapDialog::Test finished successfully");
}
#endif
