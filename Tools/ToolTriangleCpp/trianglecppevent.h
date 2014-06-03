#ifndef TRIANGLECPPEVENT_H
#define TRIANGLECPPEVENT_H

#ifdef TRIANGLECPP_USE_EVENT

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic pop


namespace ribi {
namespace tricpp {

/// A node in a heap used to store events for the sweepline Delaunay
///   algorithm.  Nodes do not point directly to their parents or children in
///   the heap.  Instead, each node knows its position in the heap, and can
///   look up its parent and children in a separate array.  The `eventptr'
///   points either to a `vertex' or to a triangle (in encoded format, so
///   that an orientation is included).  In the latter case, the origin of
///   the oriented triangle is the apex of a "circle event" of the sweepline
///   algorithm.  To distinguish site events from circle events, all circle
///   events are given an invalid (smaller than `xmin') x-coordinate `xkey'.
struct Event
{
  Event();
  /// Can be a vertex or the location of a circle event
  void *m_eventptr;
  /// Marks this event's position in the heap.
  int m_heapposition;
  /// Coordinates of the event
  double m_xkey;
  double m_ykey;
};

void eventheapdelete(
  Event ** const heap,
  const int heapsize,
  int eventnum
);

void eventheapify(
  Event ** const heap,
  const int heapsize,
  int eventnum
);

void eventheapinsert(
  Event ** const heap,
  const int heapsize,
  Event * const newevent
);

} //~namespace tricpp
} //~namespace ribi

#endif // TRIANGLECPP_USE_EVENT

#endif // TRIANGLECPPEVENT_H
