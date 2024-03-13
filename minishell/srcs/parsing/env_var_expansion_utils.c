/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_expansion_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherve <aherve@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:04:55 by aherve            #+#    #+#             */
/*   Updated: 2024/03/11 18:27:25 by aherve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern int	g_signal;

int	var_len(char *str)
{
	int	len;

	if (str == NULL)
		return (-1);
	len = 0;
	while (str[len] != '\0')
	{
		if (str[len] == '"' || str[len] == '\'' || str[len] <= ' '
			|| str[len] > '~')
			return (len);
		len++;
	}
	return (len);
}

char	*get_var_value(char *env_var)
{
	char	*value;

	if (env_var == NULL)
		return (NULL);
	while (*env_var != '\0' && *env_var != '=')
		env_var++;
	if (*env_var == '\0')
		return (NULL);
	env_var++;
	value = ft_strdup(env_var);
	return (value);
}
