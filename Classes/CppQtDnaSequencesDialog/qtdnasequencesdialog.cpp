#include "qtdnasequencesdialog.h"

#include <cassert>
#include <functional>
#include <QLabel>

#include "dnasequence.h"
#include "fileio.h"
#include "ui_qtdnasequencesdialog.h"
#include "dna_r.h"

const std::string QtDnaSequencesDialog::sm_fail{":-("};

QtDnaSequencesDialog::QtDnaSequencesDialog(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::QtDnaSequencesDialog)
{
  ui->setupUi(this);
}

QtDnaSequencesDialog::~QtDnaSequencesDialog()
{
  delete ui;
}

std::vector<ribi::DnaSequence> QtDnaSequencesDialog::GetSequences() const noexcept
{
  using ribi::DnaSequence;
  std::vector<DnaSequence> sequences;
  sequences.push_back(DnaSequence(ui->edit_name_1->text().toStdString(),ui->edit_sequence_1->text().toStdString()));
  sequences.push_back(DnaSequence(ui->edit_name_2->text().toStdString(),ui->edit_sequence_2->text().toStdString()));
  sequences.push_back(DnaSequence(ui->edit_name_3->text().toStdString(),ui->edit_sequence_3->text().toStdString()));
  sequences.push_back(DnaSequence(ui->edit_name_4->text().toStdString(),ui->edit_sequence_4->text().toStdString()));
  return sequences;
}
