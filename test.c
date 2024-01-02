#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

size_t ft__strlen(char *str);

int main(void) {
  size_t res_org = strlen("HOLA");
  size_t res_lib = ft__strlen("HOLA");

  printf("%zu - %zu", res_org, res_lib);
}
