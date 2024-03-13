/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherve <aherve@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:58:33 by aherve            #+#    #+#             */
/*   Updated: 2024/03/11 18:19:58 by aherve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern int	g_signal;

t_garb	*create_garbage(t_cmd *cmds, char *buff, char ***env)
{
	t_garb	*new;

	if (cmds == NULL || buff == NULL || env == NULL)
		return (NULL);
	new = malloc(sizeof(t_garb));
	if (new == NULL)
		return (NULL);
	new->cmds = cmds;
	new->buffer = buff;
	new->env = env;
	return (new);
}

void	delete_tmp_files(t_cmd *cmds)
{
	if (cmds == NULL)
		return ;
	if (cmds->pipe != NULL)
		delete_tmp_files(cmds->pipe);
	if (cmds->fdin != NULL)
	{
		if (cmds->fdin[0] == '<' && cmds->fdin[1] == '<')
			unlink(cmds->fdin + 2);
	}
}

void	err_msg_banner(void)
{
	write(2, RED"Minishell: FATAL ERROR -> ", 33);
	write(2, "print problem\n"RESET, 15);
	printf(WHITE"\nexiting Minishell....\n"RESET);
}

int	print_banner(void)
{
	if (printf(HIGH_GREEN"  __  __ _      _    _        _ _\n") == -1)
		return (-1);
	if (printf(" |  \\/  (_)_ _ (_)__| |_  ___| | |\n") == -1)
		return (-1);
	if (printf(" | |\\/| | | ' \\| (_-< ' \\/ -_) | |\n") == -1)
		return (-1);
	if (printf(" |_|  |_|_|_||_|_/__/_||_\\___|_|_|\n\n"RESET) == -1)
		return (-1);
	return (0);
}
