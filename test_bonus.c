#include "test_bonus.h"

#define ARRAY_LEN(array) (sizeof(array) / sizeof((array)[0]))
/* Cuenta cada comprobacion y registra el fallo sin detener el resto. */
#define CHECK(condition, ...)                                                  \
  do {                                                                         \
    ++g_checks;                                                                \
    if (!(condition)) {                                                        \
      ++g_failures;                                                            \
      fprintf(stderr, "[FAIL] ");                                              \
      fprintf(stderr, __VA_ARGS__);                                            \
      fputc('\n', stderr);                                                     \
    } else {                                                                   \
      fprintf(stdout, "[SUCCESS] ");                                           \
      fprintf(stdout, __VA_ARGS__);                                            \
      fputc('\n', stdout);                                                     \
    }                                                                          \
  } while (0)

static size_t g_checks;
static size_t g_failures;
/* Permiten comprobar que free_fct se llama exactamente una vez por coincidencia. */
static size_t g_ref_freed;
static size_t g_ft_freed;

/* ============================ UTILIDADES ============================= */

static void fatal(const char *operation) {
  /* Un fallo preparando el test impide obtener un resultado fiable. */
  perror(operation);
  exit(EXIT_FAILURE);
}

static void *xmalloc(size_t size) {
  void *memory;

  memory = malloc(size);
  if (memory == NULL)
    fatal("malloc");
  return memory;
}

/* Construye una lista nueva conservando el orden del array de entrada.
 * Cada nodo y cada entero tienen su propia reserva de memoria. */
static t_list *list_from_array(const int *values, size_t count) {
  t_list *head;
  t_list **link;
  t_list *node;
  size_t i;

  head = NULL;
  link = &head;
  i = 0;
  while (i < count) {
    node = xmalloc(sizeof(*node));
    node->data = xmalloc(sizeof(int));
    *(int *)node->data = values[i];
    node->next = NULL;
    *link = node;
    link = &node->next;
    ++i;
  }
  return head;
}

/* Libera tanto los datos como las estructuras de todos los nodos restantes. */
static void free_list(t_list *list) {
  t_list *next;

  while (list != NULL) {
    next = list->next;
    free(list->data);
    free(list);
    list = next;
  }
}

/* Compara dos listas por longitud, presencia de datos y valor de cada entero. */
static int lists_equal(const t_list *left, const t_list *right) {
  while (left != NULL && right != NULL) {
    if ((left->data == NULL) != (right->data == NULL))
      return 0;
    if (left->data != NULL && *(int *)left->data != *(int *)right->data)
      return 0;
    left = left->next;
    right = right->next;
  }
  return left == NULL && right == NULL;
}

/* Implementacion C de referencia para contar nodos. */
static unsigned int ref_list_size(t_list *list) {
  unsigned int size;

  size = 0;
  while (list != NULL) {
    ++size;
    list = list->next;
  }
  return size;
}

/* Devuelve valores distintos de -1 y 1 para verificar que sort comprueba
 * cualquier resultado negativo o positivo del comparador. */
static int compare_int(const void *left, const void *right) {
  int a;
  int b;

  a = *(const int *)left;
  b = *(const int *)right;
  if (a < b)
    return -17;
  if (a > b)
    return 23;
  return 0;
}

/* remove_if elimina un nodo solamente cuando el comparador devuelve cero. */
static int compare_equal(const void *data, const void *reference) {
  return *(const int *)data != *(const int *)reference;
}

/* ======================= PRUEBAS DE FT_ATOI_BASE ====================== */

/* Reconoce el espacio ASCII 32 y los cinco caracteres del rango 9-13. */
static int is_space(unsigned char character) {
  return character == ' ' || (character >= 9 && character <= 13);
}

/* Busca un caracter en la base y devuelve su valor numerico o -1. */
static int base_index(const char *base, unsigned char character) {
  int index;

  index = 0;
  while (base[index] != '\0') {
    if ((unsigned char)base[index] == character)
      return index;
    ++index;
  }
  return -1;
}

