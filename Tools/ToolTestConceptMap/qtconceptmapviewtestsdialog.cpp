#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtconceptmapviewtestsdialog.h"

#include <cassert>

#include <boost/lexical_cast.hpp>

#include <QKeyEvent>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>

#include "conceptmap.h"
#include "conceptmapfactory.h"
#include "qtconceptmap.h"


#include "qtconceptmap.h"
#include "testtimer.h"
#include "trace.h"
#include "ui_qtconceptmapviewtestsdialog.h"
#pragma GCC diagnostic pop

ribi::cmap::QtConceptMapViewTestsDialog::QtConceptMapViewTestsDialog(QWidget* parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtConceptMapViewTestsDialog),
    m_c(cmap::ConceptMapFactory().GetComplexHomomorphousTestConceptMaps()),
    m_h(cmap::ConceptMapFactory().GetHeteromorphousTestConceptMaps()),
    m_s(cmap::ConceptMapFactory().GetSimpleHomomorphousTestConceptMaps()),
    m_widgets{}
{

  ui->setupUi(this);
  #ifndef NDEBUG
  Test();
  #endif

  const int type = 1;
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
        const boost::shared_ptr<ConceptMap> conceptmap(m_h[i]);
        assert(conceptmap);
        const boost::shared_ptr<cmap::QtConceptMap> widget(CreateWidget(conceptmap));
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
        const boost::shared_ptr<ConceptMap> conceptmap = m_s[i];
        assert(conceptmap);
        const boost::shared_ptr<cmap::QtConceptMap> widget(CreateWidget(conceptmap));
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
        const boost::shared_ptr<ConceptMap> conceptmap = m_c[i];
        assert(conceptmap);
        const boost::shared_ptr<cmap::QtConceptMap> widget(CreateWidget(conceptmap));
        assert(widget);
        //widget->setMinimumHeight(minheight);
        widget->setMinimumHeight(widget->scene()->itemsBoundingRect().height() + extra_height);
        mylayout->addWidget(widget.get());
        m_widgets.push_back(widget);
      }
    }
  }
}

ribi::cmap::QtConceptMapViewTestsDialog::~QtConceptMapViewTestsDialog() noexcept
{
  delete ui;
}

boost::shared_ptr<ribi::cmap::QtConceptMap> ribi::cmap::QtConceptMapViewTestsDialog::CreateWidget(
  const boost::shared_ptr<ConceptMap> conceptmap
)
{
  boost::shared_ptr<QtConceptMap> p(new QtConceptMap);
  assert(p);
  p->SetConceptMap(conceptmap);
  return p;
}


void ribi::cmap::QtConceptMapViewTestsDialog::keyPressEvent(QKeyEvent* event)
{
  if (event->key()  == Qt::Key_Escape) { close(); return; }
}

#ifndef NDEBUG
void ribi::cmap::QtConceptMapViewTestsDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  {
    cmap::ConceptMapFactory();
    QtConceptMapViewTestsDialog();
  }
  const ribi::TestTimer test_timer(__func__,__FILE__,1.0);
  //QtConceptMapViewTestsDialog d; //Just takes too long, for no new funtionality
}
#endif
