#include <stdlib.h>
#include <stdio.h>
#include "bt.h"

typedef struct node BTNode;
typedef struct queue Queue;

struct node
{
    BTNode *left;
    BTNode *right;
    Node *key;
};

BTNode *btnode_create(Node *key){
    BTNode *n = (BTNode*)calloc(1,sizeof(BTNode));
    n->left = n->right = NULL;
    n->key = key;
    return n;
}

BTNode *btnode_insert(BTNode *root, Node *key, int (*cmp_fn)(void *, void *)) {
    if (!root) return btnode_create(key);

    int cmp = cmp_fn(key, root->key);
    if (cmp < 0)
        root->left = btnode_insert(root->left, key, cmp_fn);
    else
        root->right = btnode_insert(root->right, key, cmp_fn);
    
    return root;
}

BTNode *btnode_min(BTNode *root) {
    BTNode *curr = root;
    while (curr && curr->left) {
        curr = curr->left;
    }
    return curr;
}

BTNode *btnode_remove_min(BTNode *root) {
    if (!root) return NULL;
    if (!root->left) {
        BTNode *right_subtree = root->right;
        free(root);
        return right_subtree;
    }
    root->left = btnode_remove_min(root->left);
    return root;
}

BTNode *btnode_remove(BTNode *root, Node *key, int (*cmp_fn)(void *, void *)) {
    if (!root) return NULL;
    
    int cmp = cmp_fn(key, root->key);
    if (cmp < 0)
        root->left = btnode_remove(root->left, key, cmp_fn);
    else if (cmp > 0)
        root->right = btnode_remove(root->right, key, cmp_fn);
    else {
        if (!root->left) {
            BTNode *right_subtree = root->right;
            free(root);
            return right_subtree;
        } 
        else if (!root->right) {
            BTNode *left_subtree = root->left;
            free(root);
            return left_subtree;
        }
        BTNode *min_node = btnode_min(root->right);
        root->key = min_node->key;
        root->right = btnode_remove(root->right, min_node->key, cmp_fn);
    }
    return root;
}

void btnode_destroy(BTNode *n){
    if(n != NULL){
        btnode_destroy(n->left);
        btnode_destroy(n->right);
        free(n);
    }
}

int btnode_height(BTNode *root) {
    if (!root)
        return 0;
    else {
        int left_height = btnode_height(root->left);
        int right_height = btnode_height(root->right);
        if (left_height >= right_height)
            return left_height + 1;
        else
            return right_height + 1;
    }
    return -1;
}

void rec_node_postorder(BTNode *root)
{
    if(!root)
        return;
    rec_node_postorder(root->left);
    rec_node_postorder(root->right);
    //printf("%d\n",root->key);
    
}

void rec_node_preorder(BTNode *root)
{
    if(!root)
        return;
    //printf("%d\n",root->key);
    rec_node_preorder(root->left);
    rec_node_preorder(root->right);
    
}

void rec_node_inorder(BTNode *root)
{
    if(!root)
        return;

    rec_node_inorder(root->left);
    //printf("%d\n",root->key);
    rec_node_inorder(root->right);
}

struct BinaryTree
{
    BTNode *root;
    int size;
    int (*cmp_fn)(void *, void *);
};

BinaryTree *bt_create(int (*cmp_fn)(void *, void *))
{
    BinaryTree *bt = (BinaryTree*)calloc(1,sizeof(BinaryTree));
    bt->root = NULL;
    bt->size = 0;
    bt->cmp_fn = cmp_fn;
    return bt;
}

void rec_visit(BinaryTree *t, void (*visit)(BinaryTree*)){
    visit(t);
}

void rec_bst_preorder(BinaryTree *bt)
{
    rec_node_preorder(bt->root);
}

void rec_bst_inorder(BinaryTree *bt)
{
    rec_node_inorder(bt->root);
}

void rec_bst_postorder(BinaryTree *bt)
{
    rec_node_postorder(bt->root);
}

int bt_height(BinaryTree *bt){
    if(bt->size == 0){
        return -1;
    }
    else if(bt->size == 1){
        return 0;
    }
    return btnode_height(bt->root) - 1; 
}

void bt_insert(BinaryTree *bt, Node *key) {
    bt->root = btnode_insert(bt->root, key, bt->cmp_fn);
    bt->size++;
}

Node *bt_min(BinaryTree *bt){
    return btnode_min(bt->root)->key;
}
/*
void bt_iter_insert(BinaryTree *bt, Node *key){
    if(bt->root != NULL){
        BTNode *n = btnode_create(key);
        BTNode *root = bt->root;
        BTNode *iter = root;

        while(iter != NULL){
            if(iter->key < n->key){
                if(iter->right != NULL){
                    iter = iter->right;
                }
                else{
                    iter->right = n;
                    iter = NULL;
                }
            }
            else if(iter->key > n->key){
                if(iter->left != NULL){
                    iter = iter->left;
                }
                else{
                    iter->left = n;
                    iter = NULL;
                }
            }
        }
    }
    else{
        bt->root = btnode_create(key);
    }
    bt->size++;
}
*/
int bt_is_empty(BinaryTree *bt) {
    return bt->size == 0;
}


