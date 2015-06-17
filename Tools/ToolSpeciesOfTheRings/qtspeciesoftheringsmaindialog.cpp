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
const double ribi::QtSpeciesOfTheRingsMainDialog::m_trait_mutation{0.1};

ribi::QtSpeciesOfTheRingsMainDialog::QtSpeciesOfTheRingsMainDialog(
  const int width,
  const int height,
  QWidget *parent
)
 :  ribi::QtHideAndShowDialog(parent),
    ui(new Ui::QtSpeciesOfTheRingsMainDialog),
    m_normal_distribution(0.0,m_trait_mutation),
    m_qtgrid{new QtFractionImage},
    m_rng_engine{41}, //41 and 42 show nice ring
    m_spatial_grid(height,std::vector<Space>(width,Space::Land)),
    m_species_grid(height,std::vector<Species>(width,Species::Absent)),
    m_trait_grid(height,std::vector<double>(width,0.0)),
    m_t{0}
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
  //Add mountain
  {
    const int height = static_cast<int>(m_species_grid.size());
    const int width = static_cast<int>(m_species_grid[0].size());
    const int x_from{width * 1 / 4};
    const int x_to{width * 3 / 4};
    const int y_from{height * 1 / 4};
    const int y_to{height * 3 / 4};
    //Wall around
    for (int y=0; y!=height; ++y)
    {
      m_spatial_grid[y][0] = Space::Mountain;
      m_spatial_grid[y][width - 1] = Space::Mountain;
    }
    for (int x=0; x!=width; ++x)
    {
      m_spatial_grid[0][x] = Space::Mountain;
      m_spatial_grid[height - 1][x] = Space::Mountain;
    }
    //Mountain at center
    for (int y=y_from; y!=y_to; ++y)
    {
      for (int x=x_from; x!=x_to; ++x)
      {
        m_spatial_grid[y][x] = Space::Mountain;
      }
    }
  }
  //Add some species
  {
    const int height = static_cast<int>(m_species_grid.size());
    const int width = static_cast<int>(m_species_grid[0].size());
    m_species_grid[height / 5][width / 2] = Species::Present;
  }
  //Add some variance
  {
    const int height = static_cast<int>(m_trait_grid.size());
    const int width = static_cast<int>(m_trait_grid[0].size());
    for (int y=0; y!=height; ++y)
    {
      const double fy{static_cast<double>(y) * 0.1};
      for (int x=0; x!=width; ++x)
      {
        const double fx{static_cast<double>(x) * 0.1};
        const double z{std::sin(fx)+cos(fy)};
        //const double z{m_normal_distribution(m_rng_engine)};
        //const double z{0.0};
        m_trait_grid[y][x] = z;
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
  Display();
  //OnTimer();
}

ribi::QtSpeciesOfTheRingsMainDialog::~QtSpeciesOfTheRingsMainDialog()
{
  delete ui;
}

void ribi::QtSpeciesOfTheRingsMainDialog::Display()
{
  m_qtgrid->Set(
    m_spatial_grid,
    m_species_grid,
    m_trait_grid
  );

}

int ribi::QtSpeciesOfTheRingsMainDialog::GetHeight() const noexcept
{
  assert(m_spatial_grid.size() == m_trait_grid.size());
  assert(m_species_grid.size() == m_trait_grid.size());
  return m_spatial_grid.size();
}

int ribi::QtSpeciesOfTheRingsMainDialog::GetWidth() const noexcept
{
  assert(!m_trait_grid.empty());
  assert(m_spatial_grid[0].size() == m_trait_grid[0].size());
  assert(m_species_grid[0].size() == m_trait_grid[0].size());
  return m_spatial_grid[0].size();
}

void ribi::QtSpeciesOfTheRingsMainDialog::OnTimer() noexcept
{
  //Add mountain
  /*
  if (m_t % 10 == 0)
  {
    const int n{std::min(m_t / 10,GetWidth() / 2)};

    for (int i=0; i!=n; ++i)
    {
      m_spatial_grid[GetHeight() / 2][-(n/2) + i + (GetWidth() / 2)]
        = Space::Mountain
      ;
    }
  }
  */
  ++m_t;

  TraitGrid new_traits(m_trait_grid);
  SpeciesGrid new_species(m_species_grid);
  const int height{GetHeight()};
  const int width{GetWidth()};
  for (int y=0; y!=height; ++y)
  {
    for (int x=0; x!=height; ++x)
    {
      if (m_spatial_grid[y][x] == Space::Mountain) continue;

      //Collect the neightbours
      std::vector<double> ts;
      const int y_above{(y - 1 + height) % height};
      const int y_below{(y + 1 + height) % height};
      const int x_left{ (x - 1 + width) % width};
      const int x_right{(x + 1 + width) % width};
      if (m_spatial_grid[y_above][x] == Space::Land
        && m_species_grid[y_above][x] == Species::Present) { ts.push_back( m_trait_grid[y_above][x]); }
      if (m_spatial_grid[y][x_right] == Space::Land
        && m_species_grid[y][x_right] == Species::Present) { ts.push_back( m_trait_grid[y][x_right]); }
      if (m_spatial_grid[y_below][x] == Space::Land
        && m_species_grid[y_below][x] == Species::Present) { ts.push_back( m_trait_grid[y_below][x]); }
      if (m_spatial_grid[y][x_left ] == Space::Land
        && m_species_grid[y][x_left ] == Species::Present) { ts.push_back( m_trait_grid[y][x_left]); }
      if (ts.empty()) continue;

      std::shuffle(
        std::begin(ts),
        std::end(ts),
        m_rng_engine
      );

      //Colonization?
      if (m_species_grid[y][x] == Species::Absent)
      {
        new_traits[y][x] = ts[0] + m_normal_distribution(m_rng_engine);
        new_species[y][x] = Species::Present;
        continue;
      }

      //Species was present
      const double this_trait{m_trait_grid[y][x]};
      const double neighbour_trait{ts[0]};
      if (std::abs(this_trait - neighbour_trait) < m_trait_distance)
      {
        const double new_trait{
          ((this_trait + neighbour_trait) / 2.0)
          + m_normal_distribution(m_rng_engine)
        };
        new_traits[y][x] = new_trait;
      }
      else
      {
        //No mating, only mutation
        new_traits[y][x]+=m_normal_distribution(m_rng_engine);
      }
    }
  }
  std::swap(m_trait_grid,new_traits);
  std::swap(m_species_grid,new_species);
  Display();
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
    const SpatialGrid v(height,std::vector<Space>(width,Space::Land));
    const SpeciesGrid w(height,std::vector<Species>(width,Species::Present));
    const TraitGrid x(height,std::vector<double>(width,0.0));
    d.Set(v,w,x);
    assert(d.GetHeight() == height);
    assert(d.GetWidth() == width);
  }
}
#endif // NDEBUG
