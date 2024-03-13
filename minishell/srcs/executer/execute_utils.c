/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherve <aherve@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:14:43 by aherve            #+#    #+#             */
/*   Updated: 2024/03/11 10:33:26 by aherve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern int	g_signal;

int	close_pipes(int *pipes)
{
	if (pipes == NULL)
		return (-1);
	if (close(pipes[0]) == -1)
	{
		close(pipes[1]);
		return (-1);
	}
	if (close(pipes[1]) == -1)
		return (-1);
	return (0);
}

int	is_builtin(char *command)
{
	if (command == NULL)
		return (-1);
	if (ft_strcmp(command, "echo") == 0)
		return (1);
	if (ft_strcmp(command, "cd") == 0)
		return (2);
	if (ft_strcmp(command, "pwd") == 0)
		return (3);
	if (ft_strcmp(command, "export") == 0)
		return (4);
	if (ft_strcmp(command, "unset") == 0)
		return (5);
	if (ft_strcmp(command, "env") == 0)
		return (6);
	if (ft_strcmp(command, "exit") == 0)
		return (7);
	return (0);
}

int	return_status(int pid)
{
	int	status;

	status = 0;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) == 1)
		return (WEXITSTATUS(status));
	return (128 + WTERMSIG(status));
}

void	free_garbage(t_garb *garbage)
{
	if (garbage == NULL)
		return ;
	free_cmds(garbage->cmds);
	free(garbage->buffer);
	ft_free_tab(*(garbage->env));
	free(garbage);
	rl_clear_history();
}
