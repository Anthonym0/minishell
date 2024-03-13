/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherve <aherve@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:08:58 by aherve            #+#    #+#             */
/*   Updated: 2024/03/08 15:51:46 by aherve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern int	g_signal;

int	open_fdout(char *str, int mode)
{
	int	fd;

	if (str == NULL)
		return (-1);
	fd = check_file(str);
	if (fd == -1)
		return (-1);
	if (check_file(str) == 1)
	{
		if (check_write(str) <= 0)
			return (err_msg_output_redir_permission(str), -1);
	}
	if (mode == 1)
		fd = open(str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (err_msg_file_creation(str), -1);
	return (fd);
}

int	output_redirect(t_token *fdout)
{
	int		fd;

	if (fdout == NULL)
		return (-1);
	while (fdout != NULL)
	{
		if (*(fdout->str) == '>' && *(fdout->str + 1) == '>')
			fd = open_fdout(fdout->str + 2, 1);
		else
			fd = open_fdout(fdout->str + 1, 0);
		if (fd == -1)
			return (-1);
		if (fdout->next != NULL)
			close(fd);
		fdout = fdout->next;
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (close(fd), -1);
	if (close(fd) == -1)
		return (-1);
	return (0);
}

int	input_redirect(char *fdin)
{
	int		fd;
	char	*temp;

	if (fdin == NULL)
		return (-1);
	if (*(fdin) == '<' && *(fdin + 1) == '<')
		temp = fdin + 2;
	else
		temp = fdin + 1;
	fd = check_file(temp);
	if (fd <= 0)
		return (err_msg_input_redir_exec_no_file(temp), -1);
	if (fd == 1)
		if (check_read(temp) <= 0)
			return (err_msg_input_redir_exec_permission(temp), -1);
	fd = open(temp, O_RDONLY);
	if (fd == -1)
		return (-1);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (close(fd), -1);
	if (close(fd) == -1)
		return (-1);
	return (0);
}
