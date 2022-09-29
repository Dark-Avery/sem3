#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    struct node *left;
    struct node *right;
} node_t;

void push_tree(node_t **tree, int value) {
    if ((*tree) == NULL) {
        node_t *elem = (node_t*)malloc(sizeof(node_t));
        elem->val = value;
        elem->left = NULL;
        elem->right = NULL;
        (*tree) = elem;
    } else {
            if (value < (*tree)->val)
                push_tree(&((*tree)->left), value);
            else if (value > (*tree)->val)
                push_tree(&((*tree)->right), value);
    }
}

node_t *get_tree() {
    node_t *tree = NULL;
    int temp;
    scanf("%d", &temp);
    while(temp != 0) {
        push_tree(&tree, temp);
        scanf("%d", &temp);
    }
    return tree;
}

void print_tree(node_t *tree, int p) {
    int i;
    if (tree != NULL) {
        print_tree(tree->right, p+3);
        for (i = 0; i < p; i++) {
            printf(" ");
        }
        printf("%d\n", tree->val);
        print_tree(tree->left, p+3);
    }
}

int deep_path(node_t *tree, int value) {
    int k = 0;
    for (;;) {
        if (tree == NULL) 
            return -1;
        if (tree->val == value)
            return k;
        k++;
        if (value < tree->val)
            tree = tree->left;
        else 
            tree = tree->right;
    }
}

void delete_tree(node_t *tree) {
    if (tree != NULL) {
        delete_tree(tree->left);
        delete_tree(tree->right);
        free(tree);
    }
}

int main() {
    int temp;
    printf("Ener your tree and 0 at the end:\n");
    node_t *tree = get_tree();
    printf("Your tree:\n");
    print_tree(tree, 0);
    printf("\nEnter element of tree(0 to exit):\n");
    scanf("%d", &temp);
    while (temp != 0) {
        printf("Deep of elem = %d\n", deep_path(tree, temp));
        printf("\nEnter element of tree(0 to exit):");
        scanf("%d", &temp);
    }
    delete_tree(tree);
    return 0;
}
