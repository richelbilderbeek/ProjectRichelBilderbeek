#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qttestconceptmapdisplaywidgetdialog.h"

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
#include "qtconceptmapdisplaywidget.h"
#include "qtconceptmapdisplayconceptitem.h"
#include "qtconceptmapdisplayconceptitem.h"
#include "qtconceptmapeditconceptitem.h"
#include "qtconceptmapnode.h"
#include "qtconceptmaprateconceptitem.h"
#include "trace.h"
#include "ui_qttestconceptmapdisplaywidgetdialog.h"
#pragma GCC diagnostic pop

ribi::cmap::QtTestConceptMapDisplayWidgetDialog::QtTestConceptMapDisplayWidgetDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtTestConceptMapDisplayWidgetDialog),
  m_concept_map(
    new QtConceptMapDisplayWidget(
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

ribi::cmap::QtTestConceptMapDisplayWidgetDialog::~QtTestConceptMapDisplayWidgetDialog() noexcept
{
  delete ui;
}

void ribi::cmap::QtTestConceptMapDisplayWidgetDialog::keyPressEvent(QKeyEvent *event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void ribi::cmap::QtTestConceptMapDisplayWidgetDialog::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("ribi::cmap::QtTestConceptMapDisplayWidgetDialog::Test started");
  QtTestConceptMapDisplayWidgetDialog d;
  for (int i=0; i!=100; ++i) d.on_button_test_modify_clicked();
  TRACE("ribi::cmap::QtTestConceptMapDisplayWidgetDialog::Test finished successfully");
}

void ribi::cmap::QtTestConceptMapDisplayWidgetDialog::on_button_test_modify_clicked()
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
        //qtitem->GetConcept()->SetRatingComplexity(rating_complexity);
        //qtitem->GetConcept()->SetRatingConcreteness(-1 + (std::rand() % 4));
        //qtitem->GetConcept()->SetRatingSpecificity(-1 + (std::rand() % 4));
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
