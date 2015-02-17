/* 
 * mm-implicit.c -  Simple allocator based on implicit free lists, 
 *                  first fit placement, and boundary tag coalescing. 
 *
 * Each block has header and footer of the form:
 * 
 *      31                     3  2  1  0 
 *      -----------------------------------
 *     | s  s  s  s  ... s  s  s  0  0  a/f
 *      ----------------------------------- 
 * 
 * where s are the meaningful size bits and a/f is set 
 * iff the block is allocated. The list has the following form:
 *
 * begin                                                          end
 * heap                                                           heap  
 *  -----------------------------------------------------------------   
 * |  pad   | hdr(8:a) | ftr(8:a) | zero or more usr blks | hdr(8:a) |
 *  -----------------------------------------------------------------
 *          |       prologue      |                       | epilogue |
 *          |         block       |                       | block    |
 *
 * The allocated prologue and epilogue blocks are overhead that
 * eliminate edge conditions during coalescing.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <memory.h>
#include "mm.h"
#include "memlib.h"

/*********************************************************
 * NOTE TO STUDENTS: Before you do anything else, please
 * provide your team information in the following struct.
 ********************************************************/
team_t team = {
  /* Team name */
  "PigBearHawk",
  /* First member's full name */
  "Adam Ross",
  /* First member's email address */
  "adam.ross-1@colorado.edu",
  /* Second member's full name (leave blank if none) */
  "Mathew Moskowitz",
  /* Second member's email address (leave blank if none) */
  "mathew.moskowitz@colorado.edu"
};

/////////////////////////////////////////////////////////////////////////////
// Constants and macros
//
// These correspond to the material in Figure 9.43 of the text
// The macros have been turned into C++ inline functions to
// make debugging code easier.
//
/////////////////////////////////////////////////////////////////////////////
#define WSIZE       4       /* word size (bytes) */  
#define DSIZE       8       /* doubleword size (bytes) */
#define CHUNKSIZE  (1<<6)  /* initial heap size (bytes) */
#define OVERHEAD    8       /* overhead of header and footer (bytes) */


static inline int MAX(int x, int y) {
  return x > y ? x : y;
}

//
// Pack a size and allocated bit into a word
// We mask of the "alloc" field to insure only
// the lower bit is used
//
static inline size_t PACK(size_t size, int alloc) {
  return ((size) | (alloc & 0x1));
}

//
// Read and write a word at address p
//
static inline size_t GET(void *p) { return  *(size_t *)p; }
static inline void PUT( void *p, size_t val)
{
  *((size_t *)p) = val;
}

//
// Read the size and allocated fields from address p
//
static inline size_t GET_SIZE( void *p )  { 
  return GET(p) & ~0x7;
}

static inline int GET_ALLOC( void *p  ) {
  return GET(p) & 0x1;
}

