/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherve <aherve@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:06:08 by aherve            #+#    #+#             */
/*   Updated: 2024/03/11 18:31:47 by aherve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern int	g_signal;

void	free_tokens(t_token *token)
{
	if (token == NULL)
		return ;
	if (token->next != NULL)
		free_tokens(token->next);
	if (token->str != NULL)
		free(token->str);
	free(token);
}

t_token	*token_addback(t_token *first, t_token *cur)
{
	if (cur == NULL)
		return (NULL);
	if (first == NULL)
		return (cur);
	last_token(first)->next = cur;
	return (first);
}

t_token	*last_token(t_token *token)
{
	if (token == NULL)
		return (NULL);
	if (token->next != NULL)
		return (last_token(token->next));
	return (token);
}

t_token	*new_token(char *str, int len)
{
	t_token	*new;

	if (str == NULL || len == -1)
		return (NULL);
	new = malloc(sizeof(t_token));
	if (new == NULL)
		return (NULL);
	new->str = str;
	new->len = len;
	new->next = NULL;
	return (new);
}
