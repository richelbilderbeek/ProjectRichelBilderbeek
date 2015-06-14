#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "newickcpp98.h"

#include <boost/numeric/conversion/cast.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>

#include "fuzzy_equal_to.h"
#include "testtimer.h"
#include "newick.h"

#pragma GCC diagnostic pop

ribi::NewickCpp98::NewickCpp98()
{
  #ifndef NDEBUG
  Test();
  #endif
}

///CreateValidTrinaryNewicks creates std::strings
///that can be converted to a TrinaryNewickVector.
///From http://www.richelbilderbeek.nl/CppCreateValidTinaryNewicks.htm
std::vector<std::string> ribi::NewickCpp98::CreateValidTrinaryNewicks() noexcept
{
  std::vector<std::string> v;
  v.push_back("(1,1,1)");
  v.push_back("(1,2,3)");
  v.push_back("((1,1),1,1)");
  v.push_back("(1,(1,1),1)");
  v.push_back("(1,1,(1,1))");
  v.push_back("(1,(2,3,4))");
  v.push_back("(1,2,(3,4))");
  v.push_back("(1,2,(3,4,5))");
  v.push_back("((1,2,3),4,5)");
  v.push_back("(11,22,33)");
  v.push_back("(11,(22,33,44))");
  v.push_back("(11,22,(33,44))");
  v.push_back("(11,22,(33,44,55))");
  v.push_back("((11,22,33),44,55)");
  v.push_back("((1,2),(3,4),(5,6))");
  v.push_back("((1,2,3),(4,5),(6,7))");
  v.push_back("((1,2),(3,4,5),(6,7))");
  v.push_back("((1,2),(3,4),(5,6,7))");
  v.push_back("((1,2,3),(4,5),(6,7))");
  v.push_back("((1,2),(3,4,5),(6,7))");
  v.push_back("((1,2),(3,4),(5,6,7))");
  v.push_back("((1,2,3),(4,5,6),(7,8))");
  v.push_back("((1,2),(3,4,5),(6,7,8))");
  v.push_back("((1,2,3),(4,5),(6,7,8))");
  v.push_back("((1,2,3),(4,5,6),(7,8,9))");
  v.push_back("((11,22,33),(44,55,66),(77,88,99))");
  return v;
}

