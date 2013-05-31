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
#include <QPrinter>
#include <QPrintDialog>
#include <QScrollBar>

#include "pvdbfile.h"
#include "pvdbconcept.h"
#include "pvdbnode.h"
#include "pvdbedge.h"
#include "pvdbconceptmapfactory.h"
#include "pvdbexample.h"
#include "pvdbexamples.h"
#include "pvdbconceptmap.h"
#include "qtpvdbconceptmapratewidget.h"
#include "ui_qtpvdbprintratingdialog.h"

QtPvdbPrintRatingDialog::QtPvdbPrintRatingDialog(
  const boost::shared_ptr<const pvdb::File>& file,
  QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtPvdbPrintRatingDialog)
{
  ui->setupUi(this);
  assert(file);
  ui->label_assessor_name->setText(
    (std::string("ASSESSOR: ")
      + file->GetAssessorName()).c_str()
  );
  ui->label_student_name->setText(
    (std::string("VAN: ")
      + file->GetStudentName()).c_str()
  );
  {
    std::time_t my_time;
    std::time( &my_time );
    const std::tm * const time_and_date = std::localtime(&my_time);
    const std::string s = std::asctime(time_and_date);

    ui->label_date->setText( (std::string("Datum: ") + s).c_str()
    );
  }
  //Concept map
  {
    const boost::shared_ptr<pvdb::ConceptMap> copy_concept_map
      = pvdb::ConceptMapFactory::DeepCopy(file->GetConceptMap());
    ui->concept_map->ReadFromConceptMap(copy_concept_map);
    ui->concept_map->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->concept_map->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->concept_map->setMinimumHeight(ui->concept_map->scene()->itemsBoundingRect().height() + 2);
  }
  //Concept map as text
  {
    std::string text;
    const int n_nodes = static_cast<int>(file->GetConceptMap()->GetNodes().size());
    for (int node_index = 1; node_index != n_nodes; ++node_index) //1: skip center node
    {
      const boost::shared_ptr<const pvdb::Node> node = file->GetConceptMap()->GetNodes().at(node_index);
      text += "Cluster bij concept: " + node->GetConcept()->GetName() + "\n";
      text += "  Complexiteit: " + boost::lexical_cast<std::string>(node->GetConcept()->GetRatingComplexity()) + "\n";
      text += "  Concreetheid: " + boost::lexical_cast<std::string>(node->GetConcept()->GetRatingConcreteness()) + "\n";
      text += "  Specificity: " + boost::lexical_cast<std::string>(node->GetConcept()->GetRatingSpecificity()) + "\n";
      text += "  Voorbeelden/toelichting bij het concept:\n";
      //Examples
      for (const boost::shared_ptr<const pvdb::Example> example: node->GetConcept()->GetExamples()->Get())
      {
        text += "    " + boost::lexical_cast<std::string>(static_cast<int>(example->GetCompetency())) + ". " + example->GetText() + "\n";
      }
      text += "  Relaties van het cluster:\n";
      for (const boost::shared_ptr<const pvdb::Edge> edge: file->GetConceptMap()->GetEdges())
      {
        if (edge->GetFrom() == node_index || edge->GetTo() == node_index)
        {
          const std::string first_arrow
            = (  (edge->GetFrom() == node_index && edge->HasTailArrow())
              || (edge->GetTo()   == node_index && edge->HasHeadArrow())
            ? "<- " : "-- ");
          const std::string second_arrow
            = (  (edge->GetFrom() == node_index && edge->HasHeadArrow())
              || (edge->GetTo()   == node_index && edge->HasTailArrow())
            ? " -> " : " -- ");
          text += "    "
            + first_arrow
            + edge->GetConcept()->GetName()
            + second_arrow
            + file->GetConceptMap()->GetNodes().at(edge->GetTo())->GetConcept()->GetName()
            + "\n";
        }
      }
    }
    ui->concept_map_as_text->setPlainText(text.c_str());
    ui->concept_map_as_text->setMinimumHeight(
      ui->concept_map_as_text->document()->lineCount() * 14);
  }
}

QtPvdbPrintRatingDialog::~QtPvdbPrintRatingDialog()
{
  delete ui;
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
  QPrinter printer;
  const QString filename = "ProjectVanDenBogaart.pdf";
  printer.setOutputFormat(QPrinter::PdfFormat);
  printer.setOrientation(QPrinter::Portrait);
  printer.setPaperSize(QPrinter::A4);
  printer.setFullPage(false);
  printer.setOutputFileName(filename);

  //Start printer dialog
  const boost::shared_ptr<QPrintDialog> print_dialog(new QPrintDialog(&printer));
  print_dialog->setWindowTitle(tr("Print document"));
  if (print_dialog->exec() != QDialog::Accepted) return;

  //ui->scrollArea->setMaximumWidth(printer.width());
  //ui->scrollArea->setWidgetResizable(false);

  //Draw the image to painter to printer
  QPainter painter;
  painter.begin(&printer);
  ui->scrollAreaWidgetContents->render(&painter);
  painter.end();

}
