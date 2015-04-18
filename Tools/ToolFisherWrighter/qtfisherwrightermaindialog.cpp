#include "qtfisherwrightermaindialog.h"

#include <cassert>
#include <iostream>
#include <sstream>

#include <QDesktopWidget>

#include "fileio.h"
#include "newickutils.h"
#include "ui_qtfisherwrightermaindialog.h"
#include "simulation.h"
#include "phylogeny_r.h"

QtFisherWrighterMainDialog::QtFisherWrighterMainDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtFisherWrighterMainDialog)
{
  ui->setupUi(this);
  ui->button_run->click();
  //Put the dialog in the screen center
  {
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->setGeometry(0,0,screen.width() * 8 / 10, screen.height() * 8 / 10);
    this->move( screen.center() - this->rect().center() );
  }
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
  //Display newick phylogeny
  try
  {

    const std::string temp_png_filename{
      ribi::fileio::FileIo().GetTempFileName(".png")
    };
    assert(!ribi::fileio::FileIo().IsRegularFile(temp_png_filename));
    PhylogenyR().NewickToPhylogeny(
      newick_pedigree,
      temp_png_filename,
      PhylogenyR::GraphicsFormat::png
    );
    ui->image_phylogeny->setPixmap(QPixmap(temp_png_filename.c_str()));
    //Delete the temporary file
    ribi::fileio::FileIo().DeleteFile(temp_png_filename);
  }
  catch (std::runtime_error& e)
  {
    std::clog << e.what() << '\n';
    ui->image_phylogeny->setText("No phylogeny");
  }
  //Display newick phylogeny of extant species
  try
  {

    const std::string temp_png_filename{
      ribi::fileio::FileIo().GetTempFileName(".png")
    };
    PhylogenyR().NewickToPhylogeny(
      newick_pedigree,
      temp_png_filename,
      PhylogenyR::GraphicsFormat::png,
      false //plot_fossils
    );
    ui->image_phylogeny_extant->setPixmap(QPixmap(temp_png_filename.c_str()));
    ribi::fileio::FileIo().DeleteFile(temp_png_filename);
  }
  catch (std::runtime_error& e)
  {
    std::clog << e.what() << '\n';
    ui->image_phylogeny_extant->setText("No phylogeny");
  }
  //NewickToLttPlot
  {
    const std::string temp_png_filename{
      ribi::fileio::FileIo().GetTempFileName(".png")
    };
    try
    {
      PhylogenyR().NewickToLttPlot(newick_pedigree,temp_png_filename,PhylogenyR::GraphicsFormat::png);
      ui->image_lttPlot->setPixmap(QPixmap(temp_png_filename.c_str()));
      ribi::fileio::FileIo().DeleteFile(temp_png_filename);
    }
    catch (std::runtime_error& e)
    {
      ui->image_lttPlot->setText(e.what());
    }
  }
  //NewickToLttPlot for extant species
  {
    const std::string temp_png_filename{
      ribi::fileio::FileIo().GetTempFileName(".png")
    };
    try
    {
      PhylogenyR().NewickToLttPlot(
        newick_pedigree,
        temp_png_filename,
        PhylogenyR::GraphicsFormat::png,
        false //show_fossils
      );
      ui->image_lttPlot_extant->setPixmap(QPixmap(temp_png_filename.c_str()));
      ribi::fileio::FileIo().DeleteFile(temp_png_filename);
    }
    catch (std::runtime_error& e)
    {
      ui->image_lttPlot_extant->setText(e.what());
    }
  }
  //Display newick pedigree as text phylogeny
  {
    std::stringstream s;
    const auto v = NewickUtils().GetPhylogeny(newick_pedigree);
    std::copy(std::begin(v),std::end(v),std::ostream_iterator<std::string>(s,"\n"));
    ui->text_newick->setPlainText(s.str().c_str());
  }
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