std::vector<boost::tuple<std::string,double,double> > ribi::NewickCpp98::GetKnownProbabilities() noexcept
{
  std::vector<boost::tuple<std::string,double,double> > v;

  //Sum equals 1
  v.push_back(boost::make_tuple("(1)"  , 10.0, 1.0000000));
  //Sum equals 2
  v.push_back(boost::make_tuple("(2)"  , 10.0, 0.0909091));
  v.push_back(boost::make_tuple("(1,1)", 10.0, 0.9090909));
  //Sum equals 3
  v.push_back(boost::make_tuple("(3)"  , 10.0, 0.0151515));
  v.push_back(boost::make_tuple("(1,2)", 10.0, 0.0757576));
  v.push_back(boost::make_tuple("(2,1)", 10.0, 0.0757576));
  v.push_back(boost::make_tuple("(1,(1,1))", 10.0, 0.2525253));
  v.push_back(boost::make_tuple("((1,1),1)", 10.0, 0.2525253));
  //Trinary
  v.push_back(boost::make_tuple("(1,1,1)"  , 10.0, 0.7575758));
  //Sum equals 4
  v.push_back(boost::make_tuple("(4)"  , 10.0, 0.0034965));
  v.push_back(boost::make_tuple("(1,3)", 10.0, 0.0116550));
  v.push_back(boost::make_tuple("(2,2)", 10.0, 0.0058275));
  v.push_back(boost::make_tuple("(3,1)", 10.0, 0.0116550));
  v.push_back(boost::make_tuple("(1,(1,2))", 10.0, 0.0194250));
  v.push_back(boost::make_tuple("(1,(2,1))", 10.0, 0.0194250));
  v.push_back(boost::make_tuple("(2,(1,1))", 10.0, 0.0194250));
  v.push_back(boost::make_tuple("((1,2),1)", 10.0, 0.0194250));
  v.push_back(boost::make_tuple("((2,1),1)", 10.0, 0.0194250));
  v.push_back(boost::make_tuple("((1,1),2)", 10.0, 0.0194250));
  //Trinary
  v.push_back(boost::make_tuple("(1,1,2)", 10.0, 0.0582751));
  v.push_back(boost::make_tuple("(1,2,1)", 10.0, 0.0582751));
  v.push_back(boost::make_tuple("(2,1,1)", 10.0, 0.0582751));
  v.push_back(boost::make_tuple("(1,1,(1,1))", 10.0, 0.1295001));   //(1)(confirmed)
  v.push_back(boost::make_tuple("(1,(1,1),1)", 10.0, 0.1295001));
  v.push_back(boost::make_tuple("((1,1),1,1)", 10.0, 0.1295001));
  v.push_back(boost::make_tuple("(1,(1,1,1))", 10.0, 0.0971251));   //(2)(confirmed)
  v.push_back(boost::make_tuple("((1,1,1),1)", 10.0, 0.0971251));
  //Quadrary
  v.push_back(boost::make_tuple("(1,1,1,1)", 10.0, 0.5827505));
  //Sum equals 5
  v.push_back(boost::make_tuple("(1,4)", 10.0, 0.0024975));
  v.push_back(boost::make_tuple("(2,3)", 10.0, 0.0008325));
  v.push_back(boost::make_tuple("(3,2)", 10.0, 0.0008325));
  v.push_back(boost::make_tuple("(4,1)", 10.0, 0.0024975));
  v.push_back(boost::make_tuple("(1,(1,3))", 10.0, 0.0028305));
  v.push_back(boost::make_tuple("(1,(2,2))", 10.0, 0.0012950));
  v.push_back(boost::make_tuple("(1,(3,1))", 10.0, 0.0028305));
  v.push_back(boost::make_tuple("(2,(1,2))", 10.0, 0.0014338));
  v.push_back(boost::make_tuple("(2,(2,1))", 10.0, 0.0014338));
  v.push_back(boost::make_tuple("(3,(1,1))", 10.0, 0.0026640));
  //Trinary
  v.push_back(boost::make_tuple("(1,1,(1,2))"  , 10.0, 0.0092731));   //(3)(confirmed)
  v.push_back(boost::make_tuple("(1,1,(2,1))"  , 10.0, 0.0092731));
  v.push_back(boost::make_tuple("(1,1,(1,1,1))", 10.0, 0.0348263));   //(4)(confirmed)
  v.push_back(boost::make_tuple("(1,(1,1,1),1)", 10.0, 0.0348263));
  v.push_back(boost::make_tuple("((1,1,1),1,1)", 10.0, 0.0348263));
  v.push_back(boost::make_tuple("(2,(1,1,1))"  , 10.0, 0.0070069));   //(5)(confirmed)
  v.push_back(boost::make_tuple("((1,1,1),2)"  , 10.0, 0.0070069));
  v.push_back(boost::make_tuple("(1,1,1,(1,1))", 10.0, 0.0692918));   //(6)(confirmed)
  v.push_back(boost::make_tuple("(1,2,(1,1))"  , 10.0, 0.0092223));   //(7)(confirmed)
  v.push_back(boost::make_tuple("(2,1,(1,1))"  , 10.0, 0.0092223));
  v.push_back(boost::make_tuple("(1,(1,1),2)"  , 10.0, 0.0092223));
  v.push_back(boost::make_tuple("(2,(1,1),1)"  , 10.0, 0.0092223));
  v.push_back(boost::make_tuple("((1,1),1,2)"  , 10.0, 0.0092223));
  v.push_back(boost::make_tuple("((1,1),2,1)"  , 10.0, 0.0092223));
  v.push_back(boost::make_tuple("(1,(1,1,2))"  , 10.0, 0.0069190));   //(9)(confirmed)
  v.push_back(boost::make_tuple("(1,(1,2,1))"  , 10.0, 0.0069190));
  v.push_back(boost::make_tuple("(1,(2,1,1))"  , 10.0, 0.0069190));
  v.push_back(boost::make_tuple("((1,1,2),1)"  , 10.0, 0.0069190));
  v.push_back(boost::make_tuple("((1,2,1),1)"  , 10.0, 0.0069190));
  v.push_back(boost::make_tuple("((2,1,1),1)"  , 10.0, 0.0069190));
  //Quadrary
  v.push_back(boost::make_tuple("(1,(1,1,1,1))", 10.0, 0.0415140));   //(8)(confirmed)
  //Pentary
  v.push_back(boost::make_tuple("(1,1,1,1,1)"  , 10.0, 0.4162504));
  //Sum equals 6
  v.push_back(boost::make_tuple("(1,5)", 10.0, 0.0006660));
  v.push_back(boost::make_tuple("(2,4)", 10.0, 0.0001665));
  v.push_back(boost::make_tuple("(3,3)", 10.0, 0.0001110));
  v.push_back(boost::make_tuple("(1,(1,4))", 10.0, 0.0005804));
  v.push_back(boost::make_tuple("(1,(2,3))", 10.0, 0.0001679));
  v.push_back(boost::make_tuple("(1,(3,2))", 10.0, 0.0001679));
  v.push_back(boost::make_tuple("(1,(4,1))", 10.0, 0.0005804));
  v.push_back(boost::make_tuple("(2,(1,3))", 10.0, 0.0001991));
  v.push_back(boost::make_tuple("(2,(2,2))", 10.0, 0.0000925));
  v.push_back(boost::make_tuple("(2,(3,1))", 10.0, 0.0001991));
  v.push_back(boost::make_tuple("(3,(1,2))", 10.0, 0.0001880));
  v.push_back(boost::make_tuple("(3,(2,1))", 10.0, 0.0001880));
  v.push_back(boost::make_tuple("(4,(1,1))", 10.0, 0.0005043));
  //Trinary
  v.push_back(boost::make_tuple("(1,1,(1,3))"  , 10.0, 0.0012712));
  v.push_back(boost::make_tuple("(1,1,(2,2))"  , 10.0, 0.0005563));
  v.push_back(boost::make_tuple("(1,1,(3,1))"  , 10.0, 0.0012712));
  v.push_back(boost::make_tuple("(1,(1,3),1)"  , 10.0, 0.0012712));
  v.push_back(boost::make_tuple("(1,(2,2),1)"  , 10.0, 0.0005563));
  v.push_back(boost::make_tuple("(1,(3,1),1)"  , 10.0, 0.0012712));
  v.push_back(boost::make_tuple("((1,3),1,1)"  , 10.0, 0.0012712));
  v.push_back(boost::make_tuple("((2,2),1,1)"  , 10.0, 0.0005563));
  v.push_back(boost::make_tuple("((3,1),1,1)"  , 10.0, 0.0012712));
  v.push_back(boost::make_tuple("(1,2,(1,2))"  , 10.0, 0.0006346));
  v.push_back(boost::make_tuple("(2,1,(1,2))"  , 10.0, 0.0006346));
  v.push_back(boost::make_tuple("(1,2,(2,1))"  , 10.0, 0.0006346));
  v.push_back(boost::make_tuple("(2,1,(2,1))"  , 10.0, 0.0006346));
  v.push_back(boost::make_tuple("(1,(2,1),2)"  , 10.0, 0.0006346));
  v.push_back(boost::make_tuple("(1,(1,2),2)"  , 10.0, 0.0006346));
  v.push_back(boost::make_tuple("(2,(2,1),1)"  , 10.0, 0.0006346));
  v.push_back(boost::make_tuple("(2,(1,2),1)"  , 10.0, 0.0006346));
  v.push_back(boost::make_tuple("(1,3,(1,1))"  , 10.0, 0.0011913));
  v.push_back(boost::make_tuple("(1,(1,1),3)"  , 10.0, 0.0011913));
  v.push_back(boost::make_tuple("((1,1),1,3)"  , 10.0, 0.0011913));
  v.push_back(boost::make_tuple("(3,(1,1),1)"  , 10.0, 0.0011913));
  v.push_back(boost::make_tuple("((1,1),3,1)"  , 10.0, 0.0011913));
  v.push_back(boost::make_tuple("(1,1,(1,1,2))", 10.0, 0.0023165));
  v.push_back(boost::make_tuple("(1,1,(1,2,1))", 10.0, 0.0023165));
  v.push_back(boost::make_tuple("(1,1,(2,1,1))", 10.0, 0.0023165));
  v.push_back(boost::make_tuple("(1,(1,1,2),1)", 10.0, 0.0023165));
  v.push_back(boost::make_tuple("(1,(1,2,1),1)", 10.0, 0.0023165));
  v.push_back(boost::make_tuple("(1,(2,1,1),1)", 10.0, 0.0023165));
  v.push_back(boost::make_tuple("((1,1,2),1,1)", 10.0, 0.0023165));
  v.push_back(boost::make_tuple("((1,2,1),1,1)", 10.0, 0.0023165));
  v.push_back(boost::make_tuple("((2,1,1),1,1)", 10.0, 0.0023165));
  v.push_back(boost::make_tuple("(1,2,(1,1,1))", 10.0, 0.0023323));
  v.push_back(boost::make_tuple("(2,1,(1,1,1))", 10.0, 0.0023323));
  v.push_back(boost::make_tuple("(1,(1,1,1),2)", 10.0, 0.0023323));
  v.push_back(boost::make_tuple("(2,(1,1,1),1)", 10.0, 0.0023323));
  v.push_back(boost::make_tuple("((1,1,1),1,2)", 10.0, 0.0023323));
  v.push_back(boost::make_tuple("((1,1,1),2,1)", 10.0, 0.0023323));
  //Quadrary
  v.push_back(boost::make_tuple("(1,(1,1,1,2))"  , 10.0, 0.0027574));
  v.push_back(boost::make_tuple("(1,(1,1,2,1))"  , 10.0, 0.0027574));
  v.push_back(boost::make_tuple("(1,(1,2,1,1))"  , 10.0, 0.0027574));
  v.push_back(boost::make_tuple("(1,(2,1,1,1))"  , 10.0, 0.0027574));
  v.push_back(boost::make_tuple("((1,1,1,2),1)"  , 10.0, 0.0027574));
  v.push_back(boost::make_tuple("((1,1,2,1),1)"  , 10.0, 0.0027574));
  v.push_back(boost::make_tuple("((1,2,1,1),1)"  , 10.0, 0.0027574));
  v.push_back(boost::make_tuple("((2,1,1,1),1)"  , 10.0, 0.0027574));
  v.push_back(boost::make_tuple("(2,(1,1,1,1))"  , 10.0, 0.0028154));
  v.push_back(boost::make_tuple("((1,1,1,1),2)"  , 10.0, 0.0028154));
  //Pentary
  v.push_back(boost::make_tuple("(1,(1,1,1,1,1))", 10.0, 0.0183824));   //(7)
  v.push_back(boost::make_tuple("((1,1,1,1,1),1)", 10.0, 0.0183824));
  //Hexary
  v.push_back(boost::make_tuple("(1,1,1,1,1,1)"  , 10.0, 0.2775003));
  return v;
}

