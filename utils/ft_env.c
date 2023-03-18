/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 17:25:37 by rferrero          #+#    #+#             */
/*   Updated: 2023/03/18 15:47:16 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_env_size(char **env)
{
	int	i;

	i = 0;
	while (env[i] && *env != NULL)
		i++;
	// printf("%d\n", i);
	return (i);
}

static char	**ft_env_calloc(int size, int diff)
{
	char	**ret;

	ret = (char **)ft_calloc(sizeof(char *), size + diff);
	return (ret);
}

void	ft_add_var_env(char *new_variable, t_program *g_data)
{
	int		i;
	char	**new_env;

	// transformar esse size em token comamnd size
	if (ft_strncmp(new_variable, "export", 6) == 0)
	{
		if (!new_variable || !g_data->env)
			return ;
		new_env = ft_env_calloc(ft_env_size(g_data->env), 2);
		i = -1;
		while (g_data->env[++i])
			new_env[i] = ft_strdup(g_data->env[i]);
		ft_free_matrix(g_data->env);
		new_env[i] = ft_substr(new_variable, 7, ft_strlen(new_variable) - 6);
		g_data->env = new_env;
	}
}

void	ft_remove_var_env(char *variable, t_program *g_data)
{
	int		i;
	int		j;
	char	*aux;
	char	**new_env;

	// transformar esse size em token comamnd size
	if (ft_strncmp(variable, "unset", 5) == 0)
	{
		if (!variable || !g_data->env || ft_strlen(variable) <= 6)
			return ;
		aux = ft_substr(variable, 6, ft_strlen(variable) - 6);
		new_env = ft_env_calloc(ft_env_size(g_data->env), 0);
		i = -1;
		j = 0;
		while (g_data->env[++i + j])
		{
			if (ft_strncmp(g_data->env[i + j], aux, ft_strlen(aux)) == 0)
				j = 1;
			if (g_data->env[i + j] == NULL)
				break ;
			new_env[i] = ft_strdup(g_data->env[i + j]);
		}
		free(aux);
		ft_free_matrix(g_data->env);
		g_data->env = new_env;
	}
}

void	ft_print_env(char *cmd, t_program *g_data)
{
	int	i;

	i = -1;
	if (ft_strncmp(cmd, "env", 3) == 0)
	{
		if (!g_data->env || !cmd || ft_strlen(cmd) < 3)
			return ;
		while (g_data->env[++i])
			printf("%s\n", g_data->env[i]);
	}
}
