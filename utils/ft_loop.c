/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 20:43:08 by rferrero          #+#    #+#             */
/*   Updated: 2023/03/09 16:08:43 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_loop(t_program *g_data)
{
	while (g_data->stop == 0)
	{
		g_data->cmd = readline("hell$: ");
		//if (!g_data->cmd) 		// verificar ctr+d (EOF - free all - exit)
		//	break ;
		add_history(g_data->cmd);
		g_data->cmd_token = ft_strtok(g_data->cmd, " ");
		while (g_data->cmd_token != NULL)
		{
			ft_add_token(g_data, g_data->cmd_token, 1);
			//ft_add_token(g_data->cmd_token, g_data->cmd_type);
			g_data->cmd_token = ft_strtok(NULL, " ");
		}
		ft_print_token_list(g_data);
		ft_free_token_list(g_data, g_data->token_start, 1);
		ft_exit(g_data);
		free(g_data->cmd);
	}
	ft_free_env_list(g_data->env_start);
	ft_free_matrix(g_data->path);
	rl_clear_history();
}
