#include "qttestqtdnasequencesdisplay.h"

#include <QDesktopWidget>
#include <QPixmap>
#include <QFileDialog>

#include <cassert>
#include <fstream>

#include "dnasequence.h"
#include "fastafile.h"
#include "fileio.h"
#include "qtdnasequencesdisplay.h"
#include "qtdnasequencesdialog.h"
#include "ui_qttestqtdnasequencesdisplay.h"

QtTestQtDnaSequencesDisplay::QtTestQtDnaSequencesDisplay(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtTestQtDnaSequencesDisplay),
  m_dialog{new QtDnaSequencesDialog(this)},
  m_display{new QtDnaSequencesDisplay(this)}
{
  ui->setupUi(this);

  //assert(ui->formLayout->layout());

  assert(ui->area_content->layout());  
  ui->area_content->layout()->addWidget(m_dialog);
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

std::vector<ribi::DnaSequence> QtTestQtDnaSequencesDisplay::GetSequences() const noexcept
{
  assert(m_dialog);
  return m_dialog->GetSequences();
}

void QtTestQtDnaSequencesDisplay::on_button_display_clicked()
{
  this->m_display->SetDnaSequences(
    GetSequences()
  );
}

void QtTestQtDnaSequencesDisplay::on_button_fasta_clicked()
{
  FastaFile f(GetSequences());
  const std::string filename {QFileDialog::getSaveFileName().toStdString()};
  std::ofstream file(filename.c_str());
  file << f;
}
