#include "pch.h"
#include "C:\Users\1\Documents\cplusplus\labs_git\lab2\testLab2\lab2\variant13.c"

// Тестирование функции вставки элементов в красно-черное дерево
TEST(RedBlackTreeTest, InsertionTest) {
    struct Node* root = NULL;

    // Вставка элементов
    insert(&root, 1);
    insert(&root, 8);
    insert(&root, 17);
    insert(&root, 13);
    insert(&root, 11);
    insert(&root, 6);
    insert(&root, 15);
    insert(&root, 25);
    insert(&root, 22);
    insert(&root, 27);

    // Проверка первого корня
    ASSERT_TRUE(root != NULL);
    ASSERT_EQ(root->data, 13);
    ASSERT_EQ(root->color, BLACK);


    // Проверка правой части дерева
    ASSERT_TRUE(root->right != NULL);
    ASSERT_EQ(root->right->data, 17);
    ASSERT_EQ(root->right->color, RED);

    ASSERT_TRUE(root->right->right != NULL);
    ASSERT_EQ(root->right->right->data, 25);
    ASSERT_EQ(root->right->right->color, BLACK); 

    ASSERT_TRUE(root->right->left != NULL);
    ASSERT_EQ(root->right->left->data, 15);
    ASSERT_EQ(root->right->left->color, BLACK);

    ASSERT_TRUE(root->right->right->right != NULL);
    ASSERT_EQ(root->right->right->right->data, 27);
    ASSERT_EQ(root->right->right->right->color, RED);

    ASSERT_TRUE(root->right->right->left != NULL);
    ASSERT_EQ(root->right->right->left->data, 22);
    ASSERT_EQ(root->right->right->left->color, RED);

    // Проверка левой части дерева
    ASSERT_TRUE(root->left != NULL);
    ASSERT_EQ(root->left->data, 8);
    ASSERT_EQ(root->left->color, RED);

    ASSERT_TRUE(root->left->left != NULL);
    ASSERT_EQ(root->left->left->data, 1);
    ASSERT_EQ(root->left->left->color, BLACK);

    ASSERT_TRUE(root->left->right != NULL);
    ASSERT_EQ(root->left->right->data, 11);
    ASSERT_EQ(root->left->right->color, BLACK);

    ASSERT_TRUE(root->left->left->right != NULL);
    ASSERT_EQ(root->left->left->right->data, 6);
    ASSERT_EQ(root->left->left->right->color, RED);
}



TEST(RedBlackTreeTest, ComplexDeletionTest) {
    struct Node* root = NULL;

    insert(&root, 10);
    insert(&root, 20);
    insert(&root, 30);
    insert(&root, 40);
    insert(&root, 50);
    insert(&root, 5);
    insert(&root, 15);
    insert(&root, 25);
    insert(&root, 35);
    insert(&root, 45);

    // Удаляем корневой узел
    deleteNode(&root, 30);

    // Проверяем, что корень правильно расположен
    ASSERT_TRUE(root != NULL);
    ASSERT_EQ(root->data, 20);
    ASSERT_EQ(root->color, BLACK);


    // Левое поддерево
    ASSERT_TRUE(root->left != NULL);
    ASSERT_EQ(root->left->data, 10);
    ASSERT_EQ(root->left->color, BLACK);

    ASSERT_TRUE(root->left->left != NULL);
    ASSERT_EQ(root->left->left->data, 5);
    ASSERT_EQ(root->left->left->color, RED);

    ASSERT_TRUE(root->left->right != NULL);
    ASSERT_EQ(root->left->right->data, 15);
    ASSERT_EQ(root->left->right->color, RED);

    // Правое поддерево
    ASSERT_TRUE(root->right != NULL);
    ASSERT_EQ(root->right->data, 40);
    ASSERT_EQ(root->right->color, RED);

    ASSERT_TRUE(root->right->left != NULL);
    ASSERT_EQ(root->right->left->data, 35);
    ASSERT_EQ(root->right->left->color, BLACK);

    ASSERT_TRUE(root->right->right != NULL);
    ASSERT_EQ(root->right->right->data, 50);
    ASSERT_EQ(root->right->right->color, BLACK);

}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}