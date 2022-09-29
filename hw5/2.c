#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char *val;
    struct node *left;
    struct node *right;
} node_t;

typedef struct node1 {
    char* val;
    struct node1* next;
} list;

typedef struct node2 {
    char val;
    struct node2* next;
} word;

void push_tree(node_t **tree, char *value) {
    if ((*tree) == NULL) {
        node_t *elem = (node_t*)malloc(sizeof(node_t));
        elem->val = value;
        elem->left = NULL;
        elem->right = NULL;
        (*tree) = elem;
    } else {
        if (strncmp(value, (*tree)->val, 255) < 0)
            push_tree(&((*tree)->left), value);
        else if (strncmp(value, (*tree)->val, 255) > 0)
            push_tree(&((*tree)->right), value);
    }
}

node_t *get_tree_from_list(list *head) {
    node_t *tree = NULL;
    while (head != NULL) {
        push_tree(&tree, head->val);
        head = head->next;
    }
    return tree;
}

void print_tree(node_t *tree, int p) {
    int i;
    if (tree != NULL) {
        print_tree(tree->right, p+7);
        for (i = 0; i < p; i++) {
            printf(" ");
        }
        printf("%s\n", tree->val);
        print_tree(tree->left, p+7);
    }
}

void delete_tree(node_t *tree) {
    if (tree != NULL) {
        delete_tree(tree->left);
        delete_tree(tree->right);
        free(tree->val);
        free(tree);
    }
}

int delete_word(word* head) {
    word* ptr;
    ptr = head;
    while (ptr != NULL) {
        head = ptr->next;
        free(ptr);
        ptr = head;
    }
    return 0;
}

int delete_list(list* head) {
    list* ptr;
    ptr = head;
    while (ptr != NULL) {
        head = ptr->next;
        free(ptr);
        ptr = head;
    }
    return 0;
}

void print_list(list *head) {
    while (head != NULL) {
        printf("%s ", head->val);
        head = head->next;
    }
}

list* get_list() {
    char c;             
    char ok;    
    char* str;        
    list* head;       
    list* ptr;
    word* head1;
    word* ptr1;
    int len = 0;
    ok = scanf("%c", &c);
    while (c == ' ')
        ok = scanf("%c", &c);
    if (c == '\n' || ok == -1)
        return NULL;
    head1 = malloc(sizeof(word));
    ptr1 = head1;
    while (c != ' ' && c != '\n' && ok != -1) {
        ptr1->val = c;
        ptr1->next = malloc(sizeof(word));
        len++;
        ptr1 = ptr1->next;
        ok = scanf("%c", &c);
    }
    len++;
    ptr1->val = '\0';
    ptr1->next = NULL;
    str = malloc(sizeof(char)*len);
    ptr1 = head1;
    for (int i = 0; i < len; i++) {
        *(str+i) = ptr1->val;
        ptr1 = ptr1->next;
    }
    delete_word(head1);
    if (strcmp(str, "")) {
        head = malloc(sizeof(list));
        ptr = head;
        ptr->val = str;
    }
    else
        free(str);
    while (c != '\n' && ok != -1) {
        len = 0;
        head1 = malloc(sizeof(word));
        ptr1 = head1;
        ok = scanf("%c", &c);
        while (c == ' ')
            ok = scanf("%c", &c);
        while (c != ' ' && c != '\n' && ok != -1) {
            ptr1->val = c;
            ptr1->next = malloc(sizeof(word));
            len++;
            ptr1 = ptr1->next;
            ok = scanf("%c", &c);
        }
        len++;
        ptr1->val = '\0';
        ptr1->next = NULL;
        str = malloc(sizeof(char)*len);
        ptr1 = head1;
        for (int i = 0; i < len; i++) {
            *(str+i) = ptr1->val;
            ptr1 = ptr1->next;
        }
        delete_word(head1);
        if (strcmp(str, "")) {
            ptr->next = malloc(sizeof(list));
            ptr = ptr->next;
            ptr->val = str;
        }
        else
            free(str);
    }
    ptr->next = NULL;
    return head;
}

int main() {
    printf("Enter your words:\n");
    list *head = get_list();
    printf("\nYour words:\n");
    print_list(head);
    node_t *tree = get_tree_from_list(head);
    delete_list(head);
    printf("\n\nYour tree:\n");
    print_tree(tree, 0);
    delete_tree(tree);
    return 0;
}
