/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherve <aherve@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:58:51 by aherve            #+#    #+#             */
/*   Updated: 2024/03/07 17:05:45 by aherve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern int	g_signal;

int	path_index(char **envp)
{
	int	i;

	if (envp == NULL)
		return (-1);
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strcmp_sep("PATH", envp[i], '=') == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	path_len(char *var_value)
{
	int	i;

	if (var_value == NULL)
		return (-1);
	i = 0;
	while (var_value[i] != '\0')
	{
		if (var_value[i] == ':')
			return (i);
		i++;
	}
	return (i);
}

char	*ft_pathjoin(char *path, char *command)
{
	char	*new;
	int		i;
	int		j;

	if (path == NULL || command == NULL)
		return (NULL);
	new = malloc(sizeof(char) * (ft_strlen(path) + ft_strlen(command) + 2));
	if (new == NULL)
		return (NULL);
	i = 0;
	while (path[i] != '\0')
	{
		new[i] = path[i];
		i++;
	}
	new[i] = '/';
	i++;
	j = 0;
	while (command[j] != '\0')
	{
		new[i + j] = command[j];
		j++;
	}
	new[i + j] = '\0';
	return (new);
}
