#ifndef TEST_BONUS_H
#define TEST_BONUS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct s_list {
  void *data;
  struct s_list *next;
} t_list;

int ft_atoi_base(char *str, char *base);
int ft_atoi_base_test(char *str, char *base);
int ft_list_size(t_list *begin_list);
void ft_list_push_front(t_list **begin_list, void *data);
void ft_list_sort(t_list **begin_list, int (*cmp)());
void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(),
                       void (*free_fct)(void *));

#endif