/* Aplica las reglas del subject: longitud minima, caracteres unicos y
 * ausencia de signos o espacios dentro de la base. */
static int valid_base(const char *base) {
  size_t i;
  size_t j;

  if (base[0] == '\0' || base[1] == '\0')
    return 0;
  i = 0;
  while (base[i] != '\0') {
    if (base[i] == '+' || base[i] == '-' || is_space((unsigned char)base[i]))
      return 0;
    j = i + 1;
    while (base[j] != '\0') {
      if (base[i] == base[j])
        return 0;
      ++j;
    }
    ++i;
  }
  return 1;
}

/* Implementacion espejo en C: valida la base, salta espacios iniciales,
 * procesa signos consecutivos y convierte hasta el primer digito invalido. */
static int ref_atoi_base(const char *str, const char *base) {
  size_t index;
  int sign;
  int radix;
  int digit;
  int result;

  if (!valid_base(base))
    return 0;
  index = 0;
  while (is_space((unsigned char)str[index]))
    ++index;
  sign = 1;
  while (str[index] == '+' || str[index] == '-') {
    if (str[index] == '-')
      sign = -sign;
    ++index;
  }
  radix = (int)strlen(base);
  result = 0;
  digit = base_index(base, (unsigned char)str[index]);
  while (digit >= 0) {
    result = result * radix + digit;
    ++index;
    digit = base_index(base, (unsigned char)str[index]);
  }
  return result * sign;
}

struct atoi_case {
  char *str;
  char *base;
  const char *label;
};

/* Cada caso se calcula con la referencia C y se compara con ft_atoi_base. */
static void test_atoi_base(void) {
  struct atoi_case cases[] = {
      {"42", "0123456789", "decimal"},
      {"-42", "0123456789", "negative"},
      {"++42", "0123456789", "two plus signs"},
      {"--42", "0123456789", "two minus signs"},
      {"---42", "0123456789", "three minus signs"},
      {" \t\n\v\f\r-42", "0123456789", "leading whitespace"},
      {"- 42", "0123456789", "space after sign"},
      {"00101010", "01", "binary"},
      {"-2A", "0123456789ABCDEF", "hexadecimal"},
      {"yoyo", "poneyvif", "custom base"},
      {"42xyz", "0123456789", "invalid suffix"},
      {"", "0123456789", "empty string"},
      {"---", "0123456789", "signs only"},
      {"42", "", "empty base"},
      {"42", "0", "one-character base"},
      {"42", "012340", "duplicate in base"},
      {"42", "01+234", "plus in base"},
      {"42", "01-234", "minus in base"},
      {"42", "01 234", "space in base"},
      {"42", "01\t234", "tab in base"},
  };
  size_t i;
  int expected;
  int actual;

  printf("\n[TEST] ft_atoi_base\n");
  i = 0;
  while (i < ARRAY_LEN(cases)) {
    expected = ref_atoi_base(cases[i].str, cases[i].base);
    actual = ft_atoi_base(cases[i].str, cases[i].base);
    CHECK(actual == expected, "ft_atoi_base %-20s expected %d, got %d",
          cases[i].label, expected, actual);
    ++i;
  }
}

/* ======================= PRUEBAS DE FT_LIST_SIZE ====================== */

/* Crea una lista, compara ambos conteos y libera toda la memoria usada. */
static void check_list_size_case(const char *label, const int *values,
                                 size_t count) {
  t_list *list;
  unsigned int expected;
  unsigned int actual;

  list = list_from_array(values, count);
  expected = ref_list_size(list);
  actual = ft_list_size(list);
  CHECK(actual == expected, "ft_list_size %-19s expected %u, got %u", label,
        expected, actual);
  free_list(list);
}

