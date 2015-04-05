#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

#include "pedigree.h"

///Determines if a filename is a regular file
///From http://www.richelbilderbeek.nl/CppIsRegularFile.htm
bool IsRegularFileStl(const std::string& filename)
{
  std::fstream f;
  f.open(filename.c_str(),std::ios::in);
  return f.is_open();
}

void CoutNewick(const std::string& newick)
{
  const std::string newick_utils_path{"/home/richel/GitHubs/ProjectRichelBilderbeek/Libraries/newick_utils/src"};
  const std::string nw_display_executable{newick_utils_path+"/nw_display"};
  if (!IsRegularFileStl(nw_display_executable))
  {
    std::cerr
      << "Error: nw_display executable '" << nw_display_executable << "' not found\n"
      << "Please change the path\n"
    ;
    return;
  }
  const std::string cmd{"echo \""+ newick + "\" | " + nw_display_executable + " -"};
  std::system(cmd.c_str());
}

int main()
{



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
    if (root->ToNewick() != expected) { std::clog << root->ToNewick() << '\n'; }
    assert(root->ToNewick() == expected);
    CoutNewick(root->ToNewick());
    /* nw_display creates:
                                           /-------------------------------------+ C
                                           |
     /-------------------------------------+-------------------------------------+ D
     |                                     |
    =+                                     \-------------------------------------+ E
     |
     \---------------------------------------------------------------------------+ F

     |------------------|------------------|------------------|------------------|
     0                0.5                  1                1.5                  2
     substitutions/site
    */
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
    if (root->ToNewick() != expected) { std::clog << root->ToNewick() << '\n'; }
    assert(root->ToNewick() == expected);
    CoutNewick(root->ToNewick());
    /* nw_display creates:

                                           /-------------------------------------+ C
     /-------------------------------------+
     |                                     \-------------------------------------+ D
    =+
     |                                     /-------------------------------------+ E
     \-------------------------------------+
                                           \-------------------------------------+ F

     |------------------|------------------|------------------|------------------|
     0                0.5                  1                1.5                  2
     substitutions/site

    */
  }

  std::cout << "DONE" << std::endl;
}

