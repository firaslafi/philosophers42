

#include "./philosophers.h"

static t_mem_block *ft_new_mem_block(void *pointer)
{
 t_mem_block *block;

 block = malloc(sizeof(t_mem_block));
 if (!block)
  return (0);
 block->block_pointer = pointer;
 block->next = NULL;
 return (block);
}

static void ft_add_mem_block(t_mem_block **lst, void *pointer)
{
 t_mem_block *temp;

 if (!*lst)
 {
  *lst = ft_new_mem_block(pointer);
 }
 else
 {
  temp = *lst;
  while (temp->next != NULL)
   temp = temp->next;
  temp->next = ft_new_mem_block(pointer);
 }
}

void *ft_malloc(t_mem_block **lst, int size)
{
 void *p;

 p = malloc(size);
 if (!p)
  return (NULL);
 ft_add_mem_block(lst, p);
 return (p);
}
typedef struct s_mem_block
{
 void    *block_pointer;
 struct s_mem_block *next;
}      t_mem_block;
void ft_free_all(t_mem_block **lst)
{
 t_mem_block *temp;

 temp = (*lst);
 while ((*lst) != NULL)
 {
  temp = (*lst);
  free(temp->block_pointer);
  temp->block_pointer = NULL;
  free(temp);
  temp = NULL;
  (*lst) = (*lst)->next;
 }
 *lst = NULL;
}
