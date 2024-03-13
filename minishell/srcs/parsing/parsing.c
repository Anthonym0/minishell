/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherve <aherve@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 09:35:04 by aherve            #+#    #+#             */
/*   Updated: 2024/03/12 12:11:35 by aherve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern int	g_signal;

void	signal_catcher_new_line(int sig)
{
	g_signal = sig;
}

void	signal_catcher(void)
{
	signal(SIGINT, signal_catcher_new_line);
	signal(SIGQUIT, signal_catcher_new_line);
}

void	err_msg_parsing(char *text)
{
	if (!text)
		return ;
	write(2, RED"Minishell: PARSING ERROR -> ", 35);
	write(2, text, ft_strlen(text));
	write(2, RESET, 4);
}

int	format_tokens(t_token *list, char **envp)
{
	if (list == NULL || envp == NULL)
		return (-1);
	if (expand_env_vars(list, envp) == -1)
	{
		err_msg_parsing("Environment variables' expansion failed\n");
		return (free_tokens(list), -1);
	}
	if (handle_redirection_tokens(list) == -1)
		return (free_tokens(list), -1);
	if (are_valid_pipes(list) == -1)
		return (free_tokens(list), -1);
	return (0);
}

t_cmd	*parsing(char *line, char **envp)
{
	t_token	*list;
	t_cmd	*cmds;

	if (line == NULL || envp == NULL)
		return (NULL);
	signal_catcher();
	if (quotes_open(line) != 0)
		return (NULL);
	list = create_token_list(line);
	if (list == NULL)
		return (NULL);
	if (format_tokens(list, envp) == -1)
		return (NULL);
	cmds = create_cmd_struct(list);
	if (cmds == NULL)
		return (free_tokens(list), NULL);
	free_tokens(list);
	if (convert_tokens_in_args(cmds) == -1)
	{
		err_msg_parsing("Tokens' conversion in char** failed\n");
		return (free_cmds(cmds), NULL);
	}
	if (g_signal != 0)
		return (free_cmds(cmds), NULL);
	return (cmds);
}
