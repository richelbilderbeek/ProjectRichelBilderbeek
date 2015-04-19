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

void QtFisherWrighterMainDialog::DisplayNewick(const std::string& newick) noexcept
{
  ui->line_newick->setText(newick.c_str());
}

void QtFisherWrighterMainDialog::DisplayNewickExtant(const std::string& newick_all) noexcept
{
  const std::string newick_extant{PhylogenyR().DropExtict(newick_all)};
  ui->line_newick_extant->setText(newick_extant.c_str());
}

void QtFisherWrighterMainDialog::DisplayNewickToLttPlot(const std::string& newick) noexcept
{
  QLabel * const label{ui->image_lttPlot};
  const std::string temp_png_filename{
    ribi::fileio::FileIo().GetTempFileName(".png")
  };
  try
  {
    PhylogenyR().NewickToLttPlot(newick,temp_png_filename,PhylogenyR::GraphicsFormat::png);
    label->setPixmap(QPixmap(temp_png_filename.c_str()));
    ribi::fileio::FileIo().DeleteFile(temp_png_filename);
  }
  catch (std::runtime_error& e)
  {
    //label->setText(e.what());
    label->setText(":-(");
  }
}

void QtFisherWrighterMainDialog::DisplayNewickToLttPlotExtant(const std::string& newick) noexcept
{
  QLabel * const label{ui->image_lttPlot_extant};
  const std::string temp_png_filename{
    ribi::fileio::FileIo().GetTempFileName(".png")
  };
  try
  {
    PhylogenyR().NewickToLttPlot(
      newick,
      temp_png_filename,
      PhylogenyR::GraphicsFormat::png,
      false //show_fossils
    );
    label->setPixmap(QPixmap(temp_png_filename.c_str()));
    ribi::fileio::FileIo().DeleteFile(temp_png_filename);
  }
  catch (std::runtime_error& e)
  {
    label->setText(":-(");
    //label->setText(e.what());
  }
}

void QtFisherWrighterMainDialog::DisplayPhylogenyNewickUtilsAll(const std::string& newick) noexcept
{
  QLabel * const label{ui->image_phylogeny_newickutils};
  try
  {
    const std::string temp_svg_filename{
      ribi::fileio::FileIo().GetTempFileName(".svg")
    };
    assert(!ribi::fileio::FileIo().IsRegularFile(temp_svg_filename));
    NewickUtils().NewickToPhylogeny(
      newick,
      temp_svg_filename,
      NewickUtils::GraphicsFormat::svg
    );
    label->setPixmap(QPixmap(temp_svg_filename.c_str()));
    //Delete the temporary file
    ribi::fileio::FileIo().DeleteFile(temp_svg_filename);
  }
  catch (std::runtime_error& e)
  {
    //std::clog << e.what() << '\n';
    label->setText(":-(");
  }

}

void QtFisherWrighterMainDialog::DisplayPhylogenyNewickUtilsExtant(const std::string& newick) noexcept
{
  QLabel * const label{ui->image_phylogeny_extant_newickutils};
  try
  {
    const std::string temp_png_filename{
      ribi::fileio::FileIo().GetTempFileName(".png")
    };
    assert(!ribi::fileio::FileIo().IsRegularFile(temp_png_filename));
    NewickUtils().NewickToPhylogeny(
      newick,
      temp_png_filename,
      NewickUtils::GraphicsFormat::png,
      false //plot_fossils
    );
    label->setPixmap(QPixmap(temp_png_filename.c_str()));
    //Delete the temporary file
    ribi::fileio::FileIo().DeleteFile(temp_png_filename);
  }
  catch (std::runtime_error& e)
  {
    //std::clog << e.what() << '\n';
    label->setText(":-(");
  }
  catch (std::logic_error& e)
  {
    //std::clog << e.what() << '\n';
    label->setText(":-(");
  }

}

void QtFisherWrighterMainDialog::DisplayPhylogenyRall(const std::string& newick) noexcept
{
  QLabel * const label{ui->image_phylogeny};
  try
  {
    const std::string temp_png_filename{
      ribi::fileio::FileIo().GetTempFileName(".png")
    };
    assert(!ribi::fileio::FileIo().IsRegularFile(temp_png_filename));
    PhylogenyR().NewickToPhylogeny(
      newick,
      temp_png_filename,
      PhylogenyR::GraphicsFormat::png
    );
    label->setPixmap(QPixmap(temp_png_filename.c_str()));
    //Delete the temporary file
    ribi::fileio::FileIo().DeleteFile(temp_png_filename);
  }
  catch (std::runtime_error& e)
  {
    //std::clog << e.what() << '\n';
    label->setText(":-(");
  }
}

void QtFisherWrighterMainDialog::DisplayPhylogenyRextant(const std::string& newick) noexcept
{
  QLabel * const label{ui->image_phylogeny_extant};
  try
  {
    const std::string temp_png_filename{
      ribi::fileio::FileIo().GetTempFileName(".png")
    };
    PhylogenyR().NewickToPhylogeny(
      newick,
      temp_png_filename,
      PhylogenyR::GraphicsFormat::png,
      false //plot_fossils
    );
    label->setPixmap(QPixmap(temp_png_filename.c_str()));
    ribi::fileio::FileIo().DeleteFile(temp_png_filename);
  }
  catch (std::runtime_error& e)
  {
    label->setText(":-(");
    //std::clog << e.what() << '\n';
  }

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
  DisplayNewick(newick_pedigree);
  this->DisplayPhylogenyRall(newick_pedigree);
  this->DisplayPhylogenyRextant(newick_pedigree);
  this->DisplayPhylogenyNewickUtilsAll(newick_pedigree);
  //this->DisplayPhylogenyNewickUtilsExtant(newick_pedigree);
  this->DisplayNewickToLttPlot(newick_pedigree);
  this->DisplayNewickToLttPlotExtant(newick_pedigree);
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
