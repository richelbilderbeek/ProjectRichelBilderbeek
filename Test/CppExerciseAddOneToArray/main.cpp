//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppExerciseAddOneAnswer.htm
//---------------------------------------------------------------------------
#include <cassert>
#include <cmath>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <functional>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/foreach.hpp>
#include <boost/timer.hpp>
#include <boost/lambda/lambda.hpp>
#pragma GCC diagnostic pop

void AddForAssignment1stConstSize(int * const v, const int size)
{
  for (int i=0; i!=size; ++i) v[i]=1+v[i];
}

void AddForAssignment2ndConstSize(int * const v, const int size)
{
  for (int i=0; i!=size; ++i) v[i]=v[i]+1;
}

void AddForIncreaseConstSize(int * const v, const int size)
{
  for (int i=0; i!=size; ++i) v[i]+=1;
}

void AddForPostIncrementConstSize(int * const v, const int size)
{
  for (int i=0; i!=size; ++i) v[i]++;
}

void AddForPreIncrementConstSize(int * const v, const int size)
{
  for (int i=0; i!=size; ++i) ++v[i];
}

void AddIteratorAssignment1stConstEnd(int * const v, const int size)
{
  const int * const j = v + size;
  for (int * i = v; i!=j; ++i) (*i) = 1 + (*i);
}

void AddIteratorAssignment2ndConstEnd(int * const v, const int size)
{
  const int * const j = v + size;
  for (int * i = v; i!=j; ++i) (*i) = (*i) + 1;
}

void AddIteratorIncreaseConstEnd(int * const v, const int size)
{
    const int * const j = v + size;
  for (int * i = v; i!=j; ++i) (*i)+=1;
}

void AddIteratorPostIncrementConstEnd(int * const v, const int size)
{
  const int * const j = v + size;
  for (int * i = v; i!=j; ++i) (*i)++;
}

void AddIteratorPreIncrementConstEnd(int * const v, const int size)
{
  const int * const j = v + size;
  for (int * i = v; i!=j; ++i) ++(*i);
}

void AddIteratorAssignment1stNonConstEnd(int * const v, const int size)
{
  for (int * i = v; i!=v+size; ++i) (*i) = 1 + (*i);
}

void AddIteratorAssignment2ndNonConstEnd(int * const v, const int size)
{
  for (int * i = v; i!=v+size; ++i) (*i) = (*i) + 1;
}

void AddIteratorIncreaseNonConstEnd(int * const v, const int size)
{
  for (int * i = v; i!=v+size; ++i) (*i)+=1;
}

void AddIteratorPostIncrementNonConstEnd(int * const v, const int size)
{
  for (int * i = v; i!=v+size; ++i) (*i)++;
}

void AddIteratorPreIncrementNonConstEnd(int * const v, const int size)
{
  for (int * i = v; i!=v+size; ++i) ++(*i);
}

//non-inline functions
void AddOneAssignment1st(int& x) { x=1+x; }
void AddOneAssignment2nd(int& x) { x=x+1; }
void AddOneIncrease(int& x) { x+=1; }
void AddOnePostIncrement(int& x) { x++; }
void AddOnePreIncrement(int& x) { ++x; }

void AddAlgorithmNonInlineFunctionAssignment1st(int * const v, const int size)
{
  std::for_each(v,v+size,AddOneAssignment1st);
}

void AddAlgorithmNonInlineFunctionAssignment2nd(int * const v, const int size)
{
  std::for_each(v,v+size,AddOneAssignment2nd);
}

void AddAlgorithmNonInlineFunctionIncrease(int * const v, const int size)
{
  std::for_each(v,v+size,AddOneIncrease);
}

void AddAlgorithmNonInlineFunctionPostIncrement(int * const v, const int size)
{
  std::for_each(v,v+size,AddOnePostIncrement);
}

void AddAlgorithmNonInlineFunctionPreIncrement(int * const v, const int size)
{
  std::for_each(v,v+size,AddOnePreIncrement);
}

//inline functions
inline void AddOneAssignmentInline1st(int& x) { x=1+x; }
inline void AddOneAssignmentInline2nd(int& x) { x=x+1; }
inline void AddOneIncreaseInline(int& x) { x+=1; }
inline void AddOnePostIncrementInline(int& x) { x++; }
inline void AddOnePreIncrementInline(int& x) { ++x; }

void AddAlgorithmInlineFunctionAssignment1st(int * const v, const int size)
{
  std::for_each(v,v+size,AddOneAssignmentInline1st);
}

void AddAlgorithmInlineFunctionAssignment2nd(int * const v, const int size)
{
  std::for_each(v,v+size,AddOneAssignmentInline2nd);
}

