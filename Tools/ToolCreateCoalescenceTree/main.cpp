#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

//Lineages contain the 1D position of lineages in time
//
// 1,3
// 1,2
// 1
//
// Should be displayed as:
//
// * *
// **
// *
//
void Display(std::vector<std::vector<int>>& lineages)
{
  for (const auto& lineage: lineages)
  {
    const int max{
      *std::max_element(
        std::begin(lineage),
        std::end(lineage)
      )
    };
    std::string s(max + 1,' ');
    for (const auto index: lineage)
    {
      s[index] = '*';
    }
    std::cout << s << '\n';
  }
}

//Bad random number generator!
double GetRandomProbability() noexcept
{
  return static_cast<double>(std::rand())
    / static_cast<double>(RAND_MAX)
  ;
}

int main()
{
  const int population_size{10};
  const int sample_size{3};
  const double speciation_rate{0.1};
  assert(population_size > sample_size);
  std::vector<std::vector<int>> lineages;
  //Create first lineage
  {
    std::vector<int> first_lineage;
    for (int i=0; i!=sample_size; ++i) { first_lineage.push_back(i); }
    lineages.push_back(first_lineage);
  }
  while (lineages.back().size() > 1)
  {
    std::vector<int>& kids{lineages.back()};
    std::vector<int> parents{kids};

    //The chance something happens in these lineages
    {
      const double p_something_happens{
        static_cast<double>(kids.size()) /
        static_cast<double>(population_size)
      };
      assert(p_something_happens >= 0.0);
      assert(p_something_happens <= 1.0);
      if (GetRandomProbability() > p_something_happens)
      {
        //Nothing happens
        lineages.push_back(parents);
        continue;
      }
    }
    //There is something happening in these lineages
    const int n_parents{static_cast<int>(parents.size())};
    const int random_parent_index{std::rand() % n_parents};
    //Is it speciation?
    {
      if (GetRandomProbability() < speciation_rate)
      {
        //Event: speciation
        std::swap(parents[random_parent_index],parents.back());
        parents.pop_back();
        lineages.push_back(parents);
        continue;
      }
    }
    //Event: Dispersal
    int& random_parent{parents[random_parent_index]};
    //dispersal is from either left or right, first and last indices are connected
    const int delta_index{GetRandomProbability() < 0.5 ? -1 : 1};
    random_parent
      = ((random_parent - delta_index) + population_size)
      % population_size
    ;
    //Remove coalesced lineages
    std::vector<int>::iterator new_end
      = std::unique(std::begin(parents),std::end(parents));
    parents.erase(new_end,std::end(parents));
    lineages.push_back(parents);
  }
  Display(lineages);
}
