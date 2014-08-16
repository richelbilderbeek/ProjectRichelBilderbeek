#include "trianglecppmemorypool.h"

#include <algorithm>

#include "trianglecpptrimalloc.h"

/*
ribi::tricpp::MemoryPool::MemoryPool()
  :
    m_alignbytes{0},
    m_deaditemstack{nullptr},
    m_firstblock{nullptr},
    m_itembytes{0},
    m_items{0},
    m_itemsfirstblock{0},
    m_itemsperblock{0},
    m_maxitems{0},
    m_nextitem{nullptr},
    m_nowblock{nullptr},
    m_pathblock{nullptr},
    m_pathitem{nullptr},
    m_pathitemsleft{0},
    m_unallocateditems{0}
{

}

void * ribi::tricpp::PoolAlloc(MemoryPool * const pool)
{
  void *newitem;
  void **newblock;
  unsigned long alignptr;

  /// First check the linked list of dead items.  If the list is not
  ///   empty, allocate an item from the list rather than a fresh one.
  if (pool->m_deaditemstack != nullptr)
  {
    newitem = pool->m_deaditemstack;               /// Take first item in list.
    pool->m_deaditemstack = * (void **) pool->m_deaditemstack;
  }
  else
  {
    /// Check if there are any free items left in the current block.
    if (pool->m_unallocateditems == 0) {
      /// Check if another block must be allocated.
      if (*(pool->m_nowblock) == nullptr) {
        /// Allocate a new block of items, pointed to by the previous block.
        newblock = (void **) TriMalloc(pool->m_itemsperblock * pool->m_itembytes +
                                       (int) sizeof(void *) +
                                       pool->m_alignbytes);
        *(pool->m_nowblock) = (void *) newblock;
        /// The next block pointer is NULL.
        *newblock = nullptr;
      }

      /// Move to the new block.
      pool->m_nowblock = (void **) *(pool->m_nowblock);
      /// Find the first item in the block.
      ///   Increment by the size of (void *).
      alignptr = (unsigned long) (pool->m_nowblock + 1);
      /// Align the item on an `alignbytes'-byte boundary.
      pool->m_nextitem = (void *)
        (alignptr + (unsigned long) pool->m_alignbytes -
         (alignptr % (unsigned long) pool->m_alignbytes));
      /// There are lots of unallocated items left in this block.
      pool->m_unallocateditems = pool->m_itemsperblock;
    }

    /// Allocate a new item.
    newitem = pool->m_nextitem;
    /// Advance `nextitem' pointer to next free item in block.
    pool->m_nextitem = (void *) ((char *) pool->m_nextitem + pool->m_itembytes);
    pool->m_unallocateditems--;
    pool->m_maxitems++;
  }
  pool->m_items++;
  return newitem;
}

void ribi::tricpp::PoolDealloc(
  MemoryPool * const pool,
  void * const dyingitem
)
{
  /// Push freshly killed item onto stack.
  *((void **) dyingitem) = pool->m_deaditemstack;
  pool->m_deaditemstack = dyingitem;
  --pool->m_items;
}
*/

