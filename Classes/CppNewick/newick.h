//---------------------------------------------------------------------------
/*
Newick, Newick functions
Copyright (C) 2010-2011 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppNewick.htm
//---------------------------------------------------------------------------
#ifndef NEWICK_H
#define NEWICK_H

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

#include <cmath>
#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/tuple/tuple.hpp>
#pragma GCC diagnostic pop

#include "BigIntegerLibrary.hh"
#include "newickcpp98.h"
#include "newickstorage.h"
#include "trace.h"

///namespace Newick contains general Newick functions,
///not using an Newick class
namespace Newick
{
  enum { bracket_open  = -1 };
  enum { bracket_close = -2 };
  enum { comma         = -3 };
  enum { new_line      = -4 };
  enum { null          = -5 };

  ///fuzzy_equal_to is a predicate to test two doubles for equality
  ///with a certain tolerance. A tolerance of 0.0 denotes that
  ///an exact match is requested. Note that the value of 0.0 cannot
  ///be compared fuzzily.
  //From http://www.richelbilderbeek.nl/CppFuzzy_equal_to.htm
  struct fuzzy_equal_to : public std::binary_function<double,double,bool>
  {
    fuzzy_equal_to(const double tolerance = 0.01)
      : m_tolerance(tolerance)
    {
      assert(tolerance >= 0.0);
    }
    bool operator()(const double lhs, const double rhs) const
    {
      const double d = std::fabs(m_tolerance * lhs);
      return rhs > lhs - d
          && rhs < lhs + d;
    }
    const double m_tolerance;
  };

  ///CreateVector creates a std::vector from three arguments
  ///From http://www.richelbilderbeek.nl/CppCreateVector.htm

  template <class T>
  const std::vector<T> CreateVector(const T& a, const T& b, const T& c)
  {
    std::vector<T> v;
    v.reserve(3);
    v.push_back(a);
    v.push_back(b);
    v.push_back(c);
    return v;
  }

  ///AllAboutEqual tests if all values in a std::vector are about equal.
  ///From http://www.richelbilderbeek.nl/CppAllAboutEqual.htm
  bool AllAboutEqual(const std::vector<double>& v,const double tolerance = 0.01);

  ///CalcComplexity calculates the complexity of a Newick.
  ///From http://www.richelbilderbeek.nl/CppCalcComplexity.htm
  const BigInteger CalcComplexity(const std::vector<int>& v);

  ///CalcNumOfCombinations returns the number of combinations a Newick can have.
  ///
  ///The number of possible combinations equals
  ///     !(v0 + v1 + v2 + etc)
  /// N = -------------------------- / 2^number_of_symmetries
  ///     !v0 * !v1 * !v2 * etc
  ///
  ///      n
  ///   = --- / 2^number_of_symmetries
  ///      d
  ///
  /// where v denotes an element in vector v in range [1,-> >
  /// where v0 denotes the first element in vector v
  /// and where !v0 denotes the factorial of v0
  ///     {factorial(!SUM(v)) product terms}
  /// N = --------------------------------------------------
  ///     {product terms} + { number_symmetries times a '2'}
  ///
  ///     numerator_terms
  /// N = --------------------------------------------------
  ///     denominator_terms with appended number_symmetries times a '2'
  ///
  ///From http://www.richelbilderbeek.nl/CppCalcNumOfCombinationsBinary.htm
  const BigInteger CalcNumOfCombinationsBinary(const std::vector<int>& v);

  ///CalcNumOfSymmetries calculates the number of symmetries in a Newick.
  ///From http://www.richelbilderbeek.nl/CppCalcNumOfSymmetriesBinary.htm
  const BigInteger CalcNumOfSymmetriesBinary(std::vector<int> v);

  double CalcDenominator(const std::vector<int>& v,const double theta);

  ///CalcProbabilitySimpleNewick returns the probability of
  ///a Newick for a value of theta
  ///using the Ewens formula
  double CalcProbabilitySimpleNewick(const std::vector<int>& v,const double theta);

  ///CheckNewick checks if a std::string is a valid Newick.
  ///If this std::string is not a valid Newick,
  ///CheckNewick throws an exception with a detailed description
  ///From http://www.richelbilderbeek.nl/CppCheckNewick.htm
  void CheckNewick(const std::string& s);

  ///CheckNewick checks if a std::vector<int> is a valid Newick.
  ///If this std::vector<int> is not a valid Newick,
  ///CheckNewick throws an exception with a detailed description
  ///From http://www.richelbilderbeek.nl/CppCheckNewick.htm
  void CheckNewick(const std::vector<int>& v);

  ///CreateInvalidNewicks creates std::strings
  ///that cannot and must not be converted to a Newick
  ///From http://www.richelbilderbeek.nl/CppCreateInvalidNewicks.htm
  const std::vector<std::string> CreateInvalidNewicks();

  ///CreateRandomNewick creates an unsorted Newick string,
  ///with n values, with each value e [0,max>.
  ///From http://www.richelbilderbeek.nl/CppCreateRandomNewick.htm
  const std::string CreateRandomNewick(const int n,const int max);


  ///CreateRandomBinaryNewickVector creates an unsorted Newick
  ///std::vector<int>, with n values, with each value e [0,max>.
  ///From http://www.richelbilderbeek.nl/CppCreateRandomBinaryNewickVector.htm
  const std::vector<int> CreateRandomBinaryNewickVector(const int n,const int max);

  ///CreateValidBinaryNewicks creates std::strings
  ///that can be converted to a BinaryNewickVector.
  ///From http://www.richelbilderbeek.nl/CppCreateValidBinaryNewicks.htm
  const std::vector<std::string> CreateValidBinaryNewicks();

  ///CreateValidNewicks creates std::strings
  ///that are valid newicks.
  ///From http://www.richelbilderbeek.nl/CppCreateValidNewicks.htm
  const std::vector<std::string> CreateValidNewicks();

  ///CreateValidTrinaryNewicks creates std::strings
  ///that can be converted to a TrinaryNewickVector.
  ///From http://www.richelbilderbeek.nl/CppCreateValidTinaryNewicks.htm
  const std::vector<std::string> CreateValidTrinaryNewicks();

  ///CreateValidUnaryNewicks creates unary Newick std::strings
  const std::vector<std::string> CreateValidUnaryNewicks();


  ///DumbNewickToString converts a Newick std::vector<int> to a
  ///standard-format std::string without error checking.
  ///From http://www.richelbilderbeek.nl/CppDumbNewickToString.htm
  const std::string DumbNewickToString(const std::vector<int>& v);


  ///Factorial calculates the factorial of all std::vector elements.
  ///From http://www.richelbilderbeek.nl/CppFactorial.htm
  const std::vector<int> Factorial(const std::vector<int>& v_original);

  ///FactorialBigInt returns the factorial of an integer
  ///as a BigInteger.
  ///From http://www.richelbilderbeek.nl/CppFactorialBigInt.htm
  const BigInteger FactorialBigInt(const int n);

  ///Factorial calculates the factorial of a value.
  ///From http://www.richelbilderbeek.nl/CppFactorial.htm
  int Factorial(const int n);

  int FindPosAfter(const std::vector<int>& v,const int index,const int value);
  int FindPosBefore(const std::vector<int>& v,const int index,const int value);

  ///GetDepth returns the depth of each Newick element
  ///Example #1
  ///(1,2,3)
  ///01 1 10
  ///Example #2
  ///((1,2),(3,(4,5)))
  ///000 00 00 00 0000 <- depth layer 0 (comma's are skipped)
  ///.11 11 11 11 111. <- depth layer 1
  ///... .. .. .2 22.. <- depth layer 2
  ///011 11 11 22 2210 <- result of GetDepth
  const std::vector<int> GetDepth(const std::vector<int>& n);


  ///GetFactorialTerms returns all terms from a factorial.
  ///For example, 4! return {1,2,3,4}
  ///From http://www.richelbilderbeek.nl/CppGetFactorialTerms.htm
  const std::vector<int> GetFactorialTerms(const int n);

  std::vector<boost::tuple<std::string,double,double> > GetKnownProbabilities();
  int GetLeafMaxArity(const std::vector<int>& n);


  ///GetRootBranches obtains the root branches from a non-unary Newick.
  ///Examples:
  ///(1,2)               -> { 1     , 2             }
  ///(1,2,3)             -> { 1     , 2     , 3     }
  ///((1,1),(2,2),(3,3)) -> { (1,1) , (2,2) , (3,3) }
  ///From http://www.richelbilderbeek.nl/CppGetRootBranchesBinary.htm
  const std::vector<std::vector<int> >
    GetRootBranches(const std::vector<int>& n);

  ///GetRootBranchesBinary obtains the two root branches from a binary Newick.
  ///Examples:
  ///(1,2)                 -> { 1             , 2     }
  ///(1,(2,3))             -> { 1             , (2,3) }
  ///((1,2),(3,4))         -> { (1,2)         , (3,4) }
  ///(((1,2),(3,4)),(5,6)) -> { ((1,2),(3,4)) , (5,6) }
  ///From http://www.richelbilderbeek.nl/CppGetRootBranchesBinary.htm
  const std::pair<std::vector<int>,std::vector<int> >
    GetRootBranchesBinary(const std::vector<int>& n);

  ///GetSimplerBinaryNewicks creates simpler, derived Newicks from a binary Newick.
  ///From http://www.richelbilderbeek.nl/CppGetSimplerBinaryNewicks.htm
  const std::vector<std::vector<int> > GetSimplerBinaryNewicks(
    const std::vector<int>& n);

  ///GetSimplerNewicks creates simpler, derived Newicks from a Newick.
  ///From http://www.richelbilderbeek.nl/CppGetSimplerNewicks.htm
  const std::vector<std::vector<int> > GetSimplerNewicks(
    const std::vector<int>& n);

  ///GetSimplerNewicksFrequencyPairs creates simpler, derived Newicks from a Newick.
  ///Its simpler Newicks are identical to those created by GetSimplerNewicks.
  ///From http://www.richelbilderbeek.nl/CppGetSimplerNewicksFrequencyPairs.htm
  const std::vector<std::pair<std::vector<int>,int> >
    GetSimplerNewicksFrequencyPairs(
    const std::vector<int>& n);

  ///GetSimplerBinaryNewicksFrequencyPairs creates simpler, derived Newicks from a
  ///binary Newick as well as the frequency that is simplified.
  ///From http://www.richelbilderbeek.nl/CppGetSimplerBinaryNewicksFrequencyPairs.htm
  const std::vector<std::pair<std::vector<int>,int> >
    GetSimplerBinaryNewicksFrequencyPairs(
    const std::vector<int>& n);
  const std::string GetVersion();
  const std::vector<std::string> GetVersionHistory();

  ///InspectInvalidNewick writes the cause of the Newick invalidity
  ///to the std::ostream.
  ///From http://www.richelbilderbeek.nl/CppInspectInvalidNewick.htm
  void InspectInvalidNewick(std::ostream& os, const std::vector<int>& v);

  ///IsBinaryNewick checks if a Newick is a binary tree,
  ///that is: each node splits in two (not more) branches
  ///From http://www.richelbilderbeek.nl/CppIsBinaryNewick.htm
  bool IsBinaryNewick(std::vector<int> v);

  bool IsTrinaryNewick(std::vector<int> v);

  ///IsUnaryNewick checks if a Newick is a unary tree,
  ///that is: there is only one node.
  ///From http://www.richelbilderbeek.nl/CppIsUnaryNewick.htm
  bool IsUnaryNewick(const std::vector<int>& v);

  ///IsNewick returns true if a std::string is a valid Newick
  ///and false otherwise.
  ///From http://www.richelbilderbeek.nl/CppIsNewick.htm
  bool IsNewick(const std::string& s);

  ///IsNewick returns true if a std::vector<int> is a valid Newick
  ///and false otherwise.
  ///From http://www.richelbilderbeek.nl/CppIsNewick.htm
  bool IsNewick(const std::vector<int>& v);

  ///IsSimple returns true if the Newick std::vector contains
  ///leaves only. For example, the Newick '(1,2,3)' is simple,
  ///the Newick '((1,2),3)' is not simple
  ///From http://www.richelbilderbeek.nl/CppIsNewick.htm
  bool IsSimple(const std::vector<int>& v);

  ///NewickToString converts a Newick std::vector<int> to a
  ///standard-format std::string.
  ///From http://www.richelbilderbeek.nl/CppNewickToString.htm
  const std::string NewickToString(const std::vector<int>& v);

  ///ReplaceLeave replaces the first leaf that it finds by a value.
  ///For example, using ReplaceLeave on '((1,2),(3,4))' with a value
  ///of 42 results in '(42,(3,4))'.
  const std::vector<int> ReplaceLeave(const std::vector<int>& newick,const int value);

  ///StringToNewick converts a std::string to a Newick std::vector<int>
  ///StringToNewick assumes that the input is well-formed and
  ///has both trailing and tailing brackets.
  ///From http://www.richelbilderbeek.nl/CppNewickToVector.htm
  const std::vector<int> StringToNewick(const std::string& newick);

  ///Surround surrounds the Newick with brackets
  const std::vector<int> Surround(const std::vector<int>& newick);

  void Test();

  char ValueToChar(const int value);

  template <class NewickType>
  double CalculateProbability(
    const NewickType& n,
    const double theta,
    NewickStorage<NewickType>& storage)
{
  //#define TRACE_NEWICK_CALCULATEPROBABILITY
  while(1)
  {
    try
    {
      //Is n already known?
      {
        const double p = storage.Find(n);
        if (p!=0.0)
        {
          return p;
        }
      }

      //Check for simple phylogeny
      if (n.IsSimple())
      {
        const double p = n.CalcProbabilitySimpleNewick(theta);
        storage.Store(n,p);
        return p;
      }
      //Complex
      //Generate other Newicks and their coefficients
      std::vector<double> coefficients;
      std::vector<NewickType> newicks;
      {
        const double d = n.CalcDenominator(theta);
        #ifdef TRACE_NEWICK_CALCULATEPROBABILITY
        TRACE("Denominator for "
          + n.ToStr()
          + " = "
          + boost::lexical_cast<std::string>(d));
        #endif
        typedef std::pair<std::vector<int>,int> NewickFrequencyPair;
        const std::vector<NewickFrequencyPair> newick_freqs
          = Newick::GetSimplerNewicksFrequencyPairs(n.Peek());
        BOOST_FOREACH(const NewickFrequencyPair& p,newick_freqs)
        {
          const int frequency = p.second;
          assert(frequency > 0);
          if (frequency == 1)
          {
            newicks.push_back(p.first);
            coefficients.push_back(theta / d);
          }
          else
          {
            const double f_d = static_cast<double>(frequency);
            newicks.push_back(p.first);
            coefficients.push_back( (f_d*(f_d-1.0)) / d);
          }
          #ifdef TRACE_NEWICK_CALCULATEPROBABILITY
          TRACE(std::string("BinaryNewickVector ")
            + Newick::NewickToString(p.first)
            + " has coefficient "
            + boost::lexical_cast<std::string>(coefficients.back()))
          #endif
        }
      }
      //Ask help about these new Newicks
      {
        const int sz = newicks.size();
        assert(newicks.size() == coefficients.size() );
        double p = 0.0;
        for (int i=0; i!=sz; ++i)
        {
          //Recursive function call
          p+=(coefficients[i] * CalculateProbability(newicks[i],theta,storage));
        }
        storage.Store(n,p);
        return p;
      }
    }
    catch (std::bad_alloc& e)
    {
      storage.CleanUp();
      std::cerr << "std::bad_alloc\n";
    }
    catch (std::exception& e)
    {
      storage.CleanUp();
      std::cerr << "std::exception";
    }
    catch (...)
    {
      storage.CleanUp();
      std::cerr << "Unknown exception\n";
    }
  }
}


  /*
  template <class NewickType>
  double CalculateProbabilityMessy(
    const NewickType& n,
    const double theta,
    NewickStorage<NewickType>& storage)
  {
  //#define TRACE_CALCULATEPROBABILITYMESSY
  while(1)
  {
    try
    {

      //Is n already known?
      {
        const double p = storage.Find(n);
        if (p!=0.0)
        {
          return p;
        }
      }

      //Check for simple phylogeny
      if (n.IsSimple())
      {
        const double p = n.CalcProbabilitySimpleNewick(theta);
        storage.Store(n,p);
        return p;
      }

      //Complex
      //Generate other Newicks and their coefficients
      std::vector<NewickType> newicks;
      std::vector<double> coefficients;
      {
        const double d = n.CalcDenominator(theta);
        #ifdef TRACE_CALCULATEPROBABILITYMESSY
        TRACE("Denominator for "
          + n.ToStr()
          + " = "
          + boost::lexical_cast<std::string>(d));
        #endif
        const std::vector<int>& v = n.Peek();
        const int sz = v.size();
        for (int i=0; i!=sz; ++i)
        {
          const int x = v[i];
          if (x < 0) //x is not a digit
          {
            continue;
          }
          if (x == 1)
          {
            NewickType next_newick = n.TermIsOne(i);
            if (!next_newick.Empty())
            {
              newicks.push_back(next_newick);
              coefficients.push_back(theta / d);
            }
          }
          else
          {
            NewickType next_newick = n.TermIsNotOne(i);
            if (!next_newick.Empty())
            {
              newicks.push_back(next_newick);
              const double x_d = static_cast<double>(x);
              coefficients.push_back( (x_d*(x_d-1.0)) / d);
            }
          }
        }
      }
      //Ask help about these new Newicks
      {
        const int sz = newicks.size();
        assert(newicks.size() == coefficients.size() );
        double p = 0.0;
        for (int i=0; i!=sz; ++i)
        {
          //Recursive function call
          p+=(coefficients[i] * CalculateProbabilityMessy(newicks[i],theta,storage));
        }
        storage.Store(n,p);
        return p;
      }
    }
    catch (std::bad_alloc& e)
    {
      storage.CleanUp();
      std::cerr << "std::bad_alloc\n";
    }
    catch (std::exception& e)
    {
      storage.CleanUp();
      std::cerr << "std::exception";
    }
    catch (...)
    {
      storage.CleanUp();
      std::cerr << "Unknown exception\n";
    }

  }
}
*/
//#endif


};

#endif // NEWICK_H

