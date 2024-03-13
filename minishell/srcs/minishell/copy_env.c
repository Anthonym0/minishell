/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherve <aherve@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 19:06:05 by aherve            #+#    #+#             */
/*   Updated: 2024/03/11 18:19:06 by aherve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern int	g_signal;

void	err_msg_env(void)
{
	write(2, RED"Minishell: FATAL ERROR -> ", 33);
	write(2, "environment problem\n"RESET, 24);
	printf(WHITE"\nexiting Minishell....\n"RESET);
}

void	sigint_catcher(int sig)
{
	g_signal = sig;
}

char	**copy_environnement(char **envp)
{
	int		i;
	char	**my_env;

	signal(SIGINT, sigint_catcher);
	if (!envp)
		return (NULL);
	my_env = malloc(sizeof(char *) * (get_double_tab_size(envp) + 2));
	if (!my_env)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		my_env[i] = ft_strdup(envp[i]);
		if (my_env[i] == NULL)
			return (ft_reverse_free_tab(my_env, i), NULL);
		i++;
	}
	my_env[i] = ft_strdup("?=0");
	if (my_env[i] == NULL)
		return (ft_reverse_free_tab(my_env, i), NULL);
	my_env[i + 1] = NULL;
	if (g_signal != 0)
		return (ft_free_tab(my_env), NULL);
	return (my_env);
}
