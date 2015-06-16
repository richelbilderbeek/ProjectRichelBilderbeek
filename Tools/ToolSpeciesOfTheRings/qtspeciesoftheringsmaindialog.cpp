#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtspeciesoftheringsmaindialog.h"

#include <cassert>
#include <QHBoxLayout>
#include <QDesktopWidget>
#include <QTimer>
#include "qtfractionimage.h"
#include "testtimer.h"
#include "ui_qtspeciesoftheringsmaindialog.h"
#pragma GCC diagnostic pop

const double ribi::QtSpeciesOfTheRingsMainDialog::m_trait_distance{1.0};

ribi::QtSpeciesOfTheRingsMainDialog::QtSpeciesOfTheRingsMainDialog(
  const int width,
  const int height,
  QWidget *parent
)
 :  ribi::QtHideAndShowDialog(parent),
    ui(new Ui::QtSpeciesOfTheRingsMainDialog),
    m_qtgrid{new QtFractionImage},
    m_rng_engine{42},
    m_spatial_grid(height,std::vector<int>(width,1)),
    m_species_grid(height,std::vector<double>(width,0.0))
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);

  {

    assert(!ui->widget_right->layout());
    QLayout * const layout = new QHBoxLayout;
    ui->widget_right->setLayout(layout);
    layout->addWidget(m_qtgrid);
    m_qtgrid->setMinimumSize(200,200);
  }

  //Put dialog at screen center
  {
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->setGeometry(0,0,screen.width() * 9 / 10,screen.height() * 9 / 10);
    this->move( screen.center() - this->rect().center() );
  }
  //Add some variance
  {
    const int height = static_cast<int>(m_species_grid.size());
    const int width = static_cast<int>(m_species_grid[0].size());
    for (int y=0; y!=height; ++y)
    {
      const double fy{static_cast<double>(y) * 0.1};
      for (int x=0; x!=width; ++x)
      {
        const double fx{static_cast<double>(x) * 0.1};
        const double z{std::sin(fx)+cos(fy)};
        m_species_grid[y][x] = z;
      }
    }
  }
  //Start the timer
  {
    QTimer * const timer{new QTimer(this)};
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(OnTimer()));
    timer->setInterval(10);
    timer->start();
  }
  //OnTimer();
}

ribi::QtSpeciesOfTheRingsMainDialog::~QtSpeciesOfTheRingsMainDialog()
{
  delete ui;
}

int ribi::QtSpeciesOfTheRingsMainDialog::GetHeight() const noexcept
{
  assert(m_spatial_grid.size() == m_species_grid.size());
  return m_spatial_grid.size();
}

int ribi::QtSpeciesOfTheRingsMainDialog::GetWidth() const noexcept
{
  assert(!m_species_grid.empty());
  assert(m_spatial_grid[0].size() == m_species_grid[0].size());
  return m_spatial_grid[0].size();
}

void ribi::QtSpeciesOfTheRingsMainDialog::OnTimer() noexcept
{
  SpeciesGrid new_species(m_species_grid);
  const int height{GetHeight()};
  const int width{GetWidth()};
  for (int y=0; y!=height; ++y)
  {
    for (int x=0; x!=height; ++x)
    {
      const int y_above{(y - 1 + height) % height};
      const int y_below{(y + 1 + height) % height};
      const int x_left{ (x - 1 + width) % width};
      const int x_right{(x + 1 + width) % width};
      std::vector<double> ts;
      //Collect the neightbours
      if (m_spatial_grid[y_above][x] == 1) { ts.push_back( m_species_grid[y_above][x]); }
      if (m_spatial_grid[y][x_right] == 1) { ts.push_back( m_species_grid[y][x_right]); }
      if (m_spatial_grid[y_below][x] == 1) { ts.push_back( m_species_grid[y_below][x]); }
      if (m_spatial_grid[y][x_left] == 1)  { ts.push_back( m_species_grid[y][x_left]); }
      if (ts.empty()) continue;
      std::shuffle(
        std::begin(ts),
        std::end(ts),
        m_rng_engine
      );
      const double this_trait{m_species_grid[y][x]};
      const double neighbour_trait{ts[0]};
      if (std::abs(this_trait - neighbour_trait) < m_trait_distance)
      {
        const double new_trait{
          (this_trait + neighbour_trait) / 2.0
        };
        new_species[y][x] = new_trait;
      }
      else
      {
        //No mating
      }
    }
  }
  std::swap(m_species_grid,new_species);

  m_qtgrid->Set(
    m_species_grid,
    m_spatial_grid
  );
}

#ifndef NDEBUG
void ribi::QtSpeciesOfTheRingsMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  {
    const int width{123};
    const int height{234};
    const QtSpeciesOfTheRingsMainDialog d(width,height);
    assert(d.GetHeight() == height);
    assert(d.GetWidth() == width);
  }
  {
    const int width{123};
    const int height{234};
    QtFractionImage d;
    const SpeciesGrid v(height,std::vector<double>(width,0.0));
    const SpatialGrid w(height,std::vector<int>(width,1));
    d.Set(v,w);
    assert(d.GetHeight() == height);
    assert(d.GetWidth() == width);
  }
}
#endif // NDEBUG
