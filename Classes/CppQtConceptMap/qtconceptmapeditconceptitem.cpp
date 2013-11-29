#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtconceptmapeditconceptitem.h"

#include <QKeyEvent>

#include "conceptmapconcept.h"
#include "conceptmapconceptfactory.h"
#include "qtconceptmapbrushfactory.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::cmap::QtPvdbEditConceptItem::QtPvdbEditConceptItem(const boost::shared_ptr<ribi::cmap::Concept> concept)
  : QtConceptMapItem(concept),
    m_signal_request_edit{}
{
  #ifndef NDEBUG
  Test();
  assert(concept);
  assert(GetConcept());
  #endif

  this->setBrush(QtPvdbBrushFactory::CreateGrayGradientBrush()); //NEW 2013-04-09

  GetConcept()->m_signal_name_changed.connect(
    boost::bind(&ribi::cmap::QtPvdbEditConceptItem::OnConceptNameChanged,this)); //Obligatory

  //GetConcept()->m_signal_rating_complexity_changed.connect(
  //  boost::bind(&ribi::cmap::QtPvdbEditConceptItem::UpdateBrushesAndPens,this));
  //GetConcept()->m_signal_rating_concreteness_changed.connect(
  //  boost::bind(&ribi::cmap::QtPvdbEditConceptItem::UpdateBrushesAndPens,this));
  //GetConcept()->m_signal_rating_specificity_changed.connect(
  //  boost::bind(&ribi::cmap::QtPvdbEditConceptItem::UpdateBrushesAndPens,this));
}

ribi::cmap::QtPvdbEditConceptItem::~QtPvdbEditConceptItem() noexcept
{
  GetConcept()->m_signal_name_changed.disconnect(
    boost::bind(&ribi::cmap::QtPvdbEditConceptItem::OnConceptNameChanged,this));
}

void ribi::cmap::QtPvdbEditConceptItem::keyPressEvent(QKeyEvent *event) noexcept
{
  switch (event->key())
  {
    case Qt::Key_F2:
      m_signal_request_edit(this);
      m_signal_request_scene_update(); //???really needed
    return; //Done
    break;
  }
}

#ifndef NDEBUG
void ribi::cmap::QtPvdbEditConceptItem::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::cmap::QtPvdbEditConceptItem::Test()");
  ///Test SetText
  {
    const boost::shared_ptr<Concept> concept = ConceptFactory::Create();
    QtPvdbEditConceptItem a(concept);
    const auto v {
      "1234567890",
      "1234567890 1234567890",
      "1234567890 1234567890 1234567890",
      "1234567890 1234567890 1234567890 1234567890",
      "1234567890 1234567890 1234567890 1234567890 1234567890",
      "1234567890 1234567890 1234567890 1234567890 1234567890 1234567890",
      "1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890",
      "1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890",
      "1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890",
      "1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890",
      "1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890",
      "1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890",
      "1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890",
      "1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890"
    };
    for (const auto s: v) { a.SetName(s); } //SetName tests GetName
  }
  TRACE("Successfully finished ribi::cmap::QtPvdbEditConceptItem::Test()");
}
#endif

