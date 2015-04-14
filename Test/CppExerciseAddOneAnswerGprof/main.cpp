//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppExerciseAddOneAnswer.htm
//---------------------------------------------------------------------------
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
#pragma GCC diagnostic pop

void AddForAssignment1stConstSize(std::vector<int>& v)
{
  const std::size_t size = v.size();
  for (std::size_t i=0; i!=size; ++i) v[i]=1+v[i];
}

void AddForAssignment2ndConstSize(std::vector<int>& v)
{
  const std::size_t size = v.size();
  for (std::size_t i=0; i!=size; ++i) v[i]=v[i]+1;
}

void AddForIncreaseConstSize(std::vector<int>& v)
{
  const std::size_t size = v.size();
  for (std::size_t i=0; i!=size; ++i) v[i]+=1;
}

void AddForPostIncrementConstSize(std::vector<int>& v)
{
  const std::size_t size = v.size();
  for (std::size_t i=0; i!=size; ++i) v[i]++;
}

void AddForPreIncrementConstSize(std::vector<int>& v)
{
  const std::size_t size = v.size();
  for (std::size_t i=0; i!=size; ++i) ++v[i];
}

void AddForAssignment1stNonConstSize(std::vector<int>& v)
{
  for (std::size_t i=0; i!=v.size(); ++i) v[i]=1+v[i];
}

void AddForAssignment2ndNonConstSize(std::vector<int>& v)
{
  for (std::size_t i=0; i!=v.size(); ++i) v[i]=v[i]+1;
}

void AddForIncreaseNonConstSize(std::vector<int>& v)
{
  for (std::size_t i=0; i!=v.size(); ++i) v[i]+=1;
}

void AddForPostIncrementNonConstSize(std::vector<int>& v)
{
  for (std::size_t i=0; i!=v.size(); ++i) v[i]++;
}

void AddForPreIncrementNonConstSize(std::vector<int>& v)
{
  for (std::size_t i=0; i!=v.size(); ++i) ++v[i];
}

void AddIteratorAssignment1stConstEnd(std::vector<int>& v)
{
  const std::vector<int>::iterator j = v.end();
  for (std::vector<int>::iterator i = v.begin(); i!=j; ++i) (*i) = 1 + (*i);
}

void AddIteratorAssignment2ndConstEnd(std::vector<int>& v)
{
  const std::vector<int>::iterator j = v.end();
  for (std::vector<int>::iterator i = v.begin(); i!=j; ++i) (*i) = (*i) + 1;
}

void AddIteratorIncreaseConstEnd(std::vector<int>& v)
{
  const std::vector<int>::iterator j = v.end();
  for (std::vector<int>::iterator i = v.begin(); i!=j; ++i) (*i)+=1;
}

void AddIteratorPostIncrementConstEnd(std::vector<int>& v)
{
  const std::vector<int>::iterator j = v.end();
  for (std::vector<int>::iterator i = v.begin(); i!=j; ++i) (*i)++;
}

void AddIteratorPreIncrementConstEnd(std::vector<int>& v)
{
  const std::vector<int>::iterator j = v.end();
  for (std::vector<int>::iterator i = v.begin(); i!=j; ++i) ++(*i);
}

void AddIteratorAssignment1stNonConstEnd(std::vector<int>& v)
{
  for (std::vector<int>::iterator i = v.begin(); i!=v.end(); ++i) (*i) = 1 + (*i);
}

void AddIteratorAssignment2ndNonConstEnd(std::vector<int>& v)
{
  for (std::vector<int>::iterator i = v.begin(); i!=v.end(); ++i) (*i) = (*i) + 1;
}

void AddIteratorIncreaseNonConstEnd(std::vector<int>& v)
{
  for (std::vector<int>::iterator i = v.begin(); i!=v.end(); ++i) (*i)+=1;
}

void AddIteratorPostIncrementNonConstEnd(std::vector<int>& v)
{
  for (std::vector<int>::iterator i = v.begin(); i!=v.end(); ++i) (*i)++;
}