//
// Given block ptr bp, compute address of its header and footer
//
static inline void *HDRP(void *bp) {

  return ( (char *)bp) - WSIZE;
}
static inline void *FTRP(void *bp) {
  return ((char *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE);
}

//
// Given block ptr bp, compute address of next and previous blocks
//
static inline void *NEXT_BLKP(void *bp) {
  return  ((char *)(bp) + GET_SIZE(((char *)(bp) - WSIZE)));
}

static inline void* PREV_BLKP(void *bp){
  return  ((char *)(bp) - GET_SIZE(((char *)(bp) - DSIZE)));
}

/////////////////////////////////////////////////////////////////////////////
//
// Global Variables
//

static char *heap_listp;  /* pointer to first block */  

//
// function prototypes for internal helper routines
//

static char *heap_listp = NULL;
int global_minlist = 0;
int free_count = 0;
static void *extend_heap(size_t words);
static void place(void *bp, size_t asize);
static void *find_fit(size_t asize);
static void *coalesce(void *bp);
static void printblock(void *bp); 
static void checkblock(void *bp);
static void add_free_list(void *bp);
static void remove_free_list(void *bp);

//
// mm_init - Initialize the memory manager 
//
int mm_init(void) 
{
  if ((heap_listp = mem_sbrk(88*WSIZE)) == (void *)-1)
    return -1;

  PUT(heap_listp, 0);
  
  PUT(heap_listp + (1*WSIZE), PACK(43*DSIZE, 1));
  
  int i;
  for(i = 2; i < 86; i++) {
    PUT(heap_listp + (i*WSIZE), 0);
  }
  
  PUT(heap_listp + (86*WSIZE), PACK(43*DSIZE, 1));
  PUT(heap_listp + (87*WSIZE), PACK(0, 1));
  heap_listp += (2*WSIZE);
  global_minlist = 100;
  free_count = 0;

  if (extend_heap(CHUNKSIZE/WSIZE) == NULL)
    return -1;
  
  return 0;
}


//
// extend_heap - Extend heap with free block and return its block pointer
//
static void *extend_heap(size_t words) 
{
  char *bp;
  size_t size;

  size = (words % 2) ? (words+1) * WSIZE : words * WSIZE;
  
  if ((long)(bp = mem_sbrk(size)) == -1)
    return NULL;

  PUT(HDRP(bp), PACK(size, 0));
  PUT(FTRP(bp), PACK(size, 0));
  PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1));
  

  bp = coalesce(bp);

  return bp;
}


//
// Practice problem 9.8
//
// find_fit - Find a fit for a block with asize bytes 
//
static void *find_fit(size_t asize)
{
  void *bp;
 
  if(free_count == 0)
    return NULL;
 
  int minlist = asize / 50;
 
  if(minlist > 83)
    minlist = 83;
 
  if(minlist < global_minlist)
    minlist = global_minlist;
 
  for(; minlist < 84; minlist+=2){
    int i = 0;

    for (bp = (char *)GET(heap_listp + (minlist * WSIZE)); (int)bp != 0 && GET_SIZE(HDRP(bp)) > 0 && i < 250; bp = (char *)GET(bp+WSIZE)) {
      if (!GET_ALLOC(HDRP(bp)) && (asize <= GET_SIZE(HDRP(bp)))) {
	return bp;
      }
      i++;
    }
  }

  return NULL;
}

// 
// mm_free - Free a block 
//
void mm_free(void *bp)
{

  size_t size = GET_SIZE(HDRP(bp));

  PUT(HDRP(bp), PACK(size, 0));
  PUT(FTRP(bp), PACK(size, 0));

  coalesce(bp);
}

//
// coalesce - boundary tag coalescing. Return ptr to coalesced block
//
static void *coalesce(void *bp) 
{
  size_t prev_alloc = GET_ALLOC(FTRP(PREV_BLKP(bp)));
  size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));

  size_t size = GET_SIZE(HDRP(bp));

  if (prev_alloc && next_alloc) { 

    add_free_list(bp);
    return bp;
  }

  else if (prev_alloc && !next_alloc) {

    remove_free_list(NEXT_BLKP(bp));
 
    size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
 
    PUT(HDRP(bp), PACK(size, 0));
    PUT(FTRP(bp), PACK(size,0));

    add_free_list(bp);


  }

  else if (!prev_alloc && next_alloc) {

    remove_free_list(PREV_BLKP(bp));

    size += GET_SIZE(HDRP(PREV_BLKP(bp)));

    PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
    PUT(FTRP(PREV_BLKP(bp)), PACK(size, 0));

    bp = PREV_BLKP(bp);

    add_free_list(bp);

  }

  else {

    remove_free_list(PREV_BLKP(bp));
    remove_free_list(NEXT_BLKP(bp));

    size += GET_SIZE(HDRP(PREV_BLKP(bp))) + GET_SIZE(FTRP(NEXT_BLKP(bp)));

    PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
    PUT(FTRP(PREV_BLKP(bp)), PACK(size, 0));

    bp = PREV_BLKP(bp);

    add_free_list(bp);

  }

  return bp;
}

