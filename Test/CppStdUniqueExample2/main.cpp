#include <algorithm>
#include <cassert>
#include <vector>

template <class Iterator>
bool AreAllUnique(const Iterator& begin, const Iterator& end)
{
  std::sort(begin,end);
  const Iterator new_end {
    std::unique(begin,end)
  };
  return new_end == end;
}

template <class Container>
bool AreAllUnique(Container container)
{
  return AreAllUnique(std::begin(container),std::end(container));
}

int main()
{
  assert(AreAllUnique( std::vector<int>( {} )));
  assert(AreAllUnique( std::vector<int>( { 1 } )));
  assert(AreAllUnique( std::vector<int>( { 1,2 } )));
  assert(AreAllUnique( std::vector<int>( { 2,1 } )));
  assert(AreAllUnique( std::vector<int>( { 1,2,3 } )));
  assert(AreAllUnique( std::vector<int>( { 2,3,1 } )));
  assert(AreAllUnique( std::vector<int>( { 1,2,3,4 } )));
  assert(AreAllUnique( std::vector<int>( { 4,3,2,1 } )));

  assert(!AreAllUnique( std::vector<int>( { 1,2,1 } )));
  assert(!AreAllUnique( std::vector<int>( { 2,2,1 } )));
  assert(!AreAllUnique( std::vector<int>( { 1,2,3,2 } )));
  assert(!AreAllUnique( std::vector<int>( { 2,3,1,1 } )));
  assert(!AreAllUnique( std::vector<int>( { 1,2,3,4,3 } )));
  assert(!AreAllUnique( std::vector<int>( { 4,3,2,1,3 } )));
}
