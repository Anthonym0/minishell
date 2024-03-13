/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherve <aherve@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:10:34 by aherve            #+#    #+#             */
/*   Updated: 2024/03/08 13:23:46 by aherve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern int	g_signal;

int	manage_fds(t_cmd *cmds, int pipes[2][2])
{
	if (cmds == NULL || pipes == NULL)
		return (-1);
	if (cmds->fdout != NULL && output_redirect(cmds->fdout) == -1)
		return (-1);
	if (cmds->fdout == NULL && cmds->pipe != NULL)
		if (dup2(pipes[1][1], STDOUT_FILENO) == -1)
			return (-1);
	if (cmds->fdin != NULL && input_redirect(cmds->fdin) == -1)
		return (-1);
	if (cmds->fdin == NULL)
		if (dup2(pipes[0][0], STDIN_FILENO) == -1)
			return (-1);
	if (close(pipes[0][0]) == -1 || close(pipes[0][1]) == -1)
		return (-1);
	if (cmds->pipe != NULL)
		if (close(pipes[1][0]) == -1 || close(pipes[1][1]) == -1)
			return (-1);
	return (0);
}

int	first_fds(t_cmd *cmds, int *pipes)
{
	if (cmds == NULL || pipes == NULL)
		return (-1);
	if (cmds->fdout != NULL && output_redirect(cmds->fdout) == -1)
		return (-1);
	if (cmds->fdin != NULL && input_redirect(cmds->fdin) == -1)
		return (-1);
	if (cmds->fdout == NULL && cmds->pipe != NULL)
		if (dup2(pipes[1], STDOUT_FILENO) == -1)
			return (-1);
	if (cmds->pipe != NULL)
	{
		if (close(pipes[0]) == -1)
			return (-1);
		if (close(pipes[1]) == -1)
			return (-1);
	}
	return (0);
}

int	close_fds(void)
{
	if (close(STDOUT_FILENO) == -1)
		return (-1);
	if (close(STDIN_FILENO) == -1)
		return (-1);
	return (0);
}

int	init_stdfds(int *stdfds)
{
	if (stdfds == NULL)
		return (-1);
	stdfds[0] = dup(STDIN_FILENO);
	if (stdfds[0] == -1)
		return (-1);
	stdfds[1] = dup(STDOUT_FILENO);
	if (stdfds[1] == -1)
	{
		close(stdfds[0]);
		return (-1);
	}
	return (0);
}

int	reinstate_stdfds(int *stdfds)
{
	if (stdfds == NULL)
		return (-1);
	if (dup2(stdfds[0], STDIN_FILENO) == -1)
		return (-1);
	if (dup2(stdfds[1], STDOUT_FILENO) == -1)
		return (-1);
	return (0);
}
