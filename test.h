#ifndef TEST_H
#define TEST_H

#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define STRLEN(s) printf("(%s) \t %zu === %zu\n", s, strlen(s), ft__strlen(s));
#define STRCMP(s1, s2)                                                         \
  printf("compare (%s - %s) %i === %i\n", s1, s2, strcmp(s1, s2),              \
         ft__strcmp(s1, s2));
#define ATOI_BASE(s, b)

size_t ft__strlen(char *str);
int ft__strcmp(const char *str1, const char *str2);
char *ft__strcpy(char *restrict dst, const char *restrict src);
char *ft__strdup(const char *str);
ssize_t ft__read(int fd, void *buf, size_t count);
ssize_t ft__write(int fd, const void *buf, size_t count);
int ft__atoi_base(char *str, char *base);
int ft_atoi_base(char *str, char *base);

void strdup_test(const char *s) {
  char *res = ft__strdup(s);
  printf("%s - %p === %s - %p \n", s, s, res, res);
  free(res);
}

void atoibase(char *str, char *base) {
  char buff[200];
  sprintf(buff, "[%s - %s] %d === %d\n", str, base, ft_atoi_base(str, base),
          ft__atoi_base(str, base));
  printf("%s", buff);
}

void write_test(int fd, void *buff, size_t count) {
  char errno_str[20];

  write(fd, buff, count);
  snprintf(errno_str, sizeof(errno_str), " %d", errno);
  write(1, errno_str, strlen(errno_str));
  ft__write(1, " - ", 3);
  snprintf(errno_str, sizeof(errno_str), "%d ", errno);
  write(1, errno_str, strlen(errno_str));
  ft__write(fd, buff, count);
  ft__write(1, "\n", 1);
}

typedef struct s_list {
  void *data;
  struct s_list *next;
} t_list;

#endif