/*
void ribi::tricpp::PoolDealloc(
  std::vector<Triangle>& triangles,
  Triangle& dying_triangle
)
{
  std::swap(
    *std::find(triangles.begin(),triangles.end(),dying_triangle),
    triangles.back()
  );
  triangles.pop_back();
}

void ribi::tricpp::PoolDealloc(
  std::vector<Vertex>& vertices,Vertex& dyingitem
)
{
  /// Push freshly killed item onto stack.
  //*((void **) dyingitem) = pool->m_deaditemstack;
  //pool->m_deaditemstack = dyingitem;
  //--pool->m_items;
  std::swap(
    *std::find(vertices.begin(),vertices.end(),dyingitem),
    vertices.back()
  );
  vertices.pop_back();

}
*/
/*
void ribi::tricpp::PoolDeinit(MemoryPool * const pool)
{
  while (pool->m_firstblock != nullptr) {
    pool->m_nowblock = (void **) *(pool->m_firstblock);
    delete pool->m_firstblock;
    pool->m_firstblock = nullptr;
    pool->m_firstblock = pool->m_nowblock;
  }
}
*/
/*
void ribi::tricpp::PoolDeinit(std::vector<Vertex>& vertices)
{
  vertices.resize(0);
}
*/
/*
void ribi::tricpp::PoolInit(
  MemoryPool * const pool,
  const int bytecount,
  const int itemcount,
  const int firstitemcount,
  const int alignment
)
{
  /// Find the proper alignment, which must be at least as large as:
  ///   - The parameter `alignment'.
  ///   - sizeof(void *), so the stack of dead items can be maintained
  ///       without unaligned accesses.
  if (alignment > static_cast<int>(sizeof(void *))) {
    pool->m_alignbytes = alignment;
  } else {
    pool->m_alignbytes = sizeof(void *);
  }
  pool->m_itembytes = ((bytecount - 1) / pool->m_alignbytes + 1) *
                    pool->m_alignbytes;
  pool->m_itemsperblock = itemcount;
  if (firstitemcount == 0)
  {
    pool->m_itemsfirstblock = itemcount;
  } else
  {
    pool->m_itemsfirstblock = firstitemcount;
  }

  /// Allocate a block of items.  Space for `itemsfirstblock' items and one
  ///   pointer (to point to the next block) are allocated, as well as space
  ///   to ensure alignment of the items.
  pool->m_firstblock = (void **)
    TriMalloc(pool->m_itemsfirstblock * pool->m_itembytes + (int) sizeof(void *) +
              pool->m_alignbytes);
  /// Set the next block pointer to NULL.
  *(pool->m_firstblock) = nullptr;
  PoolRestart(pool);
}

void ribi::tricpp::PoolRestart(MemoryPool * const pool)
{
  pool->m_items = 0;
  pool->m_maxitems = 0;

  /// Set the currently active block.
  pool->m_nowblock = pool->m_firstblock;
  /// Find the first item in the pool.  Increment by the size of (void *).
  const unsigned long alignptr = (unsigned long) (pool->m_nowblock + 1);
  /// Align the item on an `alignbytes'-byte boundary.
  pool->m_nextitem = (void *)
    (alignptr + (unsigned long) pool->m_alignbytes -
     (alignptr % (unsigned long) pool->m_alignbytes));
  /// There are lots of unallocated items left in this block.
  pool->m_unallocateditems = pool->m_itemsfirstblock;
  /// The stack of deallocated items is empty.
  pool->m_deaditemstack = nullptr;
}

void ribi::tricpp::TraversalInit(MemoryPool * const pool)
{
  /// Begin the traversal in the first block.
  pool->m_pathblock = pool->m_firstblock;
  /// Find the first item in the block.  Increment by the size of (void *).
  const unsigned long alignptr = (unsigned long) (pool->m_pathblock + 1);
  /// Align with item on an `alignbytes'-byte boundary.
  pool->m_pathitem = (void *)
    (alignptr + (unsigned long) pool->m_alignbytes -
     (alignptr % (unsigned long) pool->m_alignbytes));
  /// Set the number of items left in the current block.
  pool->m_pathitemsleft = pool->m_itemsfirstblock;
}

void * ribi::tricpp::Traverse(MemoryPool * const pool)
{
  /// Stop upon exhausting the list of items.
  if (pool->m_pathitem == pool->m_nextitem)
  {
    return nullptr;
  }

  /// Check whether any untraversed items remain in the current block.
  if (pool->m_pathitemsleft == 0)
  {
    /// Find the next block.
    pool->m_pathblock = (void **) *(pool->m_pathblock);
    /// Find the first item in the block.  Increment by the size of (void *).
    unsigned long alignptr = (unsigned long)pool->m_pathblock + 1;
    /// Align with item on an `alignbytes'-byte boundary.
    pool->m_pathitem = (void *)
      (alignptr + (unsigned long) pool->m_alignbytes -
       (alignptr % (unsigned long) pool->m_alignbytes));
    /// Set the number of items left in the current block.
    pool->m_pathitemsleft = pool->m_itemsperblock;
  }

  void * const newitem = pool->m_pathitem;
  /// Find the next item in the block.
  pool->m_pathitem = (void *) ((char *) pool->m_pathitem + pool->m_itembytes);
  --pool->m_pathitemsleft;
  return newitem;
}
*/