static void test_list_size(void) {
  const int one[] = {42};
  const int several[] = {3, -1, 3, 0, 99, -42};

  printf("\n[TEST] ft_list_size\n");
  check_list_size_case("empty list", NULL, 0);
  check_list_size_case("one node", one, ARRAY_LEN(one));
  check_list_size_case("several nodes", several, ARRAY_LEN(several));
}

/* ==================== PRUEBAS DE FT_LIST_PUSH_FRONT =================== */

/* Implementacion C espejo que enlaza un nodo nuevo delante de la cabeza. */
static void ref_list_push_front(t_list **begin_list, void *data) {
  t_list *node;

  node = xmalloc(sizeof(*node));
  node->data = data;
  node->next = *begin_list;
  *begin_list = node;
}

/* Usa dos listas independientes y verifica cabeza, data, next y contenido. */
static void check_push_front_case(const char *label, const int *values,
                                  size_t count, int value) {
  t_list *expected;
  t_list *actual;
  t_list *old_head;
  int *expected_data;
  int *actual_data;

  expected = list_from_array(values, count);
  actual = list_from_array(values, count);
  expected_data = xmalloc(sizeof(*expected_data));
  actual_data = xmalloc(sizeof(*actual_data));
  *expected_data = value;
  *actual_data = value;
  old_head = actual;
  ref_list_push_front(&expected, expected_data);
  ft_list_push_front(&actual, actual_data);
  /* Estas comprobaciones validan el enlace, no solo los valores visibles. */
  CHECK(actual != old_head, "ft_list_push_front %-12s did not replace the head",
        label);
  CHECK(actual != NULL && actual->data == actual_data,
        "ft_list_push_front %-12s stored the wrong data pointer", label);
  CHECK(actual != NULL && actual->next == old_head,
        "ft_list_push_front %-12s stored the wrong next pointer", label);
  CHECK(lists_equal(actual, expected),
        "ft_list_push_front %-12s differs from the C reference", label);
  free_list(expected);
  if (actual == old_head)
    free(actual_data);
  free_list(actual);
}

static void test_list_push_front(void) {
  const int values[] = {10, 20, 30};

  printf("\n[TEST] ft_list_push_front\n");
  check_push_front_case("empty list", NULL, 0, 42);
  check_push_front_case("non-empty", values, ARRAY_LEN(values), -7);
}

/* ======================= PRUEBAS DE FT_LIST_SORT ====================== */

/* Ordena como la funcion ASM: compara cada nodo con los posteriores e
 * intercambia los punteros data, sin cambiar los enlaces entre nodos. */
static void ref_list_sort(t_list **begin_list,
                          int (*cmp)(const void *, const void *)) {
  t_list *current;
  t_list *other;
  void *temporary;

  current = *begin_list;
  while (current != NULL) {
    other = current->next;
    while (other != NULL) {
      if (cmp(current->data, other->data) > 0) {
        temporary = current->data;
        current->data = other->data;
        other->data = temporary;
      }
      other = other->next;
    }
    current = current->next;
  }
}

/* Ordena dos copias y compara el resultado y la cantidad final de nodos. */
static void check_sort_case(const char *label, const int *values,
                            size_t count) {
  t_list *expected;
  t_list *actual;

  expected = list_from_array(values, count);
  actual = list_from_array(values, count);
  ref_list_sort(&expected, compare_int);
  ft_list_sort(&actual, compare_int);
  CHECK(lists_equal(actual, expected),
        "ft_list_sort %-20s differs from the C reference", label);
  CHECK(ft_list_size(actual) == count,
        "ft_list_sort %-20s changed the number of nodes", label);
  free_list(expected);
  free_list(actual);
}

static void test_list_sort(void) {
  const int one[] = {42};
  const int sorted[] = {-5, -1, 0, 3, 10};
  const int reverse[] = {10, 3, 0, -1, -5};
  const int duplicates[] = {4, 1, 4, 2, 1, 0, 4};
  const int mixed[] = {9, -3, 7, 0, -100, 42, 8};

  printf("\n[TEST] ft_list_sort\n");
  check_sort_case("empty list", NULL, 0);
  check_sort_case("one node", one, ARRAY_LEN(one));
  check_sort_case("already sorted", sorted, ARRAY_LEN(sorted));
  check_sort_case("reverse order", reverse, ARRAY_LEN(reverse));
  check_sort_case("duplicates", duplicates, ARRAY_LEN(duplicates));
  check_sort_case("mixed values", mixed, ARRAY_LEN(mixed));
}

