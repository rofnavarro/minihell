/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 04:17:06 by rinacio           #+#    #+#             */
/*   Updated: 2023/05/04 20:55:19 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_child_process(t_token *token, char *cmd_path)
{
	g_data.sa_child.sa_handler = &handle_sig_child;
	sigaction(SIGINT, &g_data.sa_child, NULL);
	sigaction(SIGQUIT, &g_data.sa_child, NULL);
	ft_check_pipe_redirection_child(token, cmd_path);
	if (ft_is_builtin_child(token->cmd[0]) || ft_is_export_wo_arg(token))
		ft_exec_child_builtin(token, cmd_path);
	else if (cmd_path)
	{
		if (execve(cmd_path, token->cmd, g_data.env) == -1)
			return (perror(NULL));
	}
	if (!cmd_path)
	{
		if (execve(token->cmd[0], token->cmd, g_data.env) == -1)
			return (perror(NULL));
	}
}

void	ft_check_pipe_redirection_child(t_token *token, char *cmd_path)
{
	if (token->prev && token->prev->type == LESS)
	{
		dup2(g_data.infile, STDIN_FILENO);
		close(g_data.infile);
	}
	if (token->type == PIPE || (ft_next_pipe(token)
			&& token->type != GREATER && token->type != GREATER_GREATER))
		redirect_to_pipe();
	if (token->prev && token->prev->type == PIPE)
	{
		redirect_from_pipe(token->type);
		if (handle_redirections(token) == 2)
		{
			free(cmd_path);
			ft_free_child_process();
			exit (1);
		}
	}
}

void	ft_exec_child_builtin(t_token *token, char *cmd_path)
{
	g_data.exit_code = 0;
	if (ft_strncmp(token->cmd[0], "env",
			ft_strlen(token->cmd[0])) == 0 && token->cmd[1] == NULL)
		ft_print_env(token->cmd[0]);
	else if (ft_strncmp(token->cmd[0], "pwd", ft_strlen(token->cmd[0])) == 0)
		ft_pwd(token->cmd[0]);
	else if (ft_strncmp(token->cmd[0], "echo", ft_strlen(token->cmd[0])) == 0)
		ft_echo(token->cmd);
	else if (ft_strncmp(token->cmd[0], "export", ft_strlen(token->cmd[0])) == 0)
		ft_export(token->cmd);
	free(cmd_path);
	ft_free_child_process();
	exit (g_data.exit_code);
}

void	ft_wait_children(void)
{
	int	pid_waited;
	int	wstatus;
	int	i;

	wstatus = 0;
	if (g_data.count_fork)
	{
		i = 0;
		g_data.exit_code = 0;
		while (i++ < g_data.count_fork)
		{
			pid_waited = waitpid(-1, &wstatus, 0);
			if (!ft_check_if_signaled(wstatus)
				&& WIFEXITED(wstatus) && WEXITSTATUS(wstatus))
				wstatus = WEXITSTATUS(wstatus);
			if (pid_waited == g_data.pid[g_data.count_fork - 1]
				&& g_data.exit_code != 130 && g_data.exit_code != 131)
				g_data.exit_code = wstatus;
			if (wstatus == 13)
				g_data.exit_code = 1;
		}
	}
}

void	ft_fork(char *cmd_path, t_token *token)
{
	signal(SIGINT, SIG_IGN);
	g_data.pid[g_data.count_fork] = fork();
	if (g_data.pid[g_data.count_fork] < 0)
		return (ft_error_perror(1));
	g_data.count_fork++;
	if (!g_data.pid[g_data.count_fork - 1])
	{
		if (cmd_path)
			ft_child_process(token, cmd_path);
		else
			ft_child_process(token, NULL);
	}
	if (cmd_path)
		free(cmd_path);
}
