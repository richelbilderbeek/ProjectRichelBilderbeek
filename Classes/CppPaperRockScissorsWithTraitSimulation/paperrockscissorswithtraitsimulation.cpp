#include "paperrockscissorswithtraitsimulation.h"

#include <array>
#include <cassert>
#include <algorithm>
#include <cstdlib>
#include <map>
#include <tuple>

ribi::prswt::Simulation::Simulation(
  const Parameters& parameters)
  : m_grid{},
    m_rng(parameters.GetRngSeed()),
    m_uniform_distribution(0,3), //Inclusive
    m_normal_distribution(0.0,1.0),
    m_popsizes{},
    m_mean_traits{},
    m_parameters{parameters}
{
  #ifndef NDEBUG
  Test();
  #endif
  SetInitialization(m_parameters.GetInitialization());
}

std::tuple<int,int,int> ribi::prswt::Simulation::GetLastPopSizes() const
{
  assert(!m_popsizes.empty());
  return m_popsizes.back();
}

std::tuple<double,double,double> ribi::prswt::Simulation::GetLastMeanTraits() const
{
  assert(!m_mean_traits.empty());
  return m_mean_traits.back();
}


void ribi::prswt::Simulation::Next()
{
  using Prs = PaperRockScissors;
  std::map<Prs,double> sum_traits;
  sum_traits[Prs::paper   ] = 0.0;
  sum_traits[Prs::rock    ] = 0.0;
  sum_traits[Prs::scissors] = 0.0;

  std::map<Prs,int> tally_popsizes;
  tally_popsizes[Prs::paper   ] = 0;
  tally_popsizes[Prs::rock    ] = 0;
  tally_popsizes[Prs::scissors] = 0;

  std::vector<std::vector<Individual>> next(m_grid);
  const int height{static_cast<int>(m_grid.size())};
  const int width{static_cast<int>(m_grid[0].size())};
  for (int y=0; y!=height; ++y)
  {
    for (int x=0; x!=width; ++x)
    {
      int dx{0};
      int dy{0};

      switch (m_uniform_distribution(m_rng))
      {
        case 0: --dy; break;
        case 1: ++dx; break;
        case 2: ++dy; break;
        case 3: --dx; break;
        default: assert(!"Should not get here");
      }
      auto& here = m_grid[y][x];
      const auto& neighbour = m_grid[(y+dy+height)%height][(x+dx+width)%width];
      const auto& winner = DoesBeat(neighbour,here) ? neighbour : here;
      if (winner == neighbour)
      {
        const double new_trait{winner.GetTrait() + m_normal_distribution(m_rng)};
        next[y][x]
          = Individual(
            winner.GetPrs(),
            new_trait
          )
        ;
        ++tally_popsizes[winner.GetPrs()];
        sum_traits[winner.GetPrs()] += winner.GetTrait();
      }
      else
      {
        const double new_trait{here.GetTrait() + m_normal_distribution(m_rng)};
        next[y][x]
          = Individual(
            here.GetPrs(),
            new_trait
          )
        ;
        sum_traits[here.GetPrs()] += here.GetTrait();
        ++tally_popsizes[here.GetPrs()];
      }
    }
  }

  {
    const int n_p{tally_popsizes[Prs::paper]};
    const int n_r{tally_popsizes[Prs::rock]};
    const int n_s{tally_popsizes[Prs::scissors]};
    assert(n_p >= 0);
    assert(n_r >= 0);
    assert(n_s >= 0);
    m_popsizes.push_back(std::make_tuple(n_p,n_r,n_s));
  }
  m_mean_traits.push_back(
    std::make_tuple(
      sum_traits[Prs::paper   ] / static_cast<double>(tally_popsizes[Prs::paper   ]),
      sum_traits[Prs::rock    ] / static_cast<double>(tally_popsizes[Prs::rock    ]),
      sum_traits[Prs::scissors] / static_cast<double>(tally_popsizes[Prs::scissors])
    )

  );
  std::swap(m_grid,next);
}

void ribi::prswt::Simulation::SetInitialization(const Initialization initialization) noexcept
{
  using Prs = PaperRockScissors;

  m_popsizes.clear();
  m_mean_traits.clear();
  m_grid.clear();
  std::map<Prs,int> tally;
  tally[Prs::paper] = 0;
  tally[Prs::rock] = 0;
  tally[Prs::scissors] = 0;


  m_parameters.SetInitialization(initialization);

  //Initialize the grid
  assert(m_grid.empty());
  const int height = m_parameters.GetHeight();
  const int width = m_parameters.GetWidth();
  for (int y=0; y!=height; ++y)
  {
    assert(y == static_cast<int>(m_grid.size()));
    m_grid.push_back(std::vector<Individual>());
    assert(y < static_cast<int>(m_grid.size()));
    for (int x=0; x!=width; ++x)
    {
      assert(x == static_cast<int>(m_grid[y].size()));

      Prs prs = Prs::paper;
      switch(initialization)
      {
        case Initialization::random:
        {
          static std::uniform_int_distribution<int> d(0,2); //Inclusive
          switch (d(m_rng))
          {
            case 0: prs = Prs::paper; break;
            case 1: prs = Prs::rock; break;
            case 2: prs = Prs::scissors; break;
            default: assert(!"Should not get here");
          }
        }
        break;
        case Initialization::vertical_bands:
        {
          switch ((y / (height / 15)) % 3)
          {
            case 0: prs = Prs::paper; break;
            case 1: prs = Prs::rock; break;
            case 2: prs = Prs::scissors; break;
            default: assert(!"Should not get here");
          }
        }
        break;
        case Initialization::monomorph:
          prs = Prs::paper;
        break;
        default: assert(!"Should not get here");
      }
      m_grid[y].push_back(Individual(prs,0.0));
      ++tally[prs];
    }
  }

  {
    const int n_p{tally[Prs::paper]};
    const int n_r{tally[Prs::rock]};
    const int n_s{tally[Prs::scissors]};
    assert(n_p >= 0);
    assert(n_r >= 0);
    assert(n_s >= 0);
    m_popsizes.push_back(std::make_tuple(n_p,n_r,n_s));
  }
  m_mean_traits.push_back(
    std::make_tuple(0.0,0.0,0.0)
  );
}

#ifndef NDEBUG
void ribi::prswt::Simulation::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  TestInitialization();
}
#endif
