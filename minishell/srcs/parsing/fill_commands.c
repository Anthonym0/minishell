/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherve <aherve@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:33:24 by aherve            #+#    #+#             */
/*   Updated: 2024/03/08 15:42:10 by aherve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern int	g_signal;

int	output_redirection(t_token *token, t_cmd *cmds)
{
	t_token	*new;
	char	*str;

	if (token == NULL || cmds == NULL)
		return (-1);
	str = ft_strdup(token->str);
	if (str == NULL)
		return (-1);
	new = new_token(str, token->len);
	if (new == NULL)
		return (free(str), -1);
	cmds->fdout = token_addback(cmds->fdout, new);
	if (cmds->fdout == NULL)
		return (free(str), free(new), -1);
	return (0);
}

int	is_in_redirection(char *str)
{
	if (str == NULL)
		return (-1);
	if (*str == '<')
		return (1);
	return (0);
}

int	input_redirection(t_token *token, t_cmd *cmds)
{
	t_token	*cur;

	if (token == NULL || cmds == NULL)
		return (-1);
	if (check_file(token->str + 1) <= 0)
		return (err_msg_input_redir_no_file(token->str + 1), -1);
	if (check_read(token->str + 1) <= 0)
		return (err_msg_input_redir_permission(token->str + 1), -1);
	cur = token->next;
	while (cur != NULL)
	{
		if (is_pipe(cur->str) == 1)
			break ;
		if (is_in_redirection(cur->str) == 1)
		{
			free(token->str);
			token->str = NULL;
			return (0);
		}
		cur = cur->next;
	}
	cmds->fdin = ft_strdup(token->str);
	if (cmds->fdin == NULL)
		return (-1);
	return (0);
}

int	fill_tokens(t_token *token, t_cmd *cmds)
{
	t_token	*new;
	char	*str;

	if (token == NULL || cmds == NULL)
		return (-1);
	str = ft_strdup(token->str);
	if (str == NULL)
		return (-1);
	new = new_token(str, token->len);
	if (new == NULL)
		return (free(str), -1);
	cmds->tokens = token_addback(cmds->tokens, new);
	if (cmds->tokens == NULL)
		return (free(str), free(new), -1);
	return (0);
}

int	fill_command(t_token *token, t_cmd *cmds)
{
	if (token == NULL || cmds == NULL)
		return (-1);
	cmds->command = ft_strdup(token->str);
	if (cmds->command == NULL)
		return (-1);
	return (0);
}
