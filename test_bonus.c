#include "test_bonus.h"

void atoibase(char *str, char *base) {
  char buff[200];
  sprintf(buff, "[%s - %s] \t%d === %d\n", str, base, ft_atoi_base(str, base),
          ft__atoi_base(str, base));
  printf("%s", buff);
}

t_list *create_list(int i) {
  t_list *list = NULL;

  for (int j = 0; j < i; j++) {
    t_list *new_node = (t_list *)malloc(sizeof(t_list));
    new_node->data = malloc(sizeof(int));
    *(int *)new_node->data = j;
    new_node->next = list;
    list = new_node;
  }
  return list;
}

void free_list(t_list *list) {
  while (list != NULL) {
    t_list *tmp = list;
    list = list->next;
    free(tmp);
  }
}

void print_list(t_list *list) {
  int j = 0;
  printf("LIST---------------\n");
  while (list != NULL) {
    printf("data - %d\n", *(int *)list->data);
    j++;
    list = list->next;
  }
  printf("LIST SIZE: %d\n\n", j);
}

void list_size(int i) {
  t_list *list = create_list(i);
  printf("%d === %d\n", i, ft__list_size(list));
  free_list(list);
}

void add_node_front(int i, int data) {
  t_list *list = create_list(i);

  printf("DATA %d\n", data);
  printf("\t**List Before**\n");
  print_list(list);
  ft__list_push_front(&list, (void *)&data);
  printf("\t**List After**\n");
  print_list(list);
  printf("\n");
  free_list(list);
}

int cmp_num(int i, int j) {
  if (i < j) {
    return (-1);
  } else if (i == j) {
    return (0);
  }
  return (1);
}

void listsort(int i) {
  t_list *list = create_list(i);
  print_list(list);
  ft__list_sort(&list, &cmp_num);
  print_list(list);
  free_list(list);
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
  list_size(999);
  list_size(1);
  list_size(0);
  printf("\n");
  printf("\n\033[1mTesting: \033[0m\033[35m%s\033[0m...\n",
         "FT_LIST_PUSH_FRONT");
  add_node_front(10, 99999);
  add_node_front(1, 99999);
  add_node_front(0, 99999);
  printf("\n");
  printf("\n\033[1mTesting: \033[0m\033[35m%s\033[0m...\n", "FT_LIST_SHORT");
  listsort(10);
  listsort(0);
  listsort(1);
}
