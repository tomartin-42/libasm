#ifndef TEST_BONUS_H
# define TEST_BONUS_H

# include "test.h"

typedef struct s_list {
  void          *data;
  struct s_list *next;
} t_list;

int          ft_atoi_base(char *str, char *base);
unsigned int ft_list_size(t_list *begin_list);
void         ft_list_push_front(t_list **begin_list, void *data);
void         ft_list_sort(t_list **begin_list,
                          int (*cmp)(const void *, const void *));
void         ft_list_remove_if(t_list **begin_list, void *data_ref,
                               int (*cmp)(const void *, const void *),
                               void (*free_fct)(void *));

#endif