/* ==================== PRUEBAS DE FT_LIST_REMOVE_IF ==================== */

/* Los dos callbacks liberan datos y registran cuantas veces fueron llamados. */
static void ref_free_data(void *data) {
  ++g_ref_freed;
  free(data);
}

static void ft_free_data(void *data) {
  ++g_ft_freed;
  free(data);
}

/* Referencia C basada en puntero-a-puntero. El mismo enlace se conserva tras
 * eliminar para poder procesar correctamente coincidencias consecutivas. */
static void ref_list_remove_if(t_list **begin_list, void *data_ref,
                               int (*cmp)(const void *, const void *),
                               void (*free_fct)(void *)) {
  t_list **link;
  t_list *node;

  link = begin_list;
  while (*link != NULL) {
    node = *link;
    if (cmp(node->data, data_ref) == 0) {
      *link = node->next;
      free_fct(node->data);
      free(node);
    } else {
      link = &node->next;
    }
  }
}

/* Compara la lista resultante, el numero de liberaciones y el tamano final. */
static void check_remove_case(const char *label, const int *values,
                              size_t count, int reference) {
  t_list *expected;
  t_list *actual;

  expected = list_from_array(values, count);
  actual = list_from_array(values, count);
  g_ref_freed = 0;
  g_ft_freed = 0;
  /* Cada implementacion trabaja sobre una copia para no compartir memoria. */
  ref_list_remove_if(&expected, &reference, compare_equal, ref_free_data);
  ft_list_remove_if(&actual, &reference, compare_equal, ft_free_data);
  CHECK(lists_equal(actual, expected),
        "ft_list_remove_if %-15s differs from the C reference", label);
  CHECK(g_ft_freed == g_ref_freed,
        "ft_list_remove_if %-15s expected %zu frees, got %zu", label,
        g_ref_freed, g_ft_freed);
  CHECK(ft_list_size(actual) == ref_list_size(expected),
        "ft_list_remove_if %-15s produced the wrong size", label);
  free_list(expected);
  free_list(actual);
}

static void test_list_remove_if(void) {
  const int no_match[] = {1, 2, 3};
  const int head[] = {7, 1, 2, 3};
  const int middle[] = {1, 7, 2, 3};
  const int tail[] = {1, 2, 3, 7};
  const int consecutive[] = {7, 7, 1, 7, 7, 2, 7};
  const int all[] = {7, 7, 7};

  printf("\n[TEST] ft_list_remove_if\n");
  check_remove_case("empty list", NULL, 0, 7);
  check_remove_case("no matches", no_match, ARRAY_LEN(no_match), 7);
  check_remove_case("head", head, ARRAY_LEN(head), 7);
  check_remove_case("middle", middle, ARRAY_LEN(middle), 7);
  check_remove_case("tail", tail, ARRAY_LEN(tail), 7);
  check_remove_case("consecutive", consecutive, ARRAY_LEN(consecutive), 7);
  check_remove_case("all nodes", all, ARRAY_LEN(all), 7);
}

int main(void) {
  /* Ejecuta todos los grupos aunque alguno falle y resume al finalizar. */
  test_atoi_base();
  test_list_size();
  test_list_push_front();
  test_list_sort();
  test_list_remove_if();
  if (g_failures == 0) {
    printf("[OK] %zu bonus checks passed\n", g_checks);
    return EXIT_SUCCESS;
  }
  fprintf(stderr, "[KO] %zu of %zu bonus checks failed\n", g_failures,
          g_checks);
  return EXIT_FAILURE;
}
