#include <stdio.h>
#include <stdlib.h>
#include "lab2.h"

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->color = RED;
    newNode->parent = NULL;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void rotateLeft(struct Node** root, struct Node* x) {
    struct Node* y = x->right;
    x->right = y->left;
    if (y->left != NULL)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void rotateRight(struct Node** root, struct Node* y) {
    struct Node* x = y->left;
    y->left = x->right;
    if (x->right != NULL)
        x->right->parent = y;
    x->parent = y->parent;
    if (y->parent == NULL)
        *root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;
    x->right = y;
    y->parent = x;
}

void fixInsertion(struct Node** root, struct Node* z) {
    while (z->parent != NULL && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            struct Node* y = z->parent->parent->right;
            if (y != NULL && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->right) {
                    z = z->parent;
                    rotateLeft(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rotateRight(root, z->parent->parent);
            }
        }
        else {
            struct Node* y = z->parent->parent->left;
            if (y != NULL && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rotateRight(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rotateLeft(root, z->parent->parent);
            }
        }
    }
    (*root)->color = BLACK;
}

void insert(struct Node** root, int data) {
    struct Node* newNode = createNode(data);
    struct Node* y = NULL;
    struct Node* x = *root;
    while (x != NULL) {
        y = x;
        if (newNode->data < x->data)
            x = x->left;
        else
            x = x->right;
    }
    newNode->parent = y;
    if (y == NULL)
        *root = newNode;
    else if (newNode->data < y->data)
        y->left = newNode;
    else
        y->right = newNode;
    newNode->color = RED;
    fixInsertion(root, newNode);
}

struct Node* minimum(struct Node* x) {
    while (x->left != NULL)
        x = x->left;
    return x;
}

void fixDelete(struct Node** root, struct Node* x) {
    while (x != *root && (x == NULL || x->color == BLACK)) {
        if (x == x->parent->left) {
            struct Node* w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rotateLeft(root, x->parent);
                w = x->parent->right;
            }
            if ((w->left == NULL || w->left->color == BLACK) &&
                (w->right == NULL || w->right->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            }
            else {
                if (w->right == NULL || w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rotateRight(root, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                rotateLeft(root, x->parent);
                x = *root;
            }
        }
        else {
            struct Node* w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rotateRight(root, x->parent);
                w = x->parent->left;
            }
            if ((w->right == NULL || w->right->color == BLACK) &&
                (w->left == NULL || w->left->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            }
            else {
                if (w->left == NULL || w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    rotateLeft(root, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rotateRight(root, x->parent);
                x = *root;
            }
        }
    }
    if (x != NULL)
        x->color = BLACK;
}

void transplant(struct Node** root, struct Node* u, struct Node* v) {
    if (u->parent == NULL)
        *root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    if (v != NULL)
        v->parent = u->parent;
}

void deleteNode(struct Node** root, int data) {
    struct Node* z = *root;
    while (z != NULL) {
        if (z->data == data)
            break;
        else if (data < z->data)
            z = z->left;
        else
            z = z->right;
    }
    if (z == NULL)
        return;

    struct Node* y = z;
    enum Color y_original_color = y->color;
    struct Node* x = NULL;

    if (z->left == NULL) {
        x = z->right;
        transplant(root, z, z->right);
    }
    else if (z->right == NULL) {
        x = z->left;
        transplant(root, z, z->left);
    }
    else {
        y = minimum(z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent != z) {
            transplant(root, y, y->right);
            y->right = z->right;
            if (y->right != NULL) {
                y->right->parent = y;
            }
        }
        transplant(root, z, y);
        y->left = z->left;
        if (y->left != NULL) {
            y->left->parent = y;
        }
        y->color = z->color;
    }
    free(z);
    if (y_original_color == BLACK && x != NULL) {
        fixDelete(root, x);
    }
}



void inorderTraversal(struct Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}


