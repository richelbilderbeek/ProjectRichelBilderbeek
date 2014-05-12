#include "trianglecppmemorypool.h"

#include "trianglecpptrimalloc.h"

tricpp::MemoryPool::MemoryPool()
{
  firstblock = nullptr;
  nowblock = nullptr;
  nextitem = nullptr;
  deaditemstack = nullptr;
  pathblock = nullptr;
  pathitem = nullptr;
  alignbytes = 0;
  itembytes = 0;
  itemsperblock = 0;
  itemsfirstblock = 0;
  items = 0;
  maxitems = 0;
  unallocateditems = 0;
  pathitemsleft = 0;
}

void * tricpp::poolalloc(MemoryPool * const pool)
{
  void *newitem;
  void **newblock;
  unsigned long alignptr;

  /// First check the linked list of dead items.  If the list is not
  ///   empty, allocate an item from the list rather than a fresh one.
  if (pool->deaditemstack != nullptr) {
    newitem = pool->deaditemstack;               /// Take first item in list.
    pool->deaditemstack = * (void **) pool->deaditemstack;
  } else {
    /// Check if there are any free items left in the current block.
    if (pool->unallocateditems == 0) {
      /// Check if another block must be allocated.
      if (*(pool->nowblock) == nullptr) {
        /// Allocate a new block of items, pointed to by the previous block.
        newblock = (void **) trimalloc(pool->itemsperblock * pool->itembytes +
                                       (int) sizeof(void *) +
                                       pool->alignbytes);
        *(pool->nowblock) = (void *) newblock;
        /// The next block pointer is NULL.
        *newblock = nullptr;
      }

      /// Move to the new block.
      pool->nowblock = (void **) *(pool->nowblock);
      /// Find the first item in the block.
      ///   Increment by the size of (void *).
      alignptr = (unsigned long) (pool->nowblock + 1);
      /// Align the item on an `alignbytes'-byte boundary.
      pool->nextitem = (void *)
        (alignptr + (unsigned long) pool->alignbytes -
         (alignptr % (unsigned long) pool->alignbytes));
      /// There are lots of unallocated items left in this block.
      pool->unallocateditems = pool->itemsperblock;
    }

    /// Allocate a new item.
    newitem = pool->nextitem;
    /// Advance `nextitem' pointer to next free item in block.
    pool->nextitem = (void *) ((char *) pool->nextitem + pool->itembytes);
    pool->unallocateditems--;
    pool->maxitems++;
  }
  pool->items++;
  return newitem;
}

void tricpp::pooldealloc(
  MemoryPool * const pool,
  void * const dyingitem
)
{
  /// Push freshly killed item onto stack.
  *((void **) dyingitem) = pool->deaditemstack;
  pool->deaditemstack = dyingitem;
  pool->items--;
}

void tricpp::pooldeinit(MemoryPool * const pool)
{
  while (pool->firstblock != nullptr) {
    pool->nowblock = (void **) *(pool->firstblock);
    delete pool->firstblock;
    pool->firstblock = nullptr;
    pool->firstblock = pool->nowblock;
  }
}

void tricpp::poolinit(
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
    pool->alignbytes = alignment;
  } else {
    pool->alignbytes = sizeof(void *);
  }
  pool->itembytes = ((bytecount - 1) / pool->alignbytes + 1) *
                    pool->alignbytes;
  pool->itemsperblock = itemcount;
  if (firstitemcount == 0) {
    pool->itemsfirstblock = itemcount;
  } else {
    pool->itemsfirstblock = firstitemcount;
  }

  /// Allocate a block of items.  Space for `itemsfirstblock' items and one
  ///   pointer (to point to the next block) are allocated, as well as space
  ///   to ensure alignment of the items.
  pool->firstblock = (void **)
    trimalloc(pool->itemsfirstblock * pool->itembytes + (int) sizeof(void *) +
              pool->alignbytes);
  /// Set the next block pointer to NULL.
  *(pool->firstblock) = nullptr;
  poolrestart(pool);
}

void tricpp::poolrestart(MemoryPool * const pool)
{
  unsigned long alignptr;

  pool->items = 0;
  pool->maxitems = 0;

  /// Set the currently active block.
  pool->nowblock = pool->firstblock;
  /// Find the first item in the pool.  Increment by the size of (void *).
  alignptr = (unsigned long) (pool->nowblock + 1);
  /// Align the item on an `alignbytes'-byte boundary.
  pool->nextitem = (void *)
    (alignptr + (unsigned long) pool->alignbytes -
     (alignptr % (unsigned long) pool->alignbytes));
  /// There are lots of unallocated items left in this block.
  pool->unallocateditems = pool->itemsfirstblock;
  /// The stack of deallocated items is empty.
  pool->deaditemstack = nullptr;
}

/*
void tricpp::poolzero(MemoryPool * const pool)
{
  pool->firstblock = nullptr;
  pool->nowblock = nullptr;
  pool->nextitem = nullptr;
  pool->deaditemstack = nullptr;
  pool->pathblock = nullptr;
  pool->pathitem = nullptr;
  pool->alignbytes = 0;
  pool->itembytes = 0;
  pool->itemsperblock = 0;
  pool->itemsfirstblock = 0;
  pool->items = 0;
  pool->maxitems = 0;
  pool->unallocateditems = 0;
  pool->pathitemsleft = 0;
}
*/

void tricpp::traversalinit(MemoryPool * const pool)
{
  unsigned long alignptr;

  /// Begin the traversal in the first block.
  pool->pathblock = pool->firstblock;
  /// Find the first item in the block.  Increment by the size of (void *).
  alignptr = (unsigned long) (pool->pathblock + 1);
  /// Align with item on an `alignbytes'-byte boundary.
  pool->pathitem = (void *)
    (alignptr + (unsigned long) pool->alignbytes -
     (alignptr % (unsigned long) pool->alignbytes));
  /// Set the number of items left in the current block.
  pool->pathitemsleft = pool->itemsfirstblock;
}

void * tricpp::traverse(MemoryPool * const pool)
{
  void *newitem;
  unsigned long alignptr;

  /// Stop upon exhausting the list of items.
  if (pool->pathitem == pool->nextitem) {
    return nullptr;
  }

  /// Check whether any untraversed items remain in the current block.
  if (pool->pathitemsleft == 0) {
    /// Find the next block.
    pool->pathblock = (void **) *(pool->pathblock);
    /// Find the first item in the block.  Increment by the size of (void *).
    alignptr = (unsigned long) (pool->pathblock + 1);
    /// Align with item on an `alignbytes'-byte boundary.
    pool->pathitem = (void *)
      (alignptr + (unsigned long) pool->alignbytes -
       (alignptr % (unsigned long) pool->alignbytes));
    /// Set the number of items left in the current block.
    pool->pathitemsleft = pool->itemsperblock;
  }

  newitem = pool->pathitem;
  /// Find the next item in the block.
  pool->pathitem = (void *) ((char *) pool->pathitem + pool->itembytes);
  pool->pathitemsleft--;
  return newitem;
}
