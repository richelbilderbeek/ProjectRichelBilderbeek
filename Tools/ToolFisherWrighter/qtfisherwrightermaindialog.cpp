#include "qtfisherwrightermaindialog.h"

#include <cassert>
#include <iostream>
#include <sstream>

#include <QDesktopWidget>
#include <QTimer>

#include "fileio.h"
#include "newickutils.h"
#include "ui_qtfisherwrightermaindialog.h"
#include "fisherwrightermenudialog.h"
#include "fisherwrightersimulation.h"
#include "phylogeny_r.h"
#include "qtdnasequencesdisplay.h"
#include "qtbeastdisplay.h"
#include "qtnewickdisplay.h"

ribi::fw::QtFisherWrighterMainDialog::QtFisherWrighterMainDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtFisherWrighterMainDialog),
  m_beast_display{new QtBeastDisplay(this)},
  m_dna_sequences_display{new QtDnaSequencesDisplay(this)},
  m_newick_display{new QtNewickDisplay(this)}
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);

  assert(!ui->area_results->layout());
  assert(ui->results->layout());
  ui->results->layout()->addWidget(m_dna_sequences_display);
  ui->results->layout()->addWidget(m_beast_display);
  ui->results->layout()->addWidget(m_newick_display);

  //Put the dialog in the screen center
  {
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->setGeometry(0,0,screen.width() * 8 / 10, screen.height() * 8 / 10);
    this->move( screen.center() - this->rect().center() );
  }

  //QTimer::singleShot(1000,this,SLOT(on_button_run_clicked()));
}

ribi::fw::QtFisherWrighterMainDialog::~QtFisherWrighterMainDialog()
{
  delete ui;
}

void ribi::fw::QtFisherWrighterMainDialog::on_button_run_clicked()
{
  //1) Read parameters from file
  const int dna_length{this->ui->box_dna_length->value()};
  const double mutation_rate{ui->box_mutation_rate->value()};
  const int n_generations{ReadNumberOfGenerations()};
  const int pop_size{ui->box_pop_size->value()};
  const int seed{ui->box_seed->value()};
  const ribi::fw::Parameters parameters(
    dna_length,
    mutation_rate,
    n_generations,
    pop_size,
    seed
  );

  //2) Run simulation
  ribi::fw::Simulation simulation(parameters);
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

  this->m_beast_display->Analyze(
    simulation.GetCurrentSequences(),
    ui->box_mcmc_chainlength->value()
  );

  this->repaint();

  this->m_dna_sequences_display->SetDnaSequences(simulation.GetCurrentSequences());

  this->repaint();

  //Display newick
  this->m_newick_display->SetNewick(newick);

}

int ribi::fw::QtFisherWrighterMainDialog::ReadNumberOfGenerations() const noexcept
{
  const int n_generations{ui->box_n_generation->value()};
  return n_generations;
}

void ribi::fw::QtFisherWrighterMainDialog::on_button_run_next_clicked()
{
  ui->box_seed->setValue(ui->box_seed->value() + 1);
  ui->button_run->click();
}

#ifndef NDEBUG
void ribi::fw::QtFisherWrighterMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  ribi::fw::MenuDialog();
}
#endif // NDEBUG
