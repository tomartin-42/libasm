#include "test.h"

void strdup_test(const char *s) {
  char *res = ft_strdup(s);
  printf("%s - %p === %s - %p \n", s, s, res, res);
  free(res);
}

void write_test(int fd, void *buff, size_t count) {
  int res;
  errno = 0;

  res = write(fd, buff, count);
  printf(" - RET %d - ERRNO = %d\n", res, errno);
  ft_write(fd, buff, count);
  printf(" - RET %d - ERRNO = %d\n", res, errno);
  printf("************************\n");
}

void read_test(char *file, int len) {
  char buff[20];

  int f = open(file, O_RDONLY);
  errno = 0;
  int r = read(f, buff, len);
  printf("%s - RET %d - ERRNO = %d\n", buff, r, errno);
  lseek(f, 0, SEEK_SET);
  r = ft_read(f, buff, len);
  printf("%s - RET %d - ERRNO = %d\n", buff, r, errno);
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
  write_test(1000000000, "HOLA", 4);
  write_test(2, "HOLA", 4);
  write_test(1, "", 0);
  write_test(42424242, "HOLA", 4);
  printf("\n");
  printf("\n\033[1mTesting: \033[0m\033[35m%s\033[0m...\n", "READ");
  read_test("test_file.txt", 5);
  read_test("test_file.txt", 2);
  read_test("test_file.txt", 10);
  read_test("test_file.txt", 1);
  read_test("test_file.txt", 0);
  read_test("FAIL", 20);
}
