/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherve <aherve@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:05:24 by aherve            #+#    #+#             */
/*   Updated: 2024/03/11 18:22:04 by aherve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern int	g_signal;

int	count_tokens(t_token *token)
{
	if (token == NULL)
		return (-1);
	if (token->next == NULL)
		return (1);
	return (count_tokens(token->next) + 1);
}

char	**create_args(t_token *token, int count)
{
	char	**new;
	int		i;

	if (token == NULL)
		return (NULL);
	new = malloc(sizeof(char *) * (count + 2));
	if (new == NULL)
		return (NULL);
	new[0] = ft_strdup("\0");
	if (new[0] == NULL)
		return (free(new), NULL);
	i = 1;
	while (token != NULL)
	{
		new[i] = ft_strdup(token->str);
		if (new[i] == NULL)
			return (ft_reverse_free_tab(new, i), NULL);
		i++;
		token = token->next;
	}
	new[i] = NULL;
	return (new);
}

char	**no_args(void)
{
	char	**new;

	new = malloc(sizeof(char *) * 2);
	if (new == NULL)
		return (NULL);
	new[0] = ft_strdup("\0");
	if (new[0] == NULL)
		return (free(new), NULL);
	new[1] = NULL;
	return (new);
}

int	convert_tokens_in_args(t_cmd *cmds)
{
	int	count;

	if (cmds == NULL)
		return (-1);
	while (cmds != NULL)
	{
		count = count_tokens(cmds->tokens);
		if (count <= 0)
		{
			cmds->args = no_args();
			if (cmds->args == NULL)
				return (-1);
		}
		if (count > 0)
		{
			cmds->args = create_args(cmds->tokens, count);
			if (cmds->args == NULL)
				return (-1);
		}
		cmds = cmds->pipe;
	}
	return (0);
}
