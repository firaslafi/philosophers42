

#include "./philosophers.h"



static t_mem_block *ft_new_mem_block(void *pointer) {
    t_mem_block *block = malloc(sizeof(t_mem_block));
    if (!block)
        return NULL;

    block->block_pointer = pointer;
    block->next = NULL;
    return block;
}

static void ft_add_mem_block(t_mem_block **lst, void *pointer) {
    if (!lst)
        return;

    if (!*lst) {
        *lst = ft_new_mem_block(pointer);
    } else {
        t_mem_block *temp = *lst;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = ft_new_mem_block(pointer);
    }
}

void *ft_malloc(t_mem_block **lst, int size) {
    if (size <= 0)
        return NULL;

    void *p = malloc(size);
    if (!p)
        return NULL;

    ft_add_mem_block(lst, p);
    return p;
}

void ft_free_all(t_mem_block **lst) {
    if (!lst || !*lst)
        return;

    t_mem_block *temp = *lst;
    while (temp != NULL) {
        t_mem_block *to_free = temp;
        temp = temp->next;

        free(to_free->block_pointer);
        free(to_free);
    }
    *lst = NULL;
}
