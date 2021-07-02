# my-shell-for-unix
Учебный проект разработка мини оболочки

## Команда

#### [Pavel-Bylkov](https://github.com/Pavel-Bylkov)

#### [aamarei-21](https://github.com/aamarei-21)

## Цель проекта

Сделать мини версию Bash.
В проекте мы использовали нашу библиотеку стандартных функций для работы со строками (libft), стандартные функции (printf, malloc, free, write, open, read, close, fork, wait, waitpid, signal, kill, exit, getcwd, chdir, stat, lstat, fstat, unlink, execve, dup, dup2, pipe, opendir, readdir, closedir, strerror, errno, isatty, ttyname, ttyslot, ioctl, getenv) и
некоторое количество функций из библиотек readline и termcap (readline, rl_on_new_line, rl_replace_line,
rl_redisplay, add_history, tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs).

Mshell работает в macos (требуется установка readline) и linux (требуется установка termcap).

## Building

Запуск оболочки:
``$> make && ./mshell``

## Возможности

|:---------|
|Отображение приглашения ввода команд|
|Сохранение истории выполненных команд|
|Выполнение стандартных команд и двоичных файлов из PATH или с указанием пути к файлу|
|Логические операторы `&&` `\|\|`|
|Разделение на команды через `;`|
|Использование двойных и одинарных ковычек|
|Редиректы `>>` `<<` `>` `<`|
|Пайпы (трубы) `\|`|
|Использование переменных виртуального окружения (с редактированием, добавлением и удалением)|
|Обработка сигналов|
|`Ctrl + D`|
|`Ctrl + \`|
|`Ctrl + C`|

|Встроенные команды   |
|:---------|
|echo: с -n опцией|
|cd: с `-` опцией и переходами по абсолютным и относительным путям|
|pwd: без опций|
|export: без опций|
|env: без опций|
|unset: без опций|
|exit: с аргументом|

## Редактор командной строки

|Клавиши   |Описание действия             |
|:---------:|:------------------------|
`↑/↓`		|Навигация по истории команд
`→`			|Перемещение курсора на один символ вправо
`←`			|Перемещение на один символ влево
`home`		|Перемещение в начало строки
`end`		|Перемещение в конец строки
`ctrl + →`	|Перемещение на одно слово вправо
`ctrl + ←`	|Перемещение на одно слово влево
