/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherve <aherve@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 13:19:46 by agranjon          #+#    #+#             */
/*   Updated: 2024/03/11 18:02:07 by aherve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern int	g_signal;

int	has_separator(char *str, char sep)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (-1);
	while (str[i])
	{
		if (str[i] == sep)
			return (1);
		i++;
	}
	return (0);
}

int	env(char **env)
{
	int		i;

	i = 0;
	if (env == NULL)
		return (-1);
	while (env[i])
	{
		if (g_signal != 0)
			return (return_signals());
		if (ft_strcmp_sep(env[i], "?", '=') != 0)
		{
			if (has_separator(env[i], '='))
			{
				if (printf("%s", env[i]) != ft_strlen(env[i]))
					return (-1);
				if (printf("\n") != 1)
					return (-1);
			}
		}
		i++;
	}
	return (0);
}
