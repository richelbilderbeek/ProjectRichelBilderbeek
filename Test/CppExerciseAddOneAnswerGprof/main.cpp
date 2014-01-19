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
#include <boost/foreach.hpp>
#include <boost/timer.hpp>
#include <boost/lambda/lambda.hpp>
//#include <QObject>

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
struct AddOnerNonInlineAssignment1st : public std::unary_function<int,void>
  { void operator()(int& x) { x=1+x; } };
struct AddOnerNonInlineAssignment2nd : public std::unary_function<int,void>
  { void operator()(int& x) { x=x+1; } };
struct AddOnerNonInlineIncrease : public std::unary_function<int,void>
  { void operator()(int& x) { x+=1; } };
struct AddOnerNonInlinePostIncrement : public std::unary_function<int,void>
  { void operator()(int& x) { x++; } };
struct AddOnerNonInlinePreIncrement : public std::unary_function<int,void>
  { void operator()(int& x) { ++x; } };

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
struct AddOnerInlineAssignment1st : public std::unary_function<int,void>
  { inline void operator()(int& x) { x=1+x; } };
struct AddOnerInlineAssignment2nd : public std::unary_function<int,void>
  { inline void operator()(int& x) { x=x+1; } };
struct AddOnerInlineIncrease : public std::unary_function<int,void>
  { inline void operator()(int& x) { x+=1; } };
struct AddOnerInlinePostIncrement : public std::unary_function<int,void>
  { inline void operator()(int& x) { x++; } };
struct AddOnerInlinePreIncrement : public std::unary_function<int,void>
  { inline void operator()(int& x) { ++x; } };

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

void AddCpp0xForPreIncrement(std::vector<int>& v)
{
  for(int &i: v) { ++i; }
}

void AddCpp0xForPostIncrement(std::vector<int>& v)
{
  for(int &i: v) { i++; }
}

void AddCpp0xForIncrease(std::vector<int>& v)
{
  for(int &i: v) { i+=1; }
}

void AddCpp0xForAssignment1st(std::vector<int>& v)
{
  for(int &i: v) { i=1+i; }
}

void AddCpp0xForAssignment2nd(std::vector<int>& v)
{
  for(int &i: v) { i=i+1; }
}

void AddCpp0xLambdaPreIncrement(std::vector<int>& v)
{
  std::for_each(v.begin(),v.end(), [](int&i) { ++i; } );
}

void AddCpp0xLambdaPostIncrement(std::vector<int>& v)
{
  std::for_each(v.begin(),v.end(), [](int&i) { i++; } );
}

void AddCpp0xLambdaIncrease(std::vector<int>& v)
{
  std::for_each(v.begin(),v.end(), [](int&i) { i+=1; } );
}

void AddCpp0xLambdaAssignment1st(std::vector<int>& v)
{
  std::for_each(v.begin(),v.end(), [](int&i) { i = i + 1; } );
}

void AddCpp0xLambdaAssignment2nd(std::vector<int>& v)
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

  const int size = 1000000;
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
}

/*
Size std::vector: 40000000
Repeats: 10
Timer minimal interval: 1e-06
Results (best result first):
C++0x lambda expression, pre-increment: 0.37
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
C++0x ranged for loop, pre-increment: 0.39
Algorithm, functor, non-inline, assignment 1st: 0.39
C++0x ranged for loop, assignment 2nd: 0.39
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
C++0x lambda expression, increase: 0.4
Boost.Lambda, post-increment: 0.4
Boost.Lambda, increase: 0.4
Iterator, increase, const end: 0.4
Algorithm, std::plus, std::bind1st: 0.4
Iterator, assignment 1st, non-const end: 0.4
C++0x ranged for loop, increase: 0.4
Algorithm, functor, inline, increase: 0.4
C++0x lambda expression, post-increment: 0.4
Algorithm, functor, inline, assignment 2nd: 0.4
C++0x ranged for loop, post-increment: 0.4
Algorithm, inline function, increase: 0.4
Algorithm, non-inline function, increase: 0.4
Algorithm, non-inline function, pre-increment: 0.4
C++0x ranged for loop, assignment 1st: 0.4
BOOST_FOREACH, post-increment: 0.4
Iterator, assignment 1st, const end: 0.4
C++0x lambda expression, assignment 1st: 0.41
Algorithm, functor, inline, pre-increment: 0.41
For-loop, increase, const size: 0.44
For-loop, increase, non-const size: 0.44
For-loop, assignment 1st, const size: 0.44
For-loop, assignment 2nd, non-const size: 0.45
For-loop, assignment 1st, non-const size: 0.46
For-loop, assignment 2nd, const size: 0.46
C++0x lambda expression, assignment 2nd: 0.46
For-loop, post-increment, const size: 0.47
For-loop, post-increment, non-const size: 0.47
For-loop, pre-increment, non-const size: 0.48
For-loop, pre-increment, const size: 0.49
Total running time: 25.16 seconds.
*/
