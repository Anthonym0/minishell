/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherve <aherve@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:32:25 by aherve            #+#    #+#             */
/*   Updated: 2024/03/11 11:45:04 by aherve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern int	g_signal;

int	nb_len(int status)
{
	int	count;

	count = 1;
	while (status > 10)
	{
		status /= 10;
		count++;
	}
	return (count);
}

char	*create_new_return_var(int status)
{
	char	*new;
	int		status_len;
	int		i;

	status_len = nb_len(status);
	new = malloc(sizeof(char) * (status_len + 3));
	if (new == NULL)
		return (NULL);
	new[0] = '?';
	new[1] = '=';
	i = status_len + 2;
	new[i] = '\0';
	while (status_len > 0)
	{
		i--;
		new[i] = status % 10 + '0';
		status /= 10;
		status_len--;
	}
	return (new);
}

int	change_return_status(char **env, int status)
{
	int		i;
	char	*temp;

	if (env == NULL)
		return (err_msg_env(), -1);
	i = 0;
	while (env[i] != NULL && ft_strcmp_sep("?", env[i], '=') != 0)
		i++;
	if (env[i] == NULL)
		return (err_msg_env(), -1);
	temp = env[i];
	env[i] = create_new_return_var(status);
	if (env[i] == NULL)
	{
		env[i] = temp;
		err_msg_env();
		return (-1);
	}
	free(temp);
	return (0);
}
