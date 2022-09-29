#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define n 4
struct list
{ struct word* elem;
  struct list * next;
};

struct word
{
    char sym;
    struct word *ptr;
};

struct word * addsym(struct word *lst, char s)
{
  struct word *temp, *p;
  temp = (struct word*)malloc(sizeof(struct word));
  lst->ptr = temp;
  temp->sym = s;
  temp->ptr = NULL;
  return(temp);
}


struct list *newtext(char c)
{
    struct list *p;
    p = (struct list*)malloc(sizeof(struct list));
    //first sym
    p->elem = (struct word*)malloc(sizeof(struct word));
    p->next = NULL;
    p->elem->sym = c;
    p->elem->ptr = NULL;
    return p;
}

struct list * insert(struct list *lst, char firstsym)
{
    struct list *temp, *p;
    temp = (struct list*)malloc(sizeof(struct list));
    p = lst->next;
    lst->next = temp;
    temp->next = p;
    temp->elem = (struct word*)malloc(sizeof(struct word));
    temp->elem->sym = firstsym;
    temp->elem->ptr = NULL;
    return(temp);
}



//write
void writeword(struct word *s)
{ if (s == NULL ) return;
  struct word *p;
  p = s;
  do {
    printf("%c", p->sym);
    p = p->ptr;
  } while (p != NULL);

  return;
}

void writelist(struct list *s)
{   if (s == NULL ) return;
    struct list *p;
    p = s;
    do {
    writeword(p->elem);
    printf(" ");
    p = p->next;
    } while (p != NULL);
    printf("\n");
    return;
}


struct list *readall()
{
    char c;
    while ((c = fgetc(stdin)) == ' ');
    if ((c == EOF) || (c == '\n')) return NULL;
    struct list *p, *root;
    struct word *t;
    p = newtext(c);
    t = p->elem;
    root = p;
    while ((c = fgetc(stdin)) != '\n' && c != EOF  && c != ' '){
        t = addsym(t, c);
    }
    if ((c == EOF) || (c == '\n')) return(p);
    while ((c = fgetc(stdin)) == ' ');
    if ((c == EOF) || (c == '\n')) return(p);
    while(1){
        p = insert(p, c);
        t = p->elem;
        while ((c = fgetc(stdin)) != '\n' && c != EOF && c != ' '){
            t = addsym(t, c);
        }
        if ((c == EOF) || (c == '\n')) return(root);
        while ((c = fgetc(stdin)) == ' ');
        if ((c == EOF) || (c == '\n')) return(root);
    }

    return(root);
}

///// < = 1; > = 0;
int comparison(struct word *s1, struct word *s2){
    struct word * t1, *t2;
    t1 = s1;
    t2 = s2;
    while(1){
        if (t1 == NULL) return 0;
        if (t2 == NULL) return 0;
        if ((t1->sym) > (t2->sym)) return 0;
        if ((t1->sym) < (t2->sym)) return 1;
        t1 = t1 ->ptr;
        t2 = t2 ->ptr;
    }
}


void reverseoutput(struct list *s)
{   if (s->next == NULL ){
        writeword(s->elem);
        printf(" ");
    }
    else {
        reverseoutput(s->next);
        writeword(s->elem);
        printf(" ");
    }
    return;
}

struct list * sort( struct list *root )
{
    struct list *new_root = NULL;
    while ( root != NULL )
    {
        struct list *node = root;
        root = root->next;
        if ( new_root == NULL || comparison(node->elem, new_root->elem) )
        {
            node->next = new_root;
            new_root = node;
        }
        else
        {
            struct list *current = new_root;
            while ( current->next != NULL && comparison( current->next->elem, node->elem ) )
            {
                  current = current->next;
            }
            node->next = current->next;
            current->next = node;
        }
    }

    return new_root;
}

void delword(struct word* p);

struct list * deleteheadlist(struct list *root) { 
    struct list *temp;

    temp = root->next;
    delword(root->elem);
    free(root);
    return(temp); 
}

struct word * deleteheadword(struct word *root) { 
    struct word *temp;
    temp = root->ptr;
    free(root);
    return(temp); 
}

void dellist(struct list* p)
{   while( p != NULL )
        p = deleteheadlist(p);
    return;
}

void delword(struct word* p)
{   while( p != NULL )
        p = deleteheadword(p);
    return;
}


/////////////////////////////////////////main////
int main() {

    struct list *a;
    a = readall();
    if(a){
        printf("-------------Our list:-------------\n");
        printf("\n");
        writelist(a);
        printf("\n");
        printf("-------------Reverse output:-------------\n");
        printf("\n");
        reverseoutput(a);
        printf("\n");
        printf("-------------After sort:-------------\n");
        printf("\n");
        a = sort(a);
        writelist(a);
        printf("\n");

        dellist(a);
    } else {
        puts("Empty list\n");
    }
    return 0;
}
