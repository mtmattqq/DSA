#include <algorithm>
#include <cstdint>
#include <utility>

using i64 = int64_t;

// === AVL TREE ===
struct AvlNode {
    AvlNode *lch, *rch;
    i64 val, height;
};

AvlNode* ANodeNew(i64 val);
i64 ANodeGetHeight(AvlNode*);
i64 ANodeGetBananceFactor(AvlNode*);
AvlNode* ANodeRightRotation(AvlNode*);
AvlNode* ANodeLeftRotation(AvlNode*);
AvlNode* ANodeInsert(AvlNode*, i64 val);
AvlNode* ANodeErase(AvlNode*, i64 val);
AvlNode* ANodeBanalce(AvlNode*);
void ANodeUpdateHeight(AvlNode*);
void ANodeDelete(AvlNode *sub_tree);
AvlNode* ANodeFindMax(AvlNode*);
AvlNode* ANodeRemoveMax(AvlNode *node);

struct AvlTree{
    AvlNode *root;
};

AvlTree AvlTreeNew();
void AvlTreeDelete(AvlTree*);
void AvlInsert(AvlTree*, i64 val);
void AvlErase(AvlTree*, i64 val);
i64 AvlFindMax(AvlTree*);

// === AVL TREE ===
AvlNode* ANodeNew(i64 val) {
    AvlNode *new_node = new AvlNode;
    new_node->lch = new_node->rch = nullptr;
    new_node->val = val;
    new_node->height = 0;
    return new_node;
}

i64 ANodeGetHeight(AvlNode *node) {
    if(node == nullptr) {
        return -1;
    }
    return node->height;
}

i64 ANodeGetBananceFactor(AvlNode *node) {
    if(node == nullptr) {
        return 0;
    }
    return ANodeGetHeight(node->lch) - ANodeGetHeight(node->rch);
}

AvlNode* ANodeRightRotation(AvlNode *node) {
    AvlNode *pivot = node->lch, *tp = pivot->rch;
    pivot->rch = node;
    node->lch = tp;
    ANodeUpdateHeight(node);
    ANodeUpdateHeight(pivot);
    return pivot;
}

AvlNode* ANodeLeftRotation(AvlNode *node) {
    AvlNode *pivot = node->rch, *tp = pivot->lch;
    pivot->lch = node;
    node->rch = tp;
    ANodeUpdateHeight(node);
    ANodeUpdateHeight(pivot);
    return pivot;
}

void ANodeUpdateHeight(AvlNode *node) {
    if(node == nullptr) {
        return;
    }
    node->height = std::max(ANodeGetHeight(node->lch), ANodeGetHeight(node->rch)) + 1;
}

void ANodeDelete(AvlNode *node) {
    if(node == nullptr) return;
    ANodeDelete(node->lch);
    ANodeDelete(node->rch);
    free(node);
}

AvlNode* ANodeInsert(AvlNode *node, i64 val) {
    if(node == nullptr) {
        return ANodeNew(val);
    }
    if(node->val < val) {
        node->rch = ANodeInsert(node->rch, val);
    } else {
        node->lch = ANodeInsert(node->lch, val);
    }
    ANodeUpdateHeight(node);
    node = ANodeBanalce(node);
    return node;
}

AvlNode* ANodeErase(AvlNode *node, i64 val) {
    if(node == nullptr) return nullptr;
    if(node->val < val) {
        node->rch = ANodeErase(node->rch, val);
    } else if(node->val > val) {
        node->lch = ANodeErase(node->lch, val);
    } else { // node->val == val
        if(node->lch == nullptr && node->rch == nullptr) {
            free(node);
            return nullptr;
        } else if(node->lch == nullptr) {
            AvlNode *rch = node->rch;
            free(node);
            return rch;
        } else if(node->rch == nullptr) {
            AvlNode *lch = node->lch;
            free(node);
            return lch;
        } else {
            AvlNode *left_max = ANodeFindMax(node->lch);
            std::swap((left_max->val), (node->val));
            node->lch = ANodeRemoveMax(node->lch);
            ANodeUpdateHeight(node->lch);
        }
    }
    ANodeUpdateHeight(node);
    return ANodeBanalce(node);
}

AvlNode* ANodeRemoveMax(AvlNode *node) {
    if(node == nullptr) return nullptr;
    if(node->rch == nullptr) {
        AvlNode *tp = node->lch;
        free(node);
        return tp;
    }
    AvlNode *par = node;
    while(par->rch != nullptr && par->rch->rch != nullptr) {
        par = par->rch;
    }
    AvlNode *tp = par->rch->lch;
    free(par->rch);
    par->rch = tp;
    ANodeUpdateHeight(par->rch);
    return node;
}

AvlNode* ANodeBanalce(AvlNode *node) {
    i64 balance_factor = ANodeGetBananceFactor(node);
    if(balance_factor > 1) {
        if(ANodeGetBananceFactor(node->lch) < 0) {
            node->lch = ANodeLeftRotation(node->lch);
        }
        return ANodeRightRotation(node);
    } else if(balance_factor < -1) {
        if(ANodeGetBananceFactor(node->rch) > 0) {
            node->rch = ANodeRightRotation(node->rch);
        }
        return ANodeLeftRotation(node);
    }
    return node;
}

AvlNode* ANodeFindMax(AvlNode *node) {
    if(node == nullptr) return nullptr;
    AvlNode *ret = node;
    while(ret->rch != nullptr) {
        ret = ret->rch;
    }
    return ret;
}

AvlTree AvlTreeNew() {
    AvlTree new_avl_tree = {nullptr};
    return new_avl_tree;
}

void AvlTreeDelete(AvlTree *tree) {
    ANodeDelete(tree->root);
}

void AvlInsert(AvlTree *tree, i64 val) {
    tree->root = ANodeInsert(tree->root, val);
}

void AvlErase(AvlTree *tree, i64 val) {
    tree->root = ANodeErase(tree->root, val);
}

i64 AvlFindMax(AvlTree *tree) {
    AvlNode *ret = ANodeFindMax(tree->root);
    if(ret == nullptr) {
        return 0;
    }
    return ret->val;
}