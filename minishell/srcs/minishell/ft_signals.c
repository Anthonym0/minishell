/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherve <aherve@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:35:06 by aherve            #+#    #+#             */
/*   Updated: 2024/03/12 12:14:02 by aherve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern int	g_signal;

void	init_signals(void)
{	
	g_signal = 0;
	signal(SIGINT, sigint_received);
	signal(SIGQUIT, SIG_IGN);
}

void	change_sigint(char **env)
{
	if (!env)
		return ;
	if (g_signal != 0)
	{
		g_signal = 0;
		change_return_status(env, 130);
	}
}

void	sigint_received(int sig)
{
	static int	post_heredoc = 0;

	if (sig == 42)
	{
		post_heredoc = 1;
		return ;
	}
	if (sig == 142)
	{
		post_heredoc = 0;
		return ;
	}
	g_signal = sig;
	if (post_heredoc == 0)
		printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	signal(SIGINT, sigint_received);
	signal(SIGQUIT, SIG_IGN);
}

int	return_signals(void)
{
	if (g_signal == SIGINT)
		return (130);
	if (g_signal == SIGQUIT)
		return (131);
	return (0);
}
