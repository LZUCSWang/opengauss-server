/*
 * Copyright (c) 2020 Huawei Technologies Co.,Ltd.
 *
 * openGauss is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan PSL v2.
 * You may obtain a copy of Mulan PSL v2 at:
 *
 *          http://license.coscl.org.cn/MulanPSL2
 *
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PSL v2 for more details.
 * ---------------------------------------------------------------------------------------
 * 
 * binaryheap.h
 *        A simple binary heap implementation
 * 
 * 
 * IDENTIFICATION
 *        src/include/lib/binaryheap.h
 *
 * ---------------------------------------------------------------------------------------
 */

#ifndef BINARYHEAP_H
#define BINARYHEAP_H

/*
 * For a max-heap, the comparator must return <0 iff a < b, 0 iff a == b,
 * and >0 iff a > b.  For a min-heap, the conditions are reversed.
 */
typedef int (*binaryheap_comparator)(Datum a, Datum b, void* arg);

/*
 * binaryheap
 *
 *		bh_size			how many nodes are currently in "nodes"
 *		bh_space		how many nodes can be stored in "nodes"
 *		bh_has_heap_property	no unordered operations since last heap build
 *		bh_compare		comparison function to define the heap property
 *		bh_arg			user data for comparison function
 *		bh_nodes		variable-length array of "space" nodes
 */
typedef struct binaryheap {
    int bh_size;            /* number of nodes currently in heap */
    int bh_space;           /* current size of bh_nodes array */
    bool bh_has_heap_property; /* debugging cross-check */
    binaryheap_comparator bh_compare;   /* comparison function */
    void* bh_arg;               /* extra argument for comparison function */
    Datum bh_nodes[FLEXIBLE_ARRAY_MEMBER];  /* VARIABLE LENGTH ARRAY */
} binaryheap;

extern binaryheap* binaryheap_allocate(int capacity, binaryheap_comparator compare, void* arg); /* allocates memory */
extern void binaryheap_reset(binaryheap* heap); /* reset heap, but not free memory*/
extern void binaryheap_free(binaryheap* heap);  /* frees memory */
extern void binaryheap_add_unordered(binaryheap* heap, Datum d);
/* add element to heap ,but may violate heap property */

extern void binaryheap_build(binaryheap* heap); /* builds heap property */
extern void binaryheap_add(binaryheap* heap, Datum d);  /*add element to heap*/

extern Datum binaryheap_first(binaryheap* heap);        /* returns first element */
extern Datum binaryheap_remove_first(binaryheap* heap);     /* removes first element */
extern void binaryheap_replace_first(binaryheap* heap, Datum d);    /* replaces first element */

#define binaryheap_empty(h) ((h)->bh_size == 0) /* judge whether heap is empty*/

#endif /* BINARYHEAP_H */
