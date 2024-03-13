/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirection_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherve <aherve@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 09:53:00 by aherve            #+#    #+#             */
/*   Updated: 2024/03/11 18:23:53 by aherve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern int	g_signal;

int	is_next_valid(char *str)
{
	if (str == NULL)
		return (-1);
	if (*str == '>' || *str == '<' || *str == '|')
		return (0);
	return (1);
}

int	is_valid_redirection(char *str)
{
	char	c;

	if (str == NULL)
		return (-1);
	c = *str;
	str++;
	if (*str == '\0')
		return (1);
	if ((*str == '>' || *str == '<') && *str != c)
		return (0);
	if (*str == '>' || *str == '<')
		str++;
	if (*str == '\0')
		return (1);
	if (*str == '>' || *str == '<')
		return (0);
	return (2);
}

int	is_redirection(char *str)
{
	if (str == NULL)
		return (-1);
	if (*str == '<' || *str == '>')
		return (1);
	return (0);
}
