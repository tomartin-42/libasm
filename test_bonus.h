#ifndef TEST_BONUS_H
#define TEST_BONUS_H

#include <stdio.h>

typedef struct s_list {
  void *data;
  struct s_list *next;
} t_list;

int ft__atoi_base(char *str, char *base);
int ft_atoi_base(char *str, char *base);
int ft__list_size(t_list *begin_list);

#endif
