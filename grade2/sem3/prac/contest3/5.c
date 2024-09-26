#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <limits.h>

enum
{
    BASE = 10
};

struct Elem
{
    struct Elem *next;
    char *str;
};

void
pr_list(struct Elem *p)
{
    while (p->next) {
        printf("%s\n", p->str);
        p = p->next;
    }
}

struct Elem *
dup_elem(struct Elem *head)
{
    struct Elem *p = head;
    while (p) {

        if (p->str) {

            char *eptr = NULL;
            errno = 0;
            long lval = strtol(p->str, &eptr, BASE);

            if (!(errno || *eptr || eptr == p->str || (int) lval != lval ||
                    lval > INT_MAX - 1)) {
                // insert new elem lval + 1 value
                printf("inserting the value %ld from %s\n", lval, p->str);
                struct Elem *new_elem = (struct Elem *) calloc(1, sizeof(*new_elem));
                struct Elem *p_next = p->next;
                char *p_str = p->str;
                asprintf(&(p->str), "%ld", lval+1);
                p->next = new_elem;
                new_elem->next = p_next;
                new_elem->str = p_str;
                p = p->next;
            }
        }
        p = p->next;
    }

    printf("\n");
    pr_list(head);
    return head;
}

int
main(void)
{
    int n;
    scanf("%d", &n);
    struct Elem *head = (struct Elem *) malloc(sizeof(struct Elem));
    struct Elem *p;
    p = head;

    while (n) {
        char *s = malloc(10);
        scanf("%s", s);

        p->str = s;
        struct Elem *new_elem = (struct Elem *) malloc(sizeof(struct Elem));
        p->next = new_elem;
        p = new_elem;
        n--;
    }
    p = head;
    // pr_list(p);
    // printf("\n");
    head = dup_elem(p);
    // printf("\n");
    // pr_list(head);
    return 0;
}
