/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 16:19:46 by rferrero          #+#    #+#             */
/*   Updated: 2023/05/01 04:19:57 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_program	g_data;

int	main(int argc, char **argv, char **envp)
{
	if (argc != 1)
	{
		printf("Minishell don't need any arguments to run\n");
		exit(EXIT_FAILURE);
	}
	g_data = (t_program){0};
	ft_start(envp);
	ft_loop();
	rl_clear_history();
	ft_free_data();
	ft_close_fds();
	return (g_data.exit_code);
}
