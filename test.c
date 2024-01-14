#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define STRLEN(s) printf("%s \t %zu === %zu\n", s, strlen(s), ft__strlen(s));
#define STRCMP(s1, s2)                                                         \
  printf("compare %s - %s %i === %i\n", s1, s2, strcmp(s1, s2),                \
         ft__strcmp(s1, s2));

size_t ft__strlen(char *str);
int ft__strcmp(const char *str1, const char *str2);
char *ft__strcpy(char *restrict dst, const char *restrict src);

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
}