void bt_remove(BinaryTree *bt, Node *key){
    bt->root = btnode_remove(bt->root, key, bt->cmp_fn);
    bt->size--;
}

void bt_remove_min(BinaryTree *bt){
    bt->root = btnode_remove_min(bt->root);
    bt->size--;
}

void bt_destroy(BinaryTree *bt)
{
    btnode_destroy(bt->root);
    free(bt);
}

void bt_print(BinaryTree *bt)
{   
    rec_node_preorder(bt->root);
}

typedef struct queue_node QueueNode;

struct queue_node {
    QueueNode *next;

    BTNode *bt_node;
};

QueueNode *queue_btnode_create(BTNode *bst_node){
    QueueNode *n = (QueueNode*)malloc(sizeof(QueueNode));
    n->bt_node = bst_node;
    n->next = NULL;
    return n;
}

void queue_node_free(QueueNode *n, int size){
    QueueNode *next = n->next;
    while(size != 0){
        free(n);
        next = next->next;
        size--;
    }
    return;
}

struct queue
{
    QueueNode *first, *last;
    int size;
};

Queue *queue_init(){
    Queue *q = (Queue*)calloc(1,sizeof(Queue));
    q->first = NULL;
    q->last = NULL;
    q->size = 0;
    return q;
}

void queue_push(Queue *q, BTNode *n){
    QueueNode *tn = queue_btnode_create(n);
    if(!q->first)
        q->first = tn;
    else{
        q->last->next = tn;
    }
    q->last = tn;
    q->size++;
}

BTNode *queue_pop(Queue *q){
    if(q->size == 1){
        QueueNode *n = q->first;
        q->first = q->last = NULL;
        q->size--;
        BTNode *bt_node = n->bt_node;
        free(n);
        return bt_node;
    }

    QueueNode *n = q->first;
    while(n->next != q->last && n->next){
        n = n->next;
    }
    q->size--;
    n->next = NULL;
    BTNode *bt_node = q->last->bt_node;
    free(q->last);
    q->last = n;
    return bt_node;
}

BTNode *queue_pop_front(Queue *q){
    QueueNode *n = q->first;
    if(!n)
        return NULL;
    if(n == q->last){
        q->first = q->last = NULL;
    }
    else{
        q->first = n->next;
    }
    q->size--;
    BTNode *bt_node = n->bt_node;
    free(n);
    return bt_node;
}

int queue_empty(Queue *q){
    if(q->size != 0)
        return 0;
    return 1;
}

BTNode *queue_peek(Queue *q){
    return q->last->bt_node;
}

void queue_free(Queue *q){
    if(q->size != 0)
        queue_node_free(q->first, q->size);
    free(q);
}

void iter_bst_preorder(BinaryTree *bt){
    BTNode *root = bt->root;
    if(!root)
        return;
    Queue *q = queue_init();
    queue_push(q,root);
    while(!queue_empty(q)){
        BTNode *n = queue_pop(q);
        //printf("%d\n",n->key);
        if(n->right){
            queue_push(q,n->right);
        }
        if(n->left){
            queue_push(q,n->left);
        }
    }
    queue_free(q);
}

void iter_bst_postorder(BinaryTree *bt){
    BTNode *n = bt->root;
    if(!n)
        return;
    Queue *q = queue_init();
    BTNode *last_node = NULL;
    while(!queue_empty(q) || n != NULL){
        if(n != NULL){
            queue_push(q,n);
            n = n->left;
        }
        else{
            BTNode *peek_node = queue_peek(q);
            if(peek_node->right != NULL && last_node != peek_node->right){
                n = peek_node->right;
            }
            else{
                //printf("%d\n", peek_node->key);
                last_node = queue_pop(q);
            }
        }
    }
}

void iter_bst_inorder(BinaryTree *bt){
    BTNode *root = bt->root;
    if(!root)
        return;
    Queue *q = queue_init();
    BTNode *n = root;
    while(!queue_empty(q) || n != NULL){
        
        if(n){
            queue_push(q, n);
            n = n->left;
        }
        else{
            n = queue_pop(q);
            //printf("%d\n",n->key);
            n = n->right;
        }
    }
    queue_free(q);
}

void iter_bst_levelorder(BinaryTree *bt){
    BTNode *n = bt->root;
    Queue *q = queue_init();
    queue_push(q,n);
    while(!queue_empty(q)){
        n = queue_pop_front(q);
        if(n->left)
            queue_push(q,n->left);
        if(n->right)
            queue_push(q,n->right);
    }
    queue_free(q);
}