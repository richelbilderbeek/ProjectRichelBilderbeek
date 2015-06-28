#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qttestdisplayconceptmapdialog.h"

#include <cassert>
#include <cstdlib>

#include <boost/lexical_cast.hpp>

#include <QKeyEvent>

#include "conceptmapcompetencies.h"
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
#include "qtdisplayconceptmap.h"
#include "qtconceptmapdisplaystrategy.h"
#include "qtconceptmapdisplaystrategy.h"
#include "qtconceptmapeditstrategy.h"
#include "qtconceptmapqtnode.h"
#include "qtconceptmapratestrategy.h"
#include "testtimer.h"
#include "trace.h"
#include "ui_qttestdisplayconceptmapdialog.h"
#pragma GCC diagnostic pop

ribi::cmap::QtTestDisplayConceptMapDialog::QtTestDisplayConceptMapDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtTestDisplayConceptMapDialog),
  m_concept_map(
    new QtDisplayConceptMap(
    )
  )
{
  ui->setupUi(this);
  #ifndef NDEBUG
  Test();
  #endif

  const auto concept_map = ribi::cmap::ConceptMapFactory().GetHeteromorphousTestConceptMaps().at(15);
  m_concept_map->SetConceptMap(concept_map);

  assert(ui->widget->layout());
  ui->widget->layout()->addWidget(m_concept_map.get());


}

ribi::cmap::QtTestDisplayConceptMapDialog::~QtTestDisplayConceptMapDialog() noexcept
{
  delete ui;
}

void ribi::cmap::QtTestDisplayConceptMapDialog::keyPressEvent(QKeyEvent *event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

#ifndef NDEBUG
void ribi::cmap::QtTestDisplayConceptMapDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer{__func__,__FILE__,0.2};
  QtTestDisplayConceptMapDialog d;
  for (int i=0; i!=10; ++i) d.on_button_test_modify_clicked();

}
#endif

void ribi::cmap::QtTestDisplayConceptMapDialog::on_button_test_modify_clicked()
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
        //qtitem->GetConcept()->SetRatingComplexity(rating_complexity);
        //qtitem->GetConcept()->SetRatingConcreteness(-1 + (std::rand() % 4));
        //qtitem->GetConcept()->SetRatingSpecificity(-1 + (std::rand() % 4));
        const auto v = qtitem->GetNode()->GetConcept()->GetExamples()->Get();
        std::for_each(v.begin(),v.end(),
          [](const boost::shared_ptr<cmap::Example>& example)
          {
            if ( (std::rand() >> 4) % 2)
            {
              const std::vector<cmap::Competency> w = Competencies().GetAllCompetencies();
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
