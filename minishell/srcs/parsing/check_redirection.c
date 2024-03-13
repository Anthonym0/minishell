/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agranjon <agranjon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 09:51:19 by aherve            #+#    #+#             */
/*   Updated: 2024/03/12 10:38:34 by agranjon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern int	g_signal;

char	*merge(t_token *token)
{
	char	*new;

	if (token == NULL || token->next == NULL)
		return (NULL);
	if (is_next_valid(token->next->str) != 1)
		return (NULL);
	new = ft_strjoin(token->str, token->next->str);
	if (new == NULL)
		return (NULL);
	free(token->next->str);
	token->next->str = NULL;
	free(token->str);
	token->len = ft_strlen(new);
	return (new);
}

char	*check_tokens(t_token *token)
{
	int	status;

	if (token == NULL)
		return (NULL);
	status = is_valid_redirection(token->str);
	if (status <= 0)
		return (NULL);
	if (status == 2)
		return (token->str);
	return (merge(token));
}

int	handle_redirection_tokens(t_token *list)
{
	char	*temp;
	int		status;

	if (list == NULL)
		return (err_msg_parsing("Redirection' checking failed\n"), -1);
	while (list != NULL)
	{
		status = is_redirection(list->str);
		if (status == 1)
		{	
			temp = check_tokens(list);
			if (temp == NULL)
				return (err_msg_parsing("Invalid redirection\n"), -1);
			list->str = temp;
		}
		list = list->next;
	}
	return (0);
}