void AddAlgorithmInlineFunctionIncrease(int * const v, const int size)
{
  std::for_each(v,v+size,AddOneIncreaseInline);
}

void AddAlgorithmInlineFunctionPostIncrement(int * const v, const int size)
{
  std::for_each(v,v+size,AddOnePostIncrementInline);
}

void AddAlgorithmInlineFunctionPreIncrement(int * const v, const int size)
{
  std::for_each(v,v+size,AddOnePreIncrementInline);
}

//Non-inline-operator() structs
struct AddOnerNonInlineAssignment1st { void operator()(int& x) { x=1+x; } };
struct AddOnerNonInlineAssignment2nd { void operator()(int& x) { x=x+1; } };
struct AddOnerNonInlineIncrease      { void operator()(int& x) { x+=1;  } };
struct AddOnerNonInlinePostIncrement { void operator()(int& x) { x++;   } };
struct AddOnerNonInlinePreIncrement  { void operator()(int& x) { ++x;   } };

void AddAlgorithmFunctorNonInlineAssignment1st(int * const v, const int size)
{
  std::for_each(v,v+size, AddOnerNonInlineAssignment1st() );
}

void AddAlgorithmFunctorNonInlineAssignment2nd(int * const v, const int size)
{
  std::for_each(v,v+size, AddOnerNonInlineAssignment2nd() );
}

void AddAlgorithmFunctorNonInlineIncrease(int * const v, const int size)
{
  std::for_each(v,v+size, AddOnerNonInlineIncrease() );
}

void AddAlgorithmFunctorNonInlinePostIncrement(int * const v, const int size)
{
  std::for_each(v,v+size, AddOnerNonInlinePostIncrement() );
}

void AddAlgorithmFunctorNonInlinePreIncrement(int * const v, const int size)
{
  std::for_each(v,v+size, AddOnerNonInlinePreIncrement() );
}

//Inline-operator() structs
struct AddOnerInlineAssignment1st { inline void operator()(int& x) { x=1+x; } };
struct AddOnerInlineAssignment2nd { inline void operator()(int& x) { x=x+1; } };
struct AddOnerInlineIncrease      { inline void operator()(int& x) { x+=1;  } };
struct AddOnerInlinePostIncrement { inline void operator()(int& x) { x++;   } };
struct AddOnerInlinePreIncrement  { inline void operator()(int& x) { ++x;   } };

void AddAlgorithmFunctorInlineAssignment1st(int * const v, const int size)
{
  std::for_each(v,v+size, AddOnerInlineAssignment1st() );
}

void AddAlgorithmFunctorInlineAssignment2nd(int * const v, const int size)
{
  std::for_each(v,v+size, AddOnerInlineAssignment2nd() );
}

void AddAlgorithmFunctorInlineIncrease(int * const v, const int size)
{
  std::for_each(v,v+size, AddOnerInlineIncrease() );
}

void AddAlgorithmFunctorInlinePostIncrement(int * const v, const int size)
{
  std::for_each(v,v+size, AddOnerInlinePostIncrement() );
}

void AddAlgorithmFunctorInlinePreIncrement(int * const v, const int size)
{
  std::for_each(v,v+size, AddOnerInlinePreIncrement() );
}

void AddAlgorithmBind1st(int * const v, const int size)
{
  std::transform(v,v+size,v,
    std::bind1st(std::plus<int>(),1));
}

void AddAlgorithmBind2nd(int * const v, const int size)
{
  std::transform(v,v+size,v,
    std::bind2nd(std::plus<int>(),1));
}

void AddBoostLambdaPreIncrement(int * const v, const int size)
{
  std::for_each(v,v+size, ++boost::lambda::_1);
}

void AddBoostLambdaPostIncrement(int * const v, const int size)
{
  std::for_each(v,v+size, boost::lambda::_1++);
}

void AddBoostLambdaIncrease(int * const v, const int size)
{
  std::for_each(v,v+size, boost::lambda::_1+=1);
}

void AddBoostLambdaAssignment1st(int * const v, const int size)
{
  std::for_each(v,v+size, boost::lambda::_1 = boost::lambda::_1 + 1);
}

void AddBoostLambdaAssignment2nd(int * const v, const int size)
{
  std::for_each(v,v+size, boost::lambda::_1 = 1 + boost::lambda::_1);
}

void AddCpp11LambdaPreIncrement(int * const v, const int size)
{
  std::for_each(v,v+size, [](int&i) { ++i; } );
}

void AddCpp11LambdaPostIncrement(int * const v, const int size)
{
  std::for_each(v,v+size, [](int&i) { i++; } );
}

void AddCpp11LambdaIncrease(int * const v, const int size)
{
  std::for_each(v,v+size, [](int&i) { i+=1; } );
}

