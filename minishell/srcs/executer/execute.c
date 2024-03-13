/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherve <aherve@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:12:36 by aherve            #+#    #+#             */
/*   Updated: 2024/03/11 13:56:44 by aherve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern int	g_signal;

int	next_command(t_cmd *cmds, int pipes[2][2], t_garb *g)
{
	int	status;

	if (cmds == NULL || pipes == NULL || g == NULL || g_signal != 0)
		exit(EXIT_FAILURE);
	status = is_builtin(cmds->command);
	if (status == -1)
		exit(EXIT_FAILURE);
	pipes[0][0] = pipes[1][0];
	pipes[0][1] = pipes[1][1];
	if (g_signal != 0)
		exit(EXIT_FAILURE);
	if (status > 0)
	{
		status = built_in(cmds, pipes, status, g);
		free_garbage(g);
		exit(status);
	}
	status = exec(cmds, pipes, g);
	free_garbage(g);
	exit(status);
}

int	set_next_command(t_cmd *cmds, int pipes[2][2], int *stdfds, t_garb *g)
{
	int	pid;

	if (cmds == NULL)
		return (-1);
	pipes[0][0] = pipes[1][0];
	pipes[0][1] = pipes[1][1];
	if (pipe(pipes[1]) == -1 || g_signal != 0)
		return (-1);
	pid = fork();
	if (pid == -1 || g_signal != 0)
		return (close_pipes(pipes[1]), -1);
	if (pid == 0)
	{
		if (stdfds != NULL && close_pipes(stdfds) == -1)
		{
			if (pipes[0][0] != -1)
				close_pipes(pipes[0]);
			return (close_pipes(pipes[1]), exit(EXIT_FAILURE), -1);
		}
		if (pipes[0][0] != -1 && close_pipes(pipes[0]) == -1)
			return (close_pipes(pipes[1]), exit(EXIT_FAILURE), -1);
		next_command(cmds, pipes, g);
	}
	return (pid);
}

int	first_command(t_cmd *cmds, char ***envp, t_garb *g)
{
	int	status;
	int	stdfds[2];

	if (cmds == NULL || envp == NULL || g == NULL)
		return (-1);
	if (init_stdfds(stdfds) == -1 || g_signal != 0)
		return (-1);
	status = is_builtin(cmds->command);
	if (status == -1)
		return (-1);
	if (status > 0)
		status = first_builtin(cmds, envp, stdfds, g);
	else
		status = first_exec(cmds, envp, stdfds, g);
	if (reinstate_stdfds(stdfds) == -1)
		return (close_pipes(stdfds), -1);
	if (close_pipes(stdfds) == -1)
		return (-1);
	return (status);
}
