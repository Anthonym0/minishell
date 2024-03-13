/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agranjon <agranjon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:52:16 by aherve            #+#    #+#             */
/*   Updated: 2024/03/12 09:51:13 by agranjon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern int	g_signal;
int			g_sigusr1 = 0;

int	exec_built_in(t_cmd *cmds, int nb, char ***envp)
{
	if (cmds == NULL || envp == NULL)
		return (-1);
	if (nb == 1)
		return (echo(cmds->args));
	if (nb == 2)
		return (cd(cmds->args, *envp));
	if (nb == 3)
		return (pwd());
	if (nb == 4)
		return (export(cmds->args, envp));
	if (nb == 5)
		return (unset(cmds->args, envp));
	if (nb == 6)
		return (env(*envp));
	if (nb == 7)
		return (ft_exit(cmds->args));
	return (0);
}

void	signal_handler(int sig)
{
	g_sigusr1 = sig;
}

void	ft_sleep(void)
{
	while (1)
	{
		if (g_sigusr1 != 0)
			break ;
	}
}

int	built_in(t_cmd *cmds, int pipes[2][2], int status, t_garb *g)
{
	int	pid_cmd;

	signal(SIGUSR1, signal_handler);
	if (cmds == NULL || pipes == NULL || g == NULL)
		return (-1);
	if (cmds->pipe != NULL && g_signal == 0)
	{
		cmds->pipe->env = cmds->env;
		pid_cmd = set_next_command(cmds->pipe, pipes, NULL, g);
		if (pid_cmd == -1)
			return (-1);
	}
	if (manage_fds(cmds, pipes) == -1 || g_signal != 0)
		return (close_fds(), -1);
	status = exec_built_in(cmds, status, cmds->env);
	if (status == -1)
		return (close_fds(), -1);
	ft_sleep();
	if (cmds->pipe != NULL)
		return (close_fds(), return_status(pid_cmd));
	return (close_fds(), status);
}

int	first_builtin(t_cmd *cmds, char ***envp, int *stdfds, t_garb *g)
{
	int	pipes[2][2];
	int	pid_cmd;
	int	status;

	if (cmds == NULL || envp == NULL || stdfds == NULL || g == NULL)
		return (-1);
	cmds->env = envp;
	pipes[1][0] = -1;
	pipes[1][1] = -1;
	if (cmds->pipe != NULL && g_signal == 0)
	{
		cmds->pipe->env = cmds->env;
		pid_cmd = set_next_command(cmds->pipe, pipes, stdfds, g);
		if (pid_cmd == -1)
			return (-1);
	}
	if (first_fds(cmds, pipes[1]) == -1 || g_signal != 0)
		return (close_fds(), -1);
	status = exec_built_in(cmds, is_builtin(cmds->command), envp);
	if (status == -1)
		return (close_fds(), -1);
	if (cmds->pipe != NULL)
		return (close_fds(), return_status(pid_cmd));
	return (close_fds(), status);
}
