#include "test_bonus.h"

void atoibase(char *str, char *base) {
  char buff[200];
  sprintf(buff, "[%s - %s] \t%d === %d\n", str, base, ft_atoi_base(str, base),
          ft__atoi_base(str, base));
  printf("%s", buff);
}

void list_size(int i) {
  t_list *list = NULL;

  for (int j = 0; j < i; j++) {
    t_list *new_node = (t_list *)malloc(sizeof(t_list));
    new_node->data = malloc(sizeof(int));
    *(int *)new_node->data = j;
    new_node->next = list;
    list = new_node;
  }
  printf("%d - %d\n", i, ft__list_size(list));
  while (list != NULL) {
    t_list *tmp = list;
    list = list->next;
    printf("%d\n", *(int *)tmp->data);
    free(tmp->data);
    free(tmp);
  }
}

int main(void) {

  printf("\n\033[1mTesting: \033[0m\033[35m%s\033[0m...\n", "FT_ATOI_BASE");
  atoibase("42", "0123456789");
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
  printf("\n");
  printf("\n\033[1mTesting: \033[0m\033[35m%s\033[0m...\n", "FT_LIST_SIZE");
  list_size(10);
}
