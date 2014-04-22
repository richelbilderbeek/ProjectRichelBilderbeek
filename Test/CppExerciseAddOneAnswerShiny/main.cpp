#include <cassert>
#include <cmath>
#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <functional>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/foreach.hpp>
#include <boost/timer.hpp>
#include <boost/lambda/lambda.hpp>
#include "Shiny.h"
#pragma GCC diagnostic pop

void AddForAssignment1stConstSize(std::vector<int>& v)
{
  PROFILE_FUNC();
  const std::size_t size = v.size();
  for (std::size_t i=0; i!=size; ++i) v[i]=1+v[i];
}

void AddForAssignment2ndConstSize(std::vector<int>& v)
{
  PROFILE_FUNC();
  const std::size_t size = v.size();
  for (std::size_t i=0; i!=size; ++i) v[i]=v[i]+1;
}

void AddForIncreaseConstSize(std::vector<int>& v)
{
  PROFILE_FUNC();
  const std::size_t size = v.size();
  for (std::size_t i=0; i!=size; ++i) v[i]+=1;
}

void AddForPostIncrementConstSize(std::vector<int>& v)
{
  PROFILE_FUNC();
  const std::size_t size = v.size();
  for (std::size_t i=0; i!=size; ++i) v[i]++;
}

void AddForPreIncrementConstSize(std::vector<int>& v)
{
  PROFILE_FUNC();
  const std::size_t size = v.size();
  for (std::size_t i=0; i!=size; ++i) ++v[i];
}

void AddForAssignment1stNonConstSize(std::vector<int>& v)
{
  PROFILE_FUNC();
  for (std::size_t i=0; i!=v.size(); ++i) v[i]=1+v[i];
}

void AddForAssignment2ndNonConstSize(std::vector<int>& v)
{
  PROFILE_FUNC();
  for (std::size_t i=0; i!=v.size(); ++i) v[i]=v[i]+1;
}

void AddForIncreaseNonConstSize(std::vector<int>& v)
{
  PROFILE_FUNC();
  for (std::size_t i=0; i!=v.size(); ++i) v[i]+=1;
}

void AddForPostIncrementNonConstSize(std::vector<int>& v)
{
  PROFILE_FUNC();
  for (std::size_t i=0; i!=v.size(); ++i) v[i]++;
}

void AddForPreIncrementNonConstSize(std::vector<int>& v)
{
  PROFILE_FUNC();
  for (std::size_t i=0; i!=v.size(); ++i) ++v[i];
}

void AddIteratorAssignment1stConstEnd(std::vector<int>& v)
{
  PROFILE_FUNC();
  const std::vector<int>::iterator j = v.end();
  for (std::vector<int>::iterator i = v.begin(); i!=j; ++i) (*i) = 1 + (*i);
}

void AddIteratorAssignment2ndConstEnd(std::vector<int>& v)
{
  PROFILE_FUNC();
  const std::vector<int>::iterator j = v.end();
  for (std::vector<int>::iterator i = v.begin(); i!=j; ++i) (*i) = (*i) + 1;
}

void AddIteratorIncreaseConstEnd(std::vector<int>& v)
{
  PROFILE_FUNC();
  const std::vector<int>::iterator j = v.end();
  for (std::vector<int>::iterator i = v.begin(); i!=j; ++i) (*i)+=1;
}

void AddIteratorPostIncrementConstEnd(std::vector<int>& v)
{
  PROFILE_FUNC();
  const std::vector<int>::iterator j = v.end();
  for (std::vector<int>::iterator i = v.begin(); i!=j; ++i) (*i)++;
}

void AddIteratorPreIncrementConstEnd(std::vector<int>& v)
{
  PROFILE_FUNC();
  const std::vector<int>::iterator j = v.end();
  for (std::vector<int>::iterator i = v.begin(); i!=j; ++i) ++(*i);
}

void AddIteratorAssignment1stNonConstEnd(std::vector<int>& v)
{
  PROFILE_FUNC();
  for (std::vector<int>::iterator i = v.begin(); i!=v.end(); ++i) (*i) = 1 + (*i);
}

void AddIteratorAssignment2ndNonConstEnd(std::vector<int>& v)
{
  PROFILE_FUNC();
  for (std::vector<int>::iterator i = v.begin(); i!=v.end(); ++i) (*i) = (*i) + 1;
}

void AddIteratorIncreaseNonConstEnd(std::vector<int>& v)
{
  PROFILE_FUNC();
  for (std::vector<int>::iterator i = v.begin(); i!=v.end(); ++i) (*i)+=1;
}

void AddIteratorPostIncrementNonConstEnd(std::vector<int>& v)
{
  PROFILE_FUNC();
  for (std::vector<int>::iterator i = v.begin(); i!=v.end(); ++i) (*i)++;
}

void AddIteratorPreIncrementNonConstEnd(std::vector<int>& v)
{
  PROFILE_FUNC();
  for (std::vector<int>::iterator i = v.begin(); i!=v.end(); ++i) ++(*i);
}

//non-inline functions
void AddOneAssignment1st(int& x) { x=1+x; }
void AddOneAssignment2nd(int& x) { x=x+1; }
void AddOneIncrease(int& x) { x+=1; }
void AddOnePostIncrement(int& x) { x++; }
void AddOnePreIncrement(int& x) { ++x; }

