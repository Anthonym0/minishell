/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agranjon <agranjon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:39:36 by aherve            #+#    #+#             */
/*   Updated: 2024/03/12 09:56:48 by agranjon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern int	g_signal;

int	fill_redirections(t_token *token, t_cmd *cmds)
{
	if (token == NULL || cmds == NULL)
		return (-1);
	if (*(token->str) == '>' && *(token->str + 1) == '>')
		return (output_redirection(token, cmds));
	if (*(token->str) == '<' && *(token->str + 1) == '<')
		return (heredoc_redirection(token, cmds));
	if (*(token->str) == '>')
		return (output_redirection(token, cmds));
	return (input_redirection(token, cmds));
}

int	handle_token2(t_token *token, t_cmd *cmds)
{
	char	*temp;
	int		status;

	if (token == NULL || cmds == NULL)
		return (-1);
	temp = trim_quotes(token->str, token->len);
	if (temp == NULL)
		return (-1);
	if (has_quotes(token->str) == 1)
	{
		free(token->str);
		token->str = temp;
	}
	status = is_redirection(token->str);
	if (status == -1)
		return (-1);
	if (status == 1)
		return (fill_redirections(token, cmds));
	if (cmds->command == NULL)
		return (fill_command(token, cmds));
	else
		return (fill_tokens(token, cmds));
	return (0);
}

int	handle_token(t_token *token, t_cmd *cmds)
{
	int		status;
	t_cmd	*new;

	if (token == NULL || cmds == NULL)
		return (-1);
	status = is_pipe(token->str);
	if (status == 0)
		return (handle_token2(token, cmds));
	if (status == -1)
		return (0);
	new = new_cmd();
	if (new == NULL)
		return (-1);
	cmds = cmd_addback(cmds, new);
	if (cmds == NULL)
		return (-1);
	return (0);
}

t_cmd	*create_cmd_struct(t_token *list)
{
	t_cmd	*cmds;

	if (list == NULL)
		return (NULL);
	cmds = new_cmd();
	if (cmds == NULL)
		return (NULL);
	while (list != NULL)
	{
		if (handle_token(list, last_cmd(cmds)) == -1)
			return (free(cmds), NULL);
		list = list->next;
	}
	return (cmds);
}