void AddIteratorPreIncrementNonConstEnd(std::vector<int>& v)
{
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
  std::for_each(v.begin(),v.end(),AddOneAssignment1st);
}

void AddAlgorithmNonInlineFunctionAssignment2nd(std::vector<int>& v)
{
  std::for_each(v.begin(),v.end(),AddOneAssignment2nd);
}

void AddAlgorithmNonInlineFunctionIncrease(std::vector<int>& v)
{
  std::for_each(v.begin(),v.end(),AddOneIncrease);
}

void AddAlgorithmNonInlineFunctionPostIncrement(std::vector<int>& v)
{
  std::for_each(v.begin(),v.end(),AddOnePostIncrement);
}

void AddAlgorithmNonInlineFunctionPreIncrement(std::vector<int>& v)
{
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
  std::for_each(v.begin(),v.end(),AddOneAssignmentInline1st);
}

void AddAlgorithmInlineFunctionAssignment2nd(std::vector<int>& v)
{
  std::for_each(v.begin(),v.end(),AddOneAssignmentInline2nd);
}

void AddAlgorithmInlineFunctionIncrease(std::vector<int>& v)
{
  std::for_each(v.begin(),v.end(),AddOneIncreaseInline);
}

void AddAlgorithmInlineFunctionPostIncrement(std::vector<int>& v)
{
  std::for_each(v.begin(),v.end(),AddOnePostIncrementInline);
}

void AddAlgorithmInlineFunctionPreIncrement(std::vector<int>& v)
{
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
  std::for_each(v.begin(),v.end(), AddOnerNonInlineAssignment1st() );
}

void AddAlgorithmFunctorNonInlineAssignment2nd(std::vector<int>& v)
{
  std::for_each(v.begin(),v.end(), AddOnerNonInlineAssignment2nd() );
}

void AddAlgorithmFunctorNonInlineIncrease(std::vector<int>& v)
{
  std::for_each(v.begin(),v.end(), AddOnerNonInlineIncrease() );
}

void AddAlgorithmFunctorNonInlinePostIncrement(std::vector<int>& v)
{
  std::for_each(v.begin(),v.end(), AddOnerNonInlinePostIncrement() );
}

void AddAlgorithmFunctorNonInlinePreIncrement(std::vector<int>& v)
{
  std::for_each(v.begin(),v.end(), AddOnerNonInlinePreIncrement() );
}

//Inline-operator() structs
struct AddOnerInlineAssignment1st { inline void operator()(int& x) { x=1+x; } };
struct AddOnerInlineAssignment2nd { inline void operator()(int& x) { x=x+1; } };
struct AddOnerInlineIncrease      { inline void operator()(int& x) { x+=1;  } };
struct AddOnerInlinePostIncrement { inline void operator()(int& x) { x++;   } };
struct AddOnerInlinePreIncrement  { inline void operator()(int& x) { ++x;   } };

void AddAlgorithmFunctorInlineAssignment1st(std::vector<int>& v)
{
  std::for_each(v.begin(),v.end(), AddOnerInlineAssignment1st() );
}

void AddAlgorithmFunctorInlineAssignment2nd(std::vector<int>& v)
{
  std::for_each(v.begin(),v.end(), AddOnerInlineAssignment2nd() );
}

void AddAlgorithmFunctorInlineIncrease(std::vector<int>& v)
{
  std::for_each(v.begin(),v.end(), AddOnerInlineIncrease() );
}

void AddAlgorithmFunctorInlinePostIncrement(std::vector<int>& v)
{
  std::for_each(v.begin(),v.end(), AddOnerInlinePostIncrement() );
}

void AddAlgorithmFunctorInlinePreIncrement(std::vector<int>& v)
{
  std::for_each(v.begin(),v.end(), AddOnerInlinePreIncrement() );
}

void AddAlgorithmBind1st(std::vector<int>& v)
{
  std::transform(v.begin(),v.end(),v.begin(),
    std::bind1st(std::plus<int>(),1));
}

