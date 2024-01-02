#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define STRLEN(s) printf("%s \t %zu === %zu\n", s, strlen(s), ft__strlen(s));

size_t ft__strlen(char *str);

int main(void) {
  printf("ft__strlen------------------\n");
  STRLEN("HOLA");
  STRLEN("");
  STRLEN(" ");
  STRLEN("\n");
  printf("end ft__strlen--------------\n");
}
