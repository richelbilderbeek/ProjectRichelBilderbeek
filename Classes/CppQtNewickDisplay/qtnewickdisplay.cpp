#include "qtnewickdisplay.h"

#include <cassert>
#include <functional>
#include <QLabel>

#include "fileio.h"
#include "ui_qtnewickdisplay.h"
#include "phylogeny_r.h"
#include "newickutils.h"

const std::string QtNewickDisplay::sm_fail{":-("};

QtNewickDisplay::QtNewickDisplay(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::QtNewickDisplay)
{
  ui->setupUi(this);
}

QtNewickDisplay::~QtNewickDisplay()
{
  delete ui;
}

void QtNewickDisplay::DisplayNewick(
  const std::string& newick,
  const QtNewickDisplay::Lineages lineages
) noexcept
{
  switch (lineages)
  {
    case Lineages::all:
      ui->line_newick->setText(newick.c_str());
      return;
    break;
    case Lineages::extant:
    {
      try
      {
        const std::string newick_extant{PhylogenyR().DropExtinct(newick)};
        ui->line_newick_extant->setText(newick_extant.c_str());
      }
      catch (std::runtime_error& e)
      {
        ui->line_newick_extant->setText(sm_fail.c_str());
      }
      return;
    }
    break;
    default:
      assert(!"Should not get here");
    break;
  }
  assert(!"Should not get here");
}


void QtNewickDisplay::DisplayNewickToLttPlot(
  const std::string& newick,
  const QtNewickDisplay::Lineages lineages
) noexcept
{
  QLabel * label{nullptr};
  bool show_fossils{true};
  if (lineages == QtNewickDisplay::Lineages::all)
  {
    label = ui->image_lttPlot_all;
    show_fossils = true; //Remains the same
  }
  if (lineages == QtNewickDisplay::Lineages::extant)
  {
    label = ui->image_lttPlot_extant;
    show_fossils = false; //Changes
  }
  const std::string temp_png_filename{
    ribi::fileio::FileIo().GetTempFileName(".png")
  };
  try
  {
    PhylogenyR().NewickToLttPlot(
      newick,
      temp_png_filename,
      PhylogenyR::GraphicsFormat::png,
      show_fossils
    );
    label->setPixmap(QPixmap(temp_png_filename.c_str()));
    ribi::fileio::FileIo().DeleteFile(temp_png_filename);
  }
  catch (std::runtime_error& e)
  {
    label->setText(sm_fail.c_str());
    //label->setText(e.what());
  }
}

void QtNewickDisplay::DisplayPhylogeny(
  const std::string& newick,
  const Lineages lineages,
  const Tool tool
) noexcept
{
  QLabel * label{nullptr};
  std::function<void(const std::string&, const std::string&)> f;
  if (lineages == Lineages::all && tool == Tool::NewickUtils)
  {
    label = ui->image_phylogeny_newickutils_all;
    f = [](const std::string& newick, const std::string& filename)
    {
      NewickUtils().NewickToPhylogeny(
      newick,
      filename,
      NewickUtils::GraphicsFormat::svg,
      true //plot_fossils
      );
    };
  }
  if (lineages == Lineages::extant && tool == Tool::NewickUtils)
  {
    label = ui->image_phylogeny_newickutils_extant;
    f = [](const std::string& newick, const std::string& filename)
    {
      NewickUtils().NewickToPhylogeny(
      newick,
      filename,
      NewickUtils::GraphicsFormat::svg,
      false //plot_fossils
      );
    };
  }
  if (lineages == Lineages::all && tool == Tool::PhylogenyR)
  {
    label = ui->image_phylogeny_phylogenyr_all;
    f = [](const std::string& newick, const std::string& filename)
    {
      PhylogenyR().NewickToPhylogeny(
      newick,
      filename,
      PhylogenyR::GraphicsFormat::png,
      true //plot_fossils
      );
    };
  }
  if (lineages == Lineages::extant && tool == Tool::PhylogenyR)
  {
    label = ui->image_phylogeny_phylogenyr_extant;
    f = [](const std::string& newick, const std::string& filename)
    {
      PhylogenyR().NewickToPhylogeny(
      newick,
      filename,
      PhylogenyR::GraphicsFormat::png,
      false //plot_fossils
      );
    };
  }
  assert(label);
  try
  {
    const std::string temp_filename{
      ribi::fileio::FileIo().GetTempFileName("") //Cannot put .svg or .png here, as images won't display then
    };
    assert(!ribi::fileio::FileIo().IsRegularFile(temp_filename));
    f(newick,temp_filename);
    label->setPixmap(QPixmap(temp_filename.c_str()));
    //Delete the temporary file
    ribi::fileio::FileIo().DeleteFile(temp_filename);
  }
  catch (std::runtime_error& e)
  {
    //std::clog << e.what() << '\n';
    label->setText(sm_fail.c_str());
  }
}

void QtNewickDisplay::SetNewick(const std::string& newick) noexcept
{
  {
    const std::vector<std::function<void()>> fs = {
      [this,newick]() { DisplayNewick(newick,Lineages::all); },
      [this,newick]() { DisplayPhylogeny(newick,Lineages::all,Tool::NewickUtils); },
      [this,newick]() { DisplayNewick(newick,Lineages::extant); }
    };
    for (const auto f: fs) { f(); this->repaint();}
  }
  //Take a shortcut if extant species cannot be calculated by the R ape package
  if (ui->line_newick_extant->text().toStdString() == sm_fail)
  {
    ui->image_lttPlot_all->setText(sm_fail.c_str());
    ui->image_lttPlot_extant->setText(sm_fail.c_str());
    ui->image_phylogeny_newickutils_extant->setText(sm_fail.c_str());
    ui->image_phylogeny_phylogenyr_all->setText(sm_fail.c_str());
    ui->image_phylogeny_phylogenyr_extant->setText(sm_fail.c_str());
    return;
  }
  //Do all functions that do work
  {
    const std::vector<std::function<void()>> fs = {
      [this,newick]() { DisplayPhylogeny(newick,Lineages::extant,Tool::NewickUtils); },
      [this,newick]() { DisplayPhylogeny(newick,Lineages::all,Tool::PhylogenyR); },
      [this,newick]() { DisplayPhylogeny(newick,Lineages::extant,Tool::PhylogenyR); },
      [this,newick]() { DisplayNewickToLttPlot(newick,Lineages::all); },
      [this,newick]() { DisplayNewickToLttPlot(newick,Lineages::extant); },
      [this,newick]() {   },
      [this,newick]() {   },
    };
    for (const auto f: fs) { f(); this->repaint();}
  }
}
