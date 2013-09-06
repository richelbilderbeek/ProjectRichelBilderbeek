#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtpvdbprintconceptmapdialog.h"

#include <cassert>
#include <ctime>

#include <boost/numeric/conversion/cast.hpp>

#include <QKeyEvent>

#include <QFileDialog>
#include <QPrinter>

#include "pvdbfile.h"
#include "pvdbconceptmap.h"
#include "pvdbconceptmapfactory.h"
#include "qtpvdbratedconceptwidget.h"
#include "qtpvdbfiledialog.h"
#include "ui_qtpvdbprintconceptmapdialog.h"
#include "qtpvdbconceptmapdisplaywidget.h"

ribi::pvdb::QtPvdbPrintConceptMapDialog::QtPvdbPrintConceptMapDialog(
  const boost::shared_ptr<pvdb::File>& file,
  QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtPvdbPrintConceptMapDialog),
    m_file(file),
    m_widget(new QtPvdbConceptMapDisplayWidget(file->GetConceptMap()))
{
  ui->setupUi(this);

  {
    assert(m_widget);
    assert(ui->frame_concept_map->layout());
    ui->frame_concept_map->layout()->addWidget(m_widget);
  }


  ui->label_student_name->setText(
    (std::string("Concept map van ")
      + m_file->GetStudentName()).c_str()
  );
  {
    std::time_t my_time;
    std::time( &my_time );
    const std::tm * const time_and_date = std::localtime(&my_time);
    const std::string s = std::asctime(time_and_date);
    ui->label_date->setText( (std::string("Datum: ") + s).c_str());
  }
}

ribi::pvdb::QtPvdbPrintConceptMapDialog::~QtPvdbPrintConceptMapDialog()
{
  delete ui;
}

const std::vector<QWidget *> ribi::pvdb::QtPvdbPrintConceptMapDialog::CollectWidgets() const
{
  std::vector<QWidget *> v;
  v.push_back(ui->frame_top);
  v.push_back(ui->frame_concept_map);
  {
    //Add widgets in widget_concept_map_as_text
    const int n = ui->frame_concept_map_as_text->layout()->count();
    for (int i=0; i!=n; ++i)
    {
      v.push_back(ui->frame_concept_map_as_text->layout()->itemAt(i)->widget());
    }
  }
  return v;
}


void ribi::pvdb::QtPvdbPrintConceptMapDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void ribi::pvdb::QtPvdbPrintConceptMapDialog::on_button_print_clicked()
{
  Print();
}

void ribi::pvdb::QtPvdbPrintConceptMapDialog::Print()
{
  //Start save dialog
  const boost::shared_ptr<QFileDialog> print_dialog(
    pvdb::QtFileDialog::GetSaveFileDialog(
      pvdb::QtFileDialog::FileType::pdf));
  print_dialog->setWindowTitle("Exporteer document naar PDF");
  if (print_dialog->exec() != QDialog::Accepted
    || print_dialog->selectedFiles().empty() )
  {
    return;
  }
  assert(!print_dialog->selectedFiles().empty());
  assert(print_dialog->selectedFiles().size() == 1);
  const std::string filename = print_dialog->selectedFiles()[0].toStdString();


  QPrinter printer;
  printer.setOrientation(QPrinter::Portrait);
  printer.setPaperSize(QPrinter::A4);
  printer.setOutputFormat(QPrinter::PdfFormat); //Student exports to PDF
  printer.setFullPage(false);
  printer.setOutputFileName(filename.c_str());

  //Draw the image to painter to printer (?must be done before printing)
  QPainter painter;

  painter.begin(&printer);
  {
    //Collect widgets to print
    const std::vector<QWidget *> widgets = CollectWidgets();

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

void ribi::pvdb::QtPvdbPrintConceptMapDialog::showEvent(QShowEvent *)
{
  //Concept map
  {
    //const boost::shared_ptr<ribi::pvdb::ConceptMap> copy_concept_map
    //  = m_file->GetConceptMap();
    assert(m_widget);
    assert(m_widget->GetConceptMap());

    //m_widget->ReadFromConceptMap(copy_concept_map);
    m_widget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_widget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_widget->setMinimumHeight(m_widget->scene()->itemsBoundingRect().height() + 2);
    //Fit concept map to widget
    m_widget->fitInView(m_widget->scene()->itemsBoundingRect());

    assert(m_widget->scene()->items().count()
      >= boost::numeric_cast<int>(
        m_widget->GetConceptMap()->GetNodes().size()
        + m_widget->GetConceptMap()->GetEdges().size()));

  }
  //Concept map as text
  {

    assert(ui->frame_concept_map_as_text->layout());
    std::string text;
    const int n_nodes = static_cast<int>(m_file->GetConceptMap()->GetNodes().size());
    for (int node_index = 1; node_index != n_nodes; ++node_index) //1: skip center node
    {
      const boost::shared_ptr<ribi::pvdb::Node> node = m_file->GetConceptMap()->GetNodes().at(node_index);
      assert(node);
      QtPvdbRatedConceptWidget * const widget
        = new QtPvdbRatedConceptWidget(m_file->GetConceptMap(),node);
      assert(widget);
      widget->HideRating();
      ui->frame_concept_map_as_text->layout()->addWidget(widget);
    }
  }
}