//
// mm_malloc - Allocate a block with at least size bytes of payload 
//
void *mm_malloc(size_t size) 
{
size_t asize;
  size_t extendsize;
  char *bp;
  
  if (size == 0)
    return NULL;
  
  if (size <= DSIZE)
    asize = 2*DSIZE;
  else
    asize = DSIZE * ((size + (DSIZE) + (DSIZE-1)) / DSIZE);
  
  if ((bp = find_fit(asize)) != NULL) {
    place(bp, asize);
    return bp;
  }
  
  extendsize = MAX(asize,CHUNKSIZE);
  if ((bp = extend_heap(extendsize/WSIZE)) == NULL)
    return NULL;
  
  place(bp, asize);
  return bp;
} 

//
//
// Practice problem 9.9
//
// place - Place block of asize bytes at start of free block bp 
//         and split if remainder would be at least minimum block size
//
static void  place(void *bp, size_t asize)
{
  void *nxt_bp;
  size_t csize = GET_SIZE(HDRP(bp));

  if ((csize - asize) >= (2*DSIZE)) {
 
    remove_free_list(bp);
 
    PUT(HDRP(bp), PACK(asize, 1));
    PUT(FTRP(bp), PACK(asize, 1));
 
    nxt_bp = NEXT_BLKP(bp);
 
    PUT(HDRP(nxt_bp), PACK(csize-asize, 0));
    PUT(FTRP(nxt_bp), PACK(csize-asize, 0));
 
    add_free_list(nxt_bp);
  }
 
  else {
  PUT(HDRP(bp), PACK(csize, 1));
  PUT(FTRP(bp), PACK(csize, 1));
  remove_free_list(bp);
  }
}
 


