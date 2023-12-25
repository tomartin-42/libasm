#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

size_t _ft__strlen(char *str);

int main(int) {
  char *len;
  size_t res_org[3];
  size_t res_lib[3];

  len = "HOLA";
  for (int i = 0; i < 3; i++) {
    res_org[i] = strlen(len);
    res_lib[i] = _ft__strlen(len);
    printf("%i - %i", res_org[i], res_lib[i]);
  }
}
