#include "test.h"

#define ARRAY_LEN(array) (sizeof(array) / sizeof((array)[0]))
/* Cuenta cada comprobacion y, si falla, registra el error sin detener los
 * tests. */
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

/* Utilidades comunes para preparar los casos de prueba. */
static void fatal(const char *operation) {
  perror(operation);
  exit(EXIT_FAILURE);
}

static void *xmalloc(size_t size) {
  void *memory;

  memory = malloc(size);
  if (memory == NULL)
    fatal("malloc");
  return (memory);
}

static void write_all(int fd, const void *buffer, size_t count) {
  const unsigned char *bytes;
  size_t written;
  ssize_t result;

  bytes = buffer;
  written = 0;
  while (written < count) {
    result = write(fd, bytes + written, count - written);
    if (result > 0)
      written += (size_t)result;
    else if (result < 0 && errno != EINTR)
      fatal("write test setup");
  }
}

static size_t read_all(int fd, void *buffer, size_t capacity) {
  unsigned char *bytes;
  size_t total;
  ssize_t result;

  bytes = buffer;
  total = 0;
  while (total < capacity) {
    result = read(fd, bytes + total, capacity - total);
    if (result > 0)
      total += (size_t)result;
    else if (result == 0)
      break;
    else if (errno != EINTR)
      fatal("read test output");
  }
  return (total);
}

static int result_sign(int value) {
  /* strcmp solo garantiza el signo del resultado, no su valor exacto. */
  return ((value > 0) - (value < 0));
}

/* ======================== PRUEBAS DE FT_STRLEN ======================== */

/* Compara ft_strlen con strlen usando cadenas pequenas y una cadena larga. */
static void check_strlen_case(const char *label, const char *str) {
  size_t expected;
  size_t actual;

  /* Obtiene el valor de referencia y lo compara con la implementacion ASM. */
  expected = strlen(str);
  actual = ft_strlen(str);
  CHECK(actual == expected, "ft_strlen %-18s expected %zu, got %zu", label,
        expected, actual);
}

static void test_strlen(void) {
  char long_string[4097];
  const char embedded_null[] = {'a', 'b', '\0', 'x', 'y', '\0'};
  size_t i;

  printf("[TEST] ft_strlen\n");
  check_strlen_case("empty", "");
  check_strlen_case("one character", "x");
  check_strlen_case("spaces", "   42 Madrid   ");
  check_strlen_case("newlines", "line 1\nline 2\t");
  check_strlen_case("embedded null", embedded_null);
  i = 0;
  while (i < sizeof(long_string) - 1) {
    long_string[i] = (char)('a' + i % 26);
    ++i;
  }
  long_string[i] = '\0';
  check_strlen_case("4096 characters", long_string);
}

/* ======================== PRUEBAS DE FT_STRCMP ======================== */

struct strcmp_case {
  const char *left;
  const char *right;
  const char *label;
};

/* Incluye prefijos y bytes >= 0x80 para comprobar la comparacion sin signo. */
static void test_strcmp(void) {
  /* Cada array contiene un byte limite y '\0' para formar una cadena C valida.
   * Estos casos detectan si ft_strcmp compara incorrectamente con signo. */
  const char high_80[] = {(char)0x80, '\0'};
  const char high_ff[] = {(char)0xff, '\0'};
  const char low_7f[] = {(char)0x7f, '\0'};
  struct strcmp_case cases[] = {
      {"", "", "empty strings"},
      {"abc", "abc", "equal strings"},
      {"abc", "abd", "lower final byte"},
      {"abd", "abc", "greater final byte"},
      {"abc", "abcd", "left is prefix"},
      {"abcd", "abc", "right is prefix"},
      {"", "x", "empty vs non-empty"},
      {"x", "", "non-empty vs empty"},
      {high_80, low_7f, "unsigned 0x80 > 0x7f"},
      {low_7f, high_80, "unsigned 0x7f < 0x80"},
      {high_ff, high_80, "unsigned 0xff > 0x80"},
  };
  size_t i;
  int expected;
  int actual;

  printf("[TEST] ft_strcmp\n");
  i = 0;
  while (i < ARRAY_LEN(cases)) {
    expected = strcmp(cases[i].left, cases[i].right);
    actual = ft_strcmp(cases[i].left, cases[i].right);
    CHECK(result_sign(actual) == result_sign(expected),
          "ft_strcmp %-18s expected sign %d, got %d (value %d)", cases[i].label,
          result_sign(expected), result_sign(actual), actual);
    ++i;
  }
}

/* ======================== PRUEBAS DE FT_STRCPY ======================== */

static void check_strcpy_case(const char *label, const char *source) {
  char *expected;
  char *actual;
  char *expected_return;
  char *actual_return;
  size_t capacity;

  /* Prepara dos destinos identicos: uno para libc y otro para ft_strcpy. */
  capacity = strlen(source) + 32;
  expected = xmalloc(capacity);
  actual = xmalloc(capacity);
  memset(expected, 0xa5, capacity);
  memset(actual, 0xa5, capacity);
  /* El relleno permite detectar escrituras posteriores al terminador nulo. */
  expected_return = strcpy(expected, source);
  actual_return = ft_strcpy(actual, source);
  /* Comprueba tanto el puntero devuelto como todos los bytes del destino. */
  CHECK(expected_return == expected && actual_return == actual,
        "ft_strcpy %-18s returned the wrong destination", label);
  CHECK(memcmp(actual, expected, capacity) == 0,
        "ft_strcpy %-18s produced different bytes", label);
  free(expected);
  free(actual);
}

