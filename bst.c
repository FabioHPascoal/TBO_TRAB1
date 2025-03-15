#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "bst.h"

struct Node
{
    void *data;
    struct Node *left;
    struct Node *right;
};

struct BST
{
    Node *root;
    int node_count;
    CmpFn cmp_fn;
};

Node *node_construct(void *data, Node *left, Node *right) {
    Node *node = (Node *)malloc(sizeof(Node));

    node->data = data;
    node->left = left;
    node->right = right;

    return node;
}

void node_destruct(Node *node) {
    free(node);
}

BST *bst_construct(CmpFn cmp_fn) {

    BST *bst = (BST *)malloc(sizeof(BST));
    bst->root = NULL;
    bst->node_count = 0;
    bst->cmp_fn = cmp_fn;

    return bst;
}

void node_destruct_recursive(Node *node) {
    
    if (node == NULL) return;

    node_destruct_recursive(node->left);
    node_destruct_recursive(node->right);

    node_destruct(node);
}

void bst_destroy(BST *bst){
    if (bst == NULL) return;

    node_destruct_recursive(bst->root);
    free(bst);
}

void bst_add(BST *bst, void *data) {
    bst->node_count++;

    Node *newNode = node_construct(data, NULL, NULL);

    if (!bst->root){
        bst->root = newNode;
        return;
    }

    Node *node = bst->root;

    while (1){
        if (bst->cmp_fn(data, node->data) < 0){
            if (!node->left){
                node->left = newNode;
                break;
            }
            else{
                node = node->left;
            }
        }
        else if (bst->cmp_fn(data, node->data) > 0){
            if (!node->right){
                node->right = newNode;
                break;
            }
            else{
                node = node->right;
            }
        }
        else{
            bst->node_count--;
            node_destruct(newNode);
            break;
        }
    }
}

// Removed node has no children
void case_1_removal(BST *bst, Node *node, Node *parent){
    if (!parent){
        bst->root = NULL;
    }
    else if ((parent->left != NULL)&&(!bst->cmp_fn(parent->left->data, node->data))){
        parent->left = NULL;
    }
    else{
        parent->right = NULL;
    }
}

// Removed node has one child
void case_2_removal(BST *bst, Node *node, Node *parent){
    if (!node->left){
        if (!parent){
            bst->root = node->right;
        }
        else if ((parent->left != NULL)&&(!bst->cmp_fn(parent->left->data, node->data))){
            parent->left = node->right;
        }
        else{
            parent->right = node->right;
        }
    }
    else{
        if (!parent){
            bst->root = node->left;
        }
        else if ((parent->left != NULL)&&(!bst->cmp_fn(parent->left->data, node->data))){
            parent->left = node->right;
        }
        else{
            parent->right = node->left;
        }
    }
}

void *remove_from_node(BST *bst, Node *currentNode, Node *parentNode, bool data_return){    
    if (!currentNode->left && !currentNode->right){
        case_1_removal(bst, currentNode, parentNode);
    }

    else if (!currentNode->left ^ !currentNode->right){
        case_2_removal(bst, currentNode, parentNode);
    }
    
    if (data_return){
        void *data = currentNode->data;
        node_destruct(currentNode);
        return data;
    }
    
    node_destruct(currentNode);
    return NULL;
}

// Removed node has two children
void case_3_removal(BST *bst, Node *node, Node *parent){
    Node *successorNode = node->right;
    Node *parentNode = node;

    while (successorNode->left != NULL){
        parentNode = successorNode;
        successorNode = successorNode->left;
    }

    void *newData = successorNode->data;

    remove_from_node(bst, successorNode, parentNode, false);

    node->data = newData;
}

void bst_remove(BST *bst, void *data){
    Node *currentNode = bst->root;
    Node *parentNode = NULL;

    while ((currentNode != NULL) && (bst->cmp_fn(currentNode->data, data) != 0)){
        parentNode = currentNode;

        if (bst->cmp_fn(data, currentNode->data) < 0) currentNode = currentNode->left;
        else currentNode = currentNode->right;
    }

    if (!currentNode) return;

    bst->node_count--;
    
    if (!currentNode->left && !currentNode->right){
        case_1_removal(bst, currentNode, parentNode);
    }

    else if (!currentNode->left ^ !currentNode->right){
        case_2_removal(bst, currentNode, parentNode);
    }

    else{
        case_3_removal(bst, currentNode, parentNode);
        return;
    }
    
    node_destruct(currentNode);
}

void *bst_min(BST *bst){
    Node *node = bst->root;

    while (node->left != NULL){
        node = node->left;
    }

    return node->data;
}

void *bst_max(BST *bst){
    Node *node = bst->root;

    while (node->right != NULL){
        node = node->right;
    }

    return node->data;
}

void *bst_pop_min(BST *bst){
    Node *parentNode = NULL;
    Node *node = bst->root;

    bst->node_count--;

    while (node->left != NULL){
        parentNode = node;
        node = node->left;
    }

    return remove_from_node(bst, node, parentNode, true);
}

void *bst_pop_max(BST *bst){
    Node *parentNode = NULL;
    Node *node = bst->root;

    bst->node_count--;
    
    while (node->right != NULL){
        parentNode = node;
        node = node->right;
    }

    return remove_from_node(bst, node, parentNode, true);
}

int bst_node_count(BST *bst){
    return bst->node_count;
}

bool bst_is_empty(BST *bst) {
    if (bst->node_count > 0) return false;
    return true;
}