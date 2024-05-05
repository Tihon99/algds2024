#include <stdio.h>
#include <stdlib.h>
#include "lab2.h"

int main() {
    struct Node* root = NULL;

    // Test insertion
    insert(&root, 10);
    insert(&root, 20);
    insert(&root, 30);
    insert(&root, 40);
    insert(&root, 50);

    printf("Inorder traversal after insertion: ");
    inorderTraversal(root);
    printf("\n");

    // Test deletion
    deleteNode(&root, 20);
    deleteNode(&root, 30);

    printf("Inorder traversal after deletion: ");
    inorderTraversal(root);
    printf("\n");

    insert(&root, 20);

    printf("Inorder traversal after insertion: ");
    inorderTraversal(root);
    printf("\n");

    return 0;
}