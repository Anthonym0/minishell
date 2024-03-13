/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherve <aherve@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 16:00:05 by aherve            #+#    #+#             */
/*   Updated: 2024/03/12 11:47:08 by aherve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	g_signal = 0;

void	clean_prompt(char *buffer, t_cmd *cmds, t_garb *garbage)
{
	if (buffer != NULL)
		free(buffer);
	if (cmds != NULL)
	{
		delete_tmp_files(cmds);
		free_cmds(cmds);
	}
	if (garbage != NULL)
		free(garbage);
}

int	start_cmds(char *buffer, char ***env)
{
	t_cmd	*cmds;
	t_garb	*garbage;
	int		status;

	if (buffer == NULL || env == NULL)
		return (-1);
	garbage = NULL;
	cmds = parsing(buffer, *env);
	if (cmds == NULL)
		return (clean_prompt(buffer, cmds, garbage), printf("\n"), 2);
	garbage = create_garbage(cmds, buffer, env);
	if (garbage == NULL)
	{
		write(2, RED"Minishell: FATAL ERROR\n"RESET, 34);
		return (clean_prompt(buffer, cmds, garbage), -1);
	}
	status = first_command(cmds, env, garbage);
	if (status > 128)
		printf("\n");
	change_return_status(*env, status);
	if (ft_strcmp(cmds->command, "exit") == 0 && cmds->pipe == NULL)
		return (clean_prompt(buffer, cmds, garbage), -2);
	return (clean_prompt(buffer, cmds, garbage), 0);
}

int	start(char ***env)
{
	char	*buffer;
	int		status;

	if (env == NULL)
		return (-1);
	while (1)
	{
		init_signals();
		buffer = prompt();
		change_sigint(*env);
		if (buffer == NULL)
			return (0);
		if (*buffer == '\0')
		{
			free(buffer);
			continue ;
		}
		status = start_cmds(buffer, env);
		if (status == -1 || status == -2)
			return (status);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	**minishell_env;
	int		status;

	(void)argc;
	(void)argv;
	if (envp == NULL)
		return (err_msg_env(), -1);
	signal(SIGINT, sigint_received);
	signal(SIGQUIT, SIG_IGN);
	minishell_env = copy_environnement(envp);
	if (minishell_env == NULL)
		return (err_msg_env(), -1);
	if (print_banner() == -1)
		return (err_msg_banner(), ft_free_tab(minishell_env), -1);
	status = start(&minishell_env);
	rl_clear_history();
	printf(WHITE"\nexiting Minishell....\n"RESET);
	if (status == -1)
		return (ft_free_tab(minishell_env), -1);
	status = final_value(minishell_env);
	ft_free_tab(minishell_env);
	return (status);
}
