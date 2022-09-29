#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define lengthstr 20

typedef struct node {
    char *val;
    struct node *next;
} node_t;

char *get_string() {
    int len = 0;
    char *s = (char*) malloc(lengthstr);
    char c, ok;

    ok = scanf("%c", &c);

    while (c != '\n' && ok != -1) {
        s[len++] = c;
        ok = scanf("%c", &c);          
    }

    s[len] = '\0';

    return s;
}

node_t* read_list(char* end){
    node_t* answer = NULL;
    char* s = get_string();
    node_t* p = answer;
    while (strcmp(s, end) != 0) {
        node_t* tmp = (node_t*)malloc(sizeof(node_t));
        tmp->val = s;
        tmp->next = NULL;
        p = answer;
        if (answer != NULL) {
            while (p->next != NULL){
                p = p->next;
            }
            p->next = tmp;
        }
        else {
            answer = tmp;
        }
        s = get_string();
    }
    free(s);
    return answer;
}

void print_list(node_t *head) {
    while (head != NULL){
        printf("%s\n", head->val);
        head = head->next;
    }
}

int task1(char *s, char c) {
    int i = 0;
    while (s[i] != '\0') {
        if (s[i] == c) {
            return 1;
        }
        i++;
    }
    return 0;
}

void putin(node_t *head, char c, const char *data) {
    node_t *current = head;
    while (current != NULL) {
        if (task1(current->val, c)){
            node_t *t1 = (node_t*) malloc(sizeof(node_t));
            char *c = (char*) malloc(lengthstr);
            c = strcpy(c, data);
            t1->val = c;
            t1->next = current->next;
            current->next = t1;
            current = current->next;
        }
        current = current->next;   
    }
}

int task2(char *s, char c) {
    int i = 0;
    while (s[i] != '\0')
        i++;
    if (s[i-1] == c) 
        return 1;
    else
        return 0;
}

void dellc(node_t **head, char c) {
    node_t *current = (*head);
    node_t *pred = (*head);
    while (current != NULL) {
        if (task2(current->val, c)) {
            if (current == (*head)) {
                (*head) = (*head)->next;
                free(current->val);
                free(current);
                current = (*head);
                pred = (*head);
            } else {
                pred->next = current->next;
                
                free(current->val);
                free(current);
                current = pred->next;
            }
        } else {
            pred = current;
            current = current->next;
        }
    }
}

void deleteList(node_t **head) {
node_t* for_delete;
	while((*head) != NULL){
        free((*head)->val);
		for_delete = (*head);
		(*head) = (*head)->next;
		free(for_delete);
    }
}


int main() {
    printf("Enter \"STOP STRING\":\n");
    char *stop = get_string();
    printf("\nEnter string's and \"STOP STRING\" at the end:\n");
    node_t *head = read_list(stop);
    free(stop);
    printf("\nYour list:\n");
    print_list(head);

    printf("\nEnter your symbol: ");
    char c;
    scanf("%c", &c);
    putin(head, c, "111");
    printf("\nYour updated list:\n");
    print_list(head);

    printf("\nEnter your symbol: ");
    scanf("%c", &c);
    scanf("%c", &c);
    
    dellc(&head, c);
    printf("\nYour updated list:\n");
    print_list(head);

    deleteList(&head);
    
    return 0;
}