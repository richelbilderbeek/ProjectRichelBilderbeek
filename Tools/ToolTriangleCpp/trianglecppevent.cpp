#include "trianglecppevent.h"

ribi::tricpp::Event::Event()
  :
    m_eventptr{nullptr},
    m_heapposition{0},
    m_xkey{0.0},
    m_ykey{0.0}
{

}


void ribi::tricpp::eventheapinsert(
  Event ** const heap,
  const int heapsize,
  Event * const newevent)
{
  const double eventx = newevent->m_xkey;
  const double eventy = newevent->m_ykey;
  int eventnum = heapsize;
  int notdone = eventnum > 0;
  while (notdone)
  {
    const int parent = (eventnum - 1) >> 1;
    if ((heap[parent]->m_ykey < eventy) ||
        ((heap[parent]->m_ykey == eventy)
         && (heap[parent]->m_xkey <= eventx)))
    {
      notdone = 0;
    }
    else
    {
      heap[eventnum] = heap[parent];
      heap[eventnum]->m_heapposition = eventnum;

      eventnum = parent;
      notdone = eventnum > 0;
    }
  }
  heap[eventnum] = newevent;
  newevent->m_heapposition = eventnum;
}

void ribi::tricpp::eventheapify(
  Event ** const heap,
  const int heapsize,
  int eventnum
)
{
  int rightchild = -1;
  int smallest = -1;

  Event *thisevent = heap[eventnum];
  const double eventx = thisevent->m_xkey;
  const double eventy = thisevent->m_ykey;
  int leftchild = 2 * eventnum + 1;
  int notdone = leftchild < heapsize;
  while (notdone)
  {
    if ((heap[leftchild]->m_ykey < eventy) ||
        ((heap[leftchild]->m_ykey == eventy)
         && (heap[leftchild]->m_xkey < eventx)))
    {
      smallest = leftchild;
    }
    else
    {
      smallest = eventnum;
    }
    rightchild = leftchild + 1;
    if (rightchild < heapsize) {
      if ((heap[rightchild]->m_ykey < heap[smallest]->m_ykey) ||
          ((heap[rightchild]->m_ykey == heap[smallest]->m_ykey)
           && (heap[rightchild]->m_xkey < heap[smallest]->m_xkey))) {
        smallest = rightchild;
      }
    }
    if (smallest == eventnum) {
      notdone = 0;
    } else {
      heap[eventnum] = heap[smallest];
      heap[eventnum]->m_heapposition = eventnum;
      heap[smallest] = thisevent;
      thisevent->m_heapposition = smallest;

      eventnum = smallest;
      leftchild = 2 * eventnum + 1;
      notdone = leftchild < heapsize;
    }
  }
}

void ribi::tricpp::eventheapdelete(
  Event ** const heap,
  const int heapsize,
  int eventnum
)
{
  Event * const moveevent = heap[heapsize - 1];
  if (eventnum > 0)
  {
    int notdone = true;
    double eventx = moveevent->m_xkey;
    double eventy = moveevent->m_ykey;
    do {
      int parent = (eventnum - 1) >> 1;
      if ((heap[parent]->m_ykey < eventy) ||
          ((heap[parent]->m_ykey == eventy)
           && (heap[parent]->m_xkey <= eventx))) {
        notdone = 0;
      } else {
        heap[eventnum] = heap[parent];
        heap[eventnum]->m_heapposition = eventnum;

        eventnum = parent;
        notdone = eventnum > 0;
      }
    } while (notdone);
  }
  heap[eventnum] = moveevent;
  moveevent->m_heapposition = eventnum;
  eventheapify(heap, heapsize - 1, eventnum);
}
