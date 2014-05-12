#include "trianglecppevent.h"

void tricpp::eventheapinsert(
  Event ** const heap,
  const int heapsize,
  Event * const newevent)
{
  const double eventx = newevent->xkey;
  const double eventy = newevent->ykey;
  int eventnum = heapsize;
  int notdone = eventnum > 0;
  while (notdone)
  {
    const int parent = (eventnum - 1) >> 1;
    if ((heap[parent]->ykey < eventy) ||
        ((heap[parent]->ykey == eventy)
         && (heap[parent]->xkey <= eventx)))
    {
      notdone = 0;
    }
    else
    {
      heap[eventnum] = heap[parent];
      heap[eventnum]->heapposition = eventnum;

      eventnum = parent;
      notdone = eventnum > 0;
    }
  }
  heap[eventnum] = newevent;
  newevent->heapposition = eventnum;
}

void tricpp::eventheapify(
  Event ** const heap,
  const int heapsize,
  int eventnum
)
{
  int rightchild = -1;
  int smallest = -1;

  Event *thisevent = heap[eventnum];
  const double eventx = thisevent->xkey;
  const double eventy = thisevent->ykey;
  int leftchild = 2 * eventnum + 1;
  int notdone = leftchild < heapsize;
  while (notdone)
  {
    if ((heap[leftchild]->ykey < eventy) ||
        ((heap[leftchild]->ykey == eventy)
         && (heap[leftchild]->xkey < eventx)))
    {
      smallest = leftchild;
    }
    else
    {
      smallest = eventnum;
    }
    rightchild = leftchild + 1;
    if (rightchild < heapsize) {
      if ((heap[rightchild]->ykey < heap[smallest]->ykey) ||
          ((heap[rightchild]->ykey == heap[smallest]->ykey)
           && (heap[rightchild]->xkey < heap[smallest]->xkey))) {
        smallest = rightchild;
      }
    }
    if (smallest == eventnum) {
      notdone = 0;
    } else {
      heap[eventnum] = heap[smallest];
      heap[eventnum]->heapposition = eventnum;
      heap[smallest] = thisevent;
      thisevent->heapposition = smallest;

      eventnum = smallest;
      leftchild = 2 * eventnum + 1;
      notdone = leftchild < heapsize;
    }
  }
}

void tricpp::eventheapdelete(
  Event ** const heap,
  const int heapsize,
  int eventnum
)
{
  //Event *moveevent;
  //double eventx, eventy;
  //int parent;

  Event *moveevent = heap[heapsize - 1];
  if (eventnum > 0)
  {
    int notdone = true;
    double eventx = moveevent->xkey;
    double eventy = moveevent->ykey;
    do {
      int parent = (eventnum - 1) >> 1;
      if ((heap[parent]->ykey < eventy) ||
          ((heap[parent]->ykey == eventy)
           && (heap[parent]->xkey <= eventx))) {
        notdone = 0;
      } else {
        heap[eventnum] = heap[parent];
        heap[eventnum]->heapposition = eventnum;

        eventnum = parent;
        notdone = eventnum > 0;
      }
    } while (notdone);
  }
  heap[eventnum] = moveevent;
  moveevent->heapposition = eventnum;
  eventheapify(heap, heapsize - 1, eventnum);
}
