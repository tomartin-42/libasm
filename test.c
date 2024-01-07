#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define STRLEN(s) printf("%s \t %zu === %zu\n", s, strlen(s), ft__strlen(s));
#define STRCMP(s1, s2)                                                         \
  printf("compare %s - %s %i - %i\n", s1, s2, strcmp(s1, s2),                  \
         ft__strcmp(s1, s2));

size_t ft__strlen(char *str);
int ft__strcmp(const char *str1, const char *str2);

int main(void) {
  printf("ft__strlen------------------\n");
  STRLEN("HOLA");
  STRLEN("");
  STRLEN(" ");
  STRLEN("\n");
  printf("end ft__strlen--------------\n");
  printf("\n\n\n");
  printf("ft__strcmp------------------\n");
  STRCMP("HOLA", "HOLA");
  STRCMP("HOLA", "ADIOS");
  STRCMP("42", "");
  STRCMP("", "42");
  STRCMP("", "");
  printf("end ft__strcmp--------------\n");
}
