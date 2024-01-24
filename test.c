#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define STRLEN(s) printf("%s \t %zu === %zu\n", s, strlen(s), ft__strlen(s));
#define STRCMP(s1, s2)                                                         \
  printf("compare %s - %s %i === %i\n", s1, s2, strcmp(s1, s2),                \
         ft__strcmp(s1, s2));

size_t ft__strlen(char *str);
int ft__strcmp(const char *str1, const char *str2);
char *ft__strcpy(char *restrict dst, const char *restrict src);
char *ft__strdup(const char *str);
ssize_t ft__read(int fd, void *buf, size_t count);
ssize_t ft__write(int fd, const void *buf, size_t count);
int ft__atoi_base(char *str, char *base);

typedef struct s_list {
  void *data;
  struct s_list *next;
} t_list;

void strdup_test(const char *s) {
  char *res = ft__strdup(s);
  printf("%s - %p === %s - %p \n", s, s, res, res);
  free(res);
}

int main(void) {

  char buff[20];

  printf("\n\033[1mTesting: \033[0m\033[35m%s\033[0m...\n", "STRLEN");
  STRLEN("HOLA");
  STRLEN("");
  STRLEN(" ");
  printf("\n");
  printf("\n\033[1mTesting: \033[0m\033[35m%s\033[0m...\n", "STRCMP");
  STRCMP("HOLA", "HOLA");
  STRCMP("HOLA1", "HOLA");
  STRCMP("HOLA", "HOLA1");
  STRCMP("HOLA", "ADIOS");
  STRCMP("42", "");
  STRCMP("", "42");
  STRCMP("", "");
  STRCMP(" ", "");
  STRCMP("", " ");
  printf("\n");
  printf("\n\033[1mTesting: \033[0m\033[35m%s\033[0m...\n", "STRCPY");
  printf("('HOLA') %s === %s\n", strcpy(buff, "HOLA"),
         ft__strcpy(buff, "HOLA"));
  printf("('') %s === %s\n", strcpy(buff, ""), ft__strcpy(buff, ""));
  printf("('AAAAAAAAAAAAAAAAAA') %s === %s\n",
         strcpy(buff, "AAAAAAAAAAAAAAAAAA"),
         ft__strcpy(buff, "AAAAAAAAAAAAAAAAAA"));
  printf("\n");
  printf("\n\033[1mTesting: \033[0m\033[35m%s\033[0m...\n", "STRDUP");
  strdup_test("hola");
  strdup_test("");
  strdup_test("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
  strdup_test(" ");
  strdup_test("\n");
  printf("FTATOIBASE %d\n", ft__atoi_base("HOLA", "1232"));
}
