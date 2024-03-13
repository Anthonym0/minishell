/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agranjon <agranjon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 09:42:54 by aherve            #+#    #+#             */
/*   Updated: 2024/03/12 10:00:56 by agranjon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern int	g_signal;

int	find_lastdir(char *str)
{
	int	i;
	int	index;

	if (str == NULL)
		return (-1);
	i = 0;
	index = -1;
	while (str[i] != '\0')
	{
		if (str[i] == '/')
			index = i;
		i++;
	}
	return (index);
}

int	is_empty(char *str)
{
	if (str == NULL)
		return (-1);
	while (*str != '\0')
	{
		if (*str >= '!' && *str <= '~')
			return (0);
		str++;
	}
	return (1);
}

char	*add_color(char *str, char *color)
{
	char	*new;
	char	*temp;

	if (str == NULL || color == NULL)
		return (NULL);
	new = ft_strjoin(color, str);
	if (new == NULL)
		return (NULL);
	temp = new;
	new = ft_strjoin(new, RESET);
	free(temp);
	return (new);
}

int	count_slashes(char *ap_name, int cwd_index)
{
	int	count;
	int	i;

	if (ap_name == NULL || cwd_index < 0)
		return (-1);
	count = 0;
	i = 0;
	while (i <= cwd_index)
	{
		if (ap_name[i] == '/')
			count += 1;
		i++;
	}
	return (count);
}
