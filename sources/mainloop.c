#include "my_shell.h"

//обработчик SIGINT
static void     int_handler(int status)
{
    if (status == SIGINT)
    {
        //rl_display_prompt = SHELL_PROMT;
        printf("\n"); // Move to a new line
        rl_on_new_line(); // Regenerate the prompt on a newline
        rl_replace_line("", 0); // Clear the previous text
        rl_redisplay();
    }
}

int main_loop(t_data *data)
{
    int error;

    //read_history(HISTORY_FILE); // переписать на свою?
    //rl_prompt = ;
    (void)int_handler;
    while (1)
    {
        data->line = readline(SHELL_PROMT);
        add_history(data->line);
        //write_history(HISTORY_FILE); // переписать на свою?
        error = parse_line(data);
        run_comands(data, error);
        print_pars(data);
        if (data->line)
		    free(data->line);
	    ft_parsclear(&(data->curr_pars));
    }
}

// len = ft_strlen(data->history->line);
// endl_ignor = (backslash_is_active(data->line, len) ||
// 						quaote_is_open(data->line, len) != 0);