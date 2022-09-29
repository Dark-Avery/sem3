#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
typedef unsigned elemtype;
typedef struct node *link;
typedef struct node {
    elemtype elem;
    link right;
    link left;
} node;

typedef link tree;

void add(elemtype addelem, tree *t) {
    
    if (*t == NULL) {
        *t = (link)malloc(sizeof(node));
        (*t)->elem = addelem;
        (*t)->right = NULL;
        (*t)->left = NULL;
    }
    else {
        if (addelem < (*t)->elem) {
            add(addelem, &(*t)->left);
        }
        else {
            add(addelem, &(*t)->right);
        }
        
    }
}
int FindMax(tree t)                                      
  {
    int res=t->elem;
    int m;
    if (t->left != NULL && (m=FindMax(t->left)) > res)    
      res=m;
    if (t->right != NULL && (m=FindMax(t->right)) > res) 
      res=m;
    return res;
  }

void Del(tree *t, elemtype a)
  {
    tree q;                                         
    int m;                                         
    if (*t==NULL)
      return ;
    if ((*t)->elem==a)
      {
        if ((*t)->left==NULL && (*t)->right==NULL)  
          {
            q=*t;
            *t=NULL;
            free(q);
            return ;
          }
        else if ((*t)->left==NULL)                  
          {
            q=*t;
            *t=q->right;
            free(q);
            return ;
          }
        else if ((*t)->right==NULL)                
          {
            q=*t;
            *t=q->left;
            free(q);
            return ;
          }
        else                                        
          {
            (*t)->elem=m=FindMax((*t)->left);       
            Del(&(*t)->left, m);                
            return ;
          }
      }
    if (a>(*t)->elem)                               
      Del(&(*t)->right, a);
    if (a<(*t)->elem)
      Del(&(*t)->left, a);
  }


int Find(tree t, elemtype a)     
  {
    if (t==NULL)
      return 0;
    if (t->elem == a)
      return 1;
    if (a>t->elem)                   
      return Find(t->right, a);
    else                             
      return Find(t->left, a);
  }



int main()
{
  unsigned a;                            
  char zn;                               
  tree BinTree=NULL;
  while (scanf("%c", &zn)==1)
    {
      if (zn!='+' && zn!='-' && zn!='?')
        continue ;
      scanf("%d", &a);

      if (zn == '+')
        add(a, &BinTree);
      else if (zn == '?')
        {
          printf("%u ", a);
          if (Find(BinTree, a))
            printf("yes\n");
          else
            printf("no\n");
        }
      else
        Del(&BinTree, a);

    }
    

    return 0;
}
