#include "qtfisherwrightermaindialog.h"

#include <sstream>

#include "newickutils.h"
#include "ui_qtfisherwrightermaindialog.h"
#include "simulation.h"
#include "phylogeny_r.h"

QtFisherWrighterMainDialog::QtFisherWrighterMainDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtFisherWrighterMainDialog)
{
  ui->setupUi(this);
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
  const std::string newick_pedigree{simulation.GetPedigree()};

  //Display newick pedigree
  {
    ui->line_newick->setText(newick_pedigree.c_str());
  }
  //Display newick pedigree as text phylogeny
  {
    std::stringstream s;
    const auto v = NewickUtils().GetPhylogeny(newick_pedigree);
    std::copy(std::begin(v),std::end(v),std::ostream_iterator<std::string>(s,"\n"));
    ui->text_newick->setPlainText(s.str().c_str());
  }
  //Display newick pedigree as .SVG
  {
    const std::string temp_svg_filename{"tmp.svg"};
    PhylogenyR().NewickToPhylogenySvg(newick_pedigree,temp_svg_filename);

    ui->svg_pedigree->setPixmap(QPixmap(temp_svg_filename.c_str()));
  }
}

int QtFisherWrighterMainDialog::ReadNumberOfGenerations() const noexcept
{
  const int n_generations{ui->box_n_generation->value()};
  return n_generations;
}
