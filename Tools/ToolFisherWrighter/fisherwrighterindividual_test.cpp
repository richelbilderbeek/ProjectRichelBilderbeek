#include "fisherwrighterindividual.h"

#include <cassert>
#include <iostream>

#include "counter.h"
#include "dnasequence.h"
#include "fisherwrighterdna.h"
#include "fisherwrighterparameters.h"

#ifndef NDEBUG
void ribi::fw::Individual::Test() noexcept
{
  {
    static bool is_tested {false};
    if (is_tested) return;
    is_tested = true;
  }
  using ribi::DnaSequence;
  //operator==
  {
    const double mutation_rate1{0.123};
    const double mutation_rate2{0.123};
    std::mt19937 rnd_engine1;
    std::mt19937 rnd_engine2;
    const DnaSequence sequence1("description","ACGTACGTACGT");
    const DnaSequence sequence2("description","ACGTACGTACGT");
    assert(mutation_rate1 == mutation_rate2);
    assert(rnd_engine1 == rnd_engine2);
    assert(sequence1 == sequence2);
    const Dna dna1(mutation_rate1,rnd_engine1,sequence1.GetSequence());
    const Dna dna2(mutation_rate2,rnd_engine2,sequence2.GetSequence());
    const auto pedigree1 = Pedigree::Create("X");
    const auto pedigree2 = Pedigree::Create("X");
    assert(dna1 == dna2);
    assert(*pedigree1 == *pedigree2);
    assert(sequence1 == sequence2);
    ribi::Counter counter1;
    ribi::Counter counter2;
    assert(counter1 == counter2);
    const Individual a(dna1,pedigree1,counter1);
    const Individual b(dna2,pedigree2,counter2);
    assert(a == b);
  }
  //GetIndex
  {
    const double mutation_rate{0.123};
    std::mt19937 rnd_engine;
    const Dna dna(mutation_rate,rnd_engine,"ACGTACGTACGT");
    const auto pedigree = Pedigree::Create("X");
    ribi::Counter counter;
    const Individual a(dna,pedigree,counter);
    const Individual b(dna,pedigree,counter);
    assert(a.GetIndex() == a.GetIndex());
    assert(b.GetIndex() == b.GetIndex());
    assert(a.GetIndex() != b.GetIndex());
  }
  std::mt19937 rnd_engine;
  const int dna_length{10000};
  const int n_generations{100};
  const double mutation_rate{0.0};
  ribi::Counter counter;
  const Parameters p(dna_length,mutation_rate,n_generations,1,42);
  //Pedigree can be formed, 1 kid
  {
    const std::shared_ptr<Pedigree> parent_pedigree{Pedigree::Create("X")};
    Individual parent(
      Dna(mutation_rate,rnd_engine,dna_length),
      parent_pedigree,
      counter
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
      Dna(mutation_rate,rnd_engine,dna_length),root_pedigree,counter
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
      Dna(mutation_rate,rnd_engine,dna_length),root_pedigree,counter
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
  //CreateOffspring with same RNGs
  {
    const double mutation_rate1{0.123};
    const double mutation_rate2{0.123};
    std::mt19937 rnd_engine1{42};
    std::mt19937 rnd_engine2{42};
    const DnaSequence sequence1("description","ACGTACGTACGT");
    const DnaSequence sequence2("description","ACGTACGTACGT");
    assert(mutation_rate1 == mutation_rate2);
    assert(rnd_engine1 == rnd_engine2);
    assert(sequence1 == sequence2);
    const Dna dna1(mutation_rate1,rnd_engine1,sequence1.GetSequence());
    const Dna dna2(mutation_rate2,rnd_engine2,sequence2.GetSequence());
    const auto pedigree1 = Pedigree::Create("X");
    const auto pedigree2 = Pedigree::Create("X");
    assert(dna1 == dna2);
    assert(*pedigree1 == *pedigree2);
    assert(sequence1 == sequence2);
    ribi::Counter counter1;
    ribi::Counter counter2;
    assert(counter1 == counter2);
    Individual parent1(dna1,pedigree1,counter1);
    Individual parent2(dna2,pedigree2,counter2);
    assert(parent1 == parent2);
    Individual kid1{parent1.CreateOffspring()};
    Individual kid2{parent2.CreateOffspring()};
    assert(kid1 == kid2);
    const Individual kid3{kid1.CreateOffspring()};
    const Individual kid4{kid2.CreateOffspring()};
    assert(kid3 == kid4);
  }
  //CreateOffspring with different RNGs
  {
    const double mutation_rate1{0.123};
    const double mutation_rate2{0.123};
    std::mt19937 rnd_engine1{42};
    std::mt19937 rnd_engine2{69};
    const DnaSequence sequence1("description","ACGTACGTACGT");
    const DnaSequence sequence2("description","ACGTACGTACGT");
    assert(mutation_rate1 == mutation_rate2);
    assert(rnd_engine1 != rnd_engine2);
    assert(sequence1 == sequence2);
    const Dna dna1(mutation_rate1,rnd_engine1,sequence1.GetSequence());
    const Dna dna2(mutation_rate2,rnd_engine2,sequence2.GetSequence());
    const auto pedigree1 = Pedigree::Create("X");
    const auto pedigree2 = Pedigree::Create("X");
    assert(dna1 == dna2);
    assert(*pedigree1 == *pedigree2);
    assert(sequence1 == sequence2);
    ribi::Counter counter1;
    ribi::Counter counter2;
    assert(counter1 == counter2);
    Individual parent1(dna1,pedigree1,counter1);
    Individual parent2(dna2,pedigree2,counter2);
    assert(parent1 == parent2);
    const Individual kid1{parent1.CreateOffspring()};
    const Individual kid2{parent2.CreateOffspring()};
    assert(kid1 != kid2);
  }
}
#endif