void AddAlgorithmNonInlineFunctionAssignment1st(std::vector<int>& v)
{
  PROFILE_FUNC();
  std::for_each(v.begin(),v.end(),AddOneAssignment1st);
}

void AddAlgorithmNonInlineFunctionAssignment2nd(std::vector<int>& v)
{
  PROFILE_FUNC();
  std::for_each(v.begin(),v.end(),AddOneAssignment2nd);
}

void AddAlgorithmNonInlineFunctionIncrease(std::vector<int>& v)
{
  PROFILE_FUNC();
  std::for_each(v.begin(),v.end(),AddOneIncrease);
}

void AddAlgorithmNonInlineFunctionPostIncrement(std::vector<int>& v)
{
  PROFILE_FUNC();
  std::for_each(v.begin(),v.end(),AddOnePostIncrement);
}

void AddAlgorithmNonInlineFunctionPreIncrement(std::vector<int>& v)
{
  PROFILE_FUNC();
  std::for_each(v.begin(),v.end(),AddOnePreIncrement);
}

//inline functions
inline void AddOneAssignmentInline1st(int& x) { x=1+x; }
inline void AddOneAssignmentInline2nd(int& x) { x=x+1; }
inline void AddOneIncreaseInline(int& x) { x+=1; }
inline void AddOnePostIncrementInline(int& x) { x++; }
inline void AddOnePreIncrementInline(int& x) { ++x; }

void AddAlgorithmInlineFunctionAssignment1st(std::vector<int>& v)
{
  PROFILE_FUNC();
  std::for_each(v.begin(),v.end(),AddOneAssignmentInline1st);
}

void AddAlgorithmInlineFunctionAssignment2nd(std::vector<int>& v)
{
  PROFILE_FUNC();
  std::for_each(v.begin(),v.end(),AddOneAssignmentInline2nd);
}

void AddAlgorithmInlineFunctionIncrease(std::vector<int>& v)
{
  PROFILE_FUNC();
  std::for_each(v.begin(),v.end(),AddOneIncreaseInline);
}

void AddAlgorithmInlineFunctionPostIncrement(std::vector<int>& v)
{
  PROFILE_FUNC();
  std::for_each(v.begin(),v.end(),AddOnePostIncrementInline);
}

void AddAlgorithmInlineFunctionPreIncrement(std::vector<int>& v)
{
  PROFILE_FUNC();
  std::for_each(v.begin(),v.end(),AddOnePreIncrementInline);
}

//Non-inline-operator() structs
struct AddOnerNonInlineAssignment1st { void operator()(int& x) { x=1+x; } };
struct AddOnerNonInlineAssignment2nd { void operator()(int& x) { x=x+1; } };
struct AddOnerNonInlineIncrease      { void operator()(int& x) { x+=1;  } };
struct AddOnerNonInlinePostIncrement { void operator()(int& x) { x++;   } };
struct AddOnerNonInlinePreIncrement  { void operator()(int& x) { ++x;   } };

void AddAlgorithmFunctorNonInlineAssignment1st(std::vector<int>& v)
{
  PROFILE_FUNC();
  std::for_each(v.begin(),v.end(), AddOnerNonInlineAssignment1st() );
}

void AddAlgorithmFunctorNonInlineAssignment2nd(std::vector<int>& v)
{
  PROFILE_FUNC();
  std::for_each(v.begin(),v.end(), AddOnerNonInlineAssignment2nd() );
}

void AddAlgorithmFunctorNonInlineIncrease(std::vector<int>& v)
{
  PROFILE_FUNC();
  std::for_each(v.begin(),v.end(), AddOnerNonInlineIncrease() );
}

void AddAlgorithmFunctorNonInlinePostIncrement(std::vector<int>& v)
{
  PROFILE_FUNC();
  std::for_each(v.begin(),v.end(), AddOnerNonInlinePostIncrement() );
}

void AddAlgorithmFunctorNonInlinePreIncrement(std::vector<int>& v)
{
  PROFILE_FUNC();
  std::for_each(v.begin(),v.end(), AddOnerNonInlinePreIncrement() );
}

//Inline-operator() structs
struct AddOnerInlineAssignment1st { inline void operator()(int& x) { x=1+x; } };
struct AddOnerInlineAssignment2nd { inline void operator()(int& x) { x=x+1; } };
struct AddOnerInlineIncrease      { inline void operator()(int& x) { x+=1; } };
struct AddOnerInlinePostIncrement { inline void operator()(int& x) { x++; } };
struct AddOnerInlinePreIncrement  { inline void operator()(int& x) { ++x; } };

void AddAlgorithmFunctorInlineAssignment1st(std::vector<int>& v)
{
  PROFILE_FUNC();
  std::for_each(v.begin(),v.end(), AddOnerInlineAssignment1st() );
}

void AddAlgorithmFunctorInlineAssignment2nd(std::vector<int>& v)
{
  PROFILE_FUNC();
  std::for_each(v.begin(),v.end(), AddOnerInlineAssignment2nd() );
}

void AddAlgorithmFunctorInlineIncrease(std::vector<int>& v)
{
  PROFILE_FUNC();
  std::for_each(v.begin(),v.end(), AddOnerInlineIncrease() );
}

