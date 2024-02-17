#include "test.h"

void strdup_test(const char *s) {
  char *res = ft_strdup(s);
  printf("%s - %p === %s - %p \n", s, s, res, res);
  free(res);
}

void write_test(int fd, void *buff, size_t count) {
  char str[20];

  write(fd, buff, count);
  snprintf(str, sizeof(str), " %d", errno);
  write(1, str, strlen(str));
  write(1, " - ", 3);
  snprintf(str, sizeof(str), "%d ", errno);
  ft_write(1, str, strlen(str));
  ft_write(fd, buff, count);
  ft_write(1, "\n", 1);
}

void read_test(int i) {
  char buff[20];

  //int f = open("test_file.txt", O_RDONLY);
  int err;
  int f = open("a.txt", O_RDONLY);
  int r = read(f, buff, i);
  err = errno;
  lseek(f, 0, SEEK_SET);
  printf("%s - %d - ERRNO = %d\n", buff, r, err);
  r = ft_read(f, buff, i);
  err = errno;
  lseek(f, 0, SEEK_SET);
  printf("%s - %d - ERRNO = %d\n", buff, r, err);
  printf("************************\n");
  close(f);
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
  printf("('HOLA') %s === %s\n", strcpy(buff, "HOLA"), ft_strcpy(buff, "HOLA"));
  printf("('') %s === %s\n", strcpy(buff, ""), ft_strcpy(buff, ""));
  printf("('AAAAAAAAAAAAAAAAAA') %s === %s\n",
         strcpy(buff, "AAAAAAAAAAAAAAAAAA"),
         ft_strcpy(buff, "AAAAAAAAAAAAAAAAAA"));
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
  printf("\n\033[1mTesting: \033[0m\033[35m%s\033[0m...\n", "READ");
  read_test(5);
  read_test(2);
  read_test(10);
  read_test(1);
  read_test(0);
  read_test(20);
}
