/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agranjon <agranjon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:41:25 by aherve            #+#    #+#             */
/*   Updated: 2024/03/12 09:59:28 by agranjon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern int	g_signal;

char	*create_tmp_file(void)
{
	static int	nb = 0;
	int			fd;
	char		*file;

	if (nb == INT_MAX)
		return (NULL);
	file = create_file_name(nb);
	while (file != NULL && check_file(file + 2) != 0 && nb < INT_MAX)
	{
		free(file);
		file = create_file_name(nb);
		nb++;
	}
	if (file == NULL)
		return (NULL);
	if (nb == INT_MAX)
		return (free(file), NULL);
	fd = open(file + 2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		err_msg_heredoc("Impossible to write in /tmp directory\n");
		return (free(file), NULL);
	}
	nb++;
	return (close(fd), file);
}

int	write_in_file(char *delimiter, int fd)
{
	char	*line;
	int		len;

	if (!delimiter)
		return (-1);
	while (1)
	{
		line = readline(HIGH_GREEN"> "RESET);
		if (line == NULL)
			return (-1);
		if (ft_strcmp(delimiter, line) == 0)
			break ;
		len = ft_strlen(line);
		if (write(fd, line, len) != len)
			return (free(line), -1);
		free(line);
		if (write(fd, "\n", 1) != 1)
			return (-1);
	}
	free(line);
	return (0);
}

char	*here_doc(char *str)
{
	char	*delimiter;
	char	*file;
	int		fd;

	if (str == NULL)
		return (NULL);
	delimiter = get_delimiter(str);
	if (delimiter == NULL)
		return (NULL);
	file = create_tmp_file();
	if (file == NULL)
		return (free(delimiter), NULL);
	fd = open(file + 2, O_WRONLY | O_APPEND);
	if (fd == -1)
	{
		err_msg_heredoc("Temp file opening failed\n");
		return (free(delimiter), unlink(file + 2), free(file), NULL);
	}
	write(1, HIGH_GREEN"v---HEREDOC---v\n"RESET, 27);
	if (write_in_file(delimiter, fd) == -1)
		return (free(delimiter), unlink(file + 2), free(file), close(fd), NULL);
	free(delimiter);
	close(fd);
	return (file);
}

int	check_if_last_heredoc(t_token *token)
{
	t_token	*cur;

	if (token == NULL)
		return (-1);
	cur = token->next;
	while (cur != NULL)
	{
		if (is_pipe(cur->str) == 1)
			break ;
		if (is_in_redirection(cur->str) == 1)
		{
			free(token->str);
			token->str = NULL;
			return (0);
		}
		cur = cur->next;
	}
	return (1);
}

int	heredoc_redirection(t_token *token, t_cmd *cmds)
{
	int	fd_stdin;
	int	status;

	if (token == NULL || cmds == NULL)
		return (-1);
	fd_stdin = dup(STDIN_FILENO);
	signal(SIGINT, sigint_catched);
	signal(SIGQUIT, SIG_IGN);
	status = check_if_last_heredoc(token);
	if (status == -1)
		return (close(fd_stdin), -1);
	if (status == 0)
		return (close(fd_stdin), 0);
	cmds->fdin = here_doc(token->str);
	if (cmds->fdin == NULL)
	{
		if (g_signal != 0)
			dup2(fd_stdin, STDIN_FILENO);
		return (close(fd_stdin), -1);
	}
	return (close(fd_stdin), 0);
}
