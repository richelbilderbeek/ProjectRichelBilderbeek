#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtpvdbviewtestsdialog.h"

#include <cassert>

#include <boost/lexical_cast.hpp>

#include <QKeyEvent>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>

#include "pvdbconceptmap.h"
#include "pvdbconceptmapfactory.h"
#include "qtpvdbconceptmapdisplaywidget.h"
#include "qtpvdbconceptmapeditwidget.h"
#include "qtpvdbconceptmapratewidget.h"
#include "qtpvdbconceptmapwidget.h"
#include "trace.h"
#include "ui_qtpvdbviewtestsdialog.h"

QtPvdbViewTestsDialog::QtPvdbViewTestsDialog(QWidget* parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtPvdbViewTestsDialog),
  m_c(pvdb::ConceptMapFactory::GetComplexHomomorphousTestConceptMaps()),
  m_h(pvdb::ConceptMapFactory::GetHeteromorphousTestConceptMaps()),
  m_s(pvdb::ConceptMapFactory::GetSimpleHomomorphousTestConceptMaps())
{

  ui->setupUi(this);
  #ifndef NDEBUG
  Test();
  #endif

  for (int type=0; type!=3; ++type)
  {
    QWidget * contents = 0;
    switch (type)
    {
      case 0: contents = ui->display_contents; break;
      case 1: contents = ui->edit_contents; break;
      case 2: contents = ui->rate_contents; break;
      default: assert(!"Should not get here");
    }

    assert(!contents->layout());
    QVBoxLayout * const mylayout = new QVBoxLayout;
    assert(mylayout);
    contents->setLayout(mylayout);
    assert(contents->layout());


    //Add all concept maps
    {
      QLabel * const label = new QLabel("Heteromorphous test concept maps",this);
      assert(label);
      mylayout->addWidget(label);
    }
    const int extra_height = 4;
    {
      const int sz = static_cast<int>(m_h.size());
      for (int i=0; i!=sz; ++i)
      {
        const std::string s = "[" + boost::lexical_cast<std::string>(i)+ "]";
        QLabel * const label = new QLabel(s.c_str(),this);
        assert(label);
        mylayout->addWidget(label);
        assert(i < static_cast<int>(m_h.size()));
        assert(m_h[i]);
        const boost::shared_ptr<pvdb::ConceptMap> concept_map(m_h[i]);
        assert(concept_map);
        const boost::shared_ptr<QtPvdbConceptMapWidget> widget(CreateWidget(type,concept_map));
        assert(widget);
        assert(extra_height > 0);
        widget->setMinimumHeight(widget->scene()->itemsBoundingRect().height() + extra_height);
        mylayout->addWidget(widget.get());
        m_widgets.push_back(widget);
      }
    }
    {
      QLabel * const label = new QLabel("Simple homomorphous test concept maps",this);
      assert(label);
      mylayout->addWidget(label);
    }
    {
      const int sz = boost::numeric_cast<int>(m_s.size());
      for (int i=0; i!=sz; ++i)
      {
        const std::string s = "[" + boost::lexical_cast<std::string>(i)+ "]";
        QLabel * const label = new QLabel(s.c_str(),this);
        assert(label);
        mylayout->addWidget(label);
        //widget->setMinimumHeight(minheight);
        assert(i < static_cast<int>(m_s.size()));
        assert(m_s[i]);
        const boost::shared_ptr<pvdb::ConceptMap> concept_map = m_s[i];
        assert(concept_map);
        const boost::shared_ptr<QtPvdbConceptMapWidget> widget(CreateWidget(type,concept_map));
        assert(widget);
        widget->setMinimumHeight(widget->scene()->itemsBoundingRect().height() + extra_height);
        mylayout->addWidget(widget.get());
        m_widgets.push_back(widget);
      }
    }
    {
      QLabel * const label = new QLabel("Complex homomorphous test concept maps",this);
      assert(label);
      mylayout->addWidget(label);
    }
    {
      const int sz = boost::numeric_cast<int>(m_c.size());
      for (int i=0; i!=sz; ++i)
      {
        const std::string s = "[" + boost::lexical_cast<std::string>(i)+ "]";
        QLabel * const label = new QLabel(s.c_str(),this);
        assert(label);
        mylayout->addWidget(label);
        assert(i < static_cast<int>(m_c.size()));
        assert(m_c[i]);
        const boost::shared_ptr<pvdb::ConceptMap> concept_map = m_c[i];
        assert(concept_map);
        const boost::shared_ptr<QtPvdbConceptMapWidget> widget(CreateWidget(type,concept_map));
        assert(widget);
        //widget->setMinimumHeight(minheight);
        widget->setMinimumHeight(widget->scene()->itemsBoundingRect().height() + extra_height);
        mylayout->addWidget(widget.get());
        m_widgets.push_back(widget);
      }
    }
  }
}

QtPvdbViewTestsDialog::~QtPvdbViewTestsDialog()
{
  delete ui;
}

boost::shared_ptr<QtPvdbConceptMapWidget> QtPvdbViewTestsDialog::CreateWidget(
  const int type,
  const boost::shared_ptr<pvdb::ConceptMap> concept_map)
{
  switch (type)
  {
    case 0:
    {
      boost::shared_ptr<QtPvdbConceptMapWidget> p(new QtPvdbConceptMapDisplayWidget(concept_map));
      assert(p);
      return p;
    }
    case 1:
    {
      boost::shared_ptr<QtPvdbConceptMapWidget> p(new QtPvdbConceptMapEditWidget(concept_map));
      assert(p);
      return p;
    }
    case 2:
    {
      boost::shared_ptr<QtPvdbConceptMapWidget> p(new QtPvdbConceptMapRateWidget(concept_map));
      assert(p);
      return p;
    }
    default:
      assert(!"Should not get here");
  }
}


void QtPvdbViewTestsDialog::keyPressEvent(QKeyEvent* event)
{
  if (event->key()  == Qt::Key_Escape) { close(); return; }
}

#ifndef NDEBUG
void QtPvdbViewTestsDialog::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Started QtPvdbViewTestsDialog::Test");
  QtPvdbViewTestsDialog d;
  //d.show();
  d.exec();
  d.update();
  d.resize(100,100);
  d.show();
  d.update();
  d.resize(200,200);
  d.show();
  d.update();
  TRACE("QtPvdbViewTestsDialog::Test finished successfully");
}
#endif
