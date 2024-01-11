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
  STRLEN("\n");
  printf("end STRLEN************************\n");
  printf("\n");
  printf("STRCMP**************************\n");
  STRCMP("HOLA", "HOLA");
  STRCMP("HOLA1", "HOLA");
  STRCMP("HOLA", "HOLA1");
  STRCMP("HOLA", "ADIOS");
  STRCMP("42", "");
  STRCMP("", "42");
  STRCMP("", "");
  STRCMP(" ", "");
  STRCMP("", " ");
  printf("end STRCMP*************************\n");
  printf("\n");
  printf("STRCPY**************************\n");
  printf("('HOLA') %s === %s\n", strcpy(buff, "HOLA"),
         ft__strcpy(buff, "HOLA"));
  printf("('') %s === %s\n", strcpy(buff, ""), ft__strcpy(buff, ""));
  printf("('AAAAAAAAAAAAAAAAAAAAAAAAA') %s === %s\n",
         strcpy(buff, "AAAAAAAAAAAAAAAAAAAAAAAAA"),
         ft__strcpy(buff, "AAAAAAAAAAAAAAAAAAAAAAAAA"));
  printf("end STRCPY*************************\n");
}
