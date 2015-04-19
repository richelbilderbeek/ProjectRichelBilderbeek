#include "qtdnasequencesdisplay.h"

#include <cassert>
#include <functional>
#include <QLabel>

#include "dnasequence.h"
#include "fileio.h"
#include "ui_qtdnasequencesdisplay.h"
#include "dna_r.h"

const std::string QtDnaSequencesDisplay::sm_fail{":-("};

QtDnaSequencesDisplay::QtDnaSequencesDisplay(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::QtDnaSequencesDisplay)
{
  ui->setupUi(this);
}

QtDnaSequencesDisplay::~QtDnaSequencesDisplay()
{
  delete ui;
}

void QtDnaSequencesDisplay::SetDnaSequences(
  const std::vector<ribi::DnaSequence>& sequences
) noexcept
{
  DnaR().PlotSequences(sequences,"tmp.png");
  ui->image_dna_sequences->setPixmap(QPixmap("tmp.png"));
}