void AddAlgorithmBind2nd(std::vector<int>& v)
{
  std::transform(v.begin(),v.end(),v.begin(),
    std::bind2nd(std::plus<int>(),1));
}

void AddBoostForeachPreIncrement(std::vector<int>& v)
{
  BOOST_FOREACH(int &i, v) { ++i; }
}

void AddBoostForeachPostIncrement(std::vector<int>& v)
{
  BOOST_FOREACH(int &i, v) { i++; }
}

void AddBoostForeachIncrease(std::vector<int>& v)
{
  BOOST_FOREACH(int &i, v) { i+=1; }
}

void AddBoostForeachAssignment1st(std::vector<int>& v)
{
  BOOST_FOREACH(int &i, v) { i=1+i; }
}

void AddBoostForeachAssignment2nd(std::vector<int>& v)
{
  BOOST_FOREACH(int &i, v) { i=i+1; }
}

void AddBoostLambdaPreIncrement(std::vector<int>& v)
{
  std::for_each(v.begin(),v.end(), ++boost::lambda::_1);
}

void AddBoostLambdaPostIncrement(std::vector<int>& v)
{
  std::for_each(v.begin(),v.end(), boost::lambda::_1++);
}

void AddBoostLambdaIncrease(std::vector<int>& v)
{
  std::for_each(v.begin(),v.end(), boost::lambda::_1+=1);
}

void AddBoostLambdaAssignment1st(std::vector<int>& v)
{
  std::for_each(v.begin(),v.end(), boost::lambda::_1 = boost::lambda::_1 + 1);
}

void AddBoostLambdaAssignment2nd(std::vector<int>& v)
{
  std::for_each(v.begin(),v.end(), boost::lambda::_1 = 1 + boost::lambda::_1);
}

void AddCpp11ForPreIncrement(std::vector<int>& v)
{
  for(int &i: v) { ++i; }
}

void AddCpp11ForPostIncrement(std::vector<int>& v)
{
  for(int &i: v) { i++; }
}

void AddCpp11ForIncrease(std::vector<int>& v)
{
  for(int &i: v) { i+=1; }
}

void AddCpp11ForAssignment1st(std::vector<int>& v)
{
  for(int &i: v) { i=1+i; }
}

void AddCpp11ForAssignment2nd(std::vector<int>& v)
{
  for(int &i: v) { i=i+1; }
}

void AddCpp11LambdaPreIncrement(std::vector<int>& v)
{
  std::for_each(v.begin(),v.end(), [](int&i) { ++i; } );
}

void AddCpp11LambdaPostIncrement(std::vector<int>& v)
{
  std::for_each(v.begin(),v.end(), [](int&i) { i++; } );
}

void AddCpp11LambdaIncrease(std::vector<int>& v)
{
  std::for_each(v.begin(),v.end(), [](int&i) { i+=1; } );
}

void AddCpp11LambdaAssignment1st(std::vector<int>& v)
{
  std::for_each(v.begin(),v.end(), [](int&i) { i = i + 1; } );
}

