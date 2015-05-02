#include "qttree.h"

#include <cassert>
#include <sstream>

#include <QDesktopWidget>

#include "simulation.h"
#include "ui_qttree.h"

QtTree::QtTree(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::QtTree),
  m_rng{nullptr},
  m_tree{nullptr}
{
  Rng::Test();
  Tree::Test();
  Simulation::Test();

  ui->setupUi(this);
  {
    //Put the dialog in the screen center
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->move( screen.center() - this->rect().center() );
  }
}

QtTree::~QtTree()
{
  delete ui;
}

void QtTree::DisplayTree()
{
  if (!m_tree) return;
  std::stringstream s;
  m_tree->DisplayActive(s);
  m_log += s.str() + "\n";
  ui->text->setPlainText(m_log.c_str());
}

int QtTree::GetDispersalDistance() const noexcept
{
  return ui->box_dispersal_distance->value();
}

DispersalKernel QtTree::GetDispersalKernel() const noexcept
{
  if (ui->box_dispersal_type->currentText() == "Square") return DispersalKernel::square;
  if (ui->box_dispersal_type->currentText() == "Normal") return DispersalKernel::normal;
  assert(!"Should not get here");
}

int QtTree::GetLength() const noexcept
{
  return ui->box_height->value();
}

double QtTree::GetMinSpeciationRate() const noexcept
{
  return ui->box_min_speciation_rate->value();
}

double QtTree::GetTolerance() const noexcept
{
  return ui->box_tolerance->value();
}

Rng QtTree::GetRng() const noexcept
{
  return Rng(GetRngSeed(),GetRngType());
}

int QtTree::GetRngSeed() const noexcept
{
  return ui->box_rng_seed->value();
}

Rng::Type QtTree::GetRngType() const noexcept
{
  if (ui->box_rng_type->currentText() == "Bilderbeek") { return Rng::Type::bilderbeek;  }
  if (ui->box_rng_type->currentText() == "Rosindell" ) { return Rng::Type::rosindell;  }
  assert(!"Should not get here");
}

int QtTree::GetWidth() const noexcept
{
  return ui->box_width->value();
}

void QtTree::on_button_start_clicked()
{
  delete m_rng;
  m_rng = new Rng(GetRngSeed(),GetRngType());

  delete m_tree;
  m_tree = new Tree(
    *m_rng,
    GetWidth(),
    GetLength(),
    GetMinSpeciationRate(),
    GetDispersalDistance(),
    GetTolerance(),
    GetDispersalKernel()
  );
  m_log.clear();

  DisplayTree();
}

void QtTree::on_button_next_clicked()
{
  if (!m_tree) return;
  m_tree->Update();
  DisplayTree();
}