void AddAlgorithmFunctorInlinePostIncrement(std::vector<int>& v)
{
  PROFILE_FUNC();
  std::for_each(v.begin(),v.end(), AddOnerInlinePostIncrement() );
}

void AddAlgorithmFunctorInlinePreIncrement(std::vector<int>& v)
{
  PROFILE_FUNC();
  std::for_each(v.begin(),v.end(), AddOnerInlinePreIncrement() );
}

void AddAlgorithmBind1st(std::vector<int>& v)
{
  PROFILE_FUNC();
  std::transform(v.begin(),v.end(),v.begin(),
    std::bind1st(std::plus<int>(),1));
}

void AddAlgorithmBind2nd(std::vector<int>& v)
{
  PROFILE_FUNC();
  std::transform(v.begin(),v.end(),v.begin(),
    std::bind2nd(std::plus<int>(),1));
}

void AddBoostForeachPreIncrement(std::vector<int>& v)
{
  PROFILE_FUNC();
  BOOST_FOREACH(int &i, v) { ++i; }
}

void AddBoostForeachPostIncrement(std::vector<int>& v)
{
  PROFILE_FUNC();
  BOOST_FOREACH(int &i, v) { i++; }
}

void AddBoostForeachIncrease(std::vector<int>& v)
{
  PROFILE_FUNC();
  BOOST_FOREACH(int &i, v) { i+=1; }
}

void AddBoostForeachAssignment1st(std::vector<int>& v)
{
  PROFILE_FUNC();
  BOOST_FOREACH(int &i, v) { i=1+i; }
}

void AddBoostForeachAssignment2nd(std::vector<int>& v)
{
  PROFILE_FUNC();
  BOOST_FOREACH(int &i, v) { i=i+1; }
}

void AddBoostLambdaPreIncrement(std::vector<int>& v)
{
  PROFILE_FUNC();
  std::for_each(v.begin(),v.end(), ++boost::lambda::_1);
}

void AddBoostLambdaPostIncrement(std::vector<int>& v)
{
  PROFILE_FUNC();
  std::for_each(v.begin(),v.end(), boost::lambda::_1++);
}

void AddBoostLambdaIncrease(std::vector<int>& v)
{
  PROFILE_FUNC();
  std::for_each(v.begin(),v.end(), boost::lambda::_1+=1);
}

void AddBoostLambdaAssignment1st(std::vector<int>& v)
{
  PROFILE_FUNC();
  std::for_each(v.begin(),v.end(), boost::lambda::_1 = boost::lambda::_1 + 1);
}

void AddBoostLambdaAssignment2nd(std::vector<int>& v)
{
  PROFILE_FUNC();
  std::for_each(v.begin(),v.end(), boost::lambda::_1 = 1 + boost::lambda::_1);
}

void AddCpp0xForPreIncrement(std::vector<int>& v)
{
  PROFILE_FUNC();
  for(int &i: v) { ++i; }
}

void AddCpp0xForPostIncrement(std::vector<int>& v)
{
  PROFILE_FUNC();
  for(int &i: v) { i++; }
}

void AddCpp0xForIncrease(std::vector<int>& v)
{
  PROFILE_FUNC();
  for(int &i: v) { i+=1; }
}

void AddCpp0xForAssignment1st(std::vector<int>& v)
{
  PROFILE_FUNC();
  for(int &i: v) { i=1+i; }
}

void AddCpp0xForAssignment2nd(std::vector<int>& v)
{
  PROFILE_FUNC();
  for(int &i: v) { i=i+1; }
}

void AddCpp0xLambdaPreIncrement(std::vector<int>& v)
{
  PROFILE_FUNC();
  std::for_each(v.begin(),v.end(), [](int&i) { ++i; } );
}

void AddCpp0xLambdaPostIncrement(std::vector<int>& v)
{
  PROFILE_FUNC();
  std::for_each(v.begin(),v.end(), [](int&i) { i++; } );
}

void AddCpp0xLambdaIncrease(std::vector<int>& v)
{
  PROFILE_FUNC();
  std::for_each(v.begin(),v.end(), [](int&i) { i+=1; } );
}

void AddCpp0xLambdaAssignment1st(std::vector<int>& v)
{
  PROFILE_FUNC();
  std::for_each(v.begin(),v.end(), [](int&i) { i = i + 1; } );
}

void AddCpp0xLambdaAssignment2nd(std::vector<int>& v)
{
  PROFILE_FUNC();
  std::for_each(v.begin(),v.end(), [](int&i) { i = 1 + i; } );
}

//From http://www.richelbilderbeek.nl/CppExerciseAddOneAnswer.htm
struct Function
{
  typedef void (*FunctionPointer)(std::vector<int>&);

  Function(FunctionPointer function, const std::string& name)
    : m_function(function),
      m_name(name),
      m_time(0.0)
  {

  }
  void DoWork(std::vector<int>& v)
  {
    boost::timer t;
    m_function(v);
    m_time += t.elapsed();
  }
  const std::string& GetName() const { return m_name; }
  double GetTime() const { return m_time; }
  private:
  FunctionPointer m_function;
  std::string m_name;
  double m_time;
};

