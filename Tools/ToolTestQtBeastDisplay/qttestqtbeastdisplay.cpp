#include "qttestqtbeastdisplay.h"

#include <QDesktopWidget>

#include <cassert>

#include "dnasequence.h"
#include "qtbeastdisplay.h"
#include "qtdnasequencesdialog.h"
#include "ui_qttestqtbeastdisplay.h"

QtTestQtBeastDisplay::QtTestQtBeastDisplay(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtTestQtBeastDisplay),
  m_beast_output{new QtBeastDisplay(this)},
  m_dna_sequences_input{new QtDnaSequencesDialog(this)}
{
  ui->setupUi(this);
  assert(ui->area_content->layout());
  ui->area_content->layout()->addWidget(m_dna_sequences_input);
  ui->area_content->layout()->addWidget(m_beast_output);

  //Put the dialog in the screen center
  {
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->setGeometry(0,0,screen.width() * 8 / 10, screen.height() * 8 / 10);
    this->move( screen.center() - this->rect().center() );
  }
}

QtTestQtBeastDisplay::~QtTestQtBeastDisplay()
{
  delete ui;
}

void QtTestQtBeastDisplay::on_button_run_clicked()
{
  m_beast_output->Analyze(
    m_dna_sequences_input->GetSequences(),
    ui->box_mcmc_chainlength->value()
  );
}
