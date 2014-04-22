#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-variable"

#pragma GCC diagnostic pop

template <std::Sequence S, Equality_comparable<Value_type<S>,T>()>
Iterator_of<S> find(S& seq, const T&value)
{
}

template <typename S, typename Y>
  requires Sequence<S>()
    && Equality_comparable<Value_type<S>,T>()
Iterator_of<S> find(S& seq, const T&value)
{
}

int main()
{

}