//From http://www.richelbilderbeek.nl/CppExerciseAddOneAnswer.htm
std::vector<Function> GetFunctions()
{
  std::vector<Function> v;
  //For loop, const size
  v.push_back(Function(AddForAssignment1stConstSize,"For-loop, assignment 1st, const size"));
  v.push_back(Function(AddForAssignment2ndConstSize,"For-loop, assignment 2nd, const size"));
  v.push_back(Function(AddForIncreaseConstSize,"For-loop, increase, const size"));
  v.push_back(Function(AddForPostIncrementConstSize,"For-loop, post-increment, const size"));
  v.push_back(Function(AddForPreIncrementConstSize,"For-loop, pre-increment, const size"));
  //For loop, non-const size
  v.push_back(Function(AddForAssignment1stNonConstSize,"For-loop, assignment 1st, non-const size"));
  v.push_back(Function(AddForAssignment2ndNonConstSize,"For-loop, assignment 2nd, non-const size"));
  v.push_back(Function(AddForIncreaseNonConstSize,"For-loop, increase, non-const size"));
  v.push_back(Function(AddForPostIncrementNonConstSize,"For-loop, post-increment, non-const size"));
  v.push_back(Function(AddForPreIncrementNonConstSize,"For-loop, pre-increment, non-const size"));
  //Iterator, const end
  v.push_back(Function(AddIteratorAssignment1stConstEnd,"Iterator, assignment 1st, const end"));
  v.push_back(Function(AddIteratorAssignment2ndConstEnd,"Iterator, assignment 2nd, const end"));
  v.push_back(Function(AddIteratorIncreaseConstEnd,"Iterator, increase, const end"));
  v.push_back(Function(AddIteratorPostIncrementConstEnd,"Iterator, post-increment, const end"));
  v.push_back(Function(AddIteratorPreIncrementConstEnd,"Iterator, pre-increment, const end"));
  //Iterator, non-const end
  v.push_back(Function(AddIteratorAssignment1stNonConstEnd,"Iterator, assignment 1st, non-const end"));
  v.push_back(Function(AddIteratorAssignment2ndNonConstEnd,"Iterator, assignment 2nd, non-const end"));
  v.push_back(Function(AddIteratorIncreaseNonConstEnd,"Iterator, increase, non-const end"));
  v.push_back(Function(AddIteratorPostIncrementNonConstEnd,"Iterator, post-increment, non-const end"));
  v.push_back(Function(AddIteratorPreIncrementNonConstEnd,"Iterator, pre-increment, non-const end"));
  //Algorithm to non-inline function
  v.push_back(Function(AddAlgorithmNonInlineFunctionAssignment1st,
    "Algorithm, non-inline function, assignment 1st"));
  v.push_back(Function(AddAlgorithmNonInlineFunctionAssignment2nd,
    "Algorithm, non-inline function, assignment 2nd"));
  v.push_back(Function(AddAlgorithmNonInlineFunctionIncrease,
    "Algorithm, non-inline function, increase"));
  v.push_back(Function(AddAlgorithmNonInlineFunctionPostIncrement,
    "Algorithm, non-inline function, post-increment"));
  v.push_back(Function(AddAlgorithmNonInlineFunctionPreIncrement,
    "Algorithm, non-inline function, pre-increment"));
  //Algorithm to inline function
  v.push_back(Function(AddAlgorithmInlineFunctionAssignment1st,
    "Algorithm, inline function, assignment 1st"));
  v.push_back(Function(AddAlgorithmInlineFunctionAssignment2nd,
    "Algorithm, inline function, assignment 2nd"));
  v.push_back(Function(AddAlgorithmInlineFunctionIncrease,
    "Algorithm, inline function, increase"));
  v.push_back(Function(AddAlgorithmInlineFunctionPostIncrement,
    "Algorithm, inline function, post-increment"));
  v.push_back(Function(AddAlgorithmInlineFunctionPreIncrement,
    "Algorithm, inline function, pre-increment"));
  //Algorithm using non-inline-operator() functor
  v.push_back(Function(AddAlgorithmFunctorNonInlineAssignment1st,
    "Algorithm, functor, non-inline, assignment 1st"));
  v.push_back(Function(AddAlgorithmFunctorNonInlineAssignment2nd,
    "Algorithm, functor, non-inline, assignment 2nd"));
  v.push_back(Function(AddAlgorithmFunctorNonInlineIncrease,
    "Algorithm, functor, non-inline, increase"));
  v.push_back(Function(AddAlgorithmFunctorNonInlinePostIncrement,
    "Algorithm, functor, non-inline, post-increment"));
  v.push_back(Function(AddAlgorithmFunctorNonInlinePreIncrement,
    "Algorithm, functor, non-inline, pre-increment"));
  //Algorithm using inline-operator() functor
  v.push_back(Function(AddAlgorithmFunctorInlineAssignment1st,
    "Algorithm, functor, inline, assignment 1st"));
  v.push_back(Function(AddAlgorithmFunctorInlineAssignment2nd,
    "Algorithm, functor, inline, assignment 2nd"));
  v.push_back(Function(AddAlgorithmFunctorInlineIncrease,
    "Algorithm, functor, inline, increase"));
  v.push_back(Function(AddAlgorithmFunctorInlinePostIncrement,
    "Algorithm, functor, inline, post-increment"));
  v.push_back(Function(AddAlgorithmFunctorInlinePreIncrement,
    "Algorithm, functor, inline, pre-increment"));
  //Binders
  v.push_back(Function(AddAlgorithmBind1st,
    "Algorithm, std::plus, std::bind1st"));
  v.push_back(Function(AddAlgorithmBind2nd,
    "Algorithm, std::plus, std::bind2nd"));
  //BOOST_FOREACH
  v.push_back(Function(AddBoostForeachPreIncrement,
    "BOOST_FOREACH, pre-increment"));
  v.push_back(Function(AddBoostForeachPostIncrement,
    "BOOST_FOREACH, post-increment"));
  v.push_back(Function(AddBoostForeachIncrease,
    "BOOST_FOREACH, increase"));
  v.push_back(Function(AddBoostForeachAssignment1st,
    "BOOST_FOREACH, assignment 1st"));
  v.push_back(Function(AddBoostForeachAssignment2nd,
    "BOOST_FOREACH, assignment 2nd"));
  //Boost Lambda
  v.push_back(Function(AddBoostLambdaPreIncrement,
    "Boost.Lambda, pre-increment"));
  v.push_back(Function(AddBoostLambdaPostIncrement,
    "Boost.Lambda, post-increment"));
  v.push_back(Function(AddBoostLambdaIncrease,
    "Boost.Lambda, increase"));
  v.push_back(Function(AddBoostLambdaAssignment1st,
    "Boost.Lambda, assignment 1st"));
  v.push_back(Function(AddBoostLambdaAssignment2nd,
    "Boost.Lambda, assignment 2nd"));
  //C++0x ranged for loop
  v.push_back(Function(AddCpp0xForPreIncrement,
    "C++0x ranged for loop, pre-increment"));
  v.push_back(Function(AddCpp0xForPostIncrement,
    "C++0x ranged for loop, post-increment"));
  v.push_back(Function(AddCpp0xForIncrease,
    "C++0x ranged for loop, increase"));
  v.push_back(Function(AddCpp0xForAssignment1st,
    "C++0x ranged for loop, assignment 1st"));
  v.push_back(Function(AddCpp0xForAssignment2nd,
    "C++0x ranged for loop, assignment 2nd"));
  //C++0x Lambda
  v.push_back(Function(AddCpp0xLambdaPreIncrement,
    "C++0x lambda expression, pre-increment"));
  v.push_back(Function(AddCpp0xLambdaPostIncrement,
    "C++0x lambda expression, post-increment"));
  v.push_back(Function(AddCpp0xLambdaIncrease,
    "C++0x lambda expression, increase"));
  v.push_back(Function(AddCpp0xLambdaAssignment1st,
    "C++0x lambda expression, assignment 1st"));
  v.push_back(Function(AddCpp0xLambdaAssignment2nd,
    "C++0x lambda expression, assignment 2nd"));
  return v;
}