//
// mm_realloc -- implemented for you
//
void *mm_realloc(void *ptr, size_t size)
{

  void *oldptr = ptr;
  void *newptr;
  void *temp;
  size_t tempsize;
  size_t copySize;
  size_t prev_alloc = GET_ALLOC(FTRP(PREV_BLKP(oldptr)));
  size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(oldptr)));
  size_t size_prev = GET_SIZE(HDRP(oldptr));
  int increase;
  
  if(size_prev < size + DSIZE)
    increase = 1;
  else
    increase = 0;
  
  if (size == 0){
    mm_free(ptr);
    newptr = 0;
    return NULL;
  }
    
  if (oldptr == NULL)	
    return mm_malloc(size);

  if(increase == 0 && (size_prev - size - DSIZE) > (2*DSIZE)){
    
    if (size <= DSIZE)
      size = 2*DSIZE;
    else
      size = DSIZE * ((size + (DSIZE) + (DSIZE-1)) / DSIZE);

    if((size_prev - size) > (2*DSIZE)){

      PUT(HDRP(oldptr), PACK(size, 1));
      PUT(FTRP(oldptr), PACK(size, 1));
      newptr = oldptr;
      oldptr = (NEXT_BLKP(newptr));
      PUT(HDRP(oldptr), PACK(size_prev - size, 0));
      PUT(FTRP(oldptr), PACK(size_prev - size, 0));
      coalesce(oldptr);

      return newptr;
    }
  }

  if(increase == 0) {
    return ptr;
  }
    
  else {
    
    if (next_alloc == 0 && prev_alloc == 0 && ((GET_SIZE(HDRP(PREV_BLKP(oldptr)))) + (GET_SIZE(HDRP(NEXT_BLKP(oldptr)))) + size_prev) >= (size + DSIZE)){
    
      newptr = PREV_BLKP(oldptr);
      temp = NEXT_BLKP(oldptr);
      tempsize = GET_SIZE(FTRP(newptr)) + GET_SIZE(FTRP(temp));
      remove_free_list(PREV_BLKP(oldptr));
      remove_free_list(NEXT_BLKP(oldptr));
    
      if (size <= DSIZE)
	size = 2*DSIZE;
      else
	size = DSIZE * ((size + (DSIZE) + (DSIZE-1)) / DSIZE);

      if((tempsize + size_prev) < (size + 2*DSIZE))
	size = tempsize + size_prev;
    
      PUT(HDRP(newptr), PACK(size, 1));
      copySize = GET_SIZE(HDRP(oldptr));
      memcpy(newptr, oldptr, copySize);
      PUT(FTRP(newptr), PACK(size, 1));
    
      if((tempsize + size_prev) >= (size + 2*DSIZE)){

	temp = NEXT_BLKP(newptr);
	PUT(HDRP(temp), PACK(tempsize + size_prev - size, 0));
	PUT(FTRP(temp), PACK(tempsize + size_prev - size, 0));
	add_free_list(temp);
      }
      return newptr;
    }
    
    else if(next_alloc == 0 && ((GET_SIZE(HDRP(NEXT_BLKP(oldptr)))) + size_prev) >= (size + DSIZE)){
    
      temp = NEXT_BLKP(oldptr);
      tempsize = GET_SIZE(FTRP(temp));
      remove_free_list(NEXT_BLKP(ptr));
    
      if (size <= DSIZE)
	size = 2*DSIZE;
      else
	size = DSIZE * ((size + (DSIZE) + (DSIZE-1)) / DSIZE);

      if((tempsize + size_prev) < (size + 2*DSIZE))
	size = tempsize + size_prev;
      PUT(HDRP(oldptr), PACK(size, 1));
      PUT(FTRP(oldptr), PACK(size, 1));
    
      if((tempsize + size_prev) >= (size + 2*DSIZE)){
    
	newptr = NEXT_BLKP(oldptr);
	PUT(HDRP(newptr), PACK(tempsize + size_prev - size, 0));
	PUT(FTRP(newptr), PACK(tempsize + size_prev - size, 0));

	add_free_list(newptr);
      }
      return oldptr;
    }
    
    else if(prev_alloc == 0 && ((GET_SIZE(HDRP(PREV_BLKP(oldptr)))) + size_prev) >= (size + DSIZE)){
    
      newptr = PREV_BLKP(oldptr);
      tempsize = GET_SIZE(FTRP(newptr));   
      remove_free_list(PREV_BLKP(oldptr));
    
      if (size <= DSIZE)
	size = 2*DSIZE;
      else
	size = DSIZE * ((size + (DSIZE) + (DSIZE-1)) / DSIZE);

      if((tempsize + size_prev) < (size + 2*DSIZE))
	size = tempsize + size_prev;

      PUT(HDRP(newptr), PACK(size, 1));   
      copySize = GET_SIZE(HDRP(oldptr));
      memcpy(newptr, oldptr, copySize);
      PUT(FTRP(newptr), PACK(size, 1));
    
      if((tempsize + size_prev) >= (size + 2*DSIZE)){
    
	temp = NEXT_BLKP(newptr);
	PUT(HDRP(temp), PACK(tempsize + size_prev - size, 0));
	PUT(FTRP(temp), PACK(tempsize + size_prev - size, 0));
	add_free_list(temp);

      }

      return newptr;

    }     
    newptr = mm_malloc(size);
    copySize = GET_SIZE(HDRP(oldptr));

    if (size < copySize)
      copySize = size;

    memcpy(newptr, oldptr, copySize);
    mm_free(oldptr);

    return newptr;
  }
}


//
// mm_checkheap - Check the heap for consistency 
//
void mm_checkheap(int verbose) 
{
  //
  // This provided implementation assumes you're using the structure
  // of the sample solution in the text. If not, omit this code
  // and provide your own mm_checkheap
  //
  void *bp = heap_listp;
  
  if (verbose) {
    printf("Heap (%p):\n", heap_listp);
  }

  if ((GET_SIZE(HDRP(heap_listp)) != DSIZE) || !GET_ALLOC(HDRP(heap_listp))) {
	printf("Bad prologue header\n");
  }
  checkblock(heap_listp);

  for (bp = heap_listp; GET_SIZE(HDRP(bp)) > 0; bp = NEXT_BLKP(bp)) {
    if (verbose)  {
      printblock(bp);
    }
    checkblock(bp);
  }
     
  if (verbose) {
    printblock(bp);
  }

  if ((GET_SIZE(HDRP(bp)) != 0) || !(GET_ALLOC(HDRP(bp)))) {
    printf("Bad epilogue header\n");
  }
}

