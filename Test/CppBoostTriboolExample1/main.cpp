#include <cassert>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/logic/tribool.hpp>
#pragma GCC diagnostic pop


int main()
{
  const boost::logic::tribool t { true };
  const boost::logic::tribool f { false };
  const boost::logic::tribool i { boost::logic::indeterminate };

  /* WILL FAIL
  assert(t);
  assert(!f);
  assert(t == t);
  assert(f == f);
  assert(i == i);
  assert(t != f);
  assert(f != i);
  assert(i != t);
  assert(t != i);
  assert(f != t);
  assert(i != f);
  assert(t == true);
  assert(f == false);
  assert(i == boost::logic::indeterminate);
  assert(t != false);
  assert(f != boost::logic::indeterminate);
  assert(i != true);
  assert(t != boost::logic::indeterminate);
  assert(f != true);
  assert(i != false);
  assert(t == boost::logic::tribool::true_value);
  assert(f == boost::logic::tribool::false_value);
  assert(i == boost::logic::tribool::indeterminate_value);
  */

  assert(boost::logic::indeterminate(i));
  if ( t) { /* OK */ } else { assert(!"Should not get here"); }
  if (!t) { assert(!"Should not get here"); } else { /* OK */ }
  if (!f) { /* OK */ } else { assert(!"Should not get here"); }
  if ( f) { assert(!"Should not get here"); } else { /* OK */ }
  if ( boost::logic::indeterminate(i)) { /* OK */ } else { assert(!"Should not get here"); }
  if (!boost::logic::indeterminate(t)) { /* OK */ } else { assert(!"Should not get here"); }
  if (!boost::logic::indeterminate(f)) { /* OK */ } else { assert(!"Should not get here"); }
}