///GetRootBranches obtains the root branches from a non-unary Newick.
///Examples:
///(1,2)               -> { 1     , 2             }
///(1,2,3)             -> { 1     , 2     , 3     }
///((1,1),(2,2),(3,3)) -> { (1,1) , (2,2) , (3,3) }
///From http://www.richelbilderbeek.nl/CppGetRootBranchesBinary.htm
std::vector<std::vector<int> >
  ribi::NewickCpp98::GetRootBranches(const std::vector<int>& n)
{
  assert(Newick().IsNewick(n));
  assert(!Newick().IsUnaryNewick(n));

  const int size = boost::numeric_cast<int>(n.size());
  std::vector<std::vector<int> > v;

  if (Newick().IsSimple(n))
  {
    for (int i=1; i!=size-1; ++i) //Skip brackets
    {
      v.push_back(
        Newick().CreateVector(
          static_cast<int>(Newick::bracket_open),
          n[i],
          static_cast<int>(Newick::bracket_close)));
    }
    assert(Newick().IsNewick(v.back()));
    assert(v.size() > 1);
    return v;
  }
  //Complex newick
  assert(!Newick().IsSimple(n));
  const std::vector<int> depth = Newick().GetDepth(n);

  assert(depth.size() == n.size());
  //Search for open and closing brackets in depth 1
  for (int i=0; i!=size; ++i)
  {
    if (depth[i] == 0 && n[i] > 0)
    {
      //C++0x initialization list
      std::vector<int> tmp;
      tmp.push_back(static_cast<int>(Newick::bracket_open));
      tmp.push_back(n[i]);
      tmp.push_back(static_cast<int>(Newick::bracket_close));
      v.push_back(tmp);
      assert(Newick().IsNewick(v.back()));
      continue;
    }
    if (depth[i] != 1 || n[i]!=Newick::bracket_open) continue;
    for (int j=i+1; j!=size; ++j)
    {
      if (depth[j] != 1 || n[j]!=Newick::bracket_close) continue;
      std::vector<int> w;
      w.push_back(Newick::bracket_open);
      std::copy(n.begin() + i + 1,n.begin() + j,std::back_inserter(w));
      w.push_back(Newick::bracket_close);
      assert(Newick().IsNewick(w));
      v.push_back(w);
      //Set from index i after current end
      i = j;
      break;
    }
  }
  assert(v.size() > 1);
  return v;
}