static void printblock(void *bp) 
{
  size_t hsize, halloc, fsize, falloc;

  hsize = GET_SIZE(HDRP(bp));
  halloc = GET_ALLOC(HDRP(bp));  
  fsize = GET_SIZE(FTRP(bp));
  falloc = GET_ALLOC(FTRP(bp));  
    
  if (hsize == 0) {
    printf("%p: EOL\n", bp);
    return;
  }

  printf("%p: header: [%d:%c] footer: [%d:%c]\n", bp, 
	 (int) hsize, (halloc ? 'a' : 'f'), 
	 (int) fsize, (falloc ? 'a' : 'f')); 
}

static void checkblock(void *bp) 
{
  if ((size_t)bp % 8) {
    printf("Error: %p is not doubleword aligned\n", bp);
  }
  if (GET(HDRP(bp)) != GET(FTRP(bp))) {
    printf("Error: header does not match footer\n");
  }
}

static void remove_free_list(void *bp)
{	
  int minlist;
  int size;
 
  free_count--;
 
  size = GET_SIZE(HDRP(bp));
 
  minlist = size / 50;
  if(minlist > 83)
    minlist = 83;
 
  if(GET(bp) == 0 && GET(bp + WSIZE) == 0) {
    PUT(heap_listp+(minlist * WSIZE), 0);
 
    if(global_minlist == minlist) {
      if(free_count > 0){
	int i;
	for (i = minlist; GET(heap_listp+(i * WSIZE)) == 0; i++);
	global_minlist = i;
      }
      else(global_minlist = 100);
    }
  }
 
  else if (GET(bp) == 0 && GET(bp + WSIZE) != 0){
    PUT(heap_listp+(minlist * WSIZE), GET(bp + WSIZE));
    PUT((char *)GET(bp + WSIZE), 0);
  }
 
  else if (GET(bp) != 0 && GET(bp + WSIZE) == 0)
    PUT(((char *)GET(bp) + WSIZE), 0);
 
  else {
    PUT(((char *)GET(bp) + WSIZE), GET(bp + WSIZE));	
    PUT(((char *)GET(bp + WSIZE)), GET(bp));	
  }
}
 
 
/*
 * add_free_list - adds a given pointer to the free list.
 * updates free count and global_min_list if necessary
 */
static void add_free_list(void *bp)
{	
  int minlist;
  void *temp_next;
  void *temp_cur;
  void *temp_prev;
  int size;
 
  free_count++;
 
  size = GET_SIZE(HDRP(bp));
 
  minlist = size / 50;
  if(minlist > 83)
    minlist = 83;

  if(global_minlist > minlist || global_minlist == 100)
    global_minlist = minlist; 

  temp_cur = (char *)GET(heap_listp + (minlist * WSIZE));

  if(temp_cur == 0){
    PUT(heap_listp + (minlist * WSIZE), (int)bp);	
    PUT(bp, 0);
    PUT(bp+WSIZE, 0);
  }

  else {
    temp_prev = (char *)GET(heap_listp + (minlist * WSIZE));

    for (; (int)temp_cur != 0 && GET_SIZE(HDRP(temp_cur)) < size; temp_cur = (char *)GET(temp_cur+WSIZE))
      temp_prev = temp_cur;

    temp_cur = temp_prev;

    temp_next = (char *)GET(temp_cur + WSIZE);

    PUT(temp_cur + WSIZE, (int)bp);

    if((int)temp_next != 0)
      PUT(temp_next, (int)bp);

    PUT(bp, (int)temp_cur);
    PUT(bp+WSIZE, (int)temp_next);

  }
}

