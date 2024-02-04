#include "test.h"

int main(void) {

  //  char buff[20];
  //
  //  printf("\n\033[1mTesting: \033[0m\033[35m%s\033[0m...\n", "STRLEN");
  //  STRLEN("HOLA");
  //  STRLEN("");
  //  STRLEN(" ");
  //  printf("\n");
  //  printf("\n\033[1mTesting: \033[0m\033[35m%s\033[0m...\n", "STRCMP");
  //  STRCMP("HOLA", "HOLA");
  //  STRCMP("HOLA1", "HOLA");
  //  STRCMP("HOLA", "HOLA1");
  //  STRCMP("HOLA", "ADIOS");
  //  STRCMP("42", "");
  //  STRCMP("", "42");
  //  STRCMP("", "");
  //  STRCMP(" ", "");
  //  STRCMP("", " ");
  //  printf("\n");
  //  printf("\n\033[1mTesting: \033[0m\033[35m%s\033[0m...\n", "STRCPY");
  //  printf("('HOLA') %s === %s\n", strcpy(buff, "HOLA"),
  //         ft__strcpy(buff, "HOLA"));
  //  printf("('') %s === %s\n", strcpy(buff, ""), ft__strcpy(buff, ""));
  //  printf("('AAAAAAAAAAAAAAAAAA') %s === %s\n",
  //         strcpy(buff, "AAAAAAAAAAAAAAAAAA"),
  //         ft__strcpy(buff, "AAAAAAAAAAAAAAAAAA"));
  //  printf("\n");
  //  printf("\n\033[1mTesting: \033[0m\033[35m%s\033[0m...\n", "STRDUP");
  //  strdup_test("hola");
  //  strdup_test("");
  //  strdup_test("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
  //  strdup_test(" ");
  //  strdup_test("\n");
  //  printf("\n");
  //  printf("\n\033[1mTesting: \033[0m\033[35m%s\033[0m...\n", "WRITE");
  //  write_test(1, "HOLA", 4);
  //  write_test(2, "HOLA", 4);
  //  write_test(1, "", 0);
  //  write_test(42424242, "HOLA", 4);
  //  printf("\n");
  //  printf("\n\033[1mTesting: \033[0m\033[35m%s\033[0m...\n", "atoibase");
  atoibase("-42", "0123456789");
  atoibase("+42", "0123456789");
  atoibase("++42", "0123456789");
  atoibase("-42", "0123456789");
  atoibase("--42", "0123456789");
  atoibase("-4-2", "0123456789");
  atoibase("-4+2", "0123456789");
  atoibase("---42", "0123456789");
  atoibase("4a2", "0123456789");
  atoibase("42a", "0123456789");
  atoibase("    \r   \t-42", "0123456789");
  atoibase("00101010", "01");
  atoibase("-00101010", "01");
  atoibase("2A", "0123456789ABCDEF");
  atoibase("-2A", "0123456789ABCDEF");
  atoibase("", "0123456789ABCDEF");
  atoibase("42", "01234567891");
  atoibase("42", "01+23456789");
  atoibase("42", "01-23456789");
  atoibase("42", " 0123");
  atoibase("42", "0123 ");
  atoibase("42", "01 23");
  atoibase("42", "4");
}
