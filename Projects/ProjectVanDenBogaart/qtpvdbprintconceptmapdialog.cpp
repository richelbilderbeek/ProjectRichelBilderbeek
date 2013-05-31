#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtpvdbprintconceptmapdialog.h"

#include <cassert>
#include <ctime>

#include <QKeyEvent>
#include <QPrinter>
#include <QPrintDialog>

#include "pvdbfile.h"
#include "pvdbconceptmapfactory.h"

#include "ui_qtpvdbprintconceptmapdialog.h"

QtPvdbPrintConceptMapDialog::QtPvdbPrintConceptMapDialog(
  const boost::shared_ptr<const pvdb::File>& file,
  QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtPvdbPrintConceptMapDialog)
{
  ui->setupUi(this);

  ui->label_student_name->setText(
    (std::string("Concept map van ")
      + file->GetStudentName()).c_str()
  );
  {
    std::time_t my_time;
    std::time( &my_time );
    const std::tm * const time_and_date = std::localtime(&my_time);
    const std::string s = std::asctime(time_and_date);
    ui->label_date->setText( (std::string("Datum: ") + s).c_str());
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

}

QtPvdbPrintConceptMapDialog::~QtPvdbPrintConceptMapDialog()
{
  delete ui;
}

void QtPvdbPrintConceptMapDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void QtPvdbPrintConceptMapDialog::on_button_print_clicked()
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

  //Draw the image to painter to printer
  QPainter painter;
  painter.begin(&printer);
  ui->scrollAreaWidgetContents->render(&painter);
  painter.end();

}
