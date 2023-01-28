#include <stdio.h>
#include <stdlib.h>

void insert(struct node **root, int data) {

    struct node *new = newNode(data);
    struct node *x = *root;
    struct node *y = NULL;
    while (x != NULL) {
        y = x;
        if (new->data < x->data) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    new->parent = y;
    if (y == NULL) {
        *root = new;
    } else if (new->data < y->data) {
        y->left = new;
    } else {
        y->right = new;
    }

    fixInsert(root, new);
}

struct node* minNode(struct node* node) {

    while (node->left != NULL) {
    node = node->left;
    }

    return node;
}

struct node* deleteNode(struct node* root, int data) {

    if (root == NULL) {
        return root;
    }
    if (data < root->data) {
        root->left = deleteNode(root->left, data);
    } else if (data > root->data) {
        root->right = deleteNode(root->right, data);
    } else {
        if (root->left == NULL) {
            struct node *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct node temp = root->left;
            free(root);
            return temp;
        }
        struct node temp = minNode(root->right);
        root->data = temp->data;
    root->right = deleteNode(root->right, temp->data);
    }

    return root;
}


