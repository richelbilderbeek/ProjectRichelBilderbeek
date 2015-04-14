#include "individual.h"

#include <cassert>
#include <iostream>

#include "parameters.h"

#ifndef NDEBUG
void Individual::Test() noexcept
{
  {
    static bool is_tested {false};
    if (is_tested) return;
    is_tested = true;
  }
  std::mt19937 rnd_engine;
  const int dna_length{10000};
  const int n_generations{100};
  const double mutation_rate{0.0};
  const Parameters p(dna_length,mutation_rate,n_generations,1,42);
  //Pedigree can be formed, 1 kid
  {
    const std::shared_ptr<Pedigree> parent_pedigree{Pedigree::Create("X")};
    Individual parent(
      Dna(mutation_rate,rnd_engine,dna_length),parent_pedigree
    );
    const Individual kid{parent.CreateOffspring("A")};

    assert(kid.GetPedigree()->GetParent().lock());
    assert(kid.GetPedigree()->GetParent().lock() == parent_pedigree);
    assert(parent_pedigree->ToNewick() == kid.GetPedigree()->GetParent().lock()->ToNewick());
  }
  {
    /*

     +-A
     |
   --X
     |
     +-B

    */
    const auto root_pedigree = Pedigree::Create("X");
    Individual root(
      Dna(mutation_rate,rnd_engine,dna_length),root_pedigree
    );
    const Individual a{root.CreateOffspring("A")};
    const Individual b{root.CreateOffspring("B")};
    const std::string expected{"(A:1,B:1);"};
    const std::string found{root.GetPedigree()->ToNewick()};
    if (found != expected) { std::cerr << found << '\n'; }
    assert(found == expected);
  }
  //Three branches of short length
  {
    /*

       +-C
       |
     +-A
     | |
   --X +-D
     |
     +-B-E

    */
    const auto root_pedigree = Pedigree::Create("X");
    Individual root(
      Dna(mutation_rate,rnd_engine,dna_length),root_pedigree
    );
    auto a = root.CreateOffspring("A");
    auto b = root.CreateOffspring("B");
    const auto c = a.CreateOffspring("C");
    const auto d = a.CreateOffspring("D");
    const auto e = b.CreateOffspring("E");
    const std::string expected{"((C:1,D:1):1,E:2);"};
    const std::string found{root.GetPedigree()->ToNewick()};
    if (found != expected) { std::cerr << found << '\n'; }
    assert(found == expected);
  }
}
#endif

