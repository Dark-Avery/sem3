#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char* val;
    struct node* next;
} list;

typedef struct node1 {
    char val;
    struct node1* next;
} word;

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
        free(ptr->val);
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

void print_list_r(list *head) {
    if (head != NULL) {
        print_list_r(head->next);
        printf("%s ",head->val);
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

void sort_list(list *head) {
    list *current = head, *index;
    char *tmp;
    if (head == NULL) {
        return;
    }
    while (current != NULL) {
        index = current->next;
        while (index != NULL) {
            if (strcmp(current->val, index->val)>0) {
                tmp = current->val;
                current->val = index->val;
                index->val = tmp;
            }
            index = index->next;
        }
        current = current->next;
    }
}

int main() {
    list* head;
    printf("Enter your words:\n");
    head = get_list();
    printf("\nYour words:\n");
    print_list(head);
    printf("\n\nYour reversed words:\n");
    print_list_r(head);
    sort_list(head);
    printf("\n\nYour sorted words:\n");
    print_list(head);
    printf("\n");
    delete_list(head);
    return 0;
}