/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 02:39:36 by rinacio           #+#    #+#             */
/*   Updated: 2023/04/15 23:50:56 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_sigint_empty(int sig)
{
	if (sig == SIGINT)
	{
		g_data.exit_code = 130;
		printf("\n");
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handle_sig_child(int sig)
{
	if (sig == SIGQUIT)
	{
		g_data.aux_sig = 131;
		printf("Quit (core dumped)\n");
		g_data.exit_code = 131;
	}
	if (sig == SIGINT)
	{
		g_data.aux_sig = 130;
		g_data.exit_code = 130;
		printf("\n");
	}
}