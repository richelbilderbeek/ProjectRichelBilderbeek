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

  for (const auto& box:
    {
      ui->box_display_all,
      ui->box_display_branch_lengths,
      ui->box_display_branching_times,
      ui->box_display_extant,
      ui->box_display_lttplots,
      ui->box_display_phylogeny_newickutils,
      ui->box_display_phylogeny_phylogenyr
    }
  )
  {
    QObject::connect(box,SIGNAL(clicked()),this,SLOT(OnBoxClicked()));
  }
  OnBoxClicked();
}

QtNewickDisplay::~QtNewickDisplay()
{
  delete ui;
}

std::vector<QLabel*> QtNewickDisplay::CollectExtinctAndExtantImages()
{
  return {
    ui->image_branching_times_all,
    ui->image_branch_lengths_all,
    ui->image_lttPlot_all,
    ui->image_phylogeny_newickutils_all,
    ui->image_phylogeny_phylogenyr_all
  };
}

std::vector<QLabel*> QtNewickDisplay::CollectExtantImages()
{
  return {
    ui->image_branching_times_extant,
    ui->image_branch_lengths_extant,
    ui->image_lttPlot_extant,
    ui->image_phylogeny_newickutils_extant,
    ui->image_phylogeny_phylogenyr_extant
  };
}

void QtNewickDisplay::DisplayBranchingTimes(
  std::string newick,
  const QtNewickDisplay::Lineages lineages
) noexcept
{
  QLabel * label{nullptr};
  switch (lineages)
  {
    case Lineages::all: label = ui->image_branching_times_all; break;
    case Lineages::extant: label = ui->image_branching_times_extant; break;
  }
  assert(label);
  if (!label->isVisible()) return;
  const std::string temp_png_filename{
    ribi::fileio::FileIo().GetTempFileName(".png")
  };
  try
  {
    if (lineages == Lineages::extant)
    {
      newick = PhylogenyR().DropExtinct(newick);
    }

    PhylogenyR().NewickToBranchingTimes(
      newick,
      temp_png_filename,
      PhylogenyR::GraphicsFormat::png
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

void QtNewickDisplay::DisplayBranchLengths(
  std::string newick,
  const QtNewickDisplay::Lineages lineages
) noexcept
{
  QLabel * label{nullptr};
  switch (lineages)
  {
    case QtNewickDisplay::Lineages::all: label = ui->image_branch_lengths_all; break;
    case QtNewickDisplay::Lineages::extant: label = ui->image_branch_lengths_extant; break;
  }
  assert(label);
  if (!label->isVisible()) return;

  const std::string temp_png_filename{
    ribi::fileio::FileIo().GetTempFileName(".png")
  };
  try
  {
    if (lineages == Lineages::extant)
    {
      newick = PhylogenyR().DropExtinct(newick);
    }
    PhylogenyR().NewickToBranchLengths(
      newick,
      temp_png_filename,
      PhylogenyR::GraphicsFormat::png
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
void QtNewickDisplay::DisplayNewick(
  const std::string& newick,
  const QtNewickDisplay::Lineages lineages
) noexcept
{
  switch (lineages)
  {
    case Lineages::all:
      if (!ui->line_newick->isVisible()) return;
      ui->line_newick->setText(newick.c_str());
      return;
    break;
    case Lineages::extant:
    {
      if (!ui->line_newick_extant->isVisible()) return;
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
  assert(label);
  if (!label->isVisible()) return;

  const std::string temp_png_filename{
    ribi::fileio::FileIo().GetTempFileName(".png")
  };
  try
  {

    PhylogenyR().NewickToLttPlot(
      show_fossils ? newick : PhylogenyR().DropExtinct(newick),
      temp_png_filename,
      PhylogenyR::GraphicsFormat::png
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
        PhylogenyR::GraphicsFormat::png
      );
    };
  }
  if (lineages == Lineages::extant && tool == Tool::PhylogenyR)
  {
    label = ui->image_phylogeny_phylogenyr_extant;
    f = [](const std::string& newick, const std::string& filename)
    {
      PhylogenyR().NewickToPhylogeny(
        PhylogenyR().DropExtinct(newick),
        filename,
        PhylogenyR::GraphicsFormat::png
      );
    };
  }
  assert(label);
  if (!label->isVisible()) return;
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

void QtNewickDisplay::OnBoxClicked()
{
  ui->line_newick->setVisible(ui->box_display_all->isChecked());
  ui->line_newick_extant->setVisible(ui->box_display_extant->isChecked());

  for (auto image: CollectExtinctAndExtantImages())
  {
    image->setVisible(ui->box_display_all->isChecked());
  }
  for (auto image: CollectExtantImages())
  {
    image->setVisible(ui->box_display_extant->isChecked());
  }
  for (auto image: { ui->image_branching_times_all, ui->image_branching_times_extant } )
  {
    if (!ui->box_display_branching_times->isChecked()) image->setVisible(false);
  }
  for (auto image: { ui->image_branch_lengths_all, ui->image_branch_lengths_extant } )
  {
    if (!ui->box_display_branch_lengths->isChecked()) image->setVisible(false);
  }
  for (auto image: { ui->image_lttPlot_all, ui->image_lttPlot_extant } )
  {
    if (!ui->box_display_lttplots->isChecked()) image->setVisible(false);
  }
  for (auto image: { ui->image_phylogeny_newickutils_all, ui->image_phylogeny_newickutils_extant } )
  {
    if (!ui->box_display_phylogeny_newickutils->isChecked()) image->setVisible(false);
  }
  for (auto image: { ui->image_phylogeny_phylogenyr_all, ui->image_phylogeny_phylogenyr_extant } )
  {
    if (!ui->box_display_phylogeny_phylogenyr->isChecked()) image->setVisible(false);
  }
}

void QtNewickDisplay::SetNewick(const std::string& newick) noexcept
{
  {
    const std::vector<std::function<void()>> fs = {
      [this,newick]() { DisplayNewick(newick,Lineages::all); },
      [this,newick]() { DisplayPhylogeny(newick,Lineages::all,Tool::NewickUtils); },
      [this,newick]() { DisplayNewick(newick,Lineages::extant); },
      [this,newick]() { DisplayBranchingTimes(newick,Lineages::all); },
      [this,newick]() { DisplayBranchingTimes(newick,Lineages::extant); },
      [this,newick]() { DisplayBranchLengths(newick,Lineages::all); },
      [this,newick]() { DisplayBranchLengths(newick,Lineages::extant); }
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
      [this,newick]() { DisplayNewickToLttPlot(newick,Lineages::extant); }
    };
    for (const auto f: fs) { f(); this->repaint();}
  }
}
