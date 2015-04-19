#include "qttestqtdnasequencesdisplay.h"

#include <QDesktopWidget>
#include <QPixmap>

#include <cassert>

#include "dnasequence.h"
#include "fileio.h"
#include "qtdnasequencesdisplay.h"
#include "ui_qttestqtdnasequencesdisplay.h"

QtTestQtDnaSequencesDisplay::QtTestQtDnaSequencesDisplay(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtTestQtDnaSequencesDisplay),
  m_display{new QtDnaSequencesDisplay(this)}
{
  ui->setupUi(this);
  assert(ui->area_content->layout());
  ui->area_content->layout()->addWidget(m_display);

  ui->button_display->click();

  //Put the dialog in the screen center
  {
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->setGeometry(0,0,screen.width() * 8 / 10, screen.height() * 8 / 10);
    this->move( screen.center() - this->rect().center() );
  }
}

QtTestQtDnaSequencesDisplay::~QtTestQtDnaSequencesDisplay()
{
  delete ui;
}


void QtTestQtDnaSequencesDisplay::on_button_display_clicked()
{
  using ribi::DnaSequence;
  std::vector<DnaSequence> sequences;
  sequences.push_back(DnaSequence(ui->edit_name_1->text().toStdString(),ui->edit_sequence_1->text().toStdString()));
  sequences.push_back(DnaSequence(ui->edit_name_2->text().toStdString(),ui->edit_sequence_2->text().toStdString()));
  sequences.push_back(DnaSequence(ui->edit_name_3->text().toStdString(),ui->edit_sequence_3->text().toStdString()));
  sequences.push_back(DnaSequence(ui->edit_name_4->text().toStdString(),ui->edit_sequence_4->text().toStdString()));
  this->m_display->SetDnaSequences(sequences);
}
