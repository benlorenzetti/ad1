#ifndef XOR_TREE_H
#define XOR_TREE_H

#include "pivlib.h"

#define XOR_TREE_PTR_SIZE 6
#define XOR_TREE_MIN_ALIGNMENT (1 << 2)     // reserve 2 bits of ptrs
#define XOR_TREE_FLAGS_MASK (1<<0 | 1<<1)   // use bits 0&1 for flags 
#define XOR_TREE_LEAF_FLAG (1 << 0)         /* bit0 on r&l ptrs */
#define XOR_TREE_RED_BLACK_FLAG (1 << 1)    /* bit1 of rchild ptr */
#define XOR_TREE_LSIBLING_FLAG (1 << 1) /* bit1 of lchild ptr */

#define XOR_TREE_PTR_MASK ((((Nint)(1 << XOR_TREE_PTR_SIZE))-1)-3)

struct xor_tree_iter {
    struct xor_node *node;
    struct xor_node *parent;
};

struct xor_node {
    Wchar rchild;
    Wchar pad1[XOR_TREE_PTR_SIZE - 1];
    Wchar lchild;
    Wchar pad2[XOR_TREE_PTR_SIZE - 1];
};

/*  lchild() and rchild() functions return either (a pointer to a
    xor_node subtree or a leaf element) xor 0 if no child.
        Prior to calling, one should test if the child is expected to
    be a leaf or subtree; use the expression:
        (xor_tree_iter.node->rchild & XOR_TREE_LEAF_FLAG)
*/
Nint xor_tree_lchild(struct xor_tree_iter);
Nint xor_tree_rchild(struct xor_tree_iter);
Nint xor_tree_gparent(struct xor_tree_iter);

Nint xor_tree_grandparent(struct xor_tree_iter iter) {
    bool node_is_lchild = iter.node->lchild & XOR_TREE_LSIBLING_MASK;
    Nint lineage;
    if(node_is_lchild)
        r2r_memcpy((Nint)(&lineage), (Nint)(&(iter.parent->lchild)), XOR_TREE_PTR_SIZE, 1);
    else
        r2r_memcpy((Nint)(&lineage), (Nint)(&(iter.parent->rchild)), XOR_TREE_PTR_SIZE, 1);

    return ((Nint)iter.node) ^ lineage;
}

Nint xor_tree_lchild(struct xor_tree_iter iter) {
    Nint lchild;
    r2r_memcpy((Nint)(&lchild), (Nint)(&(iter.node->lchild)), XOR_TREE_PTR_SIZE, 1);
    lchild = lchild & XOR_TREE_PTR_MASK;
    lchild = lchild ^ iter.parent;
    return lchild;
}

Nint xor_tree_rchild(struct xor_tree_iter iter) {
    Nint rchild;
    r2r_memcpy((Nint)(&rchild), (Nint)(&(iter.node->rchild)), XOR_TREE_PTR_SIZE, 1);
    rchild = rchild & XOR_TREE_PTR_MASK;
    rchild = rchild ^ iter.parent;
    return rchild;
}

#endif