void AddCpp11LambdaAssignment1st(int * const v, const int size)
{
  std::for_each(v,v+size, [](int&i) { i = i + 1; } );
}

void AddCpp11LambdaAssignment2nd(int * const v, const int size)
{
  std::for_each(v,v+size, [](int&i) { i = 1 + i; } );
}

//From http://www.richelbilderbeek.nl/CppExerciseAddOneAnswer.htm
struct Function
{
  typedef void (*FunctionPointer)(int * const v, const int size);

  Function(FunctionPointer function, const std::string& name)
    : m_function(function),
      m_name(name),
      m_time(0.0)
  {

  }
  void DoWork(int * const v, const int size)
  {
    boost::timer t;
    m_function(v,size);
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
  const int size = 1000;
  int value = 0;
  int v[size] = {value};

  std::for_each(functions.begin(),functions.end(),
    [&v,&value](Function& function)
    {
      function.DoWork(v,size);
      assert(v[0] == value + 1);
      ++value;
    }
  );
}

//From http://www.richelbilderbeek.nl/CppExerciseAddOneAnswer.htm
int main()
{
  #ifndef NDEBUG
  std::cout << "Set program to release mode, otherwise benchmark gives misleading results\n";
  #else

  boost::timer t;

  const int size = 100000000;
  const int nTimes = 10;
  std::vector<Function> functions = GetFunctions();
  TestFunctions(functions);

  int * const v = new int[size];
  if (!v)
  {
    std::cout << "Could not allocate enough memory for the array\n";
    return 1;
  }

  for (int i=0; i!=size; ++i) { v[i] = 0; }

  for (int i=0; i!=nTimes; ++i)
  {
    std::cout << i << " / " << nTimes << std::endl;
    std::random_shuffle(functions.begin(), functions.end());
    std::for_each(functions.begin(),functions.end(),
      [&v](Function& f)
      {
        f.DoWork(v,size);
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
    << "Size array: " << size << '\n'
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

/* No significant difference

Size array: 100000000
Repeats: 10
Timer minimal interval: 1e-06
Results (best result first):
For-loop, assignment 1st, const size: 0.614131
Algorithm, inline function, assignment 1st: 0.614551
Iterator, assignment 1st, non-const end: 0.614708
Iterator, assignment 1st, const end: 0.614818
Algorithm, non-inline function, post-increment: 0.614845
For-loop, assignment 2nd, const size: 0.614929
Algorithm, non-inline function, pre-increment: 0.615032
Algorithm, non-inline function, increase: 0.615059
Iterator, assignment 2nd, const end: 0.615073
Algorithm, functor, inline, assignment 1st: 0.615091
Algorithm, functor, inline, post-increment: 0.615101
Algorithm, inline function, increase: 0.615117
Boost.Lambda, assignment 2nd: 0.615177
Algorithm, functor, inline, assignment 2nd: 0.615187
Boost.Lambda, post-increment: 0.615244
Algorithm, non-inline function, assignment 1st: 0.61526
C++11 lambda expression, post-increment: 0.615454
Algorithm, inline function, post-increment: 0.615522
Iterator, post-increment, const end: 0.615697
Algorithm, inline function, assignment 2nd: 0.615719
Iterator, increase, const end: 0.615723
Algorithm, std::plus, std::bind1st: 0.615798
Boost.Lambda, pre-increment: 0.615883
C++11 lambda expression, assignment 2nd: 0.615946
C++11 lambda expression, increase: 0.61597
Algorithm, non-inline function, assignment 2nd: 0.616021
C++11 lambda expression, assignment 1st: 0.616047
Algorithm, functor, inline, pre-increment: 0.616094
Algorithm, inline function, pre-increment: 0.616147
Iterator, pre-increment, non-const end: 0.616194
Iterator, post-increment, non-const end: 0.616624
For-loop, increase, const size: 0.616686
Algorithm, functor, non-inline, increase: 0.616775
Boost.Lambda, increase: 0.616811
Iterator, increase, non-const end: 0.617136
Algorithm, functor, non-inline, assignment 2nd: 0.617365
For-loop, post-increment, const size: 0.617465
Algorithm, functor, non-inline, pre-increment: 0.617467
Iterator, pre-increment, const end: 0.617545
For-loop, pre-increment, const size: 0.618337
Algorithm, functor, non-inline, assignment 1st: 0.618491
Boost.Lambda, assignment 1st: 0.618666
Algorithm, std::plus, std::bind2nd: 0.618894
Iterator, assignment 2nd, non-const end: 0.621255
Algorithm, functor, inline, increase: 0.62142
C++11 lambda expression, pre-increment: 0.621782
Algorithm, functor, non-inline, post-increment: 0.622907
Total running time: 29.0409 seconds.
*/


