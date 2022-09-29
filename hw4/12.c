#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodeW {
    char val;
    struct nodeW *next;
} word;

typedef struct nodeL {
    word *val;
    struct nodeL *next;
} list;

void delete_list_1(word *head) {
    word *temp;
    while (head != NULL){
        temp = head;
        head = head->next;
        free(temp);
    }
}

void delete_list(list *head) {
    list *temp;
    while (head != NULL){
        temp = head;
        head = head->next;
        free(temp->val);
        free(temp);
    }
}

char *get_string_list(char **s) {
    word *str = NULL;
    word *current;
    char inp;
    int i = 0, j = 0;

    str = (word*)malloc(sizeof(word));
    current = str;
    char checkinp = scanf("%c", &inp);
    while (checkinp != -1 && inp != '\n' && inp == ' '){
        checkinp = scanf("%c", &inp);
    }
    while (checkinp != -1 && inp != '\n' && inp != ' '){
        current->val = inp;
        current->next = (word*)malloc(sizeof(word));
        current = current->next;
        checkinp = scanf("%c", &inp);
        i++;
    }

    if (i == 0){
        delete_list_1(str);
        return NULL;
    }

    current = str;
    char *tmpstr = (char*) malloc((i+1)*sizeof(char));
    while (current->next != NULL){
        tmpstr[j++] = current->val;
        current = current->next;
    }
    tmpstr[j] = '\0';
    delete_list_1(str);
    *s = tmpstr;
    if (checkinp == -1 || inp == '\n'){
        return NULL;
    }
    return tmpstr;
}

list *get_list() {
    list *head = (list*)malloc(sizeof(list));
    // if (head == NULL){
    //     printf("Allocate memory for your list.\n");
    //     return;
    // }
    char *s = NULL;
    char **ps = &s;
    char *checks;
    list *current = head;
    list *prev;
    checks = get_string_list(ps);
    while (checks != NULL){
        current->val = s;
        current->next = (list*)malloc(sizeof(list));
        current = current->next;
        checks = get_string_list(ps);
    }
    if (s != NULL){
        current->val = s;
        current->next = NULL;
    }
    return head;
}

void print_list(list *head){
    while (head != NULL){
        printf("%s ", head->val);
        head = head->next;
    }
    printf("\n");
}

void print_list_r(list *head){
    if (head != NULL){
        print_list_r(head->next);
        printf("%s ",head->val);
    }
    printf("\n");
}

void sort_list(list *head){
    list *current = head, *index;
    char *tmp;
    if (head == NULL){
        return;
    }
    while (current != NULL){
        index = current->next;
        while (index != NULL){
            if (strcmp(current->val, index->val)>0){
                tmp = current->val;
                current->val = index->val;
                index->val = tmp;
            }
            index = index->next;
        }
        current = current->next;
    }
}

word * addsym(word *lst, char s)
{
  word *temp, *p;
  temp = (word*)malloc(sizeof(word));
  lst->next = temp;
  temp->val = s;
  temp->next = NULL;
  return(temp);
}


list *newtext(char c)
{
    list *p;
    p = (list*)malloc(sizeof(list));
    //first sym
    p->val = (word*)malloc(sizeof(word));
    p->next = NULL;
    p->val->val = c;
    p->val->next = NULL;
    return p;
}

list * insert(list *lst, char firstsym)
{
    list *temp, *p;
    temp = (list*)malloc(sizeof(list));
    p = lst->next;
    lst->next = temp;
    temp->next = p;
    temp->val = (word*)malloc(sizeof(word));
    temp->val->val = firstsym;
    temp->val->next = NULL;
    return(temp);
}

list *readall() {
    char c, ok;
    ok = scanf("%c", &c);
    while (c == ' ') 
        ok = scanf("%c", &c);
    if (ok == -1 || c == '\n') 
        return NULL;
    list *p, *root;
    word *t;
    p = newtext(c);
    t = p->val;
    root = p;
    ok = scanf("%c", &c);
    while (c != '\n' && c != ' ' && ok != -1) {
        t = addsym(t, c);
        ok = scanf("%c", &c);
    }
    if ((c == EOF) || (c == '\n')) return(p);
    while ((c = fgetc(stdin)) == ' ');
    if ((c == EOF) || (c == '\n')) return(p);
    while(1){
        p = insert(p, c);
        t = p->val;
        while ((c = fgetc(stdin)) != '\n' && c != EOF && c != ' '){
            t = addsym(t, c);
        }
        if ((c == EOF) || (c == '\n')) return(root);
        while ((c = fgetc(stdin)) == ' ');
        if ((c == EOF) || (c == '\n')) return(root);
    }

    return(root);
}


int main(){
    //list *head = (list*)malloc(sizeof(list));
    printf("Input your words:\n");
    list *head = readall();
    //char *s;
    
    //get_list(head);
    printf("\nYour input:\n");
    print_list(head);
    printf("\nReversed input:\n");
    print_list_r(head);
    printf("\nList in alphabetical order:\n");
    sort_list(head);
    print_list(head);
    delete_list(head);

    return 0;
}
