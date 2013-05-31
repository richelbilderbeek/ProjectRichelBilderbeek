#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtpvdbtestconceptmapdisplaywidgetdialog.h"

#include <cassert>
#include <cstdlib>

#ifdef COMPILER_SUPPORTS_THREADS_20130507
#include <thread>
#endif

#include <boost/lexical_cast.hpp>
#include <QKeyEvent>
#include "qtpvdbdisplayconceptitem.h"
#include "qtpvdbeditconceptitem.h"
#include "qtpvdbrateconceptitem.h"
#include "pvdbnodefactory.h"
#include "qtpvdbdisplayconceptitem.h"
#include "pvdbexample.h"
#include "pvdbcompetency.h"
#include "pvdbexamples.h"
#include "pvdbconceptmap.h"
#include "qtpvdbbrushfactory.h"
#include "qtpvdbnodeitem.h"
#include "pvdbexamples.h"
#include "pvdbexample.h"
#include "ui_qtpvdbtestconceptmapdisplaywidgetdialog.h"
#include "pvdbconcept.h"
#include "pvdbnode.h"
#include "pvdbconceptmapfactory.h"
#include "trace.h"

QtPvdbTestConceptMapDisplayWidgetDialog::QtPvdbTestConceptMapDisplayWidgetDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtPvdbTestConceptMapDisplayWidgetDialog)
{
  ui->setupUi(this);
  #ifndef NDEBUG
  Test();
  #endif
  const boost::shared_ptr<pvdb::ConceptMap> concept_map(pvdb::ConceptMapFactory::GetHeteromorphousTestConceptMaps().at(15));
  ui->concept_map->ReadFromConceptMap(concept_map);
}

QtPvdbTestConceptMapDisplayWidgetDialog::~QtPvdbTestConceptMapDisplayWidgetDialog()
{
  delete ui;
}

void QtPvdbTestConceptMapDisplayWidgetDialog::keyPressEvent(QKeyEvent *event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void QtPvdbTestConceptMapDisplayWidgetDialog::Test()
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
  TRACE("QtPvdbTestConceptMapDisplayWidgetDialog::Test started");
  QtPvdbTestConceptMapDisplayWidgetDialog d;
  for (int i=0; i!=100; ++i) d.on_button_test_modify_clicked();
  TRACE("QtPvdbTestConceptMapDisplayWidgetDialog::Test finished successfully");
  #ifdef COMPILER_SUPPORTS_THREADS_20130507
    }
  );
  t.detach();
  #endif
}

void QtPvdbTestConceptMapDisplayWidgetDialog::on_button_test_modify_clicked()
{
  const QList<QGraphicsItem *> v = ui->concept_map->GetScene()->items();
  std::for_each(v.begin(),v.end(),
    [](QGraphicsItem * const item)
    {
      if (QtPvdbNodeItem* const qtitem = dynamic_cast<QtPvdbNodeItem*>(item))
      {
        assert(qtitem->GetConcept());
        assert(!qtitem->GetConcept()->GetName().empty());
        assert(qtitem->GetConcept()->GetExamples());
        //qtitem->GetConcept()->SetRatingComplexity(rating_complexity);
        //qtitem->GetConcept()->SetRatingConcreteness(-1 + (std::rand() % 4));
        //qtitem->GetConcept()->SetRatingSpecificity(-1 + (std::rand() % 4));
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
  ui->concept_map->GetScene()->update();
}
