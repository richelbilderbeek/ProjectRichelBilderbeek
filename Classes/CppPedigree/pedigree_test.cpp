#include "pedigree.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <sstream>

#ifndef NDEBUG
void Pedigree::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  //Single parent construction
  {
    const std::string name = "Eve";
    const auto parent = Pedigree::Create(name);
    assert(parent->GetName() == name);
    assert(!parent->GetParent().lock());
    assert(parent->GetOffspring().empty());
  }
  //Parent and offspring construction
  {
    const auto parent = Pedigree::Create();
    const auto kid = parent->CreateOffspring();
    assert(parent->GetOffspring().size() == 1);
    assert(parent->GetOffspring()[0].lock());
    assert(parent->GetOffspring()[0].lock() == kid);
    assert(kid->GetParent().lock());
    assert(kid->GetParent().lock() == parent);
  }
  //Parent and two offspring construction
  {
    const auto parent = Pedigree::Create();
    const auto kid1 = parent->CreateOffspring();
    const auto kid2 = parent->CreateOffspring();
    assert(parent->GetOffspring().size() == 2);
    assert(parent->GetOffspring()[0].lock());
    assert(parent->GetOffspring()[0].lock() == kid1);
    assert(parent->GetOffspring()[1].lock());
    assert(parent->GetOffspring()[1].lock() == kid2);
    assert(kid1->GetParent().lock());
    assert(kid1->GetParent().lock() == parent);
    assert(kid2->GetParent().lock());
    assert(kid2->GetParent().lock() == parent);
  }
  //Parent and one offspring construction, kid goes out of scope
  {
    const auto parent = Pedigree::Create();
    {
      const auto kid1 = parent->CreateOffspring();
      const auto kid2 = parent->CreateOffspring();
      assert(parent->GetOffspring().size() == 2);
    }
    parent->CheckOffspring();
    assert(parent->GetOffspring().size() == 0);
  }
  //Create offspring from offspring
  {
    const auto parent = Pedigree::Create();
    const auto a = parent->CreateOffspring();
    const auto b = parent->CreateOffspring();
    const auto c = a->CreateOffspring();
    const auto d = a->CreateOffspring();
    const auto e = b->CreateOffspring();
    const auto f = b->CreateOffspring();
    assert(c->GetParent().lock()->GetParent().lock() == parent);
    assert(d->GetParent().lock()->GetParent().lock() == parent);
    assert(e->GetParent().lock()->GetParent().lock() == parent);
    assert(f->GetParent().lock()->GetParent().lock() == parent);
  }
  //Create offspring from offspring, kill second generation
  {
    std::vector<decltype(Pedigree::Create())> population;
    {
      const auto parent = Pedigree::Create();
      const auto a = parent->CreateOffspring();
      const auto b = a->CreateOffspring();
      population.push_back(parent);
      population.push_back(b);
    }
    population[0]->CheckOffspring();
    assert(population[0]->GetOffspring().empty() && "Second generation died");
    assert(!population[1]->GetParent().lock() && "Second generation died");
  }
  {
    const auto root = Pedigree::Create("X");
    const std::string expected{"(X);"};
    if (root->ToNewick() != expected) { std::clog << root->ToNewick() << '\n'; }
    assert(root->ToNewick() == expected);
  }
  //Single lineage, one generation
  {
    const auto root = Pedigree::Create("X");
    const auto a = root->CreateOffspring("A");
    const std::string expected{"(A:1);"};
    if(root->ToNewick() != expected) { std::cerr << root->ToNewick() << '\n';}
    assert(root->ToNewick() == expected);
  }
  //Single lineage, two generations
  {
    const auto root = Pedigree::Create("X");
    const auto a = root->CreateOffspring("A");
    const auto b = a->CreateOffspring("B");
    assert(b->ToNewick() == "(B);");
    assert(a->ToNewick() == "(B:1);");
    assert(root->ToNewick() == "(B:2);");
  }
  {
    /*

     +-A
     |
   --X
     |
     +-B

    */
    const auto root = Pedigree::Create("X");
    const auto a = root->CreateOffspring("A");
    const auto b = root->CreateOffspring("B");
    const std::string expected{"(A:1,B:1);"};
    const std::string found{root->ToNewick()};
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
    const auto root = Pedigree::Create("X");
    const auto a = root->CreateOffspring("A");
    const auto b = root->CreateOffspring("B");
    const auto c = a->CreateOffspring("C");
    const auto d = a->CreateOffspring("D");
    const auto e = b->CreateOffspring("E");
    const std::string expected{"((C:1,D:1):1,E:2);"};
    const std::string found{root->ToNewick()};
    if (found != expected) { std::cerr << found << '\n'; }
    assert(found == expected);
  }
  //Three branches of one longer length
  {
    /*

       +-C-F
       |
     +-A
     | |
   --X +-D-G
     |
     +-B-E-H

    */
    const auto root = Pedigree::Create("X");
    const auto a = root->CreateOffspring("A");
    const auto b = root->CreateOffspring("B");
    const auto c = a->CreateOffspring("C");
    const auto d = a->CreateOffspring("D");
    const auto e = b->CreateOffspring("E");
    const auto f = c->CreateOffspring("F");
    const auto g = d->CreateOffspring("G");
    const auto h = e->CreateOffspring("H");
    const std::string expected{"((F:2,G:2):1,H:3);"};
    const std::string found{root->ToNewick()};
    if (found != expected) { std::cerr << found << '\n'; }
    assert(found == expected);
  }
  //Four branches of short length with one trichomy
  {
    /*

       +-C
       |
     +-A-D
     | |
   --X +-E
     |
     +-B-F

    */
    const auto root = Pedigree::Create("X");
    const auto a = root->CreateOffspring("A");
    const auto b = root->CreateOffspring("B");
    const auto c = a->CreateOffspring("C");
    const auto d = a->CreateOffspring("D");
    const auto e = a->CreateOffspring("E");
    const auto f = b->CreateOffspring("F");
    const std::string expected{"((C:1,D:1,E:1):1,F:2);"};
    const std::string found{root->ToNewick()};
    if (found != expected) { std::cerr << found << '\n'; }
    assert(found == expected);
  }
  //Four branches of short length, two dichotomies
  {
    /*

       +-C
       |
     +-A
     | |
     | +-D
   --X
     | +-E
     | |
     +-B
       |
       +-F

    */
    const auto root = Pedigree::Create("X");
    const auto a = root->CreateOffspring("A");
    const auto b = root->CreateOffspring("B");
    const auto c = a->CreateOffspring("C");
    const auto d = a->CreateOffspring("D");
    const auto e = b->CreateOffspring("E");
    const auto f = b->CreateOffspring("F");
    const std::string expected{"((C:1,D:1):1,(E:1,F:1):1);"};
    const std::string found{root->ToNewick()};
    if (found != expected) { std::cerr << found << '\n'; }
    assert(found == expected);
  }
  //Four branches of one longer length with one trichomy
  {
    /*

       +-C-G
       |
     +-A-D-H
     | |
   --X +-E-I
     |
     +-B-F-J

    */
    const auto root = Pedigree::Create("X");
    const auto a = root->CreateOffspring("A");
    const auto b = root->CreateOffspring("B");
    const auto c = a->CreateOffspring("C");
    const auto d = a->CreateOffspring("D");
    const auto e = a->CreateOffspring("E");
    const auto f = b->CreateOffspring("F");

    const auto g = c->CreateOffspring("G");
    const auto h = d->CreateOffspring("H");
    const auto i = e->CreateOffspring("I");
    const auto j = f->CreateOffspring("J");

    const std::string expected{"((G:2,H:2,I:2):1,J:3);"};
    const std::string found{root->ToNewick()};
    if (found != expected) { std::cerr << found << '\n'; }
    assert(found == expected);
  }
  //Four branches with one longer length, two dichotomies
  {
    /*

       +-C-G
       |
     +-A
     | |
     | +-D-H
   --X
     | +-E-I
     | |
     +-B
       |
       +-F-J

    */
    const auto root = Pedigree::Create("X");
    const auto a = root->CreateOffspring("A");
    const auto b = root->CreateOffspring("B");
    const auto c = a->CreateOffspring("C");
    const auto d = a->CreateOffspring("D");
    const auto e = b->CreateOffspring("E");
    const auto f = b->CreateOffspring("F");

    const auto g = c->CreateOffspring("G");
    const auto h = d->CreateOffspring("H");
    const auto i = e->CreateOffspring("I");
    const auto j = f->CreateOffspring("J");

    const std::string expected{"((G:2,H:2):1,(I:2,J:2):1);"};

    const std::string found{root->ToNewick()};
    if (found != expected) { std::cerr << found << '\n'; }
    assert(found == expected);
  }

  //Four branches with two dichotomies of different length
  {
    /*

       +-C-F
       |
     +-A
     | |
     | +-D-G
   --X
     |   +-H
     |   |
     +-B-E
         |
         +-I

    */
    const auto root = Pedigree::Create("X");
    const auto a = root->CreateOffspring("A");
    const auto b = root->CreateOffspring("B");
    const auto c = a->CreateOffspring("C");
    const auto d = a->CreateOffspring("D");
    const auto e = b->CreateOffspring("E");
    const auto f = c->CreateOffspring("F");
    const auto g = d->CreateOffspring("G");
    const auto h = e->CreateOffspring("H");
    const auto i = e->CreateOffspring("I");
    const std::string expected{"((F:2,G:2):1,(H:1,I:1):2);"};
    const std::string found{root->ToNewick()};
    if (found != expected) { std::cerr << found << '\n'; }
    assert(found == expected);
  }
  //Three branches of one longer length, killing F
  {
    /*

       +-C-F           +-C
       |               |
     +-A             +-A
     | |       ->    | |
   --X +-D-G       --X +-D-G
     |               |
     +-B-E-H         +-B-E-H

    */
    const auto root = Pedigree::Create("X");
    const auto a = root->CreateOffspring("A");
    const auto b = root->CreateOffspring("B");
    const auto c = a->CreateOffspring("C");
    const auto d = a->CreateOffspring("D");
    const auto e = b->CreateOffspring("E");
    {
      const auto f = c->CreateOffspring("F");
    }
    const auto g = d->CreateOffspring("G");
    const auto h = e->CreateOffspring("H");
    const std::string expected{"((C:1,G:2):1,H:3);"};
    const std::string found{root->ToNewick()};
    if (found != expected) { std::cerr << found << '\n'; }
    assert(found == expected);
  }
  //Three branches of one longer length, killing C
  {
    /*

       +-C-F
       |
     +-A            +-A
     | |      ->    | |
   --X +-D-G      --X +-D-G
     |              |
     +-B-E-H        +-B-E-H

    */
    const auto root = Pedigree::Create("X");
    const auto a = root->CreateOffspring("A");
    const auto b = root->CreateOffspring("B");
    auto c = a->CreateOffspring("C");
    const auto d = a->CreateOffspring("D");
    const auto e = b->CreateOffspring("E");
    const auto f = c->CreateOffspring("F");
    const auto g = d->CreateOffspring("G");
    const auto h = e->CreateOffspring("H");
    c = std::shared_ptr<Pedigree>();
    const std::string expected{"(G:3,H:3);"};
    const std::string found{root->ToNewick()};
    if (found != expected) { std::cerr << found << '\n'; }
    assert(found == expected);
  }
  //Three branches of one longer length, killing A
  {
    /*

       +-C-F
       |
     +-A
     | |      ->
   --X +-D-G      --X
     |              |
     +-B-E-H        +-B-E-H

    */
    const auto root = Pedigree::Create("X");
    auto a = root->CreateOffspring("A");
    const auto b = root->CreateOffspring("B");
    const auto c = a->CreateOffspring("C");
    const auto d = a->CreateOffspring("D");
    const auto e = b->CreateOffspring("E");
    const auto f = c->CreateOffspring("F");
    const auto g = d->CreateOffspring("G");
    const auto h = e->CreateOffspring("H");
    a = std::shared_ptr<Pedigree>();
    const std::string expected{"(H:3);"};
    const std::string found{root->ToNewick()};
    if (found != expected) { std::cerr << found << '\n'; }
    assert(found == expected);
  }
}
#endif

