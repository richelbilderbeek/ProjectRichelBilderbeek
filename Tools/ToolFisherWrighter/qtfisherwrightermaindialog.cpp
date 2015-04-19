#include "qtfisherwrightermaindialog.h"

#include <cassert>
#include <iostream>
#include <sstream>

#include <QDesktopWidget>
#include <QTimer>

#include "fileio.h"
#include "newickutils.h"
#include "ui_qtfisherwrightermaindialog.h"
#include "simulation.h"
#include "phylogeny_r.h"
#include "qtdnasequencesdisplay.h"
#include "qtnewickdisplay.h"

QtFisherWrighterMainDialog::QtFisherWrighterMainDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtFisherWrighterMainDialog),
  m_dna_sequences_display{new QtDnaSequencesDisplay(this)},
  m_newick_display{new QtNewickDisplay(this)}
{
  ui->setupUi(this);

  assert(!ui->area_results->layout());
  assert(ui->results->layout());
  ui->results->layout()->addWidget(m_dna_sequences_display);
  ui->results->layout()->addWidget(m_newick_display);

  //Put the dialog in the screen center
  {
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->setGeometry(0,0,screen.width() * 8 / 10, screen.height() * 8 / 10);
    this->move( screen.center() - this->rect().center() );
  }

  //QTimer::singleShot(1000,this,SLOT(on_button_run_clicked()));
}

QtFisherWrighterMainDialog::~QtFisherWrighterMainDialog()
{
  delete ui;
}

void QtFisherWrighterMainDialog::on_button_run_clicked()
{
  //1) Read parameters from file
  const int dna_length{this->ui->box_dna_length->value()};
  const double mutation_rate{ui->box_mutation_rate->value()};
  const int n_generations{ReadNumberOfGenerations()};
  const int pop_size{ui->box_pop_size->value()};
  const int seed{ui->box_seed->value()};
  const Parameters parameters(
    dna_length,
    mutation_rate,
    n_generations,
    pop_size,
    seed
  );

  //2) Run simulation
  Simulation simulation(parameters);
  //Loop n_generations
  //const int n_generations{ReadNumberOfGenerations()};
  for (int i=0; i!=n_generations; ++i)
  {
    simulation.NextGeneration();
    if (!simulation.GetCurrentSequences().empty())
    {
      //Only show the sequence of the first individual
      //std::cout << i << ": " << simulation.GetCurrentSequences()[0].GetSequence() << '\n';
    }
  }
  const std::string newick{simulation.GetPedigree()};

  this->m_dna_sequences_display->SetDnaSequences(simulation.GetCurrentSequences());

  this->repaint();

  //Display newick
  this->m_newick_display->SetNewick(newick);

}

int QtFisherWrighterMainDialog::ReadNumberOfGenerations() const noexcept
{
  const int n_generations{ui->box_n_generation->value()};
  return n_generations;
}

void QtFisherWrighterMainDialog::on_button_run_next_clicked()
{
  ui->box_seed->setValue(ui->box_seed->value() + 1);
  ui->button_run->click();
}

