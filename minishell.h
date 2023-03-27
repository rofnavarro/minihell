/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 16:24:24 by rferrero          #+#    #+#             */
/*   Updated: 2023/03/27 17:36:40 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//  printf()
# include <stdio.h>

//  malloc()  free()  exit()  getenv()
# include <stdlib.h>

//  signal()  sigaction()  sigemptyset()  sigaddset()  kill()
# include <signal.h>

//  write()  access()  read() close()  fork()  getcwd()  chdir()  unlink()
//  execve()  dup()  dup2()  pipe()  isatty()  ttyname() ttyslot()
# include <unistd.h>

//  strerror()
# include <string.h>

//  perror()
# include <errno.h>

//  readline()  rl_clear_history()  rl_on_new_line()  rl_replace_line()
//  rl_redisplay()  add_history()
# include <readline/readline.h>
# include <readline/history.h>

//  open()  stat()  lstat()  fstat()
# include <fcntl.h>
# include <sys/stat.h>

//  wait()  waitpid()  wait3()  wait4()
# include <sys/wait.h> 

//  opendir()  readdir()  closedir()
# include <dirent.h>
# include <sys/types.h>

//  ioctl()
# include <sys/ioctl.h>

// tcsetattr()  tcgetattr()
# include <termios.h>

// tgetent()  tgetflag()  tgetnum()  tgetstr()  tgoto()  tputs()
# include <curses.h>
# include <term.h>

//  libft.a
# include "./libft/libft.h"

//  token
# include "./token.h"

typedef struct s_program
{
	char	*cmd;
	char	*cmd_token;
	int		cmd_type;
	char	**env;
	char	**path;
	int		status;
	int		stop;
	t_token	*token_start;
}	t_program;

//  utils/ft_builtin_cd.c
void		ft_cd(char *str, t_program *g_data);

//  utils/ft_builtin_pwd.c
void		ft_pwd(char *str, t_program *g_data);

//  utils/ft_error.c
void		ft_error(char *msg, int arg);
void		ft_exit(t_program *g_data);

//  utils/ft_free.c
void		ft_free_matrix(char **matrix);

//  utils/ft_init.c
void		ft_init(t_program *g_data);

//  utils/ft_loop.c
void		ft_loop(t_program *g_data);

//  utils/ft_start.c
void		ft_start(char **env, t_program *g_data);

//  utils/ft_strtok.c
char		*ft_strtok(char *str, const char *delim, t_program *g_data);

//  utils/token_list.c
void		ft_add_token(t_program *g_data, char *cmd_token, t_type cmd_type);
void		ft_print_token_list(t_program *g_data);
void		ft_free_token_list(t_program *g_data, t_token *token, int start);
int			ft_check_quotes(char *arg);
char		*ft_switch_inside_quotation(char *str);
char		*ft_switch_back_quotation(char *str, int i, char c);

#endif