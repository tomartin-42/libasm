#include "test.h"

void strdup_test(const char *s) {
  char *res = ft__strdup(s);
  printf("%s - %p === %s - %p \n", s, s, res, res);
  free(res);
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
  printf("\n");
  printf("\n\033[1mTesting: \033[0m\033[35m%s\033[0m...\n", "WRITE");
  write_test(1, "HOLA", 4);
  write_test(2, "HOLA", 4);
  write_test(1, "", 0);
  write_test(42424242, "HOLA", 4);
  printf("\n");
}
