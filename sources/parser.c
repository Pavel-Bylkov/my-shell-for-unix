#include "my_shell.h"

t_pars				*ft_parsnew(int error, char *path, char **argv, char f_spec)
{
    t_pars  *rez;
	  int     j;

    rez = (t_pars *)malloc(sizeof(*rez));
    if (rez == NULL)
        return (NULL);
    if (path)
    {
        j = -1;
        rez->path = (char *)malloc(sizeof(char) * ft_strlen(path) + 1);
        while (path[++j] != '\0')
          rez->path[j] = path[j];
        rez->path[j] = '\0';
    }
    else
      rez->path = NULL;
    rez->argv = argv;
    rez->next = NULL;
    rez->redirect = NULL;
    return (rez);
}

void				ft_parsadd_back(t_pars **lst, t_pars *new)
{
	t_pars	*last;

	if (*lst == NULL)
		*lst = new;
	else
	{
		last = *lst;
		while (last->next != NULL)
		  last = last->next;
		last->next = new;
	}
}

// void				ft_parsclear(t_pars **lst, void (*del)(void*));

int parse_line(t_data *data)
{
    t_pars *current;

    return (0);
}

/*
int fread_line(t_data *data)
{
  int bufsize = RL_BUFSIZE;
  int position = 0;
  char *buffer = malloc(sizeof(char) * bufsize);
  int c;

  data->history = ft_historynew(buffer);

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
      bufsize += RL_BUFSIZE;
      buffer = realloc(buffer, bufsize);
      if (!buffer) {
        fprintf(stderr, "lsh: ошибка выделения памяти\n");
        exit(EXIT_FAILURE);
      }
    }
  }
}
*/