static void test_strcpy(void) {
  char long_string[4097];
  const char high_bytes[] = {(char)0xff, (char)0x80, 'A', '\0'};
  size_t i;

  printf("[TEST] ft_strcpy\n");
  check_strcpy_case("empty", "");
  check_strcpy_case("one character", "x");
  check_strcpy_case("normal string", "Assembly is precise");
  check_strcpy_case("whitespace", " \t\n ");
  check_strcpy_case("high bytes", high_bytes);
  i = 0;
  while (i < sizeof(long_string) - 1) {
    long_string[i] = (char)('0' + i % 10);
    ++i;
  }
  long_string[i] = '\0';
  check_strcpy_case("4096 characters", long_string);
}

/* ======================== PRUEBAS DE FT_STRDUP ======================== */

static void check_strdup_case(const char *label, const char *source) {
  char *expected;
  char *actual;

  /* Crea dos duplicados para comparar contenido y propiedad de la memoria. */
  expected = strdup(source);
  if (expected == NULL)
    fatal("strdup");
  actual = ft_strdup(source);
  CHECK(actual != NULL, "ft_strdup %-18s returned NULL", label);
  if (actual != NULL) {
    /* El resultado debe coincidir, pero residir en una reserva diferente. */
    CHECK(strcmp(actual, expected) == 0,
          "ft_strdup %-18s produced different content", label);
    CHECK(actual != source && actual != expected,
          "ft_strdup %-18s did not return an independent allocation", label);
  }
  free(expected);
  free(actual);
}

/* Comprueba contenido y que cada duplicado tenga memoria independiente. */
static void test_strdup(void) {
  char long_string[4097];
  const char high_bytes[] = {(char)0xfe, (char)0x81, 'Z', '\0'};
  size_t i;

  printf("[TEST] ft_strdup\n");
  check_strdup_case("empty", "");
  check_strdup_case("one character", "x");
  check_strdup_case("normal string", "duplicate this string");
  check_strdup_case("whitespace", " \t\n ");
  check_strdup_case("high bytes", high_bytes);
  i = 0;
  while (i < sizeof(long_string) - 1) {
    long_string[i] = (char)('A' + i % 26);
    ++i;
  }
  long_string[i] = '\0';
  check_strdup_case("4096 characters", long_string);
}

/* ======================== PRUEBAS DE FT_WRITE ========================= */

static void check_write_success(const char *label, const void *data,
                                size_t count) {
  int ref_pipe[2];
  int ft_pipe[2];
  ssize_t ref_return;
  ssize_t ft_return;
  int ref_errno;
  int ft_errno;
  unsigned char *ref_output;
  unsigned char *ft_output;
  size_t capacity;
  size_t ref_size;
  size_t ft_size;

  /* Cada implementacion escribe en su propio pipe para comparar la salida. */
  if (pipe(ref_pipe) < 0 || pipe(ft_pipe) < 0)
    fatal("pipe");
  /* El valor previo permite comprobar que errno no cambia si hay exito. */
  errno = E2BIG;
  ref_return = write(ref_pipe[1], data, count);
  ref_errno = errno;
  errno = E2BIG;
  ft_return = ft_write(ft_pipe[1], data, count);
  ft_errno = errno;
  if (close(ref_pipe[1]) < 0 || close(ft_pipe[1]) < 0)
    fatal("close pipe writer");
  capacity = count + 1;
  ref_output = xmalloc(capacity);
  ft_output = xmalloc(capacity);
  ref_size = read_all(ref_pipe[0], ref_output, capacity);
  ft_size = read_all(ft_pipe[0], ft_output, capacity);
  /* Compara retorno, errno y contenido realmente escrito en los pipes. */
  CHECK(ft_return == ref_return, "ft_write %-18s expected return %zd, got %zd",
        label, ref_return, ft_return);
  CHECK(ft_errno == ref_errno, "ft_write %-18s expected errno %d, got %d",
        label, ref_errno, ft_errno);
  CHECK(ft_size == ref_size && memcmp(ft_output, ref_output, ref_size) == 0,
        "ft_write %-18s produced different output", label);
  close(ref_pipe[0]);
  close(ft_pipe[0]);
  free(ref_output);
  free(ft_output);
}

static void check_write_error(void) {
  const char data[] = "bad fd";
  ssize_t ref_return;
  ssize_t ft_return;
  int ref_errno;
  int ft_errno;

  /* Un descriptor invalido debe producir el mismo retorno y errno que libc. */
  errno = 0;
  ref_return = write(-1, data, sizeof(data) - 1);
  ref_errno = errno;
  errno = 0;
  ft_return = ft_write(-1, data, sizeof(data) - 1);
  ft_errno = errno;
  CHECK(ft_return == ref_return,
        "ft_write invalid fd expected return %zd, got %zd", ref_return,
        ft_return);
  CHECK(ft_errno == ref_errno, "ft_write invalid fd expected errno %d, got %d",
        ref_errno, ft_errno);
}

