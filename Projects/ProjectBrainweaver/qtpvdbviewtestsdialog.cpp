#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtpvdbviewtestsdialog.h"

#include <boost/lexical_cast.hpp>
#include <QKeyEvent>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include "pvdbconceptmap.h"
#include "pvdbconceptmapfactory.h"
#include "qtpvdbconceptmapdisplaywidget.h"
#include "qtpvdbconceptmapeditwidget.h"
#include "qtpvdbconceptmapwidget.h"
#include "trace.h"
#include "ui_qtpvdbviewtestsdialog.h"

QtPvdbViewTestsDialog::QtPvdbViewTestsDialog(QWidget* parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtPvdbViewTestsDialog),
  m_v(pvdb::ConceptMapFactory::GetHeteromorphousTestConceptMaps())
{
  ui->setupUi(this);

  assert(!ui->scrollAreaWidgetContents->layout());
  QVBoxLayout * const mylayout = new QVBoxLayout(ui->scrollAreaWidgetContents);
  assert(mylayout);
  //Add all concept maps
  {
    {
      const int sz = static_cast<int>(m_v.size());
      for (int i=0; i!=sz; ++i)
      {
        QLabel * const label = new QLabel((std::string("[")+boost::lexical_cast<std::string>(i)+std::string("]")).c_str());
        assert(label);
        mylayout->addWidget(label);
        assert(m_v[i]);
        const boost::shared_ptr<pvdb::ConceptMap> concept_map(m_v[i]);
        assert(concept_map);
        QtPvdbConceptMapDisplayWidget * const widget = new QtPvdbConceptMapDisplayWidget(concept_map);
        assert(widget);
        widget->setMinimumHeight(widget->scene()->itemsBoundingRect().height() + 2); //NEW 2013-05-11
        mylayout->addWidget(widget);
      }
    }
    {
      mylayout->addWidget(new QLabel("Simple homomorphous test concept maps"));
      const std::vector<boost::shared_ptr<pvdb::ConceptMap> > v = pvdb::ConceptMapFactory::GetSimpleHomomorphousTestConceptMaps();
      const int sz = boost::numeric_cast<int>(v.size());
      for (int i=0; i!=sz; ++i)
      {
        mylayout->addWidget(new QLabel((std::string("[")+boost::lexical_cast<std::string>(i)+std::string("]")).c_str()));
        //widget->setMinimumHeight(minheight);
        const auto concept_map = v[i];
        assert(concept_map);
        QtPvdbConceptMapWidget * const widget = new QtPvdbConceptMapDisplayWidget(concept_map);
        assert(widget);
        widget->setMinimumHeight(widget->scene()->itemsBoundingRect().height() + 2); //NEW 2013-05-11
        mylayout->addWidget(widget);
      }
    }
    {
      mylayout->addWidget(new QLabel("Complex homomorphous test concept maps"));
      const std::vector<boost::shared_ptr<pvdb::ConceptMap> > v = pvdb::ConceptMapFactory::GetComplexHomomorphousTestConceptMaps();
      const int sz = boost::numeric_cast<int>(v.size());
      for (int i=0; i!=sz; ++i)
      {
        mylayout->addWidget(new QLabel((std::string("[")+boost::lexical_cast<std::string>(i)+std::string("]")).c_str()));
        const auto concept_map = v[i];
        assert(concept_map);
        QtPvdbConceptMapWidget * const widget = new QtPvdbConceptMapDisplayWidget(concept_map);
        assert(widget);
        //widget->setMinimumHeight(minheight);
        widget->setMinimumHeight(widget->scene()->itemsBoundingRect().height() + 2); //NEW 2013-05-11
        mylayout->addWidget(widget);
      }
    }
  }
}

QtPvdbViewTestsDialog::~QtPvdbViewTestsDialog()
{
  delete ui;
}

void QtPvdbViewTestsDialog::keyPressEvent(QKeyEvent* event)
{
  if (event->key()  == Qt::Key_Escape) { close(); return; }
  //QDialog::keyPressEvent(event);
}
