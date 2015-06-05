#include <algorithm>
#include <cassert>
#include <climits>
#include <cmath>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <vector>

//From http://www.richelbilderbeek.nl/CppAccumulate_if.htm
template
<
  typename InputIterator,
  typename ElementType,
  typename Predicate
>
const ElementType accumulate_if(
  InputIterator first,
  const InputIterator last,
  ElementType init,
  const Predicate predicate)
{
  for (; first != last; ++first)
    if (predicate(*first)) init += *first;
  return init;
}

//Data from:
// * David Heath. An introduction to experimental design
// and statistics for biology. 1995. ISBN: 1-85728-132-2 PB.
// Page 263, box 10.3: Wilcoxon's signed rank test for
// paired samples: urea concentration in drinkers
// and non-drinkers
const std::vector<double> GetValuesNonDrinkers()
{
  std::vector<double> v;
  v.push_back( 4.4);
  v.push_back(18.6);
  v.push_back( 9.0);
  v.push_back(20.0);
  v.push_back(31.5);
  v.push_back(36.0);
  v.push_back(17.0);
  v.push_back(17.2);
  v.push_back(20.2);
  v.push_back(11.5);
  return v;
}

//Data from:
// * David Heath. An introduction to experimental design
// and statistics for biology. 1995. ISBN: 1-85728-132-2 PB.
// Page 263, box 10.3: Wilcoxon's signed rank test for
// paired samples: urea concentration in drinkers
// and non-drinkers
const std::vector<double> GetValuesDrinkers()
{
  std::vector<double> v;
  v.push_back( 5.0);
  v.push_back(17.2);
  v.push_back( 9.0);
  v.push_back(24.0);
  v.push_back(18.5);
  v.push_back(21.5);
  v.push_back( 7.6);
  v.push_back( 5.8);
  v.push_back( 7.6);
  v.push_back( 7.5);
  return v;
}

enum Sign { minus = -1, none = 0, plus = 1};

std::ostream& operator<<(std::ostream& os, const Sign& s)
{
  os << (s == minus ? "-" : (s == none ? " " : "+") );
  return os;
}

template <class T>
const std::vector<Sign> GetSigns(
  const std::vector<T>& a,
  const std::vector<T>& b)
{
  assert(a.size()==b.size()
    && "The two vectors must have equal "
       "sizes for a paired test");
  const std::size_t sz = a.size();
  std::vector<Sign> v(sz);
  for (std::size_t i = 0; i!=sz; ++i)
  {
    v[i] = (a[i]==b[i] ? none
         : (a[i]<b[i]? minus : plus) );
  }
  return v;
}

//From http://www.richelbilderbeek.nl/CppGetDifference.htm
template <typename T>
const std::vector<T> GetDifference(
  const std::vector<T>& a,
  const std::vector<T>& b)
{
  assert(a.size()==b.size());
  std::vector<T> v(a);
  const std::size_t sz = v.size();
  for (std::size_t i = 0; i!=sz; ++i)
  {
    v[i]-=b[i];
  }
  return v;
}

//From http://www.richelbilderbeek.nl/CppGetAbs.htm
template <typename T> struct Abs
  : public std::unary_function<T,T>
{
  const T operator()(const T& x) const
    { return (x < static_cast<T>(0.0) ? -x : x); }
};

//From http://www.richelbilderbeek.nl/CppGetAbs.htm
template <typename T>
void MakeAbs(std::vector<T>& v)
{
  std::transform(v.begin(),v.end(),v.begin(),Abs<T>());
}

//From http://www.richelbilderbeek.nl/CppGetAbs.htm
template <typename T>
const std::vector<T> GetAbs(
  const std::vector<T>& a)
{
  std::vector<T> v(a);
  MakeAbs(v);
  return v;
}

//From http://www.richelbilderbeek.nl/CppMinElementAbove.htm
double MinElementAbove(const std::vector<double>& v, const double above)
{
  const double max = std::numeric_limits<double>::max();
  double lowest = max;
  const std::vector<double>::const_iterator j = v.end();
  std::vector<double>::const_iterator i = v.begin();
  for ( ; i!=j; ++i)
  {
    if (*i > above && *i < lowest)
    {
      lowest = *i;
    }
  }
  return (lowest != max ? lowest : above);
}


