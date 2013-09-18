#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtpvdbtestconceptmapratewidgetdialog.h"

#include <cassert>
#include <cstdlib>

#include <boost/lexical_cast.hpp>

#include <QKeyEvent>

#include "pvdbcompetency.h"
#include "pvdbconcept.h"
#include "pvdbconceptmapfactory.h"
#include "pvdbconceptmap.h"
#include "pvdbexample.h"
#include "pvdbexample.h"
#include "pvdbexamples.h"
#include "pvdbexamples.h"
#include "pvdbnodefactory.h"
#include "pvdbnode.h"
#include "qtpvdbbrushfactory.h"
#include "qtpvdbconceptmapratewidget.h"
#include "qtpvdbdisplayconceptitem.h"
#include "qtpvdbdisplayconceptitem.h"
#include "qtpvdbeditconceptitem.h"
#include "qtpvdbnodeitem.h"
#include "qtpvdbrateconceptitem.h"
#include "trace.h"
#include "ui_qtpvdbtestconceptmapratewidgetdialog.h"
#pragma GCC diagnostic pop


ribi::pvdb::QtPvdbTestConceptMapRateWidgetDialog::QtPvdbTestConceptMapRateWidgetDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtPvdbTestConceptMapRateWidgetDialog),
  m_concept_map(
    new QtPvdbConceptMapRateWidget(
      ribi::pvdb::ConceptMapFactory::GetHeteromorphousTestConceptMaps().at(15)
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

ribi::pvdb::QtPvdbTestConceptMapRateWidgetDialog::~QtPvdbTestConceptMapRateWidgetDialog() noexcept
{
  delete ui;
}

void ribi::pvdb::QtPvdbTestConceptMapRateWidgetDialog::DoSomethingRandom()
{

  const QList<QGraphicsItem *> v = m_concept_map->GetScene()->items();
  std::for_each(v.begin(),v.end(),
    [](QGraphicsItem * const item)
    {
      if (QtPvdbNodeItem* const qtitem = dynamic_cast<QtPvdbNodeItem*>(item))
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
          [](const boost::shared_ptr<pvdb::Example>& example)
          {
            if ( (std::rand() >> 4) % 2)
            {
              const std::vector<pvdb::Competency> w = pvdb::GetAllCompetencies();
              example->SetCompetency(w[ std::rand() % w.size() ]);
            }
            else
            {
              example->SetCompetency(pvdb::Competency::uninitialized);
            }
          }
        );

        qtitem->update();
      }
    }
  );
  m_concept_map->GetScene()->update();
}

void ribi::pvdb::QtPvdbTestConceptMapRateWidgetDialog::keyPressEvent(QKeyEvent *e)
{
  if (e->key() == Qt::Key_Escape) { close(); return; }
  if (e->modifiers() & Qt::AltModifier && e->key() == Qt::Key_1)
  {
    DoSomethingRandom();
    return;
  }
}

void ribi::pvdb::QtPvdbTestConceptMapRateWidgetDialog::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("ribi::pvdb::QtPvdbTestConceptMapRateWidgetDialog::Test started");
  //Doing random stuff
  {
    QtPvdbTestConceptMapRateWidgetDialog d;
    for (int i=0; i!=100; ++i) d.DoSomethingRandom();
  }
  TRACE("ribi::pvdb::QtPvdbTestConceptMapRateWidgetDialog::Test finished successfully");
}