///GetSimplerNewicksFrequencyPairs creates simpler, derived Newicks from a Newick.
///Its simpler Newicks are identical to those created by GetSimplerNewicks.
///From http://www.richelbilderbeek.nl/CppGetSimplerNewicksFrequencyPairs.htm
std::vector<std::pair<std::vector<int>,int> >
  ribi::NewickCpp98::GetSimplerNewicksFrequencyPairs(const std::vector<int>& n)
{
  assert(Newick().IsNewick(n));

  std::vector<std::pair<std::vector<int>,int> > newicks;
  const std::vector<int> depths = Newick().GetDepth(n);


  const int size = boost::numeric_cast<int>(n.size());
  for (int i = 0; i!=size; ++i)
  {
    assert(i >= 0);
    assert(i < size);
    if (n[i] < 1) continue;
    assert(n[i] > 0);
    if (n[i] > 1)
    {
      std::vector<int> new_newick(n);
      --new_newick[i];
      #ifdef DEBUG_GETSIMPLERNEWICKS
      {
        const std::string stored = Newick::NewickToString(new_newick);
        TRACE(stored);
      }
      #endif

      newicks.push_back( std::make_pair(new_newick,n[i]) );
      continue;
    }
    assert(n[i] == 1); //Most difficult...
    const int depth = depths[i];
    //j must first decrement, later increment with the same code
    int j_end  = -1;
    int j_step = -1;
    for (int j=i-1; ; j+=j_step)
    {
      //j must first decrement, later increment with the same code
      if (j == j_end
        //|| depths[j] < depth
        || (depths[j] == depth && n[j] < 0))
      {
        if (j_step == -1)
        {
          j = i + 1;
          j_end = size;
          j_step = 1;
        }
        else
        {
          break;
        }
      }
      assert(i!=j);
      assert(j >= 0);
      assert(j < size);
      //Only take frequencies of the same depth into account
      if (n[j] < 1 || depths[j] != depth) continue;
      std::vector<int> new_newick_with_zero(n);
      --new_newick_with_zero[i];
      assert(new_newick_with_zero[i] == 0);
      ++new_newick_with_zero[j];
      //Remove brackets after possibly lonely value
      #ifdef DEBUG_GETSIMPLERNEWICKS
      {
        const std::string newick_str_with_zeroes = Newick::DumbNewickToString(new_newick_with_zero);
        TRACE(newick_str_with_zeroes);
        const std::string dist_i_j = boost::lexical_cast<std::string>(std::abs(i - j));
        TRACE(dist_i_j)
      }
      #endif
      //If there is only one or two values between
      //the brackets, and one of these values was a
      //1 becoming added to the other, nullify the
      //1 and both brackets:
      //'((1,1),2)' -> '(00102)' -> '(1,2)'
      if (std::abs(i - j) == 1)
        //|| (std::abs(i - j) == 2 && n[i] == 1))
      {
        const int index_bracket_open  = std::min(i,j) - 1;
        const int index_bracket_close = std::max(i,j) + 1;
        if ( new_newick_with_zero[index_bracket_open]  == Newick::bracket_open
          && new_newick_with_zero[index_bracket_close] == Newick::bracket_close)
        {
          new_newick_with_zero[index_bracket_open]  = 0;
          new_newick_with_zero[index_bracket_close] = 0;
        }
      }
      #ifdef DEBUG_GETSIMPLERNEWICKS
      {
        const std::string newick_str_with_more_zeroes = Newick::DumbNewickToString(new_newick_with_zero);
        TRACE(newick_str_with_more_zeroes);
      }
      #endif
      //Remove decremented i and possibly nullified brackets
      std::vector<int> new_newick;
      std::remove_copy(
        new_newick_with_zero.begin(),
        new_newick_with_zero.end(),
        std::back_inserter(new_newick),
        0);
      //Add brackets if these are removed
      if (new_newick.front() != Newick::bracket_open
        || new_newick.back() != Newick::bracket_close)
      {
        new_newick = Newick().Surround(new_newick);
      }
      #ifdef DEBUG_GETSIMPLERNEWICKS
      {
        const std::string newick_str_done = Newick::DumbNewickToString(new_newick);
        TRACE(newick_str_done);
      }
      #endif
      #define DEBUG_2436964926435498753298216832187
      #ifdef  DEBUG_2436964926435498753298216832187
      if (!Newick().IsNewick(new_newick))
      {
        TRACE(Newick().DumbNewickToString(new_newick));
      }
      #endif

      assert(Newick().IsNewick(new_newick));
      newicks.push_back(std::make_pair(new_newick, 1));
      continue;
    }
  }

  return newicks;

  /*
  const int size = boost::numeric_cast<int>(n.size());
  for (int i = 0; i!=size; ++i)
  {
    if (n[i] < 1) continue;
    assert(n[i] > 0);
    if (n[i] > 1)
    {
      std::vector<int> new_newick(n);
      --new_newick[i];
      #ifdef DEBUG_GETSIMPLERNEWICKSFREQUENCYPAIRS
      std::clog << "Store: " << Newick::NewickToString(new_newick) << '\n';
      #endif
      newicks.push_back(std::make_pair(new_newick,n[i]));
      continue;
    }
    assert(n[i] == 1); //Most difficult...
    const int depth = depths[i];
    const int j_start = FindPosBefore(n,Newick::bracket_open,i);
    const int j_end   = FindPosAfter( n,Newick::bracket_close,i);
    assert(j_start >= 0);
    assert(j_end >= 0);
    assert(j_start <= boost::numeric_cast<int>(n.size()));
    assert(j_end <= boost::numeric_cast<int>(n.size()));
    for (int j=j_start; j!=j_end; ++j)
    {
      if (i==j) continue;
      if (n[j] < 1) continue;
      if (depths[j] != depth) continue;
      //Decrement index i to zero
      //Increment index j
      std::vector<int> new_newick_with_zero(n);
      --new_newick_with_zero[i];
      assert(new_newick_with_zero[i] == 0);
      ++new_newick_with_zero[j];
      //Remove brackets after possibly lonely value
      #ifdef DEBUG_GETSIMPLERNEWICKSFREQUENCYPAIRS
      std::clog << "1: "
        << Newick::DumbNewickToString(new_newick_with_zero)
        << " -> ["
        << i
        << "]="
        << new_newick_with_zero[i]
        << " - ["
        << j
        << "]="
        << new_newick_with_zero[j]
        << " = "
        << std::abs(i-j)
        << '\n';
      #endif
      if (std::abs(i - j) == 1)
      {
        const int index_bracket_open  = std::min(i,j) - 1;
        const int index_bracket_close = std::max(i,j) + 1;
        #ifdef DEBUG_GETSIMPLERNEWICKSFREQUENCYPAIRS
        std::clog
          << "["
          << index_bracket_open
          << "]-["
          << index_bracket_close
          << "]\n";
        #endif
        if ( new_newick_with_zero[index_bracket_open]  == Newick::bracket_open
          && new_newick_with_zero[index_bracket_close] == Newick::bracket_close)
        {
          new_newick_with_zero[index_bracket_open]  = 0;
          new_newick_with_zero[index_bracket_close] = 0;
          #ifdef DEBUG_GETSIMPLERNEWICKSFREQUENCYPAIRS
          std::clog << "2.5: " << Newick::DumbNewickToString(new_newick_with_zero) << '\n';
          #endif
        }
      }
      #ifdef DEBUG_GETSIMPLERNEWICKS
      std::clog << "2: " << Newick::DumbNewickToString(new_newick_with_zero) << '\n';
      #endif
      //Remove decremented i and possibly nullified brackets
      std::vector<int> new_newick;
      std::remove_copy(
        new_newick_with_zero.begin(),
        new_newick_with_zero.end(),
        std::back_inserter(new_newick),
        0);
      //Add brackets if these are removed
      if (new_newick.front() != Newick::bracket_open
        || new_newick.back() != Newick::bracket_close)
      {
        new_newick = Surround(new_newick);
      }
      #ifdef DEBUG_GETSIMPLERNEWICKSFREQUENCYPAIRS
      std::clog << "Store: " << Newick::DumbNewickToString(new_newick) << '\n';
      #endif
      assert(IsNewick(new_newick));
      assert(n[i] == 1);
      newicks.push_back(std::make_pair(new_newick,1));
      //newicks.push_back(new_newick);
      continue;
    }
  }
  */
}


