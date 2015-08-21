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
#include "qtpvdbprintconceptmapdialog.h"

#include <cassert>
#include <ctime>

#include <boost/numeric/conversion/cast.hpp>

#include <QKeyEvent>

#include <QFileDialog>
#include <QPrinter>
#include <QTimer>

#include "pvdbfile.h"
#include "conceptmapconcept.h"
#include "conceptmap.h"
#include "conceptmapfactory.h"
#include "qtconceptmapqtnode.h"
#include "qtconceptmapdisplaystrategy.h"
#include "qtconceptmapratedconceptdialog.h"
#include "qtpvdbfiledialog.h"
#include "ui_qtpvdbprintconceptmapdialog.h"
#include "qtconceptmap.h"
#pragma GCC diagnostic pop

ribi::pvdb::QtPvdbPrintConceptMapDialog::QtPvdbPrintConceptMapDialog(
  const boost::shared_ptr<pvdb::File>& file,
  QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtPvdbPrintConceptMapDialog),
    m_file(file),
    m_widget(new cmap::QtConceptMap)
{
  ui->setupUi(this);
  m_widget->SetConceptMap(file->GetConceptMap());
  {
    assert(m_widget);
    assert(ui->frame_concept_map->layout());
    ui->frame_concept_map->layout()->addWidget(m_widget);
  }

  //Allow a QtConceptMapWidget to have no QtExamplesItem
  //This allows to omit showing these in the PDF versions used for printing (#205)
  m_widget->RemoveExamplesItem();

  ui->label_student_name->setText(
    ("Concept map van "
      + m_file->GetStudentName()).c_str()
  );
  {
    std::time_t my_time;
    std::time( &my_time );
    const std::tm * const time_and_date = std::localtime(&my_time);
    const std::string s = std::asctime(time_and_date);
    ui->label_date->setText( ("Datum: " + s).c_str());
  }

  //Much work done in ShowEvent
  {
    QTimer::singleShot(1000,this,SLOT(fitConceptMap()));
  }
}

ribi::pvdb::QtPvdbPrintConceptMapDialog::~QtPvdbPrintConceptMapDialog() noexcept
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

void ribi::pvdb::QtPvdbPrintConceptMapDialog::resizeEvent(QResizeEvent *)
{
    fitConceptMap();
}

void ribi::pvdb::QtPvdbPrintConceptMapDialog::fitConceptMap()
{
  assert(m_widget);
  assert(m_widget->GetConceptMap());
  const QRectF all_items_rect = m_widget->scene()->itemsBoundingRect();
  m_widget->setMinimumHeight(all_items_rect.height() + 2);
  m_widget->fitInView(all_items_rect);

}

void ribi::pvdb::QtPvdbPrintConceptMapDialog::showEvent(QShowEvent *)
{
  //Concept map
  {
    assert(m_widget);
    assert(m_widget->GetConceptMap());

    //m_widget->ReadFromConceptMap(copy_concept_map);
    m_widget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_widget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_widget->setMinimumHeight(m_widget->scene()->itemsBoundingRect().height() + 2);
    //Fit concept map to widget
    const QRectF all_items_rect {
      m_widget->scene()->itemsBoundingRect() //Does not work
      //m_widget->scene()->sceneRect() //Does not work
    };
    #ifndef NDEBUG
    for (const ribi::cmap::QtNode * const qtnode:
      const_cast<const cmap::QtConceptMap*>(m_widget)->GetQtNodes()
    )
    {
      //All QtNodes' their rectangles should be within all_items_rect
      assert(qtnode);
      assert(all_items_rect.contains(qtnode->boundingRect()));
    }
    #endif
    m_widget->fitInView(all_items_rect); //Does not work
    //m_widget->ensureVisible(all_items_rect,0,0); //Does not work

    #ifdef NOT_HERE_20141224
    assert(m_widget->scene()->items().count()
      >= boost::numeric_cast<int>(
        m_widget->GetConceptMap()->GetNodes().size()
        + m_widget->GetConceptMap()->GetEdges().size()));

    #endif // NOT_HERE_20141224
  }
  //Concept map as text
  {

    assert(ui->frame_concept_map_as_text->layout());
    std::string text;
    const int n_nodes = static_cast<int>(m_file->GetConceptMap()->GetNodes().size());
    for (int node_index = 1; node_index != n_nodes; ++node_index) //1: skip center node
    {
      using namespace cmap;
      const boost::shared_ptr<Node> node = m_file->GetConceptMap()->GetNodes().at(node_index);
      assert(node);
      QtConceptMapRatedConceptDialog * const widget
        = new QtConceptMapRatedConceptDialog(m_file->GetConceptMap(),node);
      assert(widget);
      widget->HideRating();
      ui->frame_concept_map_as_text->layout()->addWidget(widget);
    }
  }
    fitConceptMap();
}
