#include <stdlib.h>

typedef struct Node{
    int key;
    struct Node *parent;
    struct Node *left;
    struct Node *right;
}Node;

Node* tree_minimum(Node *root)
{
    Node *x, *y;
    y=root;
    x=root->left;
    while (x)
    {
        y=x;
        x=x->left;
    }
    return y;
}

Node* tree_maximum(Node *root)
{
    Node *x, *y;
    y=root;
    x=root->right;
    while (x)
    {
        y=x;
        x=x->right;
    }
    return y;
}

Node* tree_successor(Node *root)
{
    Node *x, *y;
    y=root->right;
    if (y)
    {
        return tree_minimum(y);
    }
    else
    {
        x=root;
        y=x->parent;
        while (y && y->right==x)
        {
            x=y;
            y=x->parent;
        }
        return y;
    }
}

Node* tree_search(Node *root, int key)
{
    Node *x;
    x=root;
    while (x && x->key != key)
    {
        if (x->key < key)
            x=x->right;
        else
            x=x->left;
    }
    return x;
}

void tree_insert(Node **root, int key)
{
    Node *node = *root;
    Node *parent = NULL;
    while (node)
    {
        parent = node;
        if (key < node->key)
            node = node->left;
        else if (key > node->key)
            node = node->right;
        else
            return;
    }
    node = (Node *) malloc(sizeof(Node));
    if (!parent) *root= node;
    else if (parent->key < key) parent->right = node;
    else parent->left = node;
    node -> key = key;
    node ->left = NULL;
    node -> right = NULL;
    node ->parent = parent;
}

Node* find_successor(Node *root, int key)
{
    Node *node;
    node = tree_search(root, key);
    if (node)
    {
        return tree_successor(node);
    }
    else return node;
}

Node* tree_delete(Node **root, Node *node)
{
    Node *x, *y;
    if (!node)
        return node;
    if (!node->left || !node->right)
    {
        y=node;
    }
    else
    {
        y=tree_successor(node);
    }
    if (y->left)
        x=y->left;
    else
        x=y->right;
    if (x)
        x->parent = y->parent;
    if (!y->parent)
    {
        *root=x;
    }
    else 
    {
        if (y->parent->left==y)
            y->parent->left=x;
        else
            y->parent->right=x;
    }
    if (y!=node)
    {
        node->key = y->key;
    }
    return y;
}

Node* find_in_order_successor(Node *root, int key)
{
    Node *node = root;
    Node *prev = node;
    Node *rec = NULL;
    while (node)
    {
        if (node->key > key)
        {
            prev = node;
            rec = node;
            node = node->left;
        }
        else if (node->key < key)
        {
            prev = node;
            node = node->right;
        }
        else
        {           
            if (node->right)
            {
                node = node->right;
                while (node->left)
                {
                    node = node->left;
                }
                return node;
            }
            else
            {
                return rec;
                /*while(prev!=NULL && node==prev->right)
                {
                    node=node->parent;
                    prev=node->parent;
                }
                if (prev == NULL)
                    return NULL;
                else return prev;*/
            }
        }
    }
    return NULL; 
}

void free_tree(Node *root)
{
    if (root)
    {
        if (root->left) free_tree(root->left);
        if (root->right) free_tree(root->right);
        free(root);
    }
    return;
}
