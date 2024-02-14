#ifndef TEST_H
#define TEST_H

#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct s_list {
  void *data;
  struct s_list *next;
} t_list;

#define STRLEN(s) printf("(%s) \t %zu === %zu\n", s, strlen(s), ft_strlen(s));
#define STRCMP(s1, s2)                                                         \
  printf("compare (%s - %s) %i === %i\n", s1, s2, strcmp(s1, s2),              \
         ft_strcmp(s1, s2));
#define ATOI_BASE(s, b)

size_t ft_strlen(char *str);
int ft_strcmp(const char *str1, const char *str2);
char *ft_strcpy(char *restrict dst, const char *restrict src);
char *ft_strdup(const char *str);
ssize_t ft_read(int fd, void *buf, size_t count);
ssize_t ft_write(int fd, const void *buf, size_t count);

#endif
