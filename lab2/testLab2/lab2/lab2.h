#pragma once

enum Color { RED, BLACK };

struct Node {
    int data;
    enum Color color;
    struct Node* parent;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int data);

void rotateLeft(struct Node** root, struct Node* x);

void rotateRight(struct Node** root, struct Node* y);

void fixInsertion(struct Node** root, struct Node* z);

void insert(struct Node** root, int data);

struct Node* minimum(struct Node* x);

void fixDelete(struct Node** root, struct Node* x);

void transplant(struct Node** root, struct Node* u, struct Node* v);

void deleteNode(struct Node** root, int data);

void inorderTraversal(struct Node* root);