void AddCpp11LambdaAssignment2nd(std::vector<int>& v)
{
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
  //C++11 ranged for loop
  v.push_back(Function(AddCpp11ForPreIncrement,
    "C++11 ranged for loop, pre-increment"));
  v.push_back(Function(AddCpp11ForPostIncrement,
    "C++11 ranged for loop, post-increment"));
  v.push_back(Function(AddCpp11ForIncrease,
    "C++11 ranged for loop, increase"));
  v.push_back(Function(AddCpp11ForAssignment1st,
    "C++11 ranged for loop, assignment 1st"));
  v.push_back(Function(AddCpp11ForAssignment2nd,
    "C++11 ranged for loop, assignment 2nd"));
  //C++11 Lambda
  v.push_back(Function(AddCpp11LambdaPreIncrement,
    "C++11 lambda expression, pre-increment"));
  v.push_back(Function(AddCpp11LambdaPostIncrement,
    "C++11 lambda expression, post-increment"));
  v.push_back(Function(AddCpp11LambdaIncrease,
    "C++11 lambda expression, increase"));
  v.push_back(Function(AddCpp11LambdaAssignment1st,
    "C++11 lambda expression, assignment 1st"));
  v.push_back(Function(AddCpp11LambdaAssignment2nd,
    "C++11 lambda expression, assignment 2nd"));
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
  #ifndef NDEBUG
  std::cout << "Set program to release mode, otherwise benchmark gives misleading results\n";\
  return 0;
  #else

  boost::timer t;

  const int size = 100000000;
  const int nTimes = 10;
  std::vector<Function> functions = GetFunctions();
  TestFunctions(functions);

  std::vector<int> v(size,0);

  for (int i=0; i!=nTimes; ++i)
  {
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


  std::cout << "Total running time: " << t.elapsed() << " seconds." << std::endl;
  #endif
}

/*
Size std::vector: 40000000
Repeats: 10
Timer minimal interval: 1e-06
Results (best result first):
C++11 lambda expression, pre-increment: 0.37
Iterator, increase, non-const end: 0.38
Algorithm, functor, inline, assignment 1st: 0.38
Algorithm, functor, non-inline, increase: 0.38
Algorithm, functor, non-inline, pre-increment: 0.38
BOOST_FOREACH, assignment 2nd: 0.38
Iterator, post-increment, const end: 0.38
Boost.Lambda, pre-increment: 0.38
Algorithm, non-inline function, assignment 2nd: 0.38
Algorithm, inline function, pre-increment: 0.38
Boost.Lambda, assignment 1st: 0.39
BOOST_FOREACH, increase: 0.39
Algorithm, inline function, assignment 2nd: 0.39
BOOST_FOREACH, pre-increment: 0.39
Algorithm, functor, non-inline, assignment 2nd: 0.39
Algorithm, inline function, post-increment: 0.39
C++11 ranged for loop, pre-increment: 0.39
Algorithm, functor, non-inline, assignment 1st: 0.39
C++11 ranged for loop, assignment 2nd: 0.39
Boost.Lambda, assignment 2nd: 0.39
Algorithm, functor, non-inline, post-increment: 0.39
Iterator, post-increment, non-const end: 0.39
Iterator, pre-increment, non-const end: 0.39
Algorithm, non-inline function, assignment 1st: 0.39
BOOST_FOREACH, assignment 1st: 0.39
Algorithm, std::plus, std::bind2nd: 0.39
Iterator, assignment 2nd, const end: 0.39
Algorithm, non-inline function, post-increment: 0.39
Iterator, pre-increment, const end: 0.39
Iterator, assignment 2nd, non-const end: 0.39
Algorithm, inline function, assignment 1st: 0.39
Algorithm, functor, inline, post-increment: 0.4
C++11 lambda expression, increase: 0.4
Boost.Lambda, post-increment: 0.4
Boost.Lambda, increase: 0.4
Iterator, increase, const end: 0.4
Algorithm, std::plus, std::bind1st: 0.4
Iterator, assignment 1st, non-const end: 0.4
C++11 ranged for loop, increase: 0.4
Algorithm, functor, inline, increase: 0.4
C++11 lambda expression, post-increment: 0.4
Algorithm, functor, inline, assignment 2nd: 0.4
C++11 ranged for loop, post-increment: 0.4
Algorithm, inline function, increase: 0.4
Algorithm, non-inline function, increase: 0.4
Algorithm, non-inline function, pre-increment: 0.4
C++11 ranged for loop, assignment 1st: 0.4
BOOST_FOREACH, post-increment: 0.4
Iterator, assignment 1st, const end: 0.4
C++11 lambda expression, assignment 1st: 0.41
Algorithm, functor, inline, pre-increment: 0.41
For-loop, increase, const size: 0.44
For-loop, increase, non-const size: 0.44
For-loop, assignment 1st, const size: 0.44
For-loop, assignment 2nd, non-const size: 0.45
For-loop, assignment 1st, non-const size: 0.46
For-loop, assignment 2nd, const size: 0.46
C++11 lambda expression, assignment 2nd: 0.46
For-loop, post-increment, const size: 0.47
For-loop, post-increment, non-const size: 0.47
For-loop, pre-increment, non-const size: 0.48
For-loop, pre-increment, const size: 0.49
Total running time: 25.16 seconds.
*/

/* 2015-04-10: Differences are very small

Size std::vector: 10000000
Repeats: 100
Timer minimal interval: 1e-06
Results (best result first):
C++11 ranged for loop, post-increment: 0.606102
Algorithm, std::plus, std::bind1st: 0.607189
BOOST_FOREACH, post-increment: 0.607494
Boost.Lambda, increase: 0.607584
Algorithm, inline function, assignment 2nd: 0.607798
Algorithm, non-inline function, pre-increment: 0.608403
Algorithm, inline function, pre-increment: 0.608423
Boost.Lambda, assignment 1st: 0.608449
BOOST_FOREACH, increase: 0.608545
Algorithm, functor, inline, pre-increment: 0.608674
Algorithm, functor, non-inline, pre-increment: 0.608743
Iterator, increase, non-const end: 0.608774
Boost.Lambda, pre-increment: 0.60902
For-loop, post-increment, non-const size: 0.60909
Algorithm, functor, non-inline, post-increment: 0.609102
For-loop, pre-increment, const size: 0.609103
Iterator, post-increment, non-const end: 0.609108
For-loop, assignment 2nd, const size: 0.609204
BOOST_FOREACH, assignment 2nd: 0.609284
Algorithm, non-inline function, increase: 0.609377
C++11 ranged for loop, pre-increment: 0.609492
Iterator, pre-increment, const end: 0.609536
Algorithm, non-inline function, post-increment: 0.609639
Iterator, increase, const end: 0.609649
C++11 lambda expression, assignment 2nd: 0.609673
BOOST_FOREACH, pre-increment: 0.609676
C++11 lambda expression, assignment 1st: 0.609685
C++11 ranged for loop, increase: 0.609724
Algorithm, non-inline function, assignment 1st: 0.609897
Boost.Lambda, assignment 2nd: 0.610001
Algorithm, non-inline function, assignment 2nd: 0.610085
Iterator, assignment 2nd, const end: 0.610213
C++11 ranged for loop, assignment 1st: 0.610294
Iterator, assignment 1st, const end: 0.610415
For-loop, post-increment, const size: 0.610618
Algorithm, functor, inline, post-increment: 0.610623
Algorithm, functor, inline, assignment 1st: 0.610693
Algorithm, inline function, assignment 1st: 0.61088
Iterator, post-increment, const end: 0.61091
For-loop, assignment 1st, const size: 0.611026
For-loop, increase, non-const size: 0.611066
For-loop, assignment 2nd, non-const size: 0.611367
Iterator, assignment 1st, non-const end: 0.611531
C++11 lambda expression, pre-increment: 0.611675
For-loop, assignment 1st, non-const size: 0.611689
Algorithm, functor, non-inline, assignment 2nd: 0.611726
Algorithm, functor, inline, increase: 0.611765
BOOST_FOREACH, assignment 1st: 0.611871
Algorithm, inline function, increase: 0.612154
C++11 lambda expression, increase: 0.612166
For-loop, pre-increment, non-const size: 0.612224
For-loop, increase, const size: 0.612383
Algorithm, functor, non-inline, increase: 0.612502
C++11 ranged for loop, assignment 2nd: 0.61253
Algorithm, functor, non-inline, assignment 1st: 0.612554
Boost.Lambda, post-increment: 0.612612
Iterator, assignment 2nd, non-const end: 0.612879
Algorithm, std::plus, std::bind2nd: 0.613106
Algorithm, functor, inline, assignment 2nd: 0.613279
Iterator, pre-increment, non-const end: 0.61335
Algorithm, inline function, post-increment: 0.613957
C++11 lambda expression, post-increment: 0.614741
Total running time: 37.8573 seconds.

*/