#ifndef NDEBUG
///Test tests all Newick functions
void ribi::NewickCpp98::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    Newick();
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  //Check difference between C++98 and C++0x
  assert(Newick().CreateValidTrinaryNewicks() == NewickCpp98().CreateValidTrinaryNewicks());
  assert(Newick().GetKnownProbabilities() == NewickCpp98().GetKnownProbabilities());

  //Check conversions from std::string to std::vector #1
  {
    const std::vector<int> v = Newick().StringToNewick("(11,(22,33))");
    assert(v.size() == 7);
    assert(v[0]==Newick::bracket_open);
    assert(v[1]==11);
    assert(v[2]==Newick::bracket_open);
    assert(v[3]==22);
    assert(v[4]==33);
    assert(v[5]==Newick::bracket_close);
    assert(v[6]==Newick::bracket_close);
  }
  //Check if well-formed Newicks are accepted
  {
    const std::vector<std::string> v = Newick().CreateValidNewicks();
    for(const std::string& s: v)
    {
      #ifdef TRACE_REJECTED_NEWICKS
      const std::string debug = "I must be accepted: " + s;
      TRACE(debug);
      #endif
      assert(Newick().IsNewick(s));
      const std::vector<int> v = Newick().StringToNewick(s);
      assert(Newick().IsNewick(v));
    }
  }

  //Check if ill-formed Newicks are rejected
  {
    #ifndef NDEBUG
    const std::vector<std::string> v = Newick().CreateInvalidNewicks();
    for(const std::string& s: v)
    {
      #ifdef TRACE_REJECTED_NEWICKS
      const std::string debug = "I must be rejected: " + s;
      TRACE(debug);
      #endif
      assert(!Newick().IsNewick(s));
      //Cannot test if std::vector<int> versions are rejected,
      //because Newick().StringToNewick assumes a valid Newick
      //const std::vector<int> v = Newick().StringToNewick(s);
      //assert(!Newick::IsNewick(v));
    }
    #endif
  }
  //Check conversions from std::string to std::vector #2
  {
    const std::vector<int> v = Newick().StringToNewick("((11,22),33)");
    assert(v.size() == 7);
    assert(v[0]==Newick::bracket_open);
    assert(v[1]==Newick::bracket_open);
    assert(v[2]==11);
    assert(v[3]==22);
    assert(v[4]==Newick::bracket_close);
    assert(v[5]==33);
    assert(v[6]==Newick::bracket_close);
  }
  assert(Newick().CalcNumOfSymmetriesBinary(Newick().StringToNewick("(1,(3,1))"))==0);
  assert(Newick().CalcNumOfSymmetriesBinary(Newick().StringToNewick("(3,(1,1))"))==1);
  assert(Newick().CalcNumOfSymmetriesBinary(Newick().StringToNewick("(1,((1,1),(1,1)))"))==3);
  assert(Newick().CalcNumOfSymmetriesBinary(Newick().StringToNewick("(1,((1,1),(2,2)))"))==2);
  assert(Newick().CalcNumOfSymmetriesBinary(Newick().StringToNewick("(1,(2,3))"))==0);
  assert(Newick().CalcNumOfSymmetriesBinary(Newick().StringToNewick("(99,99)"))==1);
  assert(Newick().CalcNumOfSymmetriesBinary(Newick().StringToNewick("(3,(2,2))"))==1);
  assert(Newick().CalcNumOfSymmetriesBinary(Newick().StringToNewick("(2,(2,2))"))==1);
  assert(Newick().CalcNumOfSymmetriesBinary(Newick().StringToNewick("((3,3),(2,2))"))==2);
  assert(Newick().CalcNumOfSymmetriesBinary(Newick().StringToNewick("((3,3),(3,3))"))==3);
  assert(Newick().CalcNumOfSymmetriesBinary(Newick().StringToNewick("((3,3),(3,4))"))==1);
  assert(Newick().CalcNumOfSymmetriesBinary(Newick().StringToNewick("(((3,3),(4,4)),5)"))==2);
  assert(Newick().CalcNumOfSymmetriesBinary(Newick().StringToNewick("(((3,3),(5,5)),5)"))==2);
  assert(Newick().CalcNumOfSymmetriesBinary(Newick().StringToNewick("(((5,5),(5,5)),5)"))==3);
  assert(Newick().CalcNumOfSymmetriesBinary(Newick().StringToNewick("(((5,5),(5,5)),(4,4))"))==4);
  assert(Newick().CalcNumOfSymmetriesBinary(Newick().StringToNewick("(((5,5),(4,4)),(4,4))"))==3);
  assert(Newick().CalcNumOfSymmetriesBinary(Newick().StringToNewick("(((4,4),(4,4)),(4,4))"))==4);
  assert(Newick().CalcNumOfCombinationsBinary(Newick().StringToNewick("(3,(1,1))"))==10);
  assert(Newick().CalcNumOfCombinationsBinary(Newick().StringToNewick("(1,(3,1))"))==20);
  assert(Newick().CalcNumOfCombinationsBinary(Newick().StringToNewick("(1,(1,(1,(1,1))))"))==60);
  assert(Newick().CalcNumOfCombinationsBinary(Newick().StringToNewick("(1,((1,1),(1,1)))"))==15);
  assert(bigIntegerToString(Newick().FactorialBigInt(1))=="1");
  assert(bigIntegerToString(Newick().FactorialBigInt(2))=="2");
  assert(bigIntegerToString(Newick().FactorialBigInt(3))=="6");
  assert(bigIntegerToString(Newick().FactorialBigInt(4))=="24");
  assert(bigIntegerToString(Newick().FactorialBigInt(5))=="120");
  assert(bigIntegerToString(Newick().FactorialBigInt(6))=="720");
  assert(Newick().GetLeafMaxArity(Newick().StringToNewick("(1)"))   == 1);
  assert(Newick().GetLeafMaxArity(Newick().StringToNewick("(12)"))  == 1);
  assert(Newick().GetLeafMaxArity(Newick().StringToNewick("(123)")) == 1);
  assert(Newick().GetLeafMaxArity(Newick().StringToNewick("(1,2)"))   == 2);
  assert(Newick().GetLeafMaxArity(Newick().StringToNewick("(12,2)"))  == 2);
  assert(Newick().GetLeafMaxArity(Newick().StringToNewick("(123,2)")) == 2);
  assert(Newick().GetLeafMaxArity(Newick().StringToNewick("(1,(1,2))"))   == 2);
  assert(Newick().GetLeafMaxArity(Newick().StringToNewick("(1,(12,2))"))  == 2);
  assert(Newick().GetLeafMaxArity(Newick().StringToNewick("(1,(123,2))")) == 2);
  assert(Newick().GetLeafMaxArity(Newick().StringToNewick("((1,2),3)"))   == 2);
  assert(Newick().GetLeafMaxArity(Newick().StringToNewick("((12,2),3)"))  == 2);
  assert(Newick().GetLeafMaxArity(Newick().StringToNewick("((123,2),3)")) == 2);
  assert(Newick().GetLeafMaxArity(Newick().StringToNewick("(1,2,3)"))   == 3);
  assert(Newick().GetLeafMaxArity(Newick().StringToNewick("(12,2,3)"))  == 3);
  assert(Newick().GetLeafMaxArity(Newick().StringToNewick("(123,2,3)")) == 3);
  assert(Newick().GetLeafMaxArity(Newick().StringToNewick("(1,(1,2,3))"))   == 3);
  assert(Newick().GetLeafMaxArity(Newick().StringToNewick("(1,(12,2,3))"))  == 3);
  assert(Newick().GetLeafMaxArity(Newick().StringToNewick("(1,(123,2,3))")) == 3);
  assert(Newick().GetLeafMaxArity(Newick().StringToNewick("((1,2,3),4)"))   == 3);
  assert(Newick().GetLeafMaxArity(Newick().StringToNewick("((12,2,3),4)"))  == 3);
  assert(Newick().GetLeafMaxArity(Newick().StringToNewick("((123,2,3),4)")) == 3);

  assert(fuzzy_equal_to()(  2.0,Newick().CalcDenominator(Newick().StringToNewick("(1,1)"),10.0)));
  assert(fuzzy_equal_to()(  6.0,Newick().CalcDenominator(Newick().StringToNewick("((1,1),1)"),10.0)));
  assert(fuzzy_equal_to()( 26.0,Newick().CalcDenominator(Newick().StringToNewick("(1,2)"),10.0)));
  assert(fuzzy_equal_to()( 32.0,Newick().CalcDenominator(Newick().StringToNewick("((1,1),2)"),10.0)));
  assert(fuzzy_equal_to()( 32.0,Newick().CalcDenominator(Newick().StringToNewick("(2,(1,1))"),10.0)));
  assert(fuzzy_equal_to()( 50.0,Newick().CalcDenominator(Newick().StringToNewick("((1,1),3)"),10.0)));
  assert(fuzzy_equal_to()( 80.0,Newick().CalcDenominator(Newick().StringToNewick("((1,2),3)"),10.0)));
  assert(fuzzy_equal_to()( 80.0,Newick().CalcDenominator(Newick().StringToNewick("((3,1),2)"),10.0)));
  assert(fuzzy_equal_to()( 80.0,Newick().CalcDenominator(Newick().StringToNewick("((2,3),1)"),10.0)));
  assert(fuzzy_equal_to()(102.0,Newick().CalcDenominator(Newick().StringToNewick("((2,1),4)"),10.0)));
  assert(fuzzy_equal_to()(152.0,Newick().CalcDenominator(Newick().StringToNewick("(2,(1,(3,3)))"),10.0)));
  assert(fuzzy_equal_to()(162.0,Newick().CalcDenominator(Newick().StringToNewick("((2,3),4)"),10.0)));
  assert(fuzzy_equal_to()(180.0,Newick().CalcDenominator(Newick().StringToNewick("((1,2),(3,4))"),10.0)));
  assert(fuzzy_equal_to()(180.0,Newick().CalcDenominator(Newick().StringToNewick("((4,1),(2,3))"),10.0)));
  assert(fuzzy_equal_to()(180.0,Newick().CalcDenominator(Newick().StringToNewick("((3,4),(1,2))"),10.0)));
  assert(fuzzy_equal_to()(180.0,Newick().CalcDenominator(Newick().StringToNewick("((2,3),(4,1))"),10.0)));
  {
    /*
    const std::vector<int> v = { 0,1,2,3,4,5,6 };
    assert(Newick::FindPosAfter(v,3,2)==3);
    assert(Newick::FindPosAfter(v,4,2)==4);
    assert(Newick::FindPosAfter(v,5,2)==5);
    assert(Newick::FindPosAfter(v,6,2)==6);
    assert(Newick::FindPosBefore(v,3,4)==3);
    assert(Newick::FindPosBefore(v,2,4)==2);
    assert(Newick::FindPosBefore(v,1,4)==1);
    assert(Newick::FindPosBefore(v,0,4)==0);
    */
  }
  /* C++98
  {
    const std::vector<int> v = Newick::GetDepth(Newick().StringToNewick("(1,(2,2))"));
    const std::vector<int> w = Newick::GetDepth(Newick().StringToNewick("(9,(9,9))"));
    const std::vector<int> x = { 0,0,1,1,1,1,0 };
    assert(v == x);
    assert(w == x);
  }
  {
    const std::vector<int> v = Newick::GetDepth(Newick().StringToNewick("((2,2),1)"));
    const std::vector<int> w = { 0,1,1,1,1,0,0 };
    assert(v == w);
  }
  {
    const std::vector<int> v = Newick::GetDepth(Newick().StringToNewick("(1,(2,2),1)"));
    const std::vector<int> w = { 0,0,1,1,1,1,0,0 };
    assert(v == w);
  }
  {
    const std::vector<int> v = Newick::GetDepth(Newick().StringToNewick("(1,(2,3),4,(5,6))"));
    const std::vector<int> w = { 0,0,1,1,1,1,0,1,1,1,1,0 };
    assert(v == w);
  }
  {
    const std::vector<int> v = Newick::GetDepth(Newick().StringToNewick("(1,(2,3),(5,6))"));
    const std::vector<int> w = { 0,0,1,1,1,1,1,1,1,1,0 };
    assert(v == w);
  }
  {
    const std::vector<int> v = Newick::GetDepth(Newick().StringToNewick("(1,(2,(3,4)),((5,6),7))"));
    const std::vector<int> w = { 0,0,1,1,2,2,2,2,1,1,2,2,2,2,1,1,0 };
    assert(v == w);
  }
  */
  //Test GetRootBranches
  {
    const std::vector<std::vector<int> > v = Newick().GetRootBranches(Newick().StringToNewick("(1,2)"));
    assert(v.size() == 2);
    assert(std::find(v.begin(),v.end(),
      Newick().StringToNewick("(1)")) != v.end());
    assert(std::find(v.begin(),v.end(),
      Newick().StringToNewick("(2)")) != v.end());
  }
  {
    const std::vector<std::vector<int> > v = Newick().GetRootBranches(Newick().StringToNewick("(1,(2,3))"));
    assert(v.size() == 2);
    assert(std::find(v.begin(),v.end(),
      Newick().StringToNewick("(1)")) != v.end());
    assert(std::find(v.begin(),v.end(),
      Newick().StringToNewick("(2,3)")) != v.end());
  }
  {
    const std::vector<std::vector<int> > v = Newick().GetRootBranches(Newick().StringToNewick("(1,2,(3,4))"));
    assert(v.size() == 3);
    assert(std::find(v.begin(),v.end(),
      Newick().StringToNewick("(1)")) != v.end());
    assert(std::find(v.begin(),v.end(),
      Newick().StringToNewick("(2)")) != v.end());
    assert(std::find(v.begin(),v.end(),
      Newick().StringToNewick("(3,4)")) != v.end());
  }
  //Compare C++98 and C++0x version
  {
    const std::vector<std::string> v = Newick().CreateValidBinaryNewicks();
    for(const std::string& s: v)
    {
      const std::vector<int> n = Newick().StringToNewick(s);
      assert(Newick().GetRootBranches(n) == NewickCpp98().GetRootBranches(n));
    }
  }

  //Check if binary and trinary Newicks are detected correctly
  {
    const std::vector<std::string> v = Newick().CreateValidBinaryNewicks();
    for(const std::string& s: v)
    {
      const std::vector<int> n = Newick().StringToNewick(s);
      assert(Newick().IsBinaryNewick(n));
    }
  }
  //Check if unary Newicks are detected correctly
  {
    const std::vector<std::string> v = Newick().CreateValidUnaryNewicks();
    for(const std::string& s: v)
    {
      const std::vector<int> n = Newick().StringToNewick(s);
      assert( Newick().GetLeafMaxArity(n)<=1);
      assert( Newick().IsUnaryNewick(n));
      assert(!Newick().IsBinaryNewick(n));
      assert(!Newick().IsTrinaryNewick(n));
    }
  }
  //Check if binary Newicks are detected correctly
  {
    const std::vector<std::string> v = Newick().CreateValidBinaryNewicks();
    for(const std::string& s: v)
    {
      const std::vector<int> n = Newick().StringToNewick(s);
      assert( Newick().GetLeafMaxArity(n)<=2);
      assert(!Newick().IsUnaryNewick(n));
      assert( Newick().IsBinaryNewick(n));
      assert(!Newick().IsTrinaryNewick(n));
    }
  }
  //Check if trinary Newicks are detected correctly
  {
    const std::vector<std::string> v = Newick().CreateValidTrinaryNewicks();
    for(const std::string& s: v)
    {
      //TRACE(s);
      const std::vector<int> n = Newick().StringToNewick(s);
      assert( Newick().GetLeafMaxArity(n)<=3);
      assert(!Newick().IsUnaryNewick(n));
      assert(!Newick().IsBinaryNewick(n));
      assert( Newick().IsTrinaryNewick(n));
    }
  }
  //Test binary Newick
  {
    const std::string s("(1,(2,3))");
    const std::vector<std::vector<int> > n
      = Newick().GetSimplerNewicks(Newick().StringToNewick(s));
    //#define DEBUG_1_BO_1_2_3_BC
    #ifdef  DEBUG_1_BO_1_2_3_BC
    for(const auto& t: n)
    {
      TRACE(Newick::NewickToString(t));
    }
    #endif
    assert(n.size() == 2);
    assert(std::find(n.begin(),n.end(),Newick().StringToNewick("(1,(1,3))"))
      != n.end());
    assert(std::find(n.begin(),n.end(),Newick().StringToNewick("(1,(2,2))"))
      != n.end());
  }
  {
    const std::string s("(1,(2,3,4))");
    const std::vector<std::vector<int> > n
      = Newick().GetSimplerNewicks(Newick().StringToNewick(s));
    assert(n.size() == 3);
    assert(std::find(n.begin(),n.end(),Newick().StringToNewick("(1,(1,3,4))"))
      != n.end());
    assert(std::find(n.begin(),n.end(),Newick().StringToNewick("(1,(2,2,4))"))
      != n.end());
    assert(std::find(n.begin(),n.end(),Newick().StringToNewick("(1,(2,3,3))"))
      != n.end());
  }
  {
    const std::string s("(1,(1,3,4))");
    const std::vector<std::vector<int> > n
     = Newick().GetSimplerNewicks(Newick().StringToNewick(s));
    //#define DEBUG_1_BO_1_3_4_BC
    #ifdef  DEBUG_1_BO_1_3_4_BC
    TRACE(boost::lexical_cast<std::string>(n.size()));
    for(const auto& t: n)
    {
      TRACE(Newick::NewickToString(t));
    }
    #endif
    assert(n.size() == 4);
    assert(std::find(n.begin(),n.end(),Newick().StringToNewick("(1,(4,4))"))
      != n.end());
    assert(std::find(n.begin(),n.end(),Newick().StringToNewick("(1,(3,5))"))
      != n.end());
    assert(std::find(n.begin(),n.end(),Newick().StringToNewick("(1,(1,2,4))"))
      != n.end());
    assert(std::find(n.begin(),n.end(),Newick().StringToNewick("(1,(1,3,3))"))
      != n.end());
  }
  {
    const std::string s("(1,(1,3,4))");
    const std::vector<std::pair<std::vector<int>,int> > n
      = NewickCpp98().GetSimplerNewicksFrequencyPairs(Newick().StringToNewick(s));
    #ifdef TRACE_GETSIMPLERNEWICKSFREQUENCYPAIRS_1_134
    typedef std::pair<std::vector<int>,int> Pair;
    for(const Pair& p: n)
    {
      std::cout << Newick::NewickToString(p.first) << '\n';
    }
    #endif
    assert(n.size() == 4);
    assert(std::find(n.begin(),n.end(),
      std::make_pair(Newick().StringToNewick("(1,(4,4))"),1))
      != n.end());
    assert(std::find(n.begin(),n.end(),
      std::make_pair(Newick().StringToNewick("(1,(3,5))"),1))
      != n.end());
    assert(std::find(n.begin(),n.end(),
      std::make_pair(Newick().StringToNewick("(1,(1,2,4))"),3))
      != n.end());
    assert(std::find(n.begin(),n.end(),
      std::make_pair(Newick().StringToNewick("(1,(1,3,3))"),4))
      != n.end());
  }
  {
    const std::string s("((1,1),2)");
    const std::vector<std::vector<int> > n
      = Newick().GetSimplerNewicks(
        Newick().StringToNewick(s)
      );
    //#define DEBUG_BO_1_1_BC_2
    #ifdef  DEBUG_BO_1_1_BC_2
    for(const auto& t: n)
    {
      TRACE(Newick::NewickToString(t));
    }
    #endif
    assert(n.size() == 3);
    assert(std::find(n.begin(),n.end(),
      Newick().StringToNewick("(2,2)"))
      != n.end());
    assert(std::find(n.begin(),n.end(),
      Newick().StringToNewick("((1,1),1)"))
      != n.end());
  }
  {
    const std::string s("((1,1),2)");
    typedef std::pair<std::vector<int>,int> Pair;
    const std::vector<Pair> n
      = NewickCpp98().GetSimplerNewicksFrequencyPairs(Newick().StringToNewick(s));
    #ifdef TRACE_GETSIMPLERNEWICKSFREQUENCYPAIRS_11_2
    for(const Pair& p: n)
    {
      std::clog << Newick::NewickToString(p.first) << '\n';
    }
    #endif
    assert(n.size() == 3);
    assert(std::find(n.begin(),n.end(),
      std::make_pair(Newick().StringToNewick("(2,2)"),1))
      != n.end());
    assert(std::find(n.begin(),n.end(),
      std::make_pair(Newick().StringToNewick("((1,1),1)"),2))
      != n.end());
  }
  {
    const std::string s("((2,1),4)");
    const std::vector<std::vector<int> > n
      = Newick().GetSimplerNewicks(
        Newick().StringToNewick(s)
      );
    assert(n.size() == 3);
    assert(std::find(n.begin(),n.end(),
      Newick().StringToNewick("(3,4)"))
      != n.end());
    assert(std::find(n.begin(),n.end(),
      Newick().StringToNewick("((1,1),4)"))
      != n.end());
    assert(std::find(n.begin(),n.end(),
      Newick().StringToNewick("((2,1),3)"))
      != n.end());
  }
  {
    const std::string s("((2,1),4)");
    typedef std::pair<std::vector<int>,int> Pair;
    const std::vector<Pair> n
      = NewickCpp98().GetSimplerNewicksFrequencyPairs(Newick().StringToNewick(s));
    #ifdef TRACE_GETSIMPLERNEWICKSFREQUENCYPAIRS_21_2
    for(const Pair& p: n)
    {
      TRACE(Newick::NewickToString(p.first));
    }
    #endif
    assert(n.size() == 3);
    assert(std::find(n.begin(),n.end(),
      std::make_pair(Newick().StringToNewick("(3,4)"),1))
      != n.end());
    assert(std::find(n.begin(),n.end(),
      std::make_pair(Newick().StringToNewick("((1,1),4)"),2))
      != n.end());
    assert(std::find(n.begin(),n.end(),
      std::make_pair(Newick().StringToNewick("((2,1),3)"),4))
      != n.end());
  }
  {
    const std::string s("((2,3),4)");
    const std::vector<std::vector<int> > n
      = Newick().GetSimplerNewicks(
        Newick().StringToNewick(s)
      );
    assert(n.size() == 3);
    assert(std::find(n.begin(),n.end(),
      Newick().StringToNewick("((1,3),4)"))
      != n.end());
    assert(std::find(n.begin(),n.end(),
      Newick().StringToNewick("((2,2),4)"))
      != n.end());
    assert(std::find(n.begin(),n.end(),
      Newick().StringToNewick("((2,3),3)"))
      != n.end());
  }
  {
    const std::string s("((2,3),4)");
    typedef std::pair<std::vector<int>,int> Pair;
    const std::vector<Pair> n
      = NewickCpp98().GetSimplerNewicksFrequencyPairs(Newick().StringToNewick(s));
    #ifdef TRACE_GETSIMPLERNEWICKSFREQUENCYPAIRS_23_4
    for(const Pair& p: n)
    {
      std::cout << Newick::NewickToString(p.first) << '\n';
    }
    #endif
    assert(n.size() == 3);
    assert(std::find(n.begin(),n.end(),
      std::make_pair(Newick().StringToNewick("((1,3),4)"),2))
      != n.end());
    assert(std::find(n.begin(),n.end(),
      std::make_pair(Newick().StringToNewick("((2,2),4)"),3))
      != n.end());
    assert(std::find(n.begin(),n.end(),
      std::make_pair(Newick().StringToNewick("((2,3),3)"),4))
      != n.end());
  }
  //Compare GetSimplerNewicks and
  //GetSimplerNewicksFrequencyPairs
  {
    const std::vector<std::string> newicks
      = Newick().CreateValidNewicks();
    for(const std::string& newick_str: newicks)
    {
      const std::vector<int> newick
        = Newick().StringToNewick(newick_str);
      const std::vector<std::vector<int> > v1
        = Newick().GetSimplerNewicks(newick);
      const std::vector<std::pair<std::vector<int>,int> > v2
        = Newick().GetSimplerNewicksFrequencyPairs(newick);
      assert(v1.size() == v2.size());
      const int size = boost::numeric_cast<int>(v1.size());
      for (int i=0; i!=size; ++i)
      {
        #define DEBUG_COMPARE_GSN_VS_GSNFP
        #ifdef  DEBUG_COMPARE_GSN_VS_GSNFP
        if (v1[i] != v2[i].first)
        {
          TRACE("ERROR: DIFFERENT NEWICK SIMPLIFICATIONS");
          TRACE(Newick().NewickToString(newick));
          TRACE(Newick().NewickToString(v1[i]));
          TRACE(Newick().NewickToString(v2[i].first));
        }
        #endif
        assert(v1[i] == v2[i].first);
      }
      assert(Newick().GetSimplerNewicksFrequencyPairs(newick)
        == NewickCpp98().GetSimplerNewicksFrequencyPairs(newick));
    }
  }
}
#endif
