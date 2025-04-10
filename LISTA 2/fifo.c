#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    struct node *next;
    struct node *before;
    int value;
} node;

int main()
{
    int capacity;
    int max_quadros;
    int list_size = 0;
    int elements_used = 1, value, page_fault = 1;
    int inputs;
    node *new_node;
    node **list_q;

    scanf("%d", &capacity);
    scanf("%d", &inputs);

    scanf("%d", &value);
    if (list_size < value + 1)
    {
        list_q = malloc(sizeof(node *) * (value + 1));
        for (int j = list_size; j < value + 1; j++)
        {
            list_q[j] = NULL;
        }
    }
    list_size = value + 1;
    node *begin = malloc(sizeof(node));
    begin->next = begin;
    begin->value = value;
    begin->before = begin;
    list_q[value] = begin;

    node *actual = begin;
    for (int j = 1; j < inputs; j++)
    {
        scanf("%d", &value);
        node *actual_q = list_q[value];
        if (list_size < value + 1)
        {
            list_q = (node **)realloc(list_q, sizeof(node *) * (value + 1));

            for (int j = list_size; j < value + 1; j++)
            {
                list_q[j] = NULL;
            }
            list_size = value + 1;
        }
        if (list_q[value] == NULL && elements_used < capacity)
        {
            new_node = malloc(sizeof(node));
            new_node->value = value;
            new_node->next = actual->next;
            new_node->before = actual;
            actual->next->before = new_node;
            actual->next = new_node;
            actual = new_node;
            elements_used++;
            page_fault++;
            list_q[value] = new_node;
        }
        else if (list_q[value] == NULL && elements_used == capacity)
        {
            list_q[begin->value] = NULL;
            actual->next = begin->next;
            begin->next->before = actual;

            new_node = malloc(sizeof(node));
            new_node->next = actual->next;
            new_node->value = value;
            actual->next->before = new_node;
            new_node->before = actual;
            actual->next = new_node;
            actual = new_node;
            begin = begin->next;
            list_q[value] = new_node;
            page_fault++;
        }
    }
    printf("%d\n", page_fault);

    return 0;
}
