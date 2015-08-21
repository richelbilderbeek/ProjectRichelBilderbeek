//---------------------------------------------------------------------------
/*
Brainweaver, tool to create and assess concept maps
Copyright (C) 2012-2015 The Brainweaver Team

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ProjectBrainweaver.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtpvdbprintratingdialog.h"

#include <cassert>
#include <ctime>

#include <boost/lexical_cast.hpp>

#include <QFileDialog>
#include <QKeyEvent>
#include <QScrollBar>
#include <QPrinter>

#include "pvdbfile.h"
#include "conceptmapconcept.h"
#include "qtpvdbfiledialog.h"
#include "conceptmapnode.h"
#include "conceptmapedge.h"
#include "conceptmapfactory.h"
#include "conceptmapexample.h"
#include "conceptmapexamples.h"
#include "conceptmap.h"
#include "qtconceptmapratedconceptdialog.h"
#include "qtpvdbdisplay.h"
#include "qtconceptmap.h"
#include "ui_qtpvdbprintratingdialog.h"
#pragma GCC diagnostic pop

ribi::pvdb::QtPvdbPrintRatingDialog::QtPvdbPrintRatingDialog(
  const boost::shared_ptr<pvdb::File>& file,
  QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtPvdbPrintRatingDialog),
    m_file(file),
    m_widget(new cmap::QtConceptMap)
{
  ui->setupUi(this);    
  m_widget->SetConceptMap(file->GetConceptMap());
  assert(m_file);
  ui->label_focal_question->setText(
    ("FOCUSVRAAG: "
    + m_file->GetQuestion()).c_str()
  );
  ui->label_student_name->setText(
    ("VAN: "
      + m_file->GetStudentName()).c_str()
  );
  ui->label_assessor_name->setText(
    ("ASSESSOR: "
      + m_file->GetAssessorName()).c_str()
  );

  {
    assert(m_widget);
    assert(ui->frame_concept_map->layout());
    ui->frame_concept_map->layout()->addWidget(m_widget);
  }

  //Allow a QtConceptMapWidget to have no QtExamplesItem
  //This allows to omit showing these in the PDF versions used for printing (#205)
  m_widget->RemoveExamplesItem();

  {
    std::time_t my_time;
    std::time( &my_time );
    const std::tm * const time_and_date = std::localtime(&my_time);
    const std::string s = std::asctime(time_and_date);
    ui->label_date->setText( ("Datum: " + s).c_str()
    );
  }
}

ribi::pvdb::QtPvdbPrintRatingDialog::~QtPvdbPrintRatingDialog() noexcept
{
  delete ui;
}

const std::vector<QWidget *> ribi::pvdb::QtPvdbPrintRatingDialog::CollectWidgets() const
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

QTableWidget * ribi::pvdb::QtPvdbPrintRatingDialog::GetTableConcepts()
{
  return ui->table_concepts;
}

QTableWidget * ribi::pvdb::QtPvdbPrintRatingDialog::GetTableExamples()
{
  return ui->table_examples;
}

QTableWidget * ribi::pvdb::QtPvdbPrintRatingDialog::GetTableValues()
{
  return ui->table_values;
}

void ribi::pvdb::QtPvdbPrintRatingDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void ribi::pvdb::QtPvdbPrintRatingDialog::on_button_print_clicked()
{
  Print();
}

void ribi::pvdb::QtPvdbPrintRatingDialog::Print()
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

void ribi::pvdb::QtPvdbPrintRatingDialog::showEvent(QShowEvent *)
{
  //Concept map
  {
    //const boost::shared_ptr<ribi::cmap::ConceptMap> copy_concept_map
    //  = m_file->GetConceptMap();
    //const boost::shared_ptr<ribi::cmap::ConceptMap> copy_concept_map
    //  = ribi::cmap::ConceptMapFactory::DeepCopy(m_file->GetConceptMap()); //2013-05-31 REJECT DEEP COPIES
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
      cmap::QtConceptMapRatedConceptDialog * const widget
        = new cmap::QtConceptMapRatedConceptDialog(m_file->GetConceptMap(),node);
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
