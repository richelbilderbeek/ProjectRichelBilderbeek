#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtpvdbprintratingdialog.h"

#include <cassert>
#include <ctime>

#include <boost/lexical_cast.hpp>

#include <QKeyEvent>
#include <QScrollBar>

#if (QT_VERSION >= QT_VERSION_CHECK(5,5,0))
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinter>
#else
#include <QPrintDialog>
#include <QPrinter>
#endif

#include "pvdbfile.h"
#include "pvdbconcept.h"
#include "pvdbnode.h"
#include "pvdbedge.h"
#include "pvdbconceptmapfactory.h"
#include "pvdbexample.h"
#include "pvdbexamples.h"
#include "pvdbconceptmap.h"
#include "qtpvdbratedconceptwidget.h"
#include "qtpvdbdisplay.h"
#include "qtpvdbconceptmapratewidget.h"
#include "ui_qtpvdbprintratingdialog.h"

QtPvdbPrintRatingDialog::QtPvdbPrintRatingDialog(
  const boost::shared_ptr<pvdb::File>& file,
  QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtPvdbPrintRatingDialog),
    m_file(file),
    m_widget(new QtPvdbConceptMapRateWidget(file->GetConceptMap()))
{
  ui->setupUi(this);    
  assert(m_file);
  ui->label_focal_question->setText(
    (std::string("FOCUSVRAAG: ")
    + m_file->GetQuestion()).c_str()
  );
  ui->label_student_name->setText(
    (std::string("VAN: ")
      + m_file->GetStudentName()).c_str()
  );
  ui->label_assessor_name->setText(
    (std::string("ASSESSOR: ")
      + m_file->GetAssessorName()).c_str()
  );

  {
    assert(m_widget);
    assert(ui->frame_concept_map->layout());
    ui->frame_concept_map->layout()->addWidget(m_widget);
  }


  {
    std::time_t my_time;
    std::time( &my_time );
    const std::tm * const time_and_date = std::localtime(&my_time);
    const std::string s = std::asctime(time_and_date);
    ui->label_date->setText( (std::string("Datum: ") + s).c_str()
    );
  }
}

QtPvdbPrintRatingDialog::~QtPvdbPrintRatingDialog()
{
  delete ui;
}

const std::vector<QWidget *> QtPvdbPrintRatingDialog::CollectWidgets() const
{
  std::vector<QWidget *> v { ui->frame_header, ui->frame_concept_map, ui->label_concept_map_as_text };
  {
    //Add widgets in widget_concept_map_as_text
    const int n = ui->widget_concept_map_as_text->layout()->count();
    for (int i=0; i!=n; ++i)
    {
      v.push_back(ui->widget_concept_map_as_text->layout()->itemAt(i)->widget());
    }
  }
  v.push_back(ui->frame_concepts);
  v.push_back(ui->frame_competencies);
  v.push_back(ui->frame_values);
  return v;
}

QTableWidget * QtPvdbPrintRatingDialog::GetTableConcepts()
{
  return ui->table_concepts;
}

QTableWidget * QtPvdbPrintRatingDialog::GetTableExamples()
{
  return ui->table_examples;
}

QTableWidget * QtPvdbPrintRatingDialog::GetTableValues()
{
  return ui->table_values;
}

void QtPvdbPrintRatingDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void QtPvdbPrintRatingDialog::on_button_print_clicked()
{
  Print();
}

void QtPvdbPrintRatingDialog::Print()
{
  QPrinter printer;
  printer.setOrientation(QPrinter::Portrait);
  printer.setPaperSize(QPrinter::A4);
  printer.setFullPage(false);

  //Start printer dialog
  const boost::shared_ptr<QPrintDialog> print_dialog(new QPrintDialog(&printer));
  print_dialog->setWindowTitle(tr("Print document"));
  if (print_dialog->exec() != QDialog::Accepted) return;


  //Collect widgets to print
  const std::vector<QWidget *> widgets = CollectWidgets();

  //Draw the image to painter to printer (?must be done before printing)
  QPainter painter;

  painter.begin(&printer);
  {
    int y = 0;
    for (QWidget * const widget: widgets)
    {
      const int h = widget->height();
      if (y+h > painter.window().height())
      {
        printer.newPage();
        y = 0;
      }
      widget->render(&painter,QPoint(0,y));
      y+=h;
    }
  }
  painter.end();

}

void QtPvdbPrintRatingDialog::showEvent(QShowEvent *)
{
  //Concept map
  {
    //const boost::shared_ptr<pvdb::ConceptMap> copy_concept_map
    //  = m_file->GetConceptMap();
    //const boost::shared_ptr<pvdb::ConceptMap> copy_concept_map
    //  = pvdb::ConceptMapFactory::DeepCopy(m_file->GetConceptMap()); //2013-05-31 REJECT DEEP COPIES
    //m_widget->ReadFromConceptMap(copy_concept_map);
    m_widget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_widget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_widget->setMaximumHeight(m_widget->scene()->itemsBoundingRect().height() + 2);
    m_widget->setMinimumHeight(m_widget->scene()->itemsBoundingRect().height() + 2);
    //Fit concept map to widget
    m_widget->fitInView(m_widget->scene()->itemsBoundingRect());
  }
  //Concept map as text
  {
    assert(ui->widget_concept_map_as_text->layout());
    std::string text;
    const int n_nodes = static_cast<int>(m_file->GetConceptMap()->GetNodes().size());
    for (int node_index = 1; node_index != n_nodes; ++node_index) //1: skip center node
    {
      const auto node = m_file->GetConceptMap()->GetNodes().at(node_index);
      assert(node);
      QtPvdbRatedConceptWidget * const widget
        = new QtPvdbRatedConceptWidget(m_file->GetConceptMap(),node);
      assert(widget);
      ui->widget_concept_map_as_text->layout()->addWidget(widget);
    }
  }

  //Copied from caller
  pvdb::QtDisplay::DisplayRatedConcepts(m_file,this->GetTableConcepts());
  {
    const int sz = static_cast<int>(m_file->GetConceptMap()->GetNodes().size());
    this->GetTableConcepts()->setMinimumHeight( ((sz-1) * 30) + 26 ); //Standard row is 30 pixels high, header 25 pixels
  }

  pvdb::QtDisplay::DisplayExamples(m_file,this->GetTableExamples());
  pvdb::QtDisplay::DisplayValues(m_file,this->GetTableValues());
}