/* Compara retorno, errno y bytes escritos por write y ft_write. */
static void test_write(void) {
  const unsigned char binary[] = {0x00, 0x01, 0x7f, 0x80, 0xff};

  printf("[TEST] ft_write\n");
  check_write_success("zero bytes", "ignored", 0);
  check_write_success("short text", "hello", 5);
  check_write_success("binary bytes", binary, sizeof(binary));
  check_write_error();
}

/* ========================= PRUEBAS DE FT_READ ========================= */

static void check_read_success(const char *label, const void *data,
                               size_t data_size, size_t count) {
  int ref_pipe[2];
  int ft_pipe[2];
  ssize_t ref_return;
  ssize_t ft_return;
  int ref_errno;
  int ft_errno;
  unsigned char *ref_buffer;
  unsigned char *ft_buffer;
  size_t capacity;

  /* Ambos pipes reciben exactamente los mismos datos de entrada. */
  if (pipe(ref_pipe) < 0 || pipe(ft_pipe) < 0)
    fatal("pipe");
  write_all(ref_pipe[1], data, data_size);
  write_all(ft_pipe[1], data, data_size);
  if (close(ref_pipe[1]) < 0 || close(ft_pipe[1]) < 0)
    fatal("close pipe writer");
  capacity = count + 16;
  ref_buffer = xmalloc(capacity);
  ft_buffer = xmalloc(capacity);
  /* El relleno revela si alguna lectura modifica bytes fuera del resultado. */
  memset(ref_buffer, 0xa5, capacity);
  memset(ft_buffer, 0xa5, capacity);
  /* Ejecuta ambas lecturas con el mismo errno inicial. */
  errno = E2BIG;
  ref_return = read(ref_pipe[0], ref_buffer, count);
  ref_errno = errno;
  errno = E2BIG;
  ft_return = ft_read(ft_pipe[0], ft_buffer, count);
  ft_errno = errno;
  /* Compara retorno, errno y el buffer completo, incluido el relleno. */
  CHECK(ft_return == ref_return, "ft_read  %-18s expected return %zd, got %zd",
        label, ref_return, ft_return);
  CHECK(ft_errno == ref_errno, "ft_read  %-18s expected errno %d, got %d",
        label, ref_errno, ft_errno);
  CHECK(memcmp(ft_buffer, ref_buffer, capacity) == 0,
        "ft_read  %-18s produced different buffer bytes", label);
  close(ref_pipe[0]);
  close(ft_pipe[0]);
  free(ref_buffer);
  free(ft_buffer);
}

static void check_read_error(void) {
  unsigned char ref_buffer[16];
  unsigned char ft_buffer[16];
  ssize_t ref_return;
  ssize_t ft_return;
  int ref_errno;
  int ft_errno;

  /* El relleno tambien comprueba que una lectura fallida no toque el buffer. */
  memset(ref_buffer, 0xa5, sizeof(ref_buffer));
  memset(ft_buffer, 0xa5, sizeof(ft_buffer));
  errno = 0;
  ref_return = read(-1, ref_buffer, sizeof(ref_buffer));
  ref_errno = errno;
  errno = 0;
  ft_return = ft_read(-1, ft_buffer, sizeof(ft_buffer));
  ft_errno = errno;
  /* Compara el error de syscall y confirma que ambos buffers siguen iguales. */
  CHECK(ft_return == ref_return,
        "ft_read invalid fd expected return %zd, got %zd", ref_return,
        ft_return);
  CHECK(ft_errno == ref_errno, "ft_read invalid fd expected errno %d, got %d",
        ref_errno, ft_errno);
  CHECK(memcmp(ft_buffer, ref_buffer, sizeof(ref_buffer)) == 0,
        "ft_read invalid fd modified the buffer");
}

/* Compara retorno, errno y contenido para lecturas normales y errores. */
static void test_read(void) {
  const unsigned char binary[] = {0x00, 0x01, 0x7f, 0x80, 0xff};

  printf("[TEST] ft_read\n");
  check_read_success("zero bytes", "abc", 3, 0);
  check_read_success("partial read", "abcdef", 6, 3);
  check_read_success("exact read", "abcdef", 6, 6);
  check_read_success("past EOF", "abcdef", 6, 32);
  check_read_success("empty pipe", "", 0, 16);
  check_read_success("binary bytes", binary, sizeof(binary), sizeof(binary));
  check_read_error();
}

int main(void) {
  test_strlen();
  test_strcmp();
  test_strcpy();
  test_strdup();
  test_write();
  test_read();
  if (g_failures == 0) {
    printf("[OK] %zu checks passed\n", g_checks);
    return (EXIT_SUCCESS);
  }
  fprintf(stderr, "[KO] %zu of %zu checks failed\n", g_failures, g_checks);
  return (EXIT_FAILURE);
}
