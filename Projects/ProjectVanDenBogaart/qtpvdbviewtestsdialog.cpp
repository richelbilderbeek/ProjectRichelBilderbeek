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
#include "qtpvdbconceptmapwidget.h"
#include "trace.h"
#include "ui_qtpvdbviewtestsdialog.h"

QtPvdbViewTestsDialog::QtPvdbViewTestsDialog(QWidget* parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtPvdbViewTestsDialog)
{
  ui->setupUi(this);

  assert(!ui->scrollAreaWidgetContents->layout());
  //QGridLayout * const mylayout = new QGridLayout(ui->scrollAreaWidgetContents);
  QVBoxLayout * const mylayout = new QVBoxLayout(ui->scrollAreaWidgetContents);
  ui->scrollAreaWidgetContents->setLayout(mylayout);
  assert(mylayout->parent());
  //Add all concept maps
  {
    const int minheight = 200;
    {
      //assert(mylayout->rowCount() == 1);
      mylayout->addWidget(new QLabel("Heteromorphous test concept maps"));
      //assert(mylayout->rowCount() == 2);
      const std::vector<boost::shared_ptr<pvdb::ConceptMap> > v = pvdb::ConceptMapFactory::GetHeteromorphousTestConceptMaps();
      const int sz = 2; //static_cast<int>(v.size());
      for (int i=0; i!=sz; ++i)
      {
        mylayout->addWidget(new QLabel((std::string("[")+boost::lexical_cast<std::string>(i)+std::string("]")).c_str()));
        QtPvdbConceptMapWidget * const widget = new QtPvdbConceptMapDisplayWidget;
        assert(widget);
        assert(!widget->parent());
        widget->setMinimumHeight(minheight);
        assert(v[i]);
        const boost::shared_ptr<pvdb::ConceptMap> concept_map(v[i]);
        assert(concept_map);
        widget->ReadFromConceptMap(concept_map);
        mylayout->addWidget(widget);
        assert(widget->parent());
      }
    }
    /*
    {
      mylayout->addWidget(new QLabel("Simple homomorphous test concept maps"));
      const std::vector<boost::shared_ptr<pvdb::ConceptMap> > v = pvdb::ConceptMapFactory::GetSimpleHomomorphousTestConceptMaps();
      const int sz = static_cast<int>(v.size());
      for (int i=0; i!=sz; ++i)
      {
        TRACE(i);
        mylayout->addWidget(new QLabel((std::string("[")+boost::lexical_cast<std::string>(i)+std::string("]")).c_str()));
        QtPvdbConceptMapWidget * const widget = new QtPvdbConceptMapDisplayWidget;
        assert(widget);
        widget->setMinimumHeight(minheight);
        assert(v[i]);
        widget->ReadFromConceptMap(v[i]);
        mylayout->addWidget(widget);
      }
    }
    {
      mylayout->addWidget(new QLabel("Complex homomorphous test concept maps"));
      const std::vector<boost::shared_ptr<pvdb::ConceptMap> > v = pvdb::ConceptMapFactory::GetComplexHomomorphousTestConceptMaps();
      const int sz = static_cast<int>(v.size());
      for (int i=0; i!=sz; ++i)
      {
        TRACE(i);
        mylayout->addWidget(new QLabel((std::string("[")+boost::lexical_cast<std::string>(i)+std::string("]")).c_str()));
        QtPvdbConceptMapWidget * const widget = new QtPvdbConceptMapDisplayWidget;
        assert(widget);
        widget->setMinimumHeight(minheight);
        assert(v[i]);
        widget->ReadFromConceptMap(v[i]);
        mylayout->addWidget(widget);
      }
    }
    */
  }
  TRACE_FUNC();
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
