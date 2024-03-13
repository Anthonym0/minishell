/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherve <aherve@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:55:48 by aherve            #+#    #+#             */
/*   Updated: 2024/03/11 18:22:42 by aherve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern int	g_signal;

int	is_pipe(char *str)
{
	if (str == NULL)
		return (-1);
	if (*str == '|')
		return (1);
	return (0);
}

int	are_valid_pipes(t_token *list)
{
	if (list == NULL)
		return (err_msg_parsing("Pipes' checking failed\n"), -1);
	while (list != NULL)
	{
		if (is_pipe(list->str) == 1)
		{
			if (list->next == NULL)
				return (err_msg_parsing("Parse error near a pipe |\n"), -1);
			if (is_pipe(list->next->str) == 1)
				return (err_msg_parsing("Parse error near a pipe |\n"), -1);
		}
		list = list->next;
	}
	return (1);
}