void TestFunctions(const std::vector<Function>& functions_original)
{
  std::vector<Function> functions(functions_original);
  std::vector<int> v;
  int value = 0;
  v.push_back(value);

  std::for_each(functions.begin(),functions.end(),
    [&v,&value](Function& function)
    {
      function.DoWork(v);
      assert(v[0] == value + 1);
      ++value;
    }
  );
}

//From http://www.richelbilderbeek.nl/CppExerciseAddOneAnswer.htm
int main()
{
  boost::timer t;

  const int size = 10000000;
  const int nTimes = 10;
  std::vector<Function> functions = GetFunctions();
  TestFunctions(functions);

  std::vector<int> v(size,0);

  for (int i=0; i!=nTimes; ++i)
  {
    PROFILER_UPDATE();
    std::cout << i << " / " << nTimes << std::endl;
    std::random_shuffle(functions.begin(), functions.end());
    std::for_each(functions.begin(),functions.end(),
      [&v](Function& f)
      {
        f.DoWork(v);
        assert(f.GetTime() > 0.0
          && "There must be some time passing for a test to work"
          && "Increase 'size'");
      }
    );
  }

  std::sort(functions.begin(),functions.end(),
    [](const Function& lhs, const Function& rhs)
    {
      return lhs.GetTime() < rhs.GetTime();
    }
  );

  std::cout
    << "Done!\n"
    << "Size std::vector: " << size << '\n'
    << "Repeats: " << nTimes << '\n'
    << "Timer minimal interval: " << t.elapsed_min() << '\n'
    << "Results (best result first):\n";

  std::for_each(functions.begin(),functions.end(),
    [](const Function& f)
    {
      std::cout << f.GetName() << ": " << f.GetTime() << '\n';
    }
  );

  PROFILER_OUTPUT("shiny_output.txt");

  std::cout << "Total running time: " << t.elapsed() << " seconds." << std::endl;
}

