#include "my_shell.h"

int read_line(t_data *data)
{
  int bufsize = RL_BUFSIZE;
  int position = 0;
  char *buffer = malloc(sizeof(char) * bufsize);
  t_history			*tmp;
  int c;

    data->history = t_history			*ft_historynew(char *line);

  if (!buffer) {
    fprintf(stderr, "lsh: ошибка выделения памяти\n");
    exit(EXIT_FAILURE);
  }

  while (1) {
    // Читаем символ
    c = getchar();

    // При встрече с EOF заменяем его нуль-терминатором и возвращаем буфер
    if (c == EOF || c == '\n') {
      buffer[position] = '\0';
      return buffer;
    } else {
      buffer[position] = c;
    }
    position++;

    // Если мы превысили буфер, перераспределяем блок памяти
    if (position >= bufsize) {
      bufsize += LSH_RL_BUFSIZE;
      buffer = realloc(buffer, bufsize);
      if (!buffer) {
        fprintf(stderr, "lsh: ошибка выделения памяти\n");
        exit(EXIT_FAILURE);
      }
    }
  }
}