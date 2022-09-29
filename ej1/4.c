#include <stdlib.h>
#include <string.h>

void process(struct List *pl, const char *str) {
    if (pl->first == NULL)
        return;
    struct Node *tmp = pl->first;
    struct Node *tmp2;
    struct Node *first = NULL;
    while (tmp != NULL) {
        if (!strcmp(tmp->elem, str)) {
            if (pl->last == pl->first) {
                free(tmp->elem);
                free(tmp);
                pl->last = NULL;
                pl->first = NULL;
                tmp = NULL;   
            } else if (tmp == pl->first) {
                free(tmp->elem);
                tmp = tmp->next;
                pl->first = tmp;
                free(tmp->prev);
                tmp->prev = NULL;
            } else if (tmp == pl->last) {
                free(tmp->elem);
                tmp->prev->next = NULL;
                pl->last = tmp->prev;
                free(tmp);
                tmp = NULL;
            } else {
                tmp->next->prev = tmp->prev;
                free(tmp->elem);
                tmp = tmp->next;
                free(tmp->prev->next);
                tmp->prev->next = tmp;
            }
        } else if (strcmp(tmp->elem, str) > 0) {
            if (first == NULL)
                first = tmp;
            else if (first == tmp)
                break;
            if (tmp == pl->last || pl->first == pl->last)
                tmp = NULL;
            else if (tmp->next != NULL) {
                tmp2 = pl->last;
                tmp2->next = tmp;
                if (tmp->prev != NULL)
                    tmp->prev->next = tmp->next;
                else
                    pl->first = tmp->next;
                tmp->next->prev = tmp->prev;
                tmp->prev = tmp2;
                tmp = tmp->next;
                tmp2->next->next = NULL;
                pl->last = tmp2->next;
            }
        } else
            tmp = tmp->next;
    }
}