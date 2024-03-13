/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherve <aherve@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:52:24 by aherve            #+#    #+#             */
/*   Updated: 2024/03/12 12:06:24 by aherve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern int	g_signal;

int	ft_execve(t_cmd *cmds, int *stdfds)
{
	int	pid;

	if (cmds == NULL)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		if (stdfds != NULL && close_pipes(stdfds) == -1)
			exit(EXIT_FAILURE);
		execve(cmds->command, cmds->args, *(cmds->env));
	}
	signal(SIGINT, SIG_IGN);
	sigint_received(142);
	return (pid);
}

void	err_msg_cmd_not_found(char *cmd_name)
{
	if (!cmd_name)
		return ;
	write(2, RED"Minishell: EXECUTER ERROR -> ", 36);
	write(2, cmd_name, ft_strlen(cmd_name));
	write(2, ": Command not found or Impossible to execute\n", 45);
	write(2, RESET, 4);
}

int	launch(t_cmd *cmds, int *stdfds)
{
	int		status;
	char	*temp;
	int		pid;

	if (cmds == NULL)
		return (-1);
	status = check_execute(cmds->command);
	if (status == -1)
		return (-1);
	if (status == 0)
	{
		temp = cmds->command;
		cmds->command = find_path_command(cmds->command, *(cmds->env));
		if (cmds->command == NULL)
			err_msg_cmd_not_found(temp);
		free(temp);
	}
	if (cmds->command == NULL)
		return (127);
	pid = ft_execve(cmds, stdfds);
	if (pid == -1)
		return (-1);
	return (return_status(pid));
}

int	exec(t_cmd *cmds, int pipes[2][2], t_garb *g)
{
	int	pid_cmd;
	int	status_exec;

	if (cmds == NULL || pipes == NULL || g == NULL || g_signal != 0)
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
	status_exec = launch(cmds, NULL);
	if (close_fds() == -1 || status_exec == -1)
		return (-1);
	if (cmds->pipe != NULL && is_builtin(cmds->pipe->command) != 0)
		kill(pid_cmd, SIGUSR1);
	if (cmds->pipe != NULL)
		return (return_status(pid_cmd));
	return (status_exec);
}

int	first_exec(t_cmd *cmds, char ***envp, int *stdfds, t_garb *g)
{
	int		pipes[2][2];
	int		pid_cmd;
	int		status_exec;

	if (cmds == NULL || envp == NULL || stdfds == NULL || g == NULL)
		return (-1);
	cmds->env = envp;
	pid_cmd = 0;
	pipes[1][0] = -1;
	pipes[1][1] = -1;
	if (cmds->pipe != NULL && g_signal == 0)
	{
		cmds->pipe->env = cmds->env;
		pid_cmd = set_next_command(cmds->pipe, pipes, stdfds, g);
	}
	if (pid_cmd == -1 || first_fds(cmds, pipes[1]) == -1 || g_signal != 0)
		return (close_fds(), -1);
	status_exec = launch(cmds, stdfds);
	if (close_fds() == -1 || status_exec == -1)
		return (-1);
	if (cmds->pipe != NULL && is_builtin(cmds->pipe->command) != 0)
		kill(pid_cmd, SIGUSR1);
	if (cmds->pipe != NULL)
		return (return_status(pid_cmd));
	return (status_exec);
}
