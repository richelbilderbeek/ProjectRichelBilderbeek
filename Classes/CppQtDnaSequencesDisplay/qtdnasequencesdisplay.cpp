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
  ribi::fileio::FileIo fileio;
  const std::string temp_filename{
    fileio.GetTempFileName(".png")
  };
  ribi::DnaR().PlotSequences(sequences,temp_filename);
  ui->image_dna_sequences->setPixmap(QPixmap(temp_filename.c_str()));
  fileio.DeleteFile(temp_filename);
}