//Thanks to Senbong G for detecting and fixing a bug in this code
const std::vector<double> GetRanks(const std::vector<double> &v)
{
  const size_t s = v.size();
  std::vector<double> w(s,0.0);
  double lowest_value = MinElementAbove(v, 0.0);
  int rank = 0;
  if(lowest_value != 0.0)
  {
    ++rank;
    const int n_with_this_value =
      std::count(v.begin(), v.end(), lowest_value);
    const double assigned_rank =
      static_cast<double>(rank + (rank + n_with_this_value - 1)) / 2.0;
    for(size_t i = 0; i != s; ++i)
    {
      if(v[i] == lowest_value)
      {
        w[i] = assigned_rank;
        ++rank;
      }
    }
  } // end if

  while(1)
  {
    const double new_lowest_value =
      MinElementAbove(v, lowest_value);
    if(new_lowest_value == lowest_value)
      break;
    lowest_value = new_lowest_value;

    const int n_with_this_value =
        std::count(v.begin(), v.end(), lowest_value);
    assert(n_with_this_value > 0);
    const double assigned_rank =
        static_cast<double>(rank + (rank + n_with_this_value - 1))/2.0;
    assert(assigned_rank > 0.0);
    for(size_t i = 0; i != s; ++i)
    {
      if(v[i] == lowest_value)
      {
        w[i] = assigned_rank;
      }
    }
    rank += n_with_this_value;
  }
  return w;
}

const std::vector<double> GetSignedRanks(
  const std::vector<Sign>& signs,
  const std::vector<double>& ranks)
{
  assert(signs.size() == ranks.size());
  const std::size_t sz = signs.size();
  std::vector<double> v(sz);
  for (std::size_t i = 0; i!= sz; ++i)
  {
    v[i] = (signs[i] == minus ? -ranks[i] : ranks[i]);
  }
  return v;
}

//From http://www.richelbilderbeek.nl/CppSumPositives.htm
double SumPositives(const std::vector<double>& v)
{
  return ::accumulate_if(v.begin(),v.end(),
    0.0,std::bind2nd(std::greater<double>(),0.0));
}

//From http://www.richelbilderbeek.nl/CppSumNegatives.htm
double SumNegatives(const std::vector<double>& v)
{
  return ::accumulate_if(v.begin(),v.end(),
    0.0,std::bind2nd(std::less<double>(),0.0));
}

#include <algorithm>
#include <functional>
#include <vector>

//From http://www.richelbilderbeek.nl/CppCountNonZeroes.htm
int CountNonZeroes(const std::vector<double>& v)
{
 return std::count_if(
    v.begin(),
    v.end(),
    std::bind2nd(std::not_equal_to<double>(),0.0));
}

bool AreAboutEqual(const std::vector<double> v, const std::vector<double> w)
{
  if (v.size() != w.size()) return false;
  const std::size_t sz = v.size();
  for (std::size_t i=0; i!=sz; ++i)
  {
    if ( std::abs(v[i] - w[i]) > 0.01) return false;
  }
  return true;
}

