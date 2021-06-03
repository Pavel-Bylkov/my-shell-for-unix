#include "my_shell.h"

int main(int argc, char **argv, char **envp)
{
    t_data data;
    int error;

    (void)argc;
    (void)argv;
    // Загрузка файлов конфигурации.
    init_struct(&data, envp);
    load_history(&data);

    // Запуск цикла команд.
    error = main_loop(&data);

    close(data.fd_hist);
    free_struct(&data);

    return (error);
}

