#ifndef _MB_NODE_H_
#define _MB_NODE_H_

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

//A multi-bit node data structure

#if __SIZEOF_LONG__ == 8
#define BITMAP_TYPE uint64_t
#define STRIDE 9
#define BITMAP_BITS (1<<STRIDE)
#else
#define BITMAP_TYPE uint32_t
#define STRIDE 5 
#define BITMAP_BITS (1<<STRIDE)
#endif

#define POINT(X) ((struct mb_node*)(X))
#define NODE_SIZE  (sizeof(struct mb_node))
#define FAST_TREE_FUNCTION
//#define COMPRESS_NHI

// struct mb_node{
//     BITMAP_TYPE external;
//     BITMAP_TYPE internal;
//     void     *child_ptr;
// }__attribute__((aligned(8)));

struct mb_node{
    uint64_t data;
}__attribute__((aligned(8)));

//GCC optimize
#define likely(x)       __builtin_expect((x),1)
#define unlikely(x)     __builtin_expect((x),0)


#endif