//From http://www.richelbilderbeek.nl/CppWilcoxonsSignedRankTest.htm
int main()
{
  #ifndef NDEBUG
  //Test GetRanks
  {
    {
      const std::vector<double> values   = { 10.0, 20.0, 30.0 };
      const std::vector<double> expected = {  1.0,  2.0,  3.0 };
      const std::vector<double> results = GetRanks(values);
      assert(AreAboutEqual(expected,results));
    }
    {
      const std::vector<double> values   = { 30.0, 10.0, 20.0 };
      const std::vector<double> expected = {  3.0,  1.0,  2.0 };
      const std::vector<double> results = GetRanks(values);
      assert(AreAboutEqual(expected,results));
    }
    {
      //From Heath, page 263
      const std::vector<double> values   = { 0.6, 1.4, 4.0, 13.0, 14.5, 9.4, 11.4, 12.6, 4.0 };
      const std::vector<double> expected = { 1.0, 2.0, 3.5,  8.0,  9.0, 5.0,  6.0,  7.0, 3.5 };
      const std::vector<double> results = GetRanks(values);
      assert(AreAboutEqual(expected,results) && "Heath, page 263, no zero value");
    }
    {
      //From Heath, page 263, now with zero added
      const std::vector<double> values   = { 0.6, 1.4, 0.0,  4.0, 13.0, 14.5, 9.4, 11.4, 12.6, 4.0 };
      const std::vector<double> expected = { 1.0, 2.0, 0.0,  3.5,  8.0,  9.0, 5.0,  6.0,  7.0, 3.5 };
      const std::vector<double> results = GetRanks(values);
      assert(AreAboutEqual(expected,results) && "Heath, page 263, with zero value");
    }
    {
      //Thanks to Senbong G for adding this test
      const std::vector<double> values   = { 1.0, 1.0, 1.0, 2.0, 2.0, 3.0, 3.0, 3.0};
      const std::vector<double> expected = { 2.0, 2.0, 2.0, 4.5, 4.5, 7.0, 7.0, 7.0};
      const std::vector<double> results = GetRanks(values);
      assert(AreAboutEqual(expected,results) && "Senbong G test");
    }
    {
      //Thanks to Senbong G for adding this test
      const std::vector<double> values   = { 0.0, 0.0, 0.0 };
      const std::vector<double> expected = { 0.0, 0.0, 0.0 };
      const std::vector<double> results = GetRanks(values);
      assert(AreAboutEqual(expected,results) && "Senbong G zero-only test");
    }
    {
      const std::vector<double> v1 = GetValuesNonDrinkers();
      const std::vector<double> v2 = GetValuesDrinkers();
      assert(v1.size() == v2.size());
      const std::vector<double> differences = GetDifference(v1,v2);
      assert(v1.size() == differences.size());
      const std::vector<double> values
        = GetAbs<double>(differences);
      assert(v1.size() == values.size());
      const std::vector<double> results = GetRanks(values);
      const std::vector<double> expected = { 1.0, 2.0, 0.0, 3.5, 8.0, 9.0, 5.0, 6.0,  7.0, 3.5 };
      //std::copy(values.begin(), values.end(), std::ostream_iterator<double>(std::cout,","));
      //std::cout << std::endl;
      //std::copy(expected.begin(), expected.end(), std::ostream_iterator<double>(std::cout,","));
      //std::cout << std::endl;
      //std::copy(results.begin(), results.end(), std::ostream_iterator<double>(std::cout,","));
      //std::cout << std::endl;
      assert(AreAboutEqual(expected,results) && "Heath 263, from data used");
    }
  }

  #endif

  const std::vector<double> v1
    = GetValuesNonDrinkers();
  const std::vector<double> v2
    = GetValuesDrinkers();
  assert(v1.size() == v2.size());
  const std::vector<Sign> signs = GetSigns(v1,v2);
  assert(v1.size() == signs.size());
  const std::vector<double> differences
    = GetDifference(v1,v2);
  assert(v1.size() == differences.size());
  const std::vector<double> absDifferences
    = GetAbs<double>(differences);
  assert(v1.size() == absDifferences.size());
  const std::vector<double> ranks
    = GetRanks(absDifferences);
  assert(v1.size() == ranks.size());
  const std::vector<double> signedRanks
    = GetSignedRanks(signs,ranks);
  assert(v1.size() == signedRanks.size());

  const std::size_t sz = v1.size();
  for (std::size_t i = 0; i!=sz; ++i)
  {
    std::cout
      << v1[i] << '\t'
      << v2[i] << '\t'
      << signs[i] << '\t'
      << absDifferences[i] << '\t'
      << ranks[i] << '\t'
      << signedRanks[i] << '\t'
      << std::endl;
  }

  const double sum_positives = SumPositives(signedRanks);
  const double sum_negatives = SumNegatives(signedRanks);
  const int n_non_zero_pairs = CountNonZeroes(differences);
  //Critical value from:
  // * David Heath. An introduction to experimental design
  // and statistics for biology. 1995. ISBN: 1-85728-132-2 PB.
  // Page 350, Table A15: Wilcoxon's signed rank test:
  // critical values of T.
  // Two-tailed, n_non_zero_pairs = 9, significance level 5%
  const int critical_value = 40;
  std::cout
    << "\nSUM positives: " << sum_positives
    << "\nSUM negatives: " << sum_negatives
    << "\nn_non_zero_pairs: " << n_non_zero_pairs
    << "\ncritical_value: " << critical_value;
  if (sum_positives >= critical_value)
  {
    std::cout
      << "\nReject null hypothesis that pairs do "
         "not differ, due to positives";
  }
  if (std::abs(sum_negatives) >= critical_value)
  {
    std::cout
      << "\nReject null hypothesis that pairs do "
         "not differ, due to negatives";
  }
  if (!
    (sum_positives >= critical_value)
    && (sum_positives >= critical_value))
  {
    std::cout
      << "\nPairs do not differ significantly";
  }
}