/* Screen output:

0 / 10
1 / 10
2 / 10
3 / 10
4 / 10
5 / 10
6 / 10
7 / 10
8 / 10
9 / 10
Done!
Size std::vector: 10000000
Repeats: 10
Timer minimal interval: 0.001
Results (best result first):
For-loop, increase, const size: 0.428
For-loop, post-increment, const size: 0.429
For-loop, pre-increment, const size: 0.429
For-loop, post-increment, non-const size: 0.645
For-loop, increase, non-const size: 0.646
For-loop, assignment 1st, const size: 0.699
For-loop, assignment 2nd, const size: 0.699
For-loop, pre-increment, non-const size: 0.729
For-loop, assignment 2nd, non-const size: 0.898
For-loop, assignment 1st, non-const size: 0.901
Iterator, post-increment, const end: 0.975
Iterator, pre-increment, const end: 0.976
Iterator, increase, const end: 1.008
C++0x ranged for loop, pre-increment: 1.043
C++0x ranged for loop, post-increment: 1.047
C++0x ranged for loop, assignment 1st: 1.05
C++0x ranged for loop, assignment 2nd: 1.051
C++0x ranged for loop, increase: 1.055
Iterator, assignment 2nd, const end: 1.149
Iterator, assignment 1st, const end: 1.154
Algorithm, non-inline function, increase: 1.182
Algorithm, non-inline function, assignment 1st: 1.184
Algorithm, inline function, assignment 2nd: 1.184
Algorithm, inline function, increase: 1.187
Algorithm, non-inline function, assignment 2nd: 1.187
Algorithm, inline function, post-increment: 1.188
Algorithm, non-inline function, pre-increment: 1.191
Algorithm, inline function, pre-increment: 1.191
Algorithm, non-inline function, post-increment: 1.192
Algorithm, inline function, assignment 1st: 1.193
Algorithm, functor, inline, assignment 2nd: 1.212
Algorithm, functor, non-inline, increase: 1.212
Algorithm, functor, inline, post-increment: 1.212
Algorithm, functor, inline, increase: 1.213
Algorithm, functor, non-inline, post-increment: 1.213
Algorithm, functor, inline, pre-increment: 1.214
Algorithm, functor, non-inline, pre-increment: 1.215
Algorithm, functor, non-inline, assignment 2nd: 1.215
Algorithm, functor, inline, assignment 1st: 1.216
C++0x lambda expression, post-increment: 1.216
C++0x lambda expression, assignment 1st: 1.216
C++0x lambda expression, increase: 1.217
Algorithm, functor, non-inline, assignment 1st: 1.217
C++0x lambda expression, pre-increment: 1.217
C++0x lambda expression, assignment 2nd: 1.227
Iterator, increase, non-const end: 1.604
Iterator, post-increment, non-const end: 1.607
Iterator, pre-increment, non-const end: 1.61
Iterator, assignment 2nd, non-const end: 1.769
Iterator, assignment 1st, non-const end: 1.772
Algorithm, std::plus, std::bind2nd: 1.991
Algorithm, std::plus, std::bind1st: 1.997
BOOST_FOREACH, post-increment: 2.815
BOOST_FOREACH, pre-increment: 2.823
BOOST_FOREACH, increase: 2.823
BOOST_FOREACH, assignment 1st: 2.875
BOOST_FOREACH, assignment 2nd: 2.903
Boost.Lambda, pre-increment: 3.78
Boost.Lambda, post-increment: 3.808
Boost.Lambda, increase: 5.45
Boost.Lambda, assignment 2nd: 8.69
Boost.Lambda, assignment 1st: 8.699
Total running time: 104.192 seconds.
Press <RETURN> to close this window...

*/

