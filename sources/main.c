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

    // Сохранение истории в файл .history / очистка памяти.
    save_history(&data);
    free_struct(&data);

    return (error);
}

void                init_struct(t_data *data, char **envp)
{
    data->curr_pars = NULL;
    data->envp = copy_str_array(envp);
    data->history = NULL;
}

void                load_history(t_data *data)
{
    t_history   *new;

    
}

int main_loop(t_data *data)
{
    int error;

    while (1)
    {
        ft_putstr_fd("my_shell>$ ", 1);
        error = read_line(data);
        error = parse_line(data);
        error = run_comands(data);
        error = free_tmp_data(data);
        if (error != 0)
            return (error);
    }
    
}