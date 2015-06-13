#include "fisherwrighterdna.h"

#include <cassert>

#ifndef NDEBUG
void ribi::fw::Dna::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  //Do distributions change when being worked on?
  {
    static std::uniform_real_distribution<double> a(0.0,1.0);
    static std::uniform_real_distribution<double> b(0.0,1.0);
    assert(a == b);
    std::mt19937 rnd_engine;
    const double x{a(rnd_engine)};
    assert(x >= 0.0);
    assert(x <= 1.0);
    assert(a == b);
  }
  //Create random DNA
  {
    const double mutation_rate{0.1};
    std::mt19937 rnd_engine;
    const int dna_length{3};
    const Dna dna(mutation_rate,rnd_engine,dna_length);

    assert(dna_length == static_cast<int>(dna.GetSequence().size()));
  }
  //operator==
  {
    const double mutation_rate{0.1};
    std::mt19937 rnd_engine1{42};
    std::mt19937 rnd_engine2{42};
    const int dna_length{100};
    const Dna dna1(mutation_rate,rnd_engine1,dna_length);
    const Dna dna2(mutation_rate,rnd_engine2,dna_length);
    assert(dna1 == dna2);
  }
  //operator!=
  {
    const double mutation_rate{0.1};
    std::mt19937 rnd_engine1{42};
    std::mt19937 rnd_engine2{69};
    const int dna_length{100};
    const Dna dna1(mutation_rate,rnd_engine1,dna_length);
    const Dna dna2(mutation_rate,rnd_engine2,dna_length);
    assert(dna1 != dna2);
  }
  //CreateOffspring with equal RNGs
  {
    const double mutation_rate{0.1};
    std::mt19937 rnd_engine1{42};
    std::mt19937 rnd_engine2{42};
    const int dna_length{100};
    Dna dna1(mutation_rate,rnd_engine1,dna_length);
    Dna dna2(mutation_rate,rnd_engine2,dna_length);
    Dna kid1{dna1.CreateOffspring()};
    Dna kid2{dna2.CreateOffspring()};
    assert(kid1 == kid2);
    const Dna kid3{kid1.CreateOffspring()};
    const Dna kid4{kid2.CreateOffspring()};
    assert(kid3 == kid4);
  }
  //CreateOffspring with different RNGs
  {
    const double mutation_rate{0.1};
    std::mt19937 rnd_engine1{42};
    std::mt19937 rnd_engine2{69};
    const int dna_length{100};
    Dna dna1(mutation_rate,rnd_engine1,dna_length);
    Dna dna2(mutation_rate,rnd_engine2,dna_length);
    const Dna kid1{dna1.CreateOffspring()};
    const Dna kid2{dna2.CreateOffspring()};
    assert(kid1 != kid2);
  }
  //GetRandomFraction of DNA with same RNGs should be identical
  {
    const double mutation_rate{0.1};
    std::mt19937 rnd_engine1{42};
    std::mt19937 rnd_engine2{42};
    const int dna_length{100};
    Dna dna1(mutation_rate,rnd_engine1,dna_length);
    Dna dna2(mutation_rate,rnd_engine2,dna_length);
    const double f1{dna1.GetRandomFraction()};
    const double f2{dna2.GetRandomFraction()};
    assert(f1 == f2);
  }
  //GetRandomFraction of offspring DNA with same RNGs should be identical
  {
    const double mutation_rate{0.1};
    std::mt19937 rnd_engine1{42};
    std::mt19937 rnd_engine2{42};
    const int dna_length{100};
    Dna dna1(mutation_rate,rnd_engine1,dna_length);
    Dna dna2(mutation_rate,rnd_engine2,dna_length);
    Dna kid1{dna1.CreateOffspring()};
    Dna kid2{dna2.CreateOffspring()};
    assert(kid1 == kid2);
    const double f1{kid1.GetRandomFraction()};
    const double f2{kid2.GetRandomFraction()};
    assert(f1 == f2);
  }
  //CreateRandomBasepair
  {
    const double mutation_rate{0.9};
    std::mt19937 rnd_engine1{42};
    std::mt19937 rnd_engine2{42};
    const int dna_length{100};
    Dna dna1(mutation_rate,rnd_engine1,dna_length);
    Dna dna2(mutation_rate,rnd_engine2,dna_length);
    for (int i=0; i!=100; ++i)
    {
      const char c{dna1.CreateRandomBasePair()};
      const char d{dna2.CreateRandomBasePair()};
      assert(c == d);
    }
  }
}
#endif