/* Content of shiny_output.txt:

flat profile                               hits       self time      total time
<root>                                      0.4     11 ms    0%      6 s   100%
AddForAssignment1stConstSize                1.0     43 ms    1%     43 ms    1%
AddForAssignment2ndConstSize                1.0     43 ms    1%     43 ms    1%
AddForIncreaseConstSize                     1.0     26 ms    0%     26 ms    0%
AddForPostIncrementConstSize                1.0     26 ms    0%     26 ms    0%
AddForPreIncrementConstSize                 1.0     26 ms    0%     26 ms    0%
AddForAssignment1stNonConstSize             1.0     55 ms    1%     55 ms    1%
AddForAssignment2ndNonConstSize             1.0     55 ms    1%     55 ms    1%
AddForIncreaseNonConstSize                  1.0     40 ms    1%     40 ms    1%
AddForPostIncrementNonConstSize             1.0     40 ms    1%     40 ms    1%
AddForPreIncrementNonConstSize              1.0     45 ms    1%     45 ms    1%
AddIteratorAssignment1stConstEnd            1.0     71 ms    1%     71 ms    1%
AddIteratorAssignment2ndConstEnd            1.0     71 ms    1%     71 ms    1%
AddIteratorIncreaseConstEnd                 1.0     62 ms    1%     62 ms    1%
AddIteratorPostIncrementConstEnd            1.0     60 ms    1%     60 ms    1%
AddIteratorPreIncrementConstEnd             1.0     60 ms    1%     60 ms    1%
AddIteratorAssignment1stNonConstEnd         1.0    108 ms    2%    108 ms    2%
AddIteratorAssignment2ndNonConstEnd         1.0    109 ms    2%    109 ms    2%
AddIteratorIncreaseNonConstEnd              1.0     98 ms    2%     98 ms    2%
AddIteratorPostIncrementNonConstEnd         1.0     98 ms    2%     98 ms    2%
AddIteratorPreIncrementNonConstEnd          1.0     99 ms    2%     99 ms    2%
AddAlgorithmNonInlineFunctionAssignment1    1.0     73 ms    1%     73 ms    1%
AddAlgorithmNonInlineFunctionAssignment2    1.0     73 ms    1%     73 ms    1%
AddAlgorithmNonInlineFunctionIncrease       1.0     72 ms    1%     72 ms    1%
AddAlgorithmNonInlineFunctionPostIncreme    1.0     73 ms    1%     73 ms    1%
AddAlgorithmNonInlineFunctionPreIncremen    1.0     73 ms    1%     73 ms    1%
AddAlgorithmInlineFunctionAssignment1st     1.0     73 ms    1%     73 ms    1%
AddAlgorithmInlineFunctionAssignment2nd     1.0     73 ms    1%     73 ms    1%
AddAlgorithmInlineFunctionIncrease          1.0     73 ms    1%     73 ms    1%
AddAlgorithmInlineFunctionPostIncrement     1.0     73 ms    1%     73 ms    1%
AddAlgorithmInlineFunctionPreIncrement      1.0     73 ms    1%     73 ms    1%
AddAlgorithmFunctorNonInlineAssignment1s    1.0     75 ms    1%     75 ms    1%
AddAlgorithmFunctorNonInlineAssignment2n    1.0     74 ms    1%     74 ms    1%
AddAlgorithmFunctorNonInlineIncrease        1.0     74 ms    1%     74 ms    1%
AddAlgorithmFunctorNonInlinePostIncremen    1.0     74 ms    1%     74 ms    1%
AddAlgorithmFunctorNonInlinePreIncrement    1.0     74 ms    1%     74 ms    1%
AddAlgorithmFunctorInlineAssignment1st      1.0     74 ms    1%     74 ms    1%
AddAlgorithmFunctorInlineAssignment2nd      1.0     74 ms    1%     74 ms    1%
AddAlgorithmFunctorInlineIncrease           1.0     74 ms    1%     74 ms    1%
AddAlgorithmFunctorInlinePostIncrement      1.0     74 ms    1%     74 ms    1%
AddAlgorithmFunctorInlinePreIncrement       1.0     74 ms    1%     74 ms    1%
AddAlgorithmBind1st                         1.0    122 ms    2%    122 ms    2%
AddAlgorithmBind2nd                         1.0    122 ms    2%    122 ms    2%
AddBoostForeachPreIncrement                 1.0    173 ms    3%    173 ms    3%
AddBoostForeachPostIncrement                1.0    172 ms    3%    172 ms    3%
AddBoostForeachIncrease                     1.0    173 ms    3%    173 ms    3%
AddBoostForeachAssignment1st                1.0    176 ms    3%    176 ms    3%
AddBoostForeachAssignment2nd                1.0    178 ms    3%    178 ms    3%
AddBoostLambdaPreIncrement                  1.0    231 ms    4%    231 ms    4%
AddBoostLambdaPostIncrement                 1.0    233 ms    4%    233 ms    4%
AddBoostLambdaIncrease                      1.0    334 ms    5%    334 ms    5%
AddBoostLambdaAssignment1st                 1.0    533 ms    8%    533 ms    8%
AddBoostLambdaAssignment2nd                 1.0    532 ms    8%    532 ms    8%
AddCpp0xForPreIncrement                     1.0     64 ms    1%     64 ms    1%
AddCpp0xForPostIncrement                    1.0     64 ms    1%     64 ms    1%
AddCpp0xForIncrease                         1.0     64 ms    1%     64 ms    1%
AddCpp0xForAssignment1st                    1.0     64 ms    1%     64 ms    1%
AddCpp0xForAssignment2nd                    1.0     64 ms    1%     64 ms    1%
AddCpp0xLambdaPreIncrement                  1.0     75 ms    1%     75 ms    1%
AddCpp0xLambdaPostIncrement                 1.0     74 ms    1%     74 ms    1%
AddCpp0xLambdaIncrease                      1.0     75 ms    1%     75 ms    1%
AddCpp0xLambdaAssignment1st                 1.0     74 ms    1%     74 ms    1%
AddCpp0xLambdaAssignment2nd                 1.0     75 ms    1%     75 ms    1%

call tree                                  hits       self time      total time
<root>                                      0.4     11 ms    0%      6 s   100%
  AddForAssignment1stConstSize              1.0     43 ms    1%     43 ms    1%
  AddForAssignment2ndConstSize              1.0     43 ms    1%     43 ms    1%
  AddForIncreaseConstSize                   1.0     26 ms    0%     26 ms    0%
  AddForPostIncrementConstSize              1.0     26 ms    0%     26 ms    0%
  AddForPreIncrementConstSize               1.0     26 ms    0%     26 ms    0%
  AddForAssignment1stNonConstSize           1.0     55 ms    1%     55 ms    1%
  AddForAssignment2ndNonConstSize           1.0     55 ms    1%     55 ms    1%
  AddForIncreaseNonConstSize                1.0     40 ms    1%     40 ms    1%
  AddForPostIncrementNonConstSize           1.0     40 ms    1%     40 ms    1%
  AddForPreIncrementNonConstSize            1.0     45 ms    1%     45 ms    1%
  AddIteratorAssignment1stConstEnd          1.0     71 ms    1%     71 ms    1%
  AddIteratorAssignment2ndConstEnd          1.0     71 ms    1%     71 ms    1%
  AddIteratorIncreaseConstEnd               1.0     62 ms    1%     62 ms    1%
  AddIteratorPostIncrementConstEnd          1.0     60 ms    1%     60 ms    1%
  AddIteratorPreIncrementConstEnd           1.0     60 ms    1%     60 ms    1%
  AddIteratorAssignment1stNonConstEnd       1.0    108 ms    2%    108 ms    2%
  AddIteratorAssignment2ndNonConstEnd       1.0    109 ms    2%    109 ms    2%
  AddIteratorIncreaseNonConstEnd            1.0     98 ms    2%     98 ms    2%
  AddIteratorPostIncrementNonConstEnd       1.0     98 ms    2%     98 ms    2%
  AddIteratorPreIncrementNonConstEnd        1.0     99 ms    2%     99 ms    2%
  AddAlgorithmNonInlineFunctionAssignmen    1.0     73 ms    1%     73 ms    1%
  AddAlgorithmNonInlineFunctionAssignmen    1.0     73 ms    1%     73 ms    1%
  AddAlgorithmNonInlineFunctionIncrease     1.0     72 ms    1%     72 ms    1%
  AddAlgorithmNonInlineFunctionPostIncre    1.0     73 ms    1%     73 ms    1%
  AddAlgorithmNonInlineFunctionPreIncrem    1.0     73 ms    1%     73 ms    1%
  AddAlgorithmInlineFunctionAssignment1s    1.0     73 ms    1%     73 ms    1%
  AddAlgorithmInlineFunctionAssignment2n    1.0     73 ms    1%     73 ms    1%
  AddAlgorithmInlineFunctionIncrease        1.0     73 ms    1%     73 ms    1%
  AddAlgorithmInlineFunctionPostIncremen    1.0     73 ms    1%     73 ms    1%
  AddAlgorithmInlineFunctionPreIncrement    1.0     73 ms    1%     73 ms    1%
  AddAlgorithmFunctorNonInlineAssignment    1.0     75 ms    1%     75 ms    1%
  AddAlgorithmFunctorNonInlineAssignment    1.0     74 ms    1%     74 ms    1%
  AddAlgorithmFunctorNonInlineIncrease      1.0     74 ms    1%     74 ms    1%
  AddAlgorithmFunctorNonInlinePostIncrem    1.0     74 ms    1%     74 ms    1%
  AddAlgorithmFunctorNonInlinePreIncreme    1.0     74 ms    1%     74 ms    1%
  AddAlgorithmFunctorInlineAssignment1st    1.0     74 ms    1%     74 ms    1%
  AddAlgorithmFunctorInlineAssignment2nd    1.0     74 ms    1%     74 ms    1%
  AddAlgorithmFunctorInlineIncrease         1.0     74 ms    1%     74 ms    1%
  AddAlgorithmFunctorInlinePostIncrement    1.0     74 ms    1%     74 ms    1%
  AddAlgorithmFunctorInlinePreIncrement     1.0     74 ms    1%     74 ms    1%
  AddAlgorithmBind1st                       1.0    122 ms    2%    122 ms    2%
  AddAlgorithmBind2nd                       1.0    122 ms    2%    122 ms    2%
  AddBoostForeachPreIncrement               1.0    173 ms    3%    173 ms    3%
  AddBoostForeachPostIncrement              1.0    172 ms    3%    172 ms    3%
  AddBoostForeachIncrease                   1.0    173 ms    3%    173 ms    3%
  AddBoostForeachAssignment1st              1.0    176 ms    3%    176 ms    3%
  AddBoostForeachAssignment2nd              1.0    178 ms    3%    178 ms    3%
  AddBoostLambdaPreIncrement                1.0    231 ms    4%    231 ms    4%
  AddBoostLambdaPostIncrement               1.0    233 ms    4%    233 ms    4%
  AddBoostLambdaIncrease                    1.0    334 ms    5%    334 ms    5%
  AddBoostLambdaAssignment1st               1.0    533 ms    8%    533 ms    8%
  AddBoostLambdaAssignment2nd               1.0    532 ms    8%    532 ms    8%
  AddCpp0xForPreIncrement                   1.0     64 ms    1%     64 ms    1%
  AddCpp0xForPostIncrement                  1.0     64 ms    1%     64 ms    1%
  AddCpp0xForIncrease                       1.0     64 ms    1%     64 ms    1%
  AddCpp0xForAssignment1st                  1.0     64 ms    1%     64 ms    1%
  AddCpp0xForAssignment2nd                  1.0     64 ms    1%     64 ms    1%
  AddCpp0xLambdaPreIncrement                1.0     75 ms    1%     75 ms    1%
  AddCpp0xLambdaPostIncrement               1.0     74 ms    1%     74 ms    1%
  AddCpp0xLambdaIncrease                    1.0     75 ms    1%     75 ms    1%
  AddCpp0xLambdaAssignment1st               1.0     74 ms    1%     74 ms    1%
  AddCpp0xLambdaAssignment2nd               1.0     75 ms    1%     75 ms    1%

*/

