/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherve <aherve@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:09:08 by aherve            #+#    #+#             */
/*   Updated: 2024/03/11 18:26:21 by aherve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern int	g_signal;

void	free_cmds(t_cmd *cmds)
{
	if (cmds == NULL)
		return ;
	if (cmds->pipe != NULL)
		free_cmds(cmds->pipe);
	if (cmds->command != NULL)
		free(cmds->command);
	if (cmds->tokens != NULL)
		free_tokens(cmds->tokens);
	if (cmds->args != NULL)
		ft_free_tab(cmds->args);
	if (cmds->fdout != NULL)
		free_tokens(cmds->fdout);
	if (cmds->fdin != NULL)
		free(cmds->fdin);
	free(cmds);
}

t_cmd	*new_cmd(void)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (new == NULL)
		return (NULL);
	new->command = NULL;
	new->tokens = NULL;
	new->args = NULL;
	new->env = NULL;
	new->fdout = NULL;
	new->fdin = NULL;
	new->pipe = NULL;
	return (new);
}

t_cmd	*last_cmd(t_cmd *cmd)
{
	if (cmd == NULL)
		return (NULL);
	if (cmd->pipe != NULL)
		return (last_cmd(cmd->pipe));
	return (cmd);
}

t_cmd	*cmd_addback(t_cmd *first, t_cmd *cmd)
{
	if (cmd == NULL)
		return (NULL);
	if (first == NULL)
		return (cmd);
	last_cmd(first)->pipe = cmd;
	return (first);
}
