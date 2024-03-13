/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agranjon <agranjon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:47:11 by aherve            #+#    #+#             */
/*   Updated: 2024/03/12 10:02:18 by agranjon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern int	g_signal;

void	err_msg_output_redir_permission(char *file_name)
{
	if (!file_name)
		return ;
	write(2, RED"Minishell: EXECUTER ERROR -> ", 36);
	write(2, file_name, ft_strlen(file_name));
	write(2, ": Permission to write denied\n", 29);
	write(2, RESET, 4);
}

void	err_msg_file_creation(char *file_name)
{
	if (!file_name)
		return ;
	write(2, RED"Minishell: EXECUTER ERROR -> ", 36);
	write(2, file_name, ft_strlen(file_name));
	write(2, ": Impossible to create file\n", 28);
	write(2, RESET, 4);
}

void	err_msg_input_redir_exec_no_file(char *file_name)
{
	if (!file_name)
		return ;
	write(2, RED"Minishell: EXECUTER ERROR -> ", 36);
	write(2, file_name, ft_strlen(file_name));
	write(2, ": No such file or directory\n", 28);
	write(2, RESET, 4);
}

void	err_msg_input_redir_exec_permission(char *file_name)
{
	if (!file_name)
		return ;
	write(2, RED"Minishell: EXECUTER ERROR -> ", 36);
	write(2, file_name, ft_strlen(file_name));
	write(2, ": Permission to read denied\n", 28);
	write(2, RESET, 4);
}
